#ifndef CARDINFO_H
#define CARDINFO_H

#include <QDate>
#include <QObject>
#include <QWidget>

struct CardInfoSet {
    QString setName;
    QString setCode;
    QString setRarity;
    QString setRarityCode;
};

struct CardInfo
{
public:
    CardInfo(){};
    CardInfo(int id, QString name, QString type, QString desc, QString race, QString att, QString arch, int attk, int def, int lv);

    QString cardName;
    int cardId;
    QString cardType;
    QString cardDesc;
    QString cardRace;
    QString cardAttribute;
    QString cardArchetype;
    int attack;
    int defense;
    int level;
    QList<CardInfoSet> cardSets;

};

#endif // CARDINFO_H
