#include "CardRevealCard.h"

#include <QDir>
#include <QVBoxLayout>
#include <QLabel>

CardRevealCard::CardRevealCard(Card card,QWidget *parent ): QPushButton(parent) {
    cardName = card.setRarity + " " +  card.cardInfo.cardName;
    this->setObjectName("CardRevealCard");
    this->setStyleSheet("#CardRevealCard {background-color: rgba(255, 255, 255, 0);"
                        "background-color: rgba(255, 255, 255, 0);}"
                        "#CardRevealCard:hover { background-color: lightblue; }"
                        "#CardRevealCard:pressed { background-color: rgba(173, 216, 230, 0.5); }");
    this->setAutoFillBackground(true);
    this->setMaximumSize(300,375);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QString filepath = QDir::currentPath() + "/Data/Cards/";
    QString imagePath = card.imagePath_small;
    QString backPath = filepath + "cardback.png";

    cardDisplay = new QLabel(this);
    cardDisplay->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    cardBack = new QPixmap(backPath);
    cardFront = new QPixmap(imagePath);
    cardDisplay->setPixmap(cardBack->scaled(190,300,Qt::KeepAspectRatio));
    cardDisplay->setFixedHeight(300);
    cardDisplay->setAlignment(Qt::AlignCenter);

    cardNameLabel = new QLabel(this);
    cardNameLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    cardNameLabel->setWordWrap(true);
    cardNameLabel ->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    cardNameLabel->setFont(font);

    mainLayout->addWidget(cardDisplay);
    mainLayout->addWidget(cardNameLabel);
    mainLayout->setAlignment(Qt::AlignCenter);

    connect(this, &QPushButton::clicked,this,&CardRevealCard::on_CardReveal);
}

CardRevealCard::~CardRevealCard()
{
    delete cardBack;
    delete cardFront;
}

void CardRevealCard::on_CardReveal()
{
    cardDisplay->setPixmap(cardFront->scaled(190,300,Qt::KeepAspectRatio));
    cardNameLabel->setText(cardName);
    emit OpenCardClicked();
}
