#include "BoxCardFrame.h"

#include <QLabel>
#include <QHBoxLayout>
#include <Qdebug>
#include <QEvent>


BoxCardFrame::BoxCardFrame(const Card card, QWidget *parent): card(card)
{

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    this->setFixedHeight(125);
    cardDisplay = new QLabel(this);
    image = new QPixmap(card.imagePath_small);
    cardDisplay->setPixmap(image->scaled(75,225,Qt::KeepAspectRatio));
    cardDisplay->setFixedSize(75,110);

    cardDisplayLayout = new QVBoxLayout(cardDisplay);
    QLabel *cardCount = new QLabel(cardDisplay);
    cardCount->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    cardCount->setText("<b>x"+ QString::number(card.copies)  + "</b>");
    cardDisplayLayout->addWidget(cardCount);
    cardCount->setFixedSize(40,25);
    cardDisplayLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    cardDisplayLayout->setContentsMargins(0, 0, 5, 0);
    cardDisplayLayout->setSpacing(0);

    QFrame *cardInfoDisplay = new QFrame(this);
    cardInfoDisplayLayout = new QVBoxLayout(cardInfoDisplay);


    //ROW 1 NAME
    QLabel *cardName = new QLabel(card.cardInfo.cardName,cardInfoDisplay);
    cardInfoDisplayLayout->addWidget(cardName);
    cardName->setWordWrap(true);

    //ROW 2 TYPE + RACE + ARCHTYPE
    QLabel *cardAttributes = new QLabel(cardInfoDisplay);
    cardAttributes->setWordWrap(true);
    QString cardAttFormat = "[%1] [%2] [%3]";
    QString formattedAttText = cardAttFormat.arg(card.cardInfo.cardType).arg(card.cardInfo.cardRace).arg(card.cardInfo.cardArchetype);
    cardAttributes->setText(formattedAttText);

    cardInfoDisplayLayout->addWidget(cardAttributes);

    // ROW 3 LV + ATTK + DEF
    if(card.cardInfo.level){
        QLabel *cardMonsterInfo = new QLabel(cardInfoDisplay);
        QString monsterInfoFormat = "[LV: %1] [ATTK: %2] [DEF: %3]";
        QString formattedMonster = monsterInfoFormat.arg(card.cardInfo.level).arg(card.cardInfo.attack).arg(card.cardInfo.defense);
        cardMonsterInfo->setText(formattedMonster);
        cardInfoDisplayLayout->addWidget(cardMonsterInfo);
    }

    cardInfoDisplayLayout->setContentsMargins(0, 0, 0, 0);
    cardInfoDisplayLayout->setSpacing(0);
    cardInfoDisplayLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    mainLayout->addWidget(cardDisplay);
    mainLayout->addSpacing(6);
    mainLayout->addWidget(cardInfoDisplay);

    this->setObjectName("BoxCardFrame");
    this->setStyleSheet("#BoxCardFrame {background-color: rgba(255, 255, 255, 0.5);"
                                  "border: 2px solid black;}");

}

BoxCardFrame::~BoxCardFrame()
{
    clearLayout(cardDisplayLayout);
    clearLayout(cardInfoDisplayLayout);
    delete cardDisplayLayout;
    delete cardInfoDisplayLayout;
    delete image;
    cardDisplay->deleteLater();
}

void BoxCardFrame::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
        emit addToSideDeck(card.cardId);
    }
    if(event->button() == Qt::RightButton){
        emit cardAddToDeck(card.cardId);
    }
}

void BoxCardFrame::enterEvent(QEnterEvent *event) {
    // Handle hover enter event here
     emit cardClicked(card.cardId);
}

void BoxCardFrame::clearLayout(QLayout *layout) {

        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (QWidget *widget = item->widget()) {
                widget->hide(); // Optional: Hide the widget
                delete widget;
            } else if (QLayout *childLayout = item->layout()) {
                clearLayout(childLayout); // Recursively clear nested layout
                delete childLayout;
            }
            delete item;
        }

}

