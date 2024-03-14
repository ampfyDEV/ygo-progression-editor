#include "CardBoxDisplay.h"
#include <QScrollBar>

CardBoxDisplay::CardBoxDisplay(QList<Card> cards,int prevIndex, QWidget *parent)
    : QWidget(parent), cards(cards), currentIndex(prevIndex)
{
    this->setStyleSheet("background-color: rgba(255, 255, 255, 0); border: none;");
    scrollArea = new QScrollArea(this);
    cardsWidget = new QWidget(scrollArea);
    cardsLayout = new QVBoxLayout(cardsWidget);
    cardsLayout->setAlignment(Qt::AlignTop);
    cardsLayout->setSpacing(10); // Adjust spacing between cards

    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(cardsWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);
    currentIndex = qBound(0, currentIndex, cards.size() - 1);
    displayCards(currentIndex); // Display the first batch of cards
    pageNumberDisplay = new QLabel(this);
    pageNumberDisplay->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    pageNumberDisplay->setFont(font);
    pageNumberDisplay->setText(QString::number(currentIndex + 1) + " / " + QString::number(cards.size() - 1));
    layout->addWidget(pageNumberDisplay);
}

void CardBoxDisplay::wheelEvent(QWheelEvent *event) {
    // Determine the number of steps the user scrolled
    int numSteps = -event->angleDelta().y() / 120;

    // Update the currentIndex based on the scroll direction
    currentIndex += numSteps;

    // Ensure the currentIndex stays within valid bounds
    currentIndex = qBound(0, currentIndex, cards.size() - 1);
    pageNumberDisplay->setText(QString::number(currentIndex + 1) + " / " + QString::number(cards.size() - 1));

    // Calculate the index of the first card to display based on currentIndex
    int startIndex = currentIndex;

    // Display the cards starting from the calculated index
    displayCards(startIndex);

    // Call the base class implementation of wheelEvent
    QWidget::wheelEvent(event);
}

void CardBoxDisplay::displayCards(int startIndex) {
    cardsWidgets.clear();

    int endIndex = qMin(startIndex + 5, cards.size());
    for (int i = startIndex; i < endIndex; ++i) {
        BoxCardFrame *cardWidget = new BoxCardFrame(cards[i], this);
        connect(cardWidget,&BoxCardFrame::cardClicked,this,&CardBoxDisplay::on_UpdateSelectedCardDisplay);
        connect(cardWidget,&BoxCardFrame::cardAddToDeck,this,&CardBoxDisplay::on_AddCardToDeck);
        connect(cardWidget,&BoxCardFrame::addToSideDeck,this,&CardBoxDisplay::on_addToSideDeck);
        cardsWidgets.append(cardWidget);
        cardsLayout->addWidget(cardWidget);
    }
}

void CardBoxDisplay::on_UpdateSelectedCardDisplay(int cardId)
{
    emit SelectCardDisplayClicked(cardId);
}

void CardBoxDisplay::on_AddCardToDeck(int cardId)
{
    emit AddCardToPlayerDeck(cardId, currentIndex);
}

void CardBoxDisplay::on_addToSideDeck(int cardId)
{
    emit AddCardToSideDeck(cardId, currentIndex);
}


