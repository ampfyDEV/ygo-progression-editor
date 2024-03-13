#include "BoxCardFrame.h"
#include "CardBoxDisplay.h"
#include "CardInfoFrame.h"
#include "CurrentDeckBox.h"
#include "DeckEditorPage.h"

#include <QDir>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QInputDialog>
#include <QFileDialog>


DeckEditorPage:: DeckEditorPage( QMap<int,Card> &cardBox, QMap<QString,Deck> &deckBox,QString &selectedDeck, QWidget *parent): QFrame(parent), m_cardBox(cardBox), m_deckBox(deckBox), selectedDeck(selectedDeck)
{

    this->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    deckExportFilePath = QDir::currentPath() + "/Data/DeckBox";
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setObjectName("DeckEditorPage");
    /* USE RESOURCE SYSTEM FOR THIS LATER*/
    QString bgPath = QDir::currentPath() + "/Textures/bg.jpg";
    QString bgStyleSheet =QString( "#DeckEditorPage {"
                                   "background-image: url(%1);"
                                   "background-repeat: no-repeat;"
                                   "background-position: center center;}").arg(bgPath);
    this->setStyleSheet(bgStyleSheet);

    QFrame *deckEditorPageContainer = new QFrame(this);
    deckEditorPageContainer->setObjectName("deckEditorPageContainer");
    deckEditorPageContainer->setFrameStyle(QFrame::Box);
    deckEditorPageContainer->setMinimumSize(1600,900);
    deckEditorPageContainer->setMaximumSize(1920,1080);
    deckEditorPageContainer->setLineWidth(3);
    deckEditorPageContainer->setStyleSheet("#deckEditorPageContainer {background-color: rgba(255, 255, 255, 0);"
                                  "border: none;}");
    deckEditorPageContainer->setAutoFillBackground(true);
    mainLayout->addWidget(deckEditorPageContainer);
    mainLayout->setAlignment(Qt::AlignCenter);




    //HEADER INFO
    QFrame *headerBarContainer = new QFrame(this);
    headerBarContainer->setObjectName("headerBarContainer");
    headerBarContainer->setStyleSheet("#headerBarContainer {background-color: rgba(255, 255, 255, 0.5);"
                                      "border: 2px solid black;}");
    headerBarContainer->setAutoFillBackground(true);
    headerBarContainer->setFixedHeight(110);
    headerBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *headerLayout = new QHBoxLayout(headerBarContainer);
    QString backPath = QDir::currentPath() + "/Textures/backButton.png";
    QPushButton *backButton = new QPushButton(headerBarContainer);
    backButton->setIcon(QIcon(backPath));
    backButton->setFixedWidth(100);
    backButton->setIconSize(QSize(75,75));
    backButton->setStyleSheet("QPushButton {"
                              "background-color: rgba(255, 255, 255, 0);}"
                              "QPushButton:hover { background-color: 2px solid lightblue; }"
                              "QPushButton:pressed { background-color: rgba(173, 216, 230, 0); }");
    connect(backButton,&QPushButton::clicked,this,&DeckEditorPage::BackToMainPage);

    QFrame *backButtonContainer = new QFrame(headerBarContainer);
    backButtonContainer->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QHBoxLayout *backButtonLayout = new QHBoxLayout(backButtonContainer);
    backButtonLayout->addWidget(backButton);
    backButtonLayout->setAlignment(Qt::AlignLeft);

    QFrame *myDeckInfoContainer = new QFrame(headerBarContainer);
    QVBoxLayout *myDeckInfoContainerLayout = new QVBoxLayout(myDeckInfoContainer);
    myDeckInfoContainerLayout->setContentsMargins(0, 0, 0, 0);
    myDeckInfoContainerLayout->setSpacing(0);
    QFrame *myDeckNameContainer = new QFrame(myDeckInfoContainer);


    QLabel *myDeckNameLabel = new QLabel("My Decks: ");
    allPlayerDecks = new QComboBox(headerBarContainer);
    allPlayerDecks->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    QHBoxLayout *myDeckNameContainerLayout = new QHBoxLayout(myDeckNameContainer);
    myDeckNameContainerLayout->setContentsMargins(5, 5, 5, 5);
    myDeckNameContainerLayout->setSpacing(6);
    myDeckNameContainerLayout->addWidget(myDeckNameLabel);
    myDeckNameContainerLayout->addWidget(allPlayerDecks);



    QFrame *deckNameContainer = new QFrame(myDeckInfoContainer);
    QLabel *deckNameLabel = new QLabel("Current Deck: ");
    currentDeckName = new QLabel(deckNameContainer);
    currentDeckName->setFixedWidth(100);
    currentDeckName->setMaximumHeight(25);
    currentDeckName->setObjectName("currentDeckName");
    currentDeckName->setStyleSheet("#currentDeckName {background-color: rgba(255, 255, 255, 0);"
                                   "border: 2px solid black;}");
    QHBoxLayout *deckNameContainerLayout = new QHBoxLayout(deckNameContainer);
    deckNameContainerLayout->setContentsMargins(5, 5, 5, 5);
    deckNameContainerLayout->setSpacing(6);
    deckNameContainerLayout->setAlignment(Qt::AlignLeft);
    deckNameContainerLayout->addWidget(deckNameLabel);
    deckNameContainerLayout->addWidget(currentDeckName);

    myDeckInfoContainerLayout->addWidget(myDeckNameContainer);
    myDeckInfoContainerLayout->addWidget(deckNameContainer);


    QFrame *deckInfoContainer = new QFrame(headerBarContainer);
    QVBoxLayout *deckInfoContainerLayout =new QVBoxLayout(deckInfoContainer);
    deckInfoContainerLayout->setContentsMargins(0, 0, 0, 0);
    deckInfoContainerLayout->setSpacing(0);


    QFrame *mainCountContainer = new QFrame(deckInfoContainer);
    QLabel *mainCountLabel = new QLabel("Main Deck: ");
    currentMainCount = new QLabel(QString::number(currentDeck.mainDeck.count()));
    QHBoxLayout *mainCountLayout = new QHBoxLayout(mainCountContainer);
    mainCountLayout->addWidget(mainCountLabel);
    mainCountLayout->addWidget(currentMainCount);
    mainCountLayout->setContentsMargins(5, 5, 5, 5);
    mainCountLayout->setSpacing(6);
    mainCountLayout->setAlignment(Qt::AlignRight);

    QFrame *extraCountContainer = new QFrame(deckInfoContainer);
    QLabel *extraCountLabel = new QLabel("Extra Deck: ");
    currentExtraCount = new QLabel(QString::number(currentDeck.extraDeck.count()));
    QHBoxLayout *extraCountLayout = new QHBoxLayout(extraCountContainer);
    extraCountLayout->addWidget(extraCountLabel);
    extraCountLayout->addWidget(currentExtraCount);
    extraCountLayout->setContentsMargins(5, 5, 5, 5);
    extraCountLayout->setSpacing(6);
    extraCountLayout->setAlignment(Qt::AlignRight);

    QFrame *sideCountContainer = new QFrame(deckInfoContainer);
    QLabel *sideCountLabel = new QLabel("Side Deck: ");
    currentSideCount = new QLabel(QString::number(currentDeck.sideDeck.count()));
    QHBoxLayout *sideCountLayout = new QHBoxLayout(sideCountContainer);
    sideCountLayout->addWidget(sideCountLabel);
    sideCountLayout->addWidget(currentSideCount);
    sideCountLayout->setContentsMargins(5, 5, 5, 5);
    sideCountLayout->setSpacing(6);
    sideCountLayout->setAlignment(Qt::AlignRight);

    deckInfoContainerLayout->addWidget(mainCountContainer);
    deckInfoContainerLayout->addWidget(extraCountContainer);
    deckInfoContainerLayout->addWidget(sideCountContainer);

    saveButton = new QPushButton("SAVE",this);
    saveButton->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    connect(saveButton,&QPushButton::clicked,this,&DeckEditorPage::SaveDeck);

    QPushButton *createButton = new QPushButton("Create",this);
    createButton->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    headerLayout->addWidget(createButton);
    connect(createButton,&QPushButton::clicked,this,&DeckEditorPage::CreateNewDeck);

    QPushButton *exportButton = new QPushButton("Export",this);
    exportButton->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    connect(exportButton,&QPushButton::clicked,this,&DeckEditorPage::ExportDeck);

    QFrame *deckOptionsContainer = new QFrame(headerBarContainer);
    QHBoxLayout *deckOptionsContainerLayout = new QHBoxLayout(deckOptionsContainer);
    deckOptionsContainer->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    deckOptionsContainerLayout->addWidget(myDeckInfoContainer);
    deckOptionsContainerLayout->addWidget(deckInfoContainer);
    deckOptionsContainerLayout->addWidget(createButton);
    deckOptionsContainerLayout->addWidget(saveButton);
    deckOptionsContainerLayout->addWidget(exportButton);


     // SORTING
    QFrame *sortCards = new QFrame(headerBarContainer);
    sortCards->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    QHBoxLayout *sortCardLayout = new QHBoxLayout(sortCards);
    QLabel *sortingLabel = new QLabel("Sort by:",sortCards);
    sortingLabel->setFixedWidth(50);
    QComboBox *sortingBox = new QComboBox(sortCards);
    for (int i = static_cast<int>(SortOptions::Name); i <= static_cast<int>(SortOptions::Archetype); ++i) {
        sortingBox->addItem(SortToString(static_cast<SortOptions>(i))); // Convert enum value to string
    }
    connect(sortingBox, QOverload<int>::of(&QComboBox::activated), this, &DeckEditorPage::onSortSelected);
    sortCardLayout->addWidget(sortingLabel);
    sortCardLayout->addWidget(sortingBox);
    sortCardLayout->setContentsMargins(5, 5, 5, 5);
    sortCardLayout->setSpacing(6);


    //FILTERING
    QFrame *filterCards = new QFrame(headerBarContainer);
    filterCards->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    QHBoxLayout *filterCarddLayout = new QHBoxLayout(filterCards);
    QLabel *filterLabel = new QLabel("Filter by:",filterCards);
    filterLabel->setFixedWidth(50);
    QComboBox *filterBox = new QComboBox(filterCards);
    for (int i = static_cast<int>(FilterOptions::Default); i <= static_cast<int>(FilterOptions::Link); ++i) {
        filterBox->addItem(FilterToString(static_cast<FilterOptions>(i))); // Convert enum value to string
    }
    connect(filterBox, QOverload<int>::of(&QComboBox::activated), this, &DeckEditorPage::onFilterSelected);
    filterCarddLayout->addWidget(filterLabel);
    filterCarddLayout->addWidget(filterBox);

    filterCarddLayout->setContentsMargins(5, 5, 5, 5);
    filterCarddLayout->setSpacing(6);


    //SEARCHING
    QFrame *searchCards = new QFrame(headerBarContainer);
    searchCards->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    QHBoxLayout *searchCardLayout = new QHBoxLayout(searchCards);
    QLabel *searchlabel = new QLabel("Search: ",searchCards);
    searchlabel->setFixedWidth(50);
    QLineEdit *searchText = new QLineEdit(searchCards);
    connect(searchText,&QLineEdit::textChanged,this,&DeckEditorPage::onSearchUpdate);
    searchCardLayout->addWidget(searchlabel);
    searchCardLayout->addWidget(searchText);
    searchCardLayout->setContentsMargins(5, 5, 5, 5);
    searchCardLayout->setSpacing(6);

    QFrame *editCardBoxContainer = new QFrame(headerBarContainer);
    editCardBoxContainer->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QVBoxLayout *editCardBoxContainerLayout = new QVBoxLayout(editCardBoxContainer);
    editCardBoxContainerLayout->addWidget(sortCards);
    editCardBoxContainerLayout->addWidget(filterCards);
    editCardBoxContainerLayout->addWidget(searchCards);
    editCardBoxContainerLayout->setContentsMargins(0, 0, 0, 0);
    editCardBoxContainerLayout->setSpacing(0);


    headerLayout->addWidget(backButtonContainer,1);
    headerLayout->addWidget(deckOptionsContainer,2);
    headerLayout->addWidget(editCardBoxContainer,1);


    //DECK EDITOR INFO
    QVBoxLayout *deckEditorContainerPageLayout = new QVBoxLayout(deckEditorPageContainer);
    deckEditorContainerPageLayout->addWidget(headerBarContainer);

    QFrame *deckEditorContainer = new QFrame(this);
    deckEditorContainer->setObjectName("deckEditorContainer");
    deckEditorContainer->setStyleSheet("#deckEditorContainer {background-color: rgba(255, 255, 255, 0);"
                                   "border: 2px solid black;}");
    deckEditorContainer->setAutoFillBackground(true);

    QHBoxLayout *deckEditorCotainerLayout = new QHBoxLayout(deckEditorContainer);
    deckEditorContainerPageLayout->addWidget(deckEditorContainer);

    //Displays Card into on Click
    QFrame *cardInfoDisplay = new QFrame(this);
    cardInfoDisplay->setObjectName("cardInfoDisplay");
    cardInfoDisplay->setStyleSheet("#cardInfoDisplay {background-color: rgba(255, 255, 255, 0);"
                                           "border: 2px solid black;}");
    cardInfoDisplay->setAutoFillBackground(true);
    cardInfoDisplayLayout = new QVBoxLayout(cardInfoDisplay);
    cardInfoDisplayLayout->setAlignment(Qt::AlignCenter);

    //Displays Player Deck
    QFrame *deckInfoDisplay = new QFrame(this);
    deckInfoDisplay->setObjectName("deckInfoDisplay");
    deckInfoDisplay->setStyleSheet("#deckInfoDisplay {background-color: rgba(255, 255, 255, 0);"
                                   "border: 2px solid black;}");
    deckInfoDisplay->setAutoFillBackground(true);

    deckInfoDisplayLayout = new QVBoxLayout(deckInfoDisplay);

    //Displays All of Player's Current Cards
    QFrame *cardBoxDisplay = new QFrame(this);
    cardBoxDisplay->setObjectName("cardBoxDisplay");
    cardBoxDisplay->setStyleSheet("#cardBoxDisplay {background-color: rgba(255, 255, 255, 0);"
                                   "border: 2px solid black;}");
    cardBoxDisplay->setAutoFillBackground(true);
    cardBoxDisplayLayout = new QVBoxLayout(cardBoxDisplay);

    // QScrollArea *scrollArea = new QScrollArea;
    // scrollArea->setWidgetResizable(true); // Allows the scroll area to resize its widget
    // scrollArea->setWidget(cardBoxDisplay);
    // scrollArea->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    deckEditorCotainerLayout->addWidget(cardInfoDisplay,1);
    deckEditorCotainerLayout->addWidget(deckInfoDisplay,2);
    deckEditorCotainerLayout->addWidget(cardBoxDisplay,1);

}

void DeckEditorPage::UpdateCardBoxDisplay()
{

    clearLayout(cardBoxDisplayLayout);
    //if(m_cardBox.isEmpty()) return;

    QList<Card> displayCardList = m_cardBox.values();
    displayCardList = GetActiveCardsOnly(displayCardList);
     if(!currentSearchOption.isEmpty()) displayCardList = SearchDisplayList(displayCardList);
    displayCardList = FilterDisplayList(displayCardList);
    displayCardList = SortDisplayList(displayCardList);

    CardBoxDisplay *cardDisplayBox = new CardBoxDisplay(displayCardList, currentIndex,this);
    connect(cardDisplayBox,&CardBoxDisplay::SelectCardDisplayClicked,this,&DeckEditorPage::UpdateSelectedCardDisplay);
    connect(cardDisplayBox,&CardBoxDisplay::AddCardToPlayerDeck,this,&DeckEditorPage::AddCardToDeck);
    connect(cardDisplayBox,&CardBoxDisplay::AddCardToSideDeck,this,&DeckEditorPage::onAddToSideDeck);
    cardBoxDisplayLayout->addWidget(cardDisplayBox);


}

void DeckEditorPage::UpdateDeckBoxDisplay()
{
    //if(currentDeck.deckName.isEmpty()) return;
    clearLayout(deckInfoDisplayLayout);
    CurrentDeckBox *curr_deck = new CurrentDeckBox(currentDeck,this);
    connect(curr_deck, &CurrentDeckBox::cardClicked, this, &DeckEditorPage::UpdateSelectedCardDisplay);
    connect(curr_deck, &CurrentDeckBox::cardRemoved, this, &DeckEditorPage::RemoveCardFromDeckBox);
    deckInfoDisplayLayout->addWidget(curr_deck);
    currentMainCount->setText(QString::number(currentDeck.mainDeck.count()));
    currentExtraCount->setText(QString::number(currentDeck.extraDeck.count()));
    currentSideCount->setText(QString::number(currentDeck.sideDeck.count()));
}

void DeckEditorPage::UpdateSelectedCardDisplay(int cardId)
{
    Card card = m_cardBox.value(cardId);
    clearLayout(cardInfoDisplayLayout);
    cardInfoDisplayLayout->addWidget(new CardInfoFrame(card));
}

void DeckEditorPage::AddCardToDeck(int cardId, int index)
{
    Card card = m_cardBox.value(cardId);
    if(currentDeck.deckName.isEmpty()) return;

    if(isMainDeckMon(card) && !isCardLimitReached(card) && currentDeck.mainDeck.count() < 60){
        RemoveCardFromCardBox(cardId);
        currentDeck.mainDeck.append(card);
        UpdateCardBoxDisplay();
        UpdateDeckBoxDisplay();
    }
    else if(!isMainDeckMon(card) && !isCardLimitReached(card) && currentDeck.extraDeck.count() < 15){
        RemoveCardFromCardBox(cardId);
        currentDeck.extraDeck.append(card);
        UpdateCardBoxDisplay();
        UpdateDeckBoxDisplay();
    }
    else if(!isCardLimitReached(card) && currentDeck.sideDeck.count() < 15){
        RemoveCardFromCardBox(cardId);
        currentDeck.sideDeck.append(card);
        UpdateCardBoxDisplay();
        UpdateDeckBoxDisplay();
    }
    currentIndex = index;

}

void DeckEditorPage::LoadCurrentDeck()
{
    allPlayerDecks->clear();
    clearLayout(cardInfoDisplayLayout);
    clearLayout(deckInfoDisplayLayout);
    clearLayout(cardBoxDisplayLayout);
    currentIndex = 0;

    for (const auto& pair : m_deckBox) {
        allPlayerDecks->addItem(pair.deckName);
        connect(allPlayerDecks, QOverload<int>::of(&QComboBox::activated), this, &DeckEditorPage::onDeckSelected);
        // Process key and deck
    }
    allPlayerDecks->setCurrentText(selectedDeck);
    currentDeck = m_deckBox.value(selectedDeck);
    currentDeckName->setText(currentDeck.deckName);

    UpdateDeckBoxDisplay();
    UpdateCardBoxDisplay();

}

void DeckEditorPage::onDeckSelected(int index)
{
    ClearOutDeck();
    currentDeckName->setText(allPlayerDecks->itemText(index));
    currentDeck = m_deckBox.value(currentDeckName->text());
    for (const auto& card : currentDeck.mainDeck) {
        RemoveCardFromCardBox(card.cardId);
    }
    UpdateDeckBoxDisplay();
    UpdateCardBoxDisplay();
}

void DeckEditorPage::onSortSelected(int index)
{
    currentSortOption = static_cast<SortOptions>(index);
    UpdateCardBoxDisplay();
}

void DeckEditorPage::onFilterSelected(int index)
{
    currentFilterOption = static_cast<FilterOptions>(index);
    UpdateCardBoxDisplay();
}

void DeckEditorPage::onSearchUpdate(QString search)
{
    currentSearchOption = search;
    UpdateCardBoxDisplay();
}

void DeckEditorPage::onAddToSideDeck(int cardId, int index)
{
    Card card = m_cardBox.value(cardId);
    if(!isCardLimitReached(card) && currentDeck.sideDeck.count() < 15){
        RemoveCardFromCardBox(cardId);
        currentDeck.sideDeck.append(card);
        UpdateCardBoxDisplay();
        UpdateDeckBoxDisplay();
    }
    currentIndex = index;
}



void DeckEditorPage::clearLayout(QLayout *layout) {
    if (!layout)
        return;

    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->hide(); // Optional: hide the widget before deleting it
            delete widget;
        }
        delete item;
    }
}

void DeckEditorPage::SaveDeck()
{
    if(currentDeck.deckName.isEmpty()){
        // Create a QMessageBox for user input
        QMessageBox msgBox;
        msgBox.setText("No Deck Name");
        msgBox.exec();
    }

    else {
        // Create a QMessageBox for user input
        QMessageBox msgBox;
        msgBox.setText("Deck Saved");
        msgBox.exec();
        m_deckBox.insert(currentDeck.deckName,currentDeck);
        selectedDeck = currentDeck.deckName;
        emit SavePlayerDeckBox();
    }


}

void DeckEditorPage::RemoveCardFromCardBox(int cardId)
{
    Card card = m_cardBox.value(cardId);

    if(card.copies < 0){
        qDebug() << "ERROR negative card count: " + QString::number(card.copies);
    }

    card.copies--;
    m_cardBox.insert(card.cardId,card);
}

void DeckEditorPage::RemoveCardFromDeckBox(int cardId)
{
    Card card = m_cardBox.value(cardId);
    if(m_cardBox.contains(card.cardId)){
        card.copies +=1;
    }
    else {
        qDebug() << "ERROR no card count: " + card.cardInfo.cardName;
    }
    m_cardBox.insert(card.cardId,card);
    if (currentDeck.sideDeck.contains(card)) currentDeck.sideDeck.removeOne(card);
    else if(currentDeck.mainDeck.contains(card)) currentDeck.mainDeck.removeOne(card);
    else if (currentDeck.extraDeck.contains(card)) currentDeck.extraDeck.removeOne(card);

    else qDebug() << "ERROR COULD NOT FIND CARD TO REMOVE FROM DECK";

    UpdateCardBoxDisplay();
    UpdateDeckBoxDisplay();

}

void DeckEditorPage::ClearOutDeck()
{
    for (const auto& cardItem : currentDeck.mainDeck) {

        Card card = m_cardBox.value(cardItem.cardId);
        if(m_cardBox.contains(card.cardId)){
            card.copies +=1;
        }
        else {
            qDebug() << "ERROR no card count: " + card.cardInfo.cardName;
        }
        m_cardBox.insert(card.cardId,card);
        currentDeck.mainDeck.removeOne(card);
    }

    for (const auto& cardItem : currentDeck.extraDeck) {

        Card card = m_cardBox.value(cardItem.cardId);
        if(m_cardBox.contains(card.cardId)){
            card.copies +=1;
        }
        else {
            qDebug() << "ERROR no card count: " + card.cardInfo.cardName;
        }
        m_cardBox.insert(card.cardId,card);
        currentDeck.extraDeck.removeOne(card);
    }

    for (const auto& cardItem : currentDeck.sideDeck) {

        Card card = m_cardBox.value(cardItem.cardId);
        if(m_cardBox.contains(card.cardId)){
            card.copies +=1;
        }
        else {
            qDebug() << "ERROR no card count: " + card.cardInfo.cardName;
        }
        m_cardBox.insert(card.cardId,card);
        currentDeck.sideDeck.removeOne(card);
    }
}

bool DeckEditorPage::isMainDeckMon(Card card)
{
    return !(card.cardInfo.cardType == "Link Monster" ||
             card.cardInfo.cardType == "XYZ Monster" ||
             card.cardInfo.cardType == "Synchro Monster" ||
             card.cardInfo.cardType == "Synchro Tuner Monster" ||
             card.cardInfo.cardType == "Fusion Monster");
}

bool DeckEditorPage::isCardLimitReached(Card card)
{
    int count = 0;
    for (const auto& d_card : currentDeck.mainDeck) {
        if(count == 3) return true;
        if(card.cardId == d_card.cardId) count++;
        if(count > 3) qDebug() << "SOMEHOW MORE THAN 3 COPIES ARE IN THIS DECK";
    }
    for (const auto& d_card : currentDeck.extraDeck) {
        if(count == 3) return true;
        if(card.cardId == d_card.cardId) count++;
        if(count > 3) qDebug() << "SOMEHOW MORE THAN 3 COPIES ARE IN THIS DECK";
    }
    for (const auto& d_card : currentDeck.sideDeck) {
        if(count == 3) return true;
        if(card.cardId == d_card.cardId) count++;
        if(count > 3) qDebug() << "SOMEHOW MORE THAN 3 COPIES ARE IN THIS DECK";
    }
    return false;

}

void DeckEditorPage::CreateNewDeck()
{

    bool ok;
    QString text = QInputDialog::getText(nullptr, "New Deck Name", "Create New Deck:", QLineEdit::Normal, "New Deck", &ok);
    if(ok && !text.isEmpty()){
        ClearOutDeck();
        currentDeckName->setText(text);
        currentDeck.deckName = currentDeckName->text();
        m_deckBox.insert(currentDeck.deckName,currentDeck);
        // SaveDeck();
        allPlayerDecks->clear();
        for (const auto& pair :  std::as_const(m_deckBox)) {
            allPlayerDecks->addItem(pair.deckName);
            connect(allPlayerDecks, QOverload<int>::of(&QComboBox::activated), this, &DeckEditorPage::onDeckSelected);
            // Process key and deck
        }
        allPlayerDecks->setCurrentText(text);
        // Save the user input to a variable or do something with it
        emit SavePlayerDeckBox();

        UpdateDeckBoxDisplay();
        UpdateCardBoxDisplay();
    }
}

void DeckEditorPage::ExportDeck()
{
    QString ydkData;

    ydkData = ydkData + "#main \n";
    for(const Card &card : currentDeck.mainDeck){
        ydkData = ydkData + QString::number(card.cardId) + "\n";
    }
    ydkData = ydkData + "#extra \n";
    for(const Card &card : currentDeck.extraDeck){
        ydkData = ydkData + QString::number(card.cardId) + "\n";
    }
    ydkData = ydkData + "!side \n";
    for(const Card &card : currentDeck.sideDeck){
        ydkData = ydkData + QString::number(card.cardId) + "\n";
    }

    QString filePath = QFileDialog::getSaveFileName(this,"Export File",deckExportFilePath,"YDK Files (*.ydk)");
    if(!filePath.isEmpty()){
        // Create a QFile object with the specified file path
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // Create a QTextStream object with the file as the device
            QTextStream out(&file);

            // Write the ydkData to the file
            out << ydkData << "\n"; // Add a new line

            // Close the file
            file.close();
            qDebug() << "File saved successfully!";
        } else {
            // Print an error message if the file couldn't be opened
            qWarning() << "Failed to open file for writing:" << file.errorString();
        }
    }
    else{
        qDebug() << "No File Selected";
    }
}


QList<Card> DeckEditorPage::SortDisplayList(QList<Card> displayList)
{
    QList<Card> sortedList = displayList;
    std::sort(sortedList.begin(), sortedList.end(), [this](const Card &a, const Card &b) {
        switch(currentSortOption){
        case SortOptions::Name: return a.cardInfo.cardName < b.cardInfo.cardName;
        case SortOptions::ObtainDate: return a.obtainDate < b.obtainDate;
        case SortOptions::Level: return a.cardInfo.level < b.cardInfo.level;
        case SortOptions::Type: return a.cardInfo.cardType < b.cardInfo.cardType;
        case SortOptions::Archetype: return a.cardInfo.cardArchetype < b.cardInfo.cardArchetype;
        default: return a.cardId < b.cardId;
        }
    });

    return sortedList;
}

QString DeckEditorPage::SortToString(SortOptions option)
{
    switch(option){
    case SortOptions::Name: return "Name";
    case SortOptions::ObtainDate: return "ObtainDate";
    case SortOptions::Level: return "Level";
    case SortOptions::Type: return "Type";
    case SortOptions::Archetype: return "Archetype";
    default: return "Unknown";
    }
}

QList<Card> DeckEditorPage::FilterDisplayList(QList<Card> displayList)
{
    QList<Card> filteredList;
    std::copy_if(displayList.begin(), displayList.end(), std::back_inserter(filteredList), [this](const Card &card) {
        switch(currentFilterOption){
        case FilterOptions::Monster: return card.cardInfo.cardType.endsWith("Monster");
        case FilterOptions::Fusion: return card.cardInfo.cardType.startsWith("Fusion");
        case FilterOptions::Link: return  card.cardInfo.cardType.startsWith("Link");
        case FilterOptions::Pendulum: return  card.cardInfo.cardType.startsWith("Pendulum");
        case FilterOptions::Synchro: return  card.cardInfo.cardType.startsWith("Synchro");
        case FilterOptions::XYZ: return  card.cardInfo.cardType.startsWith("XYZ");
        case FilterOptions::Spell: return card.cardInfo.cardType == "Spell Card";
        case FilterOptions::Trap: return card.cardInfo.cardType == "Trap Card";
        default: return true;
        }
    });
    return filteredList;
}

QString DeckEditorPage::FilterToString(FilterOptions option)
{
    switch(option){
    case FilterOptions::Default: return "Default";
    case FilterOptions::Monster: return "Monster";
    case FilterOptions::Fusion: return "Fusion";
    case FilterOptions::Link: return "Link";
    case FilterOptions::Pendulum: return "Pendulum";
    case FilterOptions::Spell: return "Spell";
    case FilterOptions::Trap: return "Trap";
    case FilterOptions::Synchro: return "Synchro";
    case FilterOptions::XYZ: return "XYZ";
    default: return "Unknown";

    }
}

QList<Card> DeckEditorPage::SearchDisplayList(QList<Card> displayList)
{
    QList<Card> searchedList;
    for(const Card& card : displayList){
        if(card.cardInfo.cardArchetype.contains(currentSearchOption,Qt::CaseInsensitive) ||
            card.cardInfo.cardName.contains(currentSearchOption,Qt::CaseInsensitive) ||
            card.cardInfo.cardArchetype.contains(currentSearchOption,Qt::CaseInsensitive) ||
            card.cardInfo.cardAttribute.contains(currentSearchOption,Qt::CaseInsensitive) ||
            card.cardInfo.cardRace.contains(currentSearchOption,Qt::CaseInsensitive) ||
            card.cardInfo.cardDesc.contains(currentSearchOption,Qt::CaseInsensitive)) {
            searchedList.append(card);
        }
    }
    return searchedList;
}

QList<Card> DeckEditorPage::GetActiveCardsOnly(QList<Card> displayList)
{
    QList<Card> activeCardList;
    for(const Card& card : displayList){
        if(card.copies > 0){
            activeCardList.append(card);
        }
    }
    return activeCardList;
}



