#ifndef CARDPACKBUTTON_H
#define CARDPACKBUTTON_H

#include "Card.h"
#include "CardPack.h"
#include "qrandom.h"

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QDateTime>
#include <QPushButton>

class CardPackButton: public QPushButton
{
    Q_OBJECT
public:
    explicit CardPackButton(CardPack cardPack, QWidget *parent = nullptr);
    CardPack cardPack;
    QString setName;
    QString setCode;
    int cardsPerPack;
    int packsToPull = 1;
    QDate releaseDate;
    void setPullAmount(int i);
    QList<QString> structureDeckNames = {"Deck","Decks","Decks:","Deck"};

private:
    void LoadCards(QList<Card> cards);
    QList<Card> m_cards;
    QList<Card> m_prizeCards;
    QRandomGenerator randomGenerator;
    bool isStructureDeck();

private slots:
    void on_OpenPacks();

signals:
    void OpenPacksClicked(QList<Card> selectedCards, QString setName);
};

#endif // CARDPACKBUTTON_H
