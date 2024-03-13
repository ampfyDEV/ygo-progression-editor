#ifndef PACKSMENUPAGE_H
#define PACKSMENUPAGE_H

#include "Card.h"
#include "CardInfo.h"
#include "CardPackButton.h"
#include "FlowLayout.h"
#include "playerdata.h"

#include <QComboBox>
#include <QFrame>
#include <QObject>
#include <QWidget>

enum class PackSortOptions {
    Name,
    ReleaseDate,
};

enum class PackFilterOptions{
    ALL,
    Packs,
    StructureDeck,
};

class PacksMenuPage: public QFrame
{
    Q_OBJECT
public:
    PacksMenuPage(PlayerData &playerData,QList<CardInfo> &m_cards, QWidget *parent = nullptr);
    void on_OpenPacks();

signals:
    void SavePlayerCards();
    void BackToMainPage();
    void MoveToPackOpeningPage(QList<Card>, QString);

private slots:
    void on_OpenCardPacks(QList<Card> selectedCards, QString setName);
    void on_PackAmountChange();

    void on_SortSelected(int index);
    void on_FilterSelected(int index);

private:
    PlayerData &m_playerData;
    QList<CardInfo> &m_cards;
    QComboBox *packAmount;
    QList<Card> loadCardsIntoPack(QString setCode);
    QList<CardPack> cardPacks;
    QList<CardPackButton*> cardPackButtons;
    void UpdateCardPackDisplay();
    void clearLayout(QLayout *layout);


    FlowLayout *packsContainerLayout;
    PackSortOptions currentSortOption;
    QList<CardPack> SortDisplayList(QList<CardPack> displayList);
    QString SortToString(PackSortOptions option);

    QList<QString> structureDeckNames = {"Deck","Decks","Decks:","Deck"};
    PackFilterOptions currentFilterOption;
    QList<CardPack> FilterPackList(QList<CardPack> displayList);
    QString FilterToString(PackFilterOptions option);

};



#endif // PACKSMENUPAGE_H
