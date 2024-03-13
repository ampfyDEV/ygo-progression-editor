#include "CardPack.h"

#include <QDir>

CardPack::CardPack(QString setName, QString setCode, int cardsPerPack, QDate releaseDate,QList<Card> packCards): cards(packCards),
    setCode(setCode),setName(setName), cardsPerPack(cardsPerPack), releaseDate(releaseDate)
{
    imagePath = QDir::currentPath() + "/Data/Sets/" + setCode + ".jpg";
    loadCards(cards);
}

void CardPack::loadCards(QList<Card> cards)
{
    for(const auto& card: cards){
        if(card.setRarity != "(C)" && card.setRarity != "(R)"){
            m_prizeCards.append(card);
        }
        else m_cards.append(card);
    }
}

