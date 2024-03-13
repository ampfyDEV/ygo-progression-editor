#include "CardInfoFrame.h"

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

CardInfoFrame::CardInfoFrame(Card card, QWidget *parent): QFrame(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setObjectName("CardInfoFrame");
    this->setStyleSheet("#CardInfoFrame {background-color: rgba(255, 255, 255, 0);"
                        "border: none;}");
    this->setAutoFillBackground(true);

    //Card Image
    QLabel *cardDisplay = new QLabel();
    cardDisplay->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QPixmap *image = new QPixmap(card.imagePath_small);
    cardDisplay->setAlignment(Qt::AlignCenter);
    //QPixmap imageScaled = image->scaled(75,225,Qt::KeepAspectRatio);
    cardDisplay->setPixmap(*image);
    //cardDisplay->setFixedSize(75,110);
    mainLayout->addWidget(cardDisplay);

    //Card Info
    QFrame *cardInfoDisplay = new QFrame(this);
    cardInfoDisplay->setFrameStyle(QFrame::StyledPanel);
    QVBoxLayout *cardInfoDisplayLayout = new QVBoxLayout(cardInfoDisplay);
    cardInfoDisplayLayout->setAlignment(Qt::AlignTop);

    //ROW 2 TYPE + RACE + ARCHTYPE
    QLabel *cardAttributes = new QLabel(cardInfoDisplay);
    QFont attributeFont;
    attributeFont.setBold(true);
    attributeFont.setPointSize(10);
    cardAttributes->setFont(attributeFont);
    QString cardAttFormat = "[%1] [%2] [%3]";
    QString formattedAttText = cardAttFormat.arg(card.cardInfo.cardType).arg(card.cardInfo.cardRace).arg(card.cardInfo.cardArchetype);
    cardAttributes->setText(formattedAttText);

    cardInfoDisplayLayout->addWidget(cardAttributes);

    // ROW 3 LV + ATTK + DEF
    if(card.cardInfo.level){
        QLabel *cardMonsterInfo = new QLabel(cardInfoDisplay);
        cardMonsterInfo->setFont(attributeFont);
        QString monsterInfoFormat = "[LV: %1] [ATTK: %2] [DEF: %3]";
        QString formattedMonster = monsterInfoFormat.arg(card.cardInfo.level).arg(card.cardInfo.attack).arg(card.cardInfo.defense);
        cardMonsterInfo->setText(formattedMonster);
        cardInfoDisplayLayout->addWidget(cardMonsterInfo);
    }

    QFont font;
    font.setPointSize(10);
    QLabel *cardDesc = new QLabel(cardInfoDisplay);
    cardDesc->setFont(font);
    cardDesc->setWordWrap(true);
    cardDesc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cardDesc->setText(card.cardInfo.cardDesc);
    cardInfoDisplayLayout->addWidget(cardDesc);
    cardDesc->setAlignment(Qt::AlignTop);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true); // Allows the scroll area to resize its widget
    scrollArea->setWidget(cardInfoDisplay);
    scrollArea->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    mainLayout->addWidget(scrollArea);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}
