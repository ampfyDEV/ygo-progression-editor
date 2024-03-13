#include "CardRevealCard.h"
#include "PackOpeningPage.h"

#include <QDir>

PackOpeningPage::PackOpeningPage(QWidget *parent) {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    this->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    setObjectName("PackOpeningPage");
    /* USE RESOURCE SYSTEM FOR THIS LATER*/
    QString bgPath = QDir::currentPath() + "/Textures/bg.jpg";
    QString bgStyleSheet =QString( "#PackOpeningPage {"
                                   "background-image: url(%1);"
                                   "background-repeat: no-repeat;"
                                   "background-position: center center;}").arg(bgPath);
    this->setStyleSheet(bgStyleSheet);



    QFrame *packOpeningPageContainer = new QFrame(this);
    packOpeningPageContainer->setObjectName("packOpeningPageContainer");
    packOpeningPageContainer->setFrameStyle(QFrame::Box);
    packOpeningPageContainer->setMinimumSize(1600,900);
    packOpeningPageContainer->setMaximumSize(1920,1080);
    packOpeningPageContainer->setLineWidth(3);
    packOpeningPageContainer->setStyleSheet("#packOpeningPageContainer {background-color: rgba(255, 255, 255, 0.5);"
                                           "border: 2px solid black;}");
    packOpeningPageContainer->setAutoFillBackground(true);
    mainLayout->addWidget(packOpeningPageContainer);
    mainLayout->setAlignment(Qt::AlignCenter);


    QFrame *headerContainer = new QFrame(this);
    headerContainer->setObjectName("headerContainer");
    headerContainer->setStyleSheet("#headerContainer {background-color: rgba(255, 255, 255, 0);}");
    headerContainer->setAutoFillBackground(true);

    QHBoxLayout *headerContainerLayout = new QHBoxLayout(headerContainer);

    QString backPath = QDir::currentPath() + "/Textures/backButton.png";
    QPushButton *backButton = new QPushButton(headerContainer);
    backButton->setIcon(QIcon(backPath));
    backButton->setIconSize(QSize(75,75));
    backButton->setStyleSheet("QPushButton {"
                              "background-color: rgba(255, 255, 255, 0);}"
                              "QPushButton:hover { background-color: 2px solid lightblue; }"
                              "QPushButton:pressed { background-color: rgba(173, 216, 230, 0); }");
    connect(backButton,&QPushButton::clicked,this,&PackOpeningPage::BackToPackPage);

    packNameContainer = new QLabel(currentPackName,headerContainer);
    packNameContainer->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    packNameContainer->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setBold(true);
    font.setPointSize(30);
    packNameContainer->setFont(font);

    headerContainerLayout->addWidget(backButton,1);
    headerContainerLayout->addWidget(packNameContainer,15);
    headerContainerLayout->addSpacing(100);


    //Add new name & packs

    cardDisplayContainer = new QFrame(this);
    cardDisplayContainer->setObjectName("cardDisplayContainer");
    cardDisplayContainer->setStyleSheet("#cardDisplayContainer {background-color: rgba(255, 255, 255, 0);"
                                   "border: 2px solid black;}");
    cardDisplayContainer->setAutoFillBackground(true);
    cardDisplayLayout = new QVBoxLayout(cardDisplayContainer);


    QVBoxLayout *packOpeningPageContainerLayout = new QVBoxLayout(packOpeningPageContainer);
    packOpeningPageContainerLayout->addWidget(headerContainer,1);
    packOpeningPageContainerLayout->addWidget(cardDisplayContainer,10);
    mainLayout->addWidget(packOpeningPageContainer);

}

void PackOpeningPage::loadNextPack()
{
    //no more cards to pull
    if(currentPack * 7 >= cardsToOpen.size()) return;

    QFrame *footerContainer = new QFrame(this);
    footerContainer->setObjectName("footerContainer");
    footerContainer->setStyleSheet("#footerContainer { background-color: rgba(255, 255, 255, 0); }");
    footerContainer->setAutoFillBackground(true);
    footerContainer->setMaximumHeight(250);

    QVBoxLayout *footerContainerLayout = new QVBoxLayout(footerContainer);
    QLabel *currentPackProgress = new QLabel("0 / 0",footerContainer);
    currentPackProgress->setAlignment(Qt::AlignCenter);
    currentPackProgress->setMaximumHeight(50);
    currentPackProgress->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    QFrame *cardOpenOptions = new QFrame(footerContainer);
    cardOpenOptions->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QHBoxLayout *cardOpenOptionsLayout = new QHBoxLayout(cardOpenOptions);

    QFont font;
    font.setBold(true);
    font.setPointSize(20);
    currentPackProgress->setFont(font);
    QPushButton *nextPage = new QPushButton("Next",footerContainer);
    nextPage->setMaximumWidth(100);
    nextPage->setFont(font);
    nextPage->setStyleSheet("QPushButton {"
                              "background-color: rgba(255, 255, 255, 0);}"
                              "QPushButton:hover { background-color: 2px solid lightblue; }"
                              "QPushButton:pressed { background-color: rgba(173, 216, 230, 0); }");
    connect(nextPage,&QPushButton::clicked,this,&PackOpeningPage::LoadNextPage);

    QPushButton *openAll = new QPushButton("Open All Cards",footerContainer);
    // openAll->setMaximumWidth(100);
    openAll->setFont(font);
    openAll->setObjectName("openAll");
    openAll->setStyleSheet("QPushButton {"
                            "background-color: rgba(255, 255, 255, 0);}"
                            "QPushButton:hover { background-color: 2px solid lightblue; }"
                            "QPushButton:pressed { background-color: rgba(173, 216, 230, 0); }");
    connect(openAll,&QPushButton::clicked,this,&PackOpeningPage::OpenAllCards);

    cardOpenOptionsLayout->addWidget(openAll);
    cardOpenOptionsLayout->addSpacing(12);
    cardOpenOptionsLayout->addWidget(nextPage);

    footerContainerLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    footerContainerLayout->addWidget(currentPackProgress);
    footerContainerLayout->addWidget(cardOpenOptions);

    nextPage->setEnabled(false);
    nextPackButton = nextPage;
    openAllCardsButton = openAll;


    currentPackProgress->setText(QString::number(currentPack + 1) + " / " + QString::number(maxPack));

    QFrame *cardPackDisplay = new QFrame(cardDisplayContainer);
    cardPackDisplay->setObjectName("cardPackDisplay");
    cardPackDisplay->setStyleSheet("#cardPackDisplay {background-color: rgba(255, 255, 255, 0);"
                                   "border: 2px solid black;}");
    cardPackDisplay->setAutoFillBackground(true);

    QHBoxLayout *cardPackDisplayLayout = new QHBoxLayout(cardPackDisplay);

    int currentPackIndex = currentPack * 7;
    int nextPackIndex = currentPackIndex + 7;
    for(int i = currentPackIndex; i <nextPackIndex; i++){
        CardRevealCard *pulledCard = new CardRevealCard(cardsToOpen[i], this);
        connect(pulledCard,&CardRevealCard::OpenCardClicked,this,&PackOpeningPage::OnPackOpened);
        cardPackDisplayLayout->addWidget(pulledCard);

    }

    //clearLayout(currentPackDisplay);
    currentPackDisplay = cardPackDisplayLayout;

    cardDisplayLayout->addWidget(cardPackDisplay);
    cardDisplayLayout->addWidget(footerContainer);

}

void PackOpeningPage::setupPackOpening(QList<Card> cards, QString packName)
{
    //Clear previous packs
    cardsToOpen.clear();
    clearLayout(cardDisplayLayout);

    currentPackName = packName;
    packNameContainer->setText(currentPackName);
    maxPack = cards.size() / 7;
    cardsToOpen = cards;
    currentPack = 0;
    currentCardsOpened = 0;
    loadNextPack();

}

void PackOpeningPage::LoadNextPage()
{
    currentPack++;
    clearLayout(cardDisplayLayout);
    loadNextPack();
}

void PackOpeningPage::OpenAllCards()
{
    for (int i = 0; i < currentPackDisplay->count(); ++i) {
        QLayoutItem *item = currentPackDisplay->itemAt(i);
        if (item && item->widget()) {
            CardRevealCard *cardWidget = qobject_cast<CardRevealCard *>(item->widget());
            if (cardWidget) {
                cardWidget->on_CardReveal();
            }
        }
    }
}

void PackOpeningPage::OnPackOpened()
{
    currentCardsOpened++;
    if(currentCardsOpened == 7 && (currentPack * 7) + 7 < cardsToOpen.size()){
        nextPackButton->setEnabled(currentPack <= maxPack);
        currentCardsOpened = 0;
    }
}

void PackOpeningPage::clearLayout(QLayout *layout) {
    if (!layout)
        return;

    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            widget->hide(); // Optional: Hide the widget
            delete widget;
        } else if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout); // Recursively clear nested layout
            delete childLayout;
        }
        delete item;
    }
}


// Let the User open 7 cards at a time
