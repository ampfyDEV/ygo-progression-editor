#ifndef PACKOPENINGPAGE_H
#define PACKOPENINGPAGE_H

#include "Card.h"


#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class PackOpeningPage: public QFrame
{
    Q_OBJECT
public:
    PackOpeningPage(QWidget *parent = nullptr);
    QList<Card> cardsToOpen;
    QString currentPackName;
    int maxPack;
    int currentPack;
    int currentCardsOpened = 0;
    QLabel *packNameContainer;
    QVBoxLayout *cardDisplayLayout;
    QFrame *cardDisplayContainer;
    QPushButton *nextPackButton;
    QPushButton *openAllCardsButton;
    QHBoxLayout *currentPackDisplay;


    void SetUpPacksToOpen();
    void clearLayout(QLayout *layout);

    void setupPackOpening(QList<Card> cards, QString packName);
signals:
    void BackToPackPage();

private slots:
    void LoadNextPage();
    void OpenAllCards();
private:
    void OnPackOpened();
    void loadNextPack();
};

#endif // PACKOPENINGPAGE_H
