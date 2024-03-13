#ifndef CARDBOXDISPLAY_H
#define CARDBOXDISPLAY_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWheelEvent>
#include "BoxCardFrame.h"
#include "Card.h" // Include your Card class header here

class CardBoxDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit CardBoxDisplay(QList<Card> cards,int prevIndex = 0, QWidget *parent = nullptr);

signals:
    void SelectCardDisplayClicked(int cardId);
    void AddCardToPlayerDeck(int cardId,int currIndex);
    void AddCardToSideDeck(int cardId,int currIndex);

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    int currentIndex;
    QList<Card> cards;
    QScrollArea *scrollArea;
    QWidget *cardsWidget;
    QVBoxLayout *cardsLayout;
    QList<BoxCardFrame*> cardsWidgets;
    QLabel *pageNumberDisplay;

    void displayCards(int startIndex);

private slots:
    void on_UpdateSelectedCardDisplay(int cardId);
    void on_AddCardToDeck(int cardId);
    void on_addToSideDeck(int cardId);

};

#endif // CARDBOXDISPLAY_H
