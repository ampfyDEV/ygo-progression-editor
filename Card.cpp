#include "Card.h"

#include <QDir>

Card::Card(int cardId, QDateTime obtainDate, QString setRarity) : cardId(cardId), obtainDate(obtainDate), setRarity(setRarity){

    copies = 1;
    // QString filepath = QDir::currentPath() + "/Data/Cards/";
    // imagePath = filepath + QString::number(cardId) + ".jpg";

    QString filepath_small = QDir::currentPath() + "/Data/Cards/Small/";
    imagePath_small = filepath_small + QString::number(cardId) + ".jpg";

    obtainDate = QDateTime::currentDateTime();
}


void Card::setCardInfo(CardInfo cardInfoData)
{
    cardInfo = cardInfoData;
}


Card::Card()
{

}

Card::Card(CardInfo cardInfo, QString setRarity): cardInfo(cardInfo),setRarity(setRarity)
{
    copies = 1;
    cardId = cardInfo.cardId;

    // QString filepath = QDir::currentPath() + "/Data/Cards/";
    // imagePath = filepath + QString::number(cardId) + ".jpg";

    QString filepath_small = QDir::currentPath() + "/Data/Cards/Small/";
    imagePath_small = filepath_small + QString::number(cardId) + ".jpg";
    obtainDate = QDateTime::currentDateTime();
}
