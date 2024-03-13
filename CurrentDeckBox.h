#ifndef CURRENTDECKBOX_H
#define CURRENTDECKBOX_H

#include "ClickableCard.h"
#include "playerdata.h"

#include <QFrame>
#include <QObject>
#include <QWidget>

class CurrentDeckBox: public QFrame
{
    Q_OBJECT
public:
    CurrentDeckBox(Deck deck, QWidget *parent);
    CurrentDeckBox(QWidget *parent);
    ~CurrentDeckBox();
    Deck m_deck;
    QList<ClickableCard*> clickableCards;

signals:
    void cardClicked(int card);
    void cardRemoved(int card);
    void addToSideDeck(int card);

private slots:
    void handleCardClick(int card);
    void handleCardRmoved(int card);
    void handleAddToSide(int card);
};

#endif // CURRENTDECKBOX_H
