#include "PacksMenuPage.h"
#include "FlowLayout.h"
#include "Card.h"

#include <QDir>
#include <QGridLayout>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QScrollArea>
#include <QCheckBox>

PacksMenuPage::PacksMenuPage(PlayerData &playerData, QList<CardInfo> &m_cards,QWidget *parent): QFrame(parent),m_playerData(playerData), m_cards(m_cards){

    this->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setObjectName("PacksMenuPage");
    /* USE RESOURCE SYSTEM FOR THIS LATER*/
    QString bgPath = QDir::currentPath() + "/Textures/bg.jpg";
    QString bgStyleSheet =QString( "#PacksMenuPage {"
                                   "background-image: url(%1);"
                                   "background-repeat: no-repeat;"
                                   "background-position: center center;}").arg(bgPath);
    this->setStyleSheet(bgStyleSheet);

    QFrame *packsContainer = new QFrame(this);
    packsContainer->setObjectName("packsContainer");
    packsContainer->setFrameStyle(QFrame::StyledPanel);
    packsContainer->setLineWidth(3);
    packsContainer->setStyleSheet("#packsContainer {background-color: rgba(255, 255, 255, 0);"
                                  "border: 2px solid black;}");
    //packsContainer->setFixedSize(1600,900);
    packsContainer->setAutoFillBackground(true);

    //mainLayout->addWidget(packsContainer,0,Qt::AlignCenter);

    packsContainerLayout = new FlowLayout(packsContainer);



    QString currentPath = QDir::currentPath() + "/Data/cardSetData.json";
    QFile file(currentPath);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning() << "Failed to open Json File";
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonArray = jsonDoc.array();


    foreach(QJsonValue value, jsonArray){
        if(value.isObject()){
            QJsonObject pack = value.toObject();
            if(pack["set_image"].toString().isEmpty() || pack["num_of_cards"].toInt() < 10) continue;
            QList<Card> cardsToLoad = loadCardsIntoPack(pack["set_code"].toString());
            if(cardsToLoad.isEmpty()) continue;
            QString setName = pack["set_name"].toString();
            QString setCode = pack["set_code"].toString();
            int cardsPerPack = pack["num_of_cards"].toInt();
            QDate releaseDate = QDate::fromString(pack["tcg_date"].toString(),"yyyy-MM-dd");
            CardPack *cardPack = new CardPack(setName,setCode,cardsPerPack,releaseDate,cardsToLoad);
            cardPacks.append(*cardPack);
        }
    }


    //HEADER
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
    backButton->setIconSize(QSize(75,75));
    backButton->setStyleSheet("QPushButton {"
                        "background-color: rgba(255, 255, 255, 0);}"
                        "QPushButton:hover { background-color: 2px solid lightblue; }"
                        "QPushButton:pressed { background-color: rgba(173, 216, 230, 0); }");
    connect(backButton,&QPushButton::clicked,this,&PacksMenuPage::BackToMainPage);

    //PACK AMOUNT SELECTION
    QFrame *packCount = new QFrame(headerBarContainer);
    packCount->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    QHBoxLayout *packCountLayout = new QHBoxLayout(packCount);
    QLabel *countLabel = new QLabel("Count: ");
    countLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    packAmount = new QComboBox(headerBarContainer);
    packAmount->addItem("1");
    packAmount->addItem("2");
    packAmount->addItem("3");
    packAmount->addItem("4");
    packAmount->addItem("5");
    packAmount->addItem("10");
    packAmount->addItem("15");
    packAmount->addItem("20");
    packAmount->addItem("30");
    packAmount->addItem("40");
    packAmount->addItem("50");
    packAmount->addItem("100");
    connect(packAmount, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &PacksMenuPage::on_PackAmountChange);
    packAmount->setCurrentIndex(6);
    packCountLayout->addWidget(countLabel);
    packCountLayout->addWidget(packAmount);
    packCountLayout->setAlignment(Qt::AlignLeft);
    packCountLayout->setContentsMargins(5, 5, 5, 5);
    packCountLayout->setSpacing(6);



    //SORTING
    QFrame *sortPacks = new QFrame(headerBarContainer);
    sortPacks->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    QHBoxLayout *sortCardLayout = new QHBoxLayout(sortPacks);
    QLabel *sortingLabel = new QLabel("Sort by:",sortPacks);
    sortingLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QComboBox *sortingBox = new QComboBox(sortPacks);
    for (int i = static_cast<int>(PackSortOptions::Name); i <= static_cast<int>(PackSortOptions::ReleaseDate); ++i) {
        sortingBox->addItem(SortToString(static_cast<PackSortOptions>(i))); // Convert enum value to string
    }
    connect(sortingBox, QOverload<int>::of(&QComboBox::activated), this, &PacksMenuPage::on_SortSelected);
    sortCardLayout->addWidget(sortingLabel);
    sortCardLayout->addWidget(sortingBox);
    sortCardLayout->setAlignment(Qt::AlignLeft);
    sortCardLayout->setContentsMargins(5, 5, 5, 5);
    sortCardLayout->setSpacing(6);


    //FILTER
    QFrame *filterPacks = new QFrame(headerBarContainer);
    filterPacks->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    QHBoxLayout *filterPacksLayout = new QHBoxLayout(filterPacks);
    QLabel *filterLabel = new QLabel("Filter by:",filterPacks);
    filterLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QComboBox *filterBox = new QComboBox(filterPacks);
    for (int i = static_cast<int>(PackFilterOptions::ALL); i <= static_cast<int>(PackFilterOptions::StructureDeck); ++i) {
        filterBox->addItem(FilterToString(static_cast<PackFilterOptions>(i))); // Convert enum value to string
    }
    connect(filterBox, QOverload<int>::of(&QComboBox::activated), this, &PacksMenuPage::on_FilterSelected);
    filterPacksLayout->addWidget(filterLabel);
    filterPacksLayout->addWidget(filterBox);
    filterPacksLayout->setAlignment(Qt::AlignLeft);
    //filterPacks->setMaximumHeight(30);
    filterPacksLayout->setContentsMargins(5, 5, 5, 5);
    filterPacksLayout->setSpacing(6);


    QFrame *packOptions = new QFrame(headerBarContainer);
    QVBoxLayout *packOptionsLayout = new QVBoxLayout(packOptions);
    packOptionsLayout->addWidget(packCount);
    packOptionsLayout->addWidget(sortPacks);
    packOptionsLayout->addWidget(filterPacks);
    packOptionsLayout->setContentsMargins(0, 0, 0, 0);
    packOptionsLayout->setSpacing(0);
    packOptions->setObjectName("packOptions");
    packOptions->setStyleSheet("#packOptions {background-color: rgba(255, 255, 255, 0);"
                                  "border: 2px solid black;}");

    QLabel *titlePage = new QLabel("Pack Opening Page",headerBarContainer);
    titlePage->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    titlePage->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setBold(true);
    font.setPointSize(30);
    titlePage->setFont(font);
    headerLayout->addWidget(backButton,1);
    headerLayout->addWidget(titlePage,10);
    headerLayout->addWidget(packOptions,1);


    mainLayout->addWidget(headerBarContainer);



    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true); // Allows the scroll area to resize its widget
    scrollArea->setWidget(packsContainer);
    scrollArea->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    mainLayout->addWidget(scrollArea);
    UpdateCardPackDisplay();

}

void PacksMenuPage::on_OpenCardPacks(QList<Card> selectedCards, QString setName)
{
    for(const auto& card: selectedCards){
        if(m_playerData.cardBox.contains(card.cardId)){
            Card dupeCard = m_playerData.cardBox.value(card.cardId);
            dupeCard.copies++;
            m_playerData.cardBox.insert(dupeCard.cardId,dupeCard);
        }
        else{
            m_playerData.cardBox.insert(card.cardId,card);
        }

    }

    emit SavePlayerCards();
    emit MoveToPackOpeningPage(selectedCards, setName);

}

void PacksMenuPage::on_PackAmountChange()
{
    for(CardPackButton *pack : cardPackButtons){
        pack->setPullAmount(packAmount->currentText().toInt());
    }
}

void PacksMenuPage::on_SortSelected(int index)
{
    currentSortOption = static_cast<PackSortOptions>(index);
    UpdateCardPackDisplay();
}

void PacksMenuPage::on_FilterSelected(int index)
{
    currentFilterOption = static_cast<PackFilterOptions>(index);
    UpdateCardPackDisplay();
}


QList<Card> PacksMenuPage::loadCardsIntoPack(QString setCode)
{
    QList<Card> cards;
    for (const auto& card : m_cards) {
        for (const auto& cardSet : card.cardSets) {
            if(cardSet.setCode.section('-',0,0) == setCode){
                cards.append(*new Card(card,cardSet.setRarityCode));
            }
        }
    }
    return cards;
}

void PacksMenuPage::UpdateCardPackDisplay()
{
    clearLayout(packsContainerLayout);
    cardPackButtons.clear();
    QList<CardPack> displayCardPack = cardPacks;
    displayCardPack = FilterPackList(displayCardPack);
    displayCardPack = SortDisplayList(displayCardPack);
    for(const CardPack &pack : displayCardPack){
        CardPackButton *cardPackButton = new CardPackButton(pack, this);
        cardPackButton-> setPullAmount(packAmount->currentText().toInt());
        packsContainerLayout->addWidget(cardPackButton);
        connect(cardPackButton,&CardPackButton::OpenPacksClicked,this,&PacksMenuPage::on_OpenCardPacks);
        cardPackButtons.append(cardPackButton);
    }
}

QString PacksMenuPage::SortToString(PackSortOptions option)
{
    switch(option){
    case PackSortOptions::Name: return "Name";
    case PackSortOptions::ReleaseDate: return "ReleaseDate";
    default: return "Unknown";
    }
}

QString PacksMenuPage::FilterToString(PackFilterOptions option)
{
    switch(option){
    case PackFilterOptions::ALL: return "ALL";
    case PackFilterOptions::Packs: return "Packs";
          case PackFilterOptions::StructureDeck: return "Structure Decks";
    default: return "Unknown";
    }
}

QList<CardPack> PacksMenuPage::FilterPackList(QList<CardPack> displayList)
{
    QList<CardPack> filteredList;
    std::copy_if(displayList.begin(), displayList.end(), std::back_inserter(filteredList), [this](const CardPack &pack) {
        switch(currentFilterOption){
        case PackFilterOptions::Packs: {
            for(const QString &name : structureDeckNames){
                if(pack.setName.contains(name)) return false;
            }
            return true;
        }
        case PackFilterOptions::StructureDeck: {
            for(const QString &name : structureDeckNames){
                if(pack.setName.contains(name)) return true;
            }
            return false;
        }
        default: return true;
        }
    });
    return filteredList;
}

void PacksMenuPage::clearLayout(QLayout *layout) {
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

QList<CardPack> PacksMenuPage::SortDisplayList(QList<CardPack> displayList)
{
    QList<CardPack> sortedList = displayList;
    std::sort(sortedList.begin(), sortedList.end(), [this](CardPack &a, CardPack &b) {
        switch(currentSortOption){
        case PackSortOptions::Name: return a.setName < b.setName;
        case PackSortOptions::ReleaseDate: return a.releaseDate < b.releaseDate;
        default: return a.setCode < b.setCode;

        }
    });
    return sortedList;
}


