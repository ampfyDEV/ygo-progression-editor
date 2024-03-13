#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include "Card.h"

#include <QString>
#include <QStringList>
#include <QJsonObject>

struct Deck {
public:
    QString deckName;
    QList<Card> mainDeck;
    QList<Card> extraDeck;
    QList<Card> sideDeck;
};

struct PlayerData
{
public:
    QString fileName;
    QMap<int,Card> cardBox;
    QMap<QString,Deck> decks;
    QString selectedDeck;

    PlayerData();
    bool Load(QString& filepath);
    bool Save(QString& filepath);
    bool Create(QString& filepath);
    QJsonObject toJson();
    void fromJson(QJsonObject& obj);

};

#endif // PLAYERDATA_H
