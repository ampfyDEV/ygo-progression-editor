#ifndef CARD_H
#define CARD_H

#include "CardInfo.h"


struct Card
{
public:
    Card();
    Card(CardInfo cardInfo,QString setRarity);
    Card(int cardId, QDateTime obtainDate, QString setRarity);

    int cardId;
    int copies;
    QString imagePath_small;
    QDateTime obtainDate;
    QString setRarity;
    CardInfo cardInfo;

    void setCardInfo(CardInfo cardInfoData);

    bool operator==(const Card& other) const {
        return (this->cardId == other.cardId);
    }
};

#endif // CARD_H
