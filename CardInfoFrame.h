#ifndef CARDINFOFRAME_H
#define CARDINFOFRAME_H

#include "Card.h"

#include <QFrame>
#include <QObject>
#include <QWidget>

class CardInfoFrame: public QFrame
{
    Q_OBJECT
public:
    CardInfoFrame(Card card, QWidget *parent = nullptr);
};

#endif // CARDINFOFRAME_H
