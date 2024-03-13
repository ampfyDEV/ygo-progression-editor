#include "ClickableCard.h"
#include "CurrentDeckBox.h"
#include "FlowLayout.h"

#include <QLabel>
#include <QVBoxLayout>


CurrentDeckBox::CurrentDeckBox(Deck deck, QWidget *parent): m_deck(deck), QFrame(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    QFrame *mainDeck = new QFrame(this);
    mainDeck->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    FlowLayout *mainDeckLayout = new FlowLayout(mainDeck);

    mainDeckLayout->setAlignment(Qt::AlignCenter);

    QFrame *extraDeck = new QFrame(this);
    extraDeck->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    FlowLayout *extraDeckLayout = new FlowLayout(extraDeck);

    QFrame *sideDeck = new QFrame(this);
    sideDeck->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    FlowLayout *sideDeckLayout = new FlowLayout(sideDeck);

    for(const Card& card : deck.mainDeck){
        ClickableCard *cardDisplay = new ClickableCard(card);
        connect(cardDisplay, &ClickableCard::cardClicked, this, &CurrentDeckBox::handleCardClick);
        connect(cardDisplay, &ClickableCard::removeCardFromDeck, this, &CurrentDeckBox::handleCardRmoved);
        connect(cardDisplay, &ClickableCard::addToSideDeck, this, &CurrentDeckBox::handleAddToSide);
        clickableCards.append(cardDisplay);
        //cardDisplay->setFixedSize(50,80);
        mainDeckLayout->addWidget(cardDisplay);
    }

    for(const Card& card : deck.extraDeck){
        ClickableCard *cardDisplay = new ClickableCard(card);
        connect(cardDisplay, &ClickableCard::cardClicked, this, &CurrentDeckBox::handleCardClick);
        connect(cardDisplay, &ClickableCard::removeCardFromDeck, this, &CurrentDeckBox::handleCardRmoved);
        connect(cardDisplay, &ClickableCard::addToSideDeck, this, &CurrentDeckBox::handleAddToSide);
        //cardDisplay->setFixedSize(50,80);
        clickableCards.append(cardDisplay);
        extraDeckLayout->addWidget(cardDisplay);
    }

    for(const Card& card : deck.sideDeck){
        ClickableCard *cardDisplay = new ClickableCard(card);
        connect(cardDisplay, &ClickableCard::cardClicked, this, &CurrentDeckBox::handleCardClick);
        connect(cardDisplay, &ClickableCard::removeCardFromDeck, this, &CurrentDeckBox::handleCardRmoved);
        //cardDisplay->setFixedSize(50,80);
        clickableCards.append(cardDisplay);
        sideDeckLayout->addWidget(cardDisplay);
    }

    mainLayout->addWidget(mainDeck,4);
    mainLayout->addWidget(extraDeck,1);
    mainLayout->addWidget(sideDeck,1);

}

CurrentDeckBox::~CurrentDeckBox()
{
    for(ClickableCard* card : clickableCards){
        card->deleteLater();
    }
}

void CurrentDeckBox::handleCardClick(int card)
{
    emit cardClicked(card);
}

void CurrentDeckBox::handleCardRmoved(int card)
{
    emit cardRemoved(card);
}

void CurrentDeckBox::handleAddToSide(int card)
{
    emit addToSideDeck(card);
}
