#ifndef CARDREVEALCARD_H
#define CARDREVEALCARD_H

#include "Card.h"

#include <QFrame>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class CardRevealCard: public QPushButton
{
    Q_OBJECT
public:
    CardRevealCard(Card card, QWidget *parent = nullptr);
    ~CardRevealCard();
    bool isFlipped = false;
    QPixmap *cardBack;
    QPixmap *cardFront;
    QLabel *cardNameLabel;
    QString cardName;
    QLabel *cardDisplay;
    QVBoxLayout *mainLayout;

public slots:
    void on_CardReveal();

signals:
    void OpenCardClicked();
};

#endif // CARDREVEALCARD_H
