#ifndef CLICKABLECARD_H
#define CLICKABLECARD_H

#include "Card.h"

#include <QLabel>
#include <QObject>
#include <QWidget>

class ClickableCard: public QLabel
{
    Q_OBJECT
public:
    ClickableCard(Card card);
    ~ClickableCard();
    QPixmap *image;
    Card card;

protected:
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent *event);

signals:
    void cardClicked(int card);
    void removeCardFromDeck(int card);
    void addToSideDeck(int card);
};

#endif // CLICKABLECARD_H
