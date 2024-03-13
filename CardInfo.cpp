#include "CardInfo.h"

#include <QDir>


CardInfo::CardInfo(int id, QString name, QString type, QString desc, QString race, QString att, QString arch, int attk, int def, int lv): cardId(id),cardName(name),
    cardType(type),cardDesc(desc),cardRace(race),cardAttribute(att),cardArchetype(arch),attack(attk),defense(def),level(lv)
{
}
