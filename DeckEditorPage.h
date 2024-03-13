#ifndef DECKEDITORPAGE_H
#define DECKEDITORPAGE_H

#include "BoxCardFrame.h"
#include "playerdata.h"

#include <QComboBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QObject>
#include <QPushButton>
#include <QWidget>

enum class SortOptions {
    Name,
    ObtainDate,
    Level,
    Type,
    Archetype,
};

enum class FilterOptions {
    Default,
    Monster, //just get all with type that ends with "Monster"
    Spell,
    Trap,
    Pendulum,
    Fusion, //begins with [extra deck name]
    Synchro,
    XYZ,
    Link

};

class DeckEditorPage: public QFrame
{
    Q_OBJECT
public:
    DeckEditorPage(QMap<int,Card> &cardBox,QMap<QString,Deck> &deckBox,QString &selectedDeck, QWidget *parent = nullptr);
    void UpdateCardBoxDisplay();
    void UpdateDeckBoxDisplay();
    void UpdateSelectedCardDisplay(int cardId);
    void AddCardToDeck(int card, int index);
    void LoadCurrentDeck();


signals:
    void BackToMainPage();
    void SavePlayerDeckBox();

private slots:
    void onDeckSelected(int index);
    void onSortSelected(int index);
    void onFilterSelected(int index);
    void onSearchUpdate(QString search);
    void onAddToSideDeck(int cardId, int index);

private:
    QMap<int,Card> &m_cardBox;
    QMap<QString,Deck> &m_deckBox;
    QString &selectedDeck;
    Deck currentDeck;
    QString deckExportFilePath;

    QPushButton *saveButton;
    QVBoxLayout *cardBoxDisplayLayout;
    QVBoxLayout *cardInfoDisplayLayout;
    QVBoxLayout *deckInfoDisplayLayout;
    QLabel *currentDeckName;
    QComboBox *allPlayerDecks;
    QLabel *currentMainCount;
    QLabel *currentExtraCount;
    QLabel *currentSideCount;

    QList<BoxCardFrame*> cardBoxFrames;
    void clearLayout(QLayout *layout);
    void SaveDeck();
    void RemoveCardFromCardBox(int cardId);
    void RemoveCardFromDeckBox(int cardId);
    void ClearOutDeck();
    bool isMainDeckMon(Card card);
    bool isCardLimitReached(Card card);
    void CreateNewDeck();
    void ExportDeck();


    SortOptions currentSortOption;
    QList<Card> SortDisplayList(QList<Card> displayList);
    QString SortToString(SortOptions option);

    FilterOptions currentFilterOption;
    QList<Card> FilterDisplayList(QList<Card> displayList);
    QString FilterToString(FilterOptions option);

    QString currentSearchOption;
    QList<Card> SearchDisplayList(QList<Card> displayList);

    QList<Card> GetActiveCardsOnly(QList<Card> displayList);

    int currentIndex;

};

#endif // DECKEDITORPAGE_H
