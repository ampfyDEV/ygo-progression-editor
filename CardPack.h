#ifndef CARDPACK_H
#define CARDPACK_H

#include "Card.h"

#include <QJsonObject>


struct CardPack
{

public:
    CardPack(QString setName, QString setCode, int cardsPerPack, QDate releaseDate,QList<Card> packCards);
    QString setName;
    QString setCode;
    int cardsPerPack;
    int packsToPull = 1;
    QDate releaseDate;
    void setPullAmount(int i);
    QString imagePath;
    QList<Card> cards;
    QList<Card> m_cards;
    QList<Card> m_prizeCards;

private:

    void loadCards(QList<Card> cards);
};
#endif // CARDPACK_H
