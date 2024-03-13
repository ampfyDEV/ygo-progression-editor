#include "playerdata.h"
#include "Card.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>

PlayerData::PlayerData() {
}

bool PlayerData::Load(QString& filepath){
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning() << "Could not open playerData" << file.errorString();
        return false;
    }
    QByteArray fileData = file.readAll();
    file.close();
    QJsonObject jsonData = QJsonDocument::fromJson(fileData).object();
    fromJson(jsonData);
    return true;
}

bool PlayerData::Save(QString& filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return false;
    }
    QJsonDocument saveDataJson(toJson());
    QByteArray saveData = saveDataJson.toJson();
    file.write(saveData);
    file.close();
    return true;
}

bool PlayerData::Create(QString& filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        return false;
    }
    cardBox.clear();
    decks.clear();
    selectedDeck.clear();
    QJsonDocument saveDataJson(toJson());
    QByteArray saveData = saveDataJson.toJson();
    file.write(saveData);
    file.close();
    return true;
}


QJsonObject PlayerData::toJson()
{
    QJsonObject obj;
    obj["fileName"] = fileName;
    obj["selectedDeck"] = selectedDeck;

    //CARD BOX
    QJsonArray cardBoxArr;
    for(const Card& card : cardBox.values()){
        QJsonObject cardJson;
        cardJson["id"] = card.cardId;
        cardJson["obtain_date"] = card.obtainDate.toString(Qt::ISODate);
        cardJson["set_rarity"] = card.setRarity;
        cardJson["copies"] = card.copies;
        cardBoxArr.append(cardJson);
    }
    obj["cardBox"] = cardBoxArr;

    //DECK
    QJsonArray decksArray;
    for(const auto& deck : decks.values())
    {
        // Convert Deck to JSON object
        QJsonObject deckObject;

        deckObject["deckName"] = deck.deckName;

        // Convert mainDeck to JSON array
        QJsonArray mainDeckArray;
        for(const auto& card : deck.mainDeck)
        {
            // Convert Card to JSON object
            QJsonObject cardObject;
            // Fill cardObject with card data (assuming you have appropriate methods or properties in Card struct)
            cardObject["id"] = card.cardId;
            cardObject["obtain_date"] = card.obtainDate.toString(Qt::ISODate);
            cardObject["set_rarity"] = card.setRarity;
            cardObject["copies"] = card.copies;
            // Add cardObject to mainDeckArray
            mainDeckArray.append(cardObject);
        }
        // Add mainDeckArray to deckObject
        deckObject["mainDeck"] = mainDeckArray;

        // Convert extraDeck to JSON array
        QJsonArray extraDeckArray;
        for(const auto& card : deck.extraDeck)
        {
            // Convert Card to JSON object
            QJsonObject cardObject;
            // Fill cardObject with card data (assuming you have appropriate methods or properties in Card struct)
            cardObject["id"] = card.cardId;
            cardObject["obtain_date"] = card.obtainDate.toString(Qt::ISODate);
            cardObject["set_rarity"] = card.setRarity;
            cardObject["copies"] = card.copies;
            // Add cardObject to extraDeckArray
            extraDeckArray.append(cardObject);
        }
        // Add extraDeckArray to deckObject
        deckObject["extraDeck"] = extraDeckArray;

        // Convert sideDeck to JSON array
        QJsonArray sideDeckArray;
        for(const auto& card : deck.sideDeck)
        {
            // Convert Card to JSON object
            QJsonObject cardObject;
            // Fill cardObject with card data (assuming you have appropriate methods or properties in Card struct)
            cardObject["id"] = card.cardId;
            cardObject["obtain_date"] = card.obtainDate.toString(Qt::ISODate);
            cardObject["set_rarity"] = card.setRarity;
            cardObject["copies"] = card.copies;
            sideDeckArray.append(cardObject);
        }
        // Add sideDeckArray to deckObject
        deckObject["sideDeck"] = sideDeckArray;

        // Add deckObject to decksArray
        decksArray.append(deckObject);
    }
    // Add decksArray to playerDataObject
    obj["decks"] = decksArray;


    return obj;
}

void PlayerData::fromJson(QJsonObject& obj)
{
    fileName.clear();
    cardBox.clear();
    decks.clear();

    fileName = obj["fileName"].toString();
    selectedDeck = obj["selectedDeck"].toString();

    QJsonArray cardBoxArr = obj["cardBox"].toArray();
    for(const auto& item : cardBoxArr){
        QJsonObject cardJson = item.toObject();
        Card *card = new Card(cardJson["id"].toInt(),QDateTime::fromString(cardJson["obtain_date"].toString(),Qt::ISODate),cardJson["set_rarity"].toString());
        card->copies = cardJson["copies"].toInt();
        cardBox.insert(cardJson["id"].toInt(),*card);
    }

    // Get decks array
    QJsonArray decksArray = obj["decks"].toArray();

    // Iterate over decks array
    for(const auto& deckValue : decksArray)
    {
        // Convert deckValue to JSON object
        QJsonObject deckObject = deckValue.toObject();

        // Create a new Deck
        Deck deck;

        deck.deckName = deckObject["deckName"].toString();

        // Parse mainDeck array
        QJsonArray mainDeckArray = deckObject["mainDeck"].toArray();
        for(const auto& cardValue : mainDeckArray)
        {
            // Convert cardValue to JSON object
            QJsonObject cardObject = cardValue.toObject();

            // Create a new Card and populate it
            Card *card = new Card(cardObject["id"].toInt(),QDateTime::fromString(cardObject["obtain_date"].toString(),Qt::ISODate),cardObject["set_rarity"].toString());
            card->copies = cardObject["copies"].toInt();
            // Populate other card properties as needed
            // ...

            // Add card to mainDeck
            deck.mainDeck.append(*card);
        }

        // Parse extraDeck array
        QJsonArray extraDeckArray = deckObject["extraDeck"].toArray();
        for(const auto& cardValue : extraDeckArray)
        {
            // Convert cardValue to JSON object
            QJsonObject cardObject = cardValue.toObject();

            // Create a new Card and populate it
            Card *card = new Card(cardObject["id"].toInt(),QDateTime::fromString(cardObject["obtain_date"].toString(),Qt::ISODate),cardObject["set_rarity"].toString());
            card->copies = cardObject["copies"].toInt();
            // Populate other card properties as needed
            // ...

            // Add card to mainDeck
            deck.extraDeck.append(*card);
        }

        // Parse sideDeck array
        QJsonArray sideDeckArray = deckObject["sideDeck"].toArray();
        for(const auto& cardValue : sideDeckArray)
        {
            // Convert cardValue to JSON object
            QJsonObject cardObject = cardValue.toObject();

            // Create a new Card and populate it
            Card *card = new Card(cardObject["id"].toInt(),QDateTime::fromString(cardObject["obtain_date"].toString(),Qt::ISODate),cardObject["set_rarity"].toString());
            card->copies = cardObject["copies"].toInt();
            // Populate other card properties as needed
            // ...

            // Add card to mainDeck
            deck.sideDeck.append(*card);
        }

        // Add deck to playerData
        decks.insert(deck.deckName,deck);
    }
}


