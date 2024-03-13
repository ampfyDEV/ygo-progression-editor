#ifndef DECK_H
#define DECK_H

#include "Card.h"


struct Deck
{
public:
    Deck();
    QList<Card> mainDeck;
    QList<Card> extraDeck;
    QList<Card> sideDeck;
};

#endif // DECK_H
