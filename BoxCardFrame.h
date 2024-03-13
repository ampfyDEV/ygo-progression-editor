#ifndef BOXCARDFRAME_H
#define BOXCARDFRAME_H

#include "Card.h"

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QEnterEvent>
#include <QVBoxLayout>
#include <QLabel>

class BoxCardFrame : public QFrame
{
    Q_OBJECT
public:
    BoxCardFrame(const Card card, QWidget *parent = nullptr);
    ~BoxCardFrame();
    Card card;

    QVBoxLayout *cardDisplayLayout;
    QVBoxLayout *cardInfoDisplayLayout;
    QPixmap *image;
    QLabel *cardDisplay;

    void clearLayout(QLayout *layout);
protected:
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent *event);

signals:
    void cardClicked(int card);
    void cardAddToDeck(int card);
    void addToSideDeck(int card);
};

#endif // BOXCARDFRAME_H
