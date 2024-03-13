#include "MainMenuPage.h"

#include <QDir>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QFrame>
#include <QVBoxLayout>



MainMenuPage::MainMenuPage(PlayerData &playerData, QWidget *parent): QFrame(parent),m_playerData(playerData)
{
    setObjectName("MainMenuPage");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    /* USE RESOURCE SYSTEM FOR THIS LATER*/
    QString bgPath = QDir::currentPath() + "/Textures/bg.jpg";
    QString bgStyleSheet =QString( "#MainMenuPage {"
                                "background-image: url(%1);"
                                "background-repeat: no-repeat;"
                                "background-position: center;}").arg(bgPath);
    this->setFrameStyle(QFrame::Box);
    this->setStyleSheet(bgStyleSheet);


    QFrame *frame = new QFrame(this);
    frame->setObjectName("OptionsContainer");
    frame->setFrameStyle(QFrame::Box);
    frame->setStyleSheet("QPushButton{background-color: white}"
                         "#OptionsContainer {background-color: rgba(255, 255, 255, 0);}");
    frame->setAutoFillBackground(true);

    QVBoxLayout *frameLayout = new QVBoxLayout(frame);

    mainLayout->addWidget(frame,0,Qt::AlignCenter);


    QPushButton *createProgression = new QPushButton("Create Progression", frame);
    createProgression->setFixedSize(361, 41);
    frameLayout->addWidget(createProgression);
    connect(createProgression,&QPushButton::clicked,this,&MainMenuPage::on_CreateProgression);

    QPushButton *loadProgression = new QPushButton("Load Progression", frame);
    loadProgression->setFixedSize(361, 41);
    frameLayout->addWidget(loadProgression);
    connect(loadProgression,&QPushButton::clicked,this,&MainMenuPage::on_LoadProgression);

    openPacks = new QPushButton("Open Packs", frame);
    openPacks->setFixedSize(361, 41);
    frameLayout->addWidget(openPacks);
    connect(openPacks,&QPushButton::clicked,this,&MainMenuPage::on_OpenPacks);
    openPacks->setEnabled(false);

    openEditor = new QPushButton("Open Deck Editor", frame);
    openEditor->setFixedSize(361, 41);
    frameLayout->addWidget(openEditor);
    connect(openEditor,&QPushButton::clicked,this,&MainMenuPage::on_OpenEditor);
    openEditor->setEnabled(false);
}

void MainMenuPage::on_CreateProgression()
{
    QString currentPath = QDir::currentPath() + "/Data/ProgressionSaves";
    QString filePath = QFileDialog::getSaveFileName(this,"Save File",currentPath,"JSON Files (*.json)");
    if(!filePath.isEmpty()){
        m_playerData.fileName = QFileInfo(filePath).baseName();
        m_playerData.Create(filePath);
        enableDeckAndPacks();
        emit LoadCardInfo();
    }
    else{
        qDebug() << "No File Selected";
    }

}

void MainMenuPage::on_LoadProgression()
{
    QString currentPath = QDir::currentPath() + "/Data/ProgressionSaves";
    QString filePath = QFileDialog::getOpenFileName(this,"Open File",currentPath);
    if(!filePath.isEmpty()){
        m_playerData.Load(filePath);
        emit LoadCardInfo();
        enableDeckAndPacks();
    }
    else{
        qDebug() << "No File Selected";
    }  
}

void MainMenuPage::on_OpenPacks()
{
    emit OpenPacksPageClicked(1);
}

void MainMenuPage::on_OpenEditor()
{
    emit OpenEditorPageClicked(2);
}

void MainMenuPage::enableDeckAndPacks()
{
    if(!openPacks->isEnabled()) openPacks->setEnabled(true);
    if(!openEditor->isEnabled()) openEditor->setEnabled(true);
}

