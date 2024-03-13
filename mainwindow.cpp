#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainMenuPage.h"
#include "PacksMenuPage.h"
#include "DeckEditorPage.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QStackedWidget>
#include <QJsonDocument>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadCards();
    mainMenuPage = new MainMenuPage(m_player,this);
    connect(mainMenuPage,&MainMenuPage::OpenPacksPageClicked,this,&MainWindow::on_OpenPage);
    connect(mainMenuPage,&MainMenuPage::OpenEditorPageClicked,this,&MainWindow::on_OpenPage);
    connect(mainMenuPage,&MainMenuPage::LoadCardInfo,this,&MainWindow::on_LoadCardInfo);

    QList<CardInfo> cardValues = m_cards.values();
    packsMenuPage = new PacksMenuPage(m_player,cardValues,this);
    connect(packsMenuPage, &PacksMenuPage::SavePlayerCards,this,&MainWindow::on_SaveCards);
    connect(packsMenuPage,&PacksMenuPage::BackToMainPage,this,&MainWindow::on_BackToMainPage);
    connect(packsMenuPage,&PacksMenuPage::MoveToPackOpeningPage,this,&MainWindow::on_MoveToPackOpeningPage);

    deckEditorPage = new DeckEditorPage(m_player.cardBox,m_player.decks,m_player.selectedDeck,this);
    connect(deckEditorPage,&DeckEditorPage::BackToMainPage,this,&MainWindow::on_BackToMainPage);
    connect(deckEditorPage,&DeckEditorPage::SavePlayerDeckBox,this,&MainWindow::on_SaveCards);


    packOpeningPage = new PackOpeningPage();
    connect(packOpeningPage,&PackOpeningPage::BackToPackPage,this,&MainWindow::on_BackToPackPage);
    // Create a QStackedWidget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    stackedWidget->addWidget(mainMenuPage);
    stackedWidget->addWidget(packsMenuPage);
    stackedWidget->addWidget(deckEditorPage);
    stackedWidget->addWidget(packOpeningPage);
    stackedWidget->setCurrentWidget(mainMenuPage);
    stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenPage(int i)
{
    stackedWidget->setCurrentIndex(i);
}

void MainWindow::on_SaveCards()
{
    QString currentPath = QDir::currentPath() + "/Data/ProgressionSaves/" + m_player.fileName + ".json";
    m_player.Save(currentPath);
    deckEditorPage->UpdateCardBoxDisplay();
}

void MainWindow::on_MoveToPackOpeningPage(QList<Card> cards, QString setName){
    packOpeningPage->setupPackOpening(cards,setName);
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_BackToMainPage()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_BackToPackPage()
{
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_LoadCardInfo()
{
    for(Card& card : m_player.cardBox){
        CardInfo cardInfo = m_cards.value(card.cardId);
        card.setCardInfo(cardInfo);
    }

    for(Deck& deck : m_player.decks){
        for(Card& card : deck.mainDeck){
            CardInfo cardInfo = m_cards.value(card.cardId);
            card.setCardInfo(cardInfo);
        }
        for(Card& card : deck.sideDeck){
            CardInfo cardInfo = m_cards.value(card.cardId);
            card.setCardInfo(cardInfo);
        }
        for(Card& card : deck.extraDeck){
            CardInfo cardInfo = m_cards.value(card.cardId);
            card.setCardInfo(cardInfo);
        }
    }

    deckEditorPage->LoadCurrentDeck();
}

void MainWindow::LoadCards()
{
    QString currentPath = QDir::currentPath() + "/Data/cardinfo.json";
    QFile file(currentPath);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning() << "Failed to open Json File";
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonArray = jsonDoc["data"].toArray();

    foreach(const QJsonValue &value, jsonArray){
       // Card::Card(int id, QString name, QString type, QString desc, QString race, QString att, QString arch, int attk, int def, int lv)
       int id = value["id"].toInt();
       QString name = value["name"].toString();
       QString type = value["type"].toString();
       QString desc = value["desc"].toString();
       QString race = value["race"].toString();
       QString att = value["attribute"].toString();
       QString arch = value["archetype"].toString();
       int attk = value["atk"].toInt();
       int def = value["def"].toInt();
       int lv = value["level"].toInt();

       CardInfo *card = new CardInfo(id,name,type,desc,race,att,arch,attk,def,lv);
       // Initialize card_sets
       if(!value["card_sets"].isUndefined()){
           QJsonArray cardSetsArray = value["card_sets"].toArray();
           for (const auto& set : cardSetsArray) {
               QJsonObject setObj = set.toObject();
               CardInfoSet cardSet;
               cardSet.setName = setObj["set_name"].toString();
               cardSet.setCode = setObj["set_code"].toString();
               cardSet.setRarity = setObj["set_rarity"].toString();
               cardSet.setRarityCode = setObj["set_rarity_code"].toString();
               card->cardSets.append(cardSet);
           }
       }

       m_cards.insert(card->cardId,*card);

    }
}
