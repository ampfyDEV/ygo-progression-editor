#include "CardPackButton.h"
#include <QDateTime>
#include <QDir>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QDebug>
#include <QRandomGenerator>


CardPackButton::CardPackButton(CardPack cardPack,QWidget *parent): cardPack(cardPack), QPushButton(parent)
{
    randomGenerator.seed(QDateTime::currentSecsSinceEpoch());
    this->setFixedSize(150,250);
    setName = cardPack.setName;
    setCode = cardPack.setCode;
    cardsPerPack = cardPack.cardsPerPack;
    releaseDate = cardPack.releaseDate;
    QString imagePath = cardPack.imagePath;
    m_cards = cardPack.m_cards;
    m_prizeCards = cardPack.m_prizeCards;
    QVBoxLayout *layout = new QVBoxLayout(this);
    QString text = "[ " + QString::number(releaseDate.year()) + " ] " +setName;
    QLabel *iconLabel = new QLabel(this);
    QPixmap pixmap(imagePath);

    QLabel *textLabel = new QLabel(text, this);
    iconLabel->setPixmap(pixmap); // Adjust icon size as needed
    iconLabel->setMaximumSize(150,171);
    iconLabel->setAlignment(Qt::AlignCenter);


    textLabel->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    textLabel->setWordWrap(true);
    QFont font;
    font.setBold(true);
    font.setPointSize(10);
    textLabel->setFont(font);
    layout->addWidget(iconLabel);
    layout->addWidget(textLabel);
    layout->setAlignment(Qt::AlignJustify);
    textLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    this->setStyleSheet("QPushButton { border: 1px solid grey; "
                        "background-color: rgba(255, 255, 255, 0.5);}"
                        "QPushButton:hover { background-color: lightblue; }"
                        "QPushButton:pressed { background-color: rgba(173, 216, 230, 0.5); }");

    connect(this,&CardPackButton::clicked,this,&CardPackButton::on_OpenPacks);
}

void CardPackButton::setPullAmount(int i)
{
    packsToPull = i;
}

bool CardPackButton::isStructureDeck()
{
    for(const QString &name : structureDeckNames){
        if(setName.contains(name)) return true;
    }
    return false;
}

void CardPackButton::on_OpenPacks()
{
    QList<Card> selectedCards;

    if(isStructureDeck()){
        for(Card &card : m_cards){
            Card newCard = card;
            newCard.obtainDate = QDateTime::currentDateTime();
            selectedCards.append(newCard);
        }
        for(Card &card : m_prizeCards){
            Card newCard = card;
            newCard.obtainDate = QDateTime::currentDateTime();
            selectedCards.append(newCard);
        }
    }
    else {

        int luckyNumber = 16;
        for(size_t t = 0; t < packsToPull; t++){
            // Keep selecting random cards until the desired number is reached
            for (size_t i = 0; i < 6; i++) {
                int chanceNumber = randomGenerator.bounded(101);
                if(!m_prizeCards.isEmpty() && (luckyNumber >= chanceNumber || m_cards.isEmpty())){

                    Card newCard = m_prizeCards[randomGenerator.bounded(m_prizeCards.size())];
                    newCard.obtainDate = QDateTime::currentDateTime();
                    selectedCards.append(newCard);

                }
                else{
                    int randomIndex = randomGenerator.bounded(m_cards.size()); // Generate a random index
                    Card newCard = m_cards[randomIndex]; // Get the card at the random index
                    newCard.obtainDate = QDateTime::currentDateTime();
                    selectedCards.append(newCard);
                }
            }

            //ADD atleast 1 prize card if possible
            if(!m_prizeCards.isEmpty()){
                Card newCard = m_prizeCards[randomGenerator.bounded(m_prizeCards.size())];
                newCard.obtainDate = QDateTime::currentDateTime();
                selectedCards.append(newCard);
            }
            else {
                int randomIndex = randomGenerator.bounded(m_cards.size()); // Generate a random index
                Card newCard = m_cards[randomIndex]; // Get the card at the random index
                newCard.obtainDate = QDateTime::currentDateTime();
                selectedCards.append(newCard);
            }
        }
    }

    emit CardPackButton::OpenPacksClicked(selectedCards,setName);
}





