#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainMenu)
{
    ui->setupUi(this);

    connect(ui->createProgression, &QPushButton::clicked,this,&mainMenu::on_CreateProgression);
    connect(ui->loadProgression, &QPushButton::clicked,this,&mainMenu::on_LoadProgression);
    connect(ui->openPacks, &QPushButton::clicked,this,&mainMenu::on_OpenCardsPage);

}

mainMenu::mainMenu(QWidget *parent, PlayerData &playerData)
{
    m_player = &playerData;
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::on_CreateProgression()
{
    QString currentPath = QDir::currentPath() + "/Data/ProgressionSaves";
    QString filePath = QFileDialog::getSaveFileName(this,"Save File",currentPath,"JSON Files (*.json)");
    m_player.fileName = QFileInfo(filePath).baseName();
    qDebug() << filePath;
    m_player.Save(filePath);

    qDebug() << "Creation Clicked";
}

void mainMenu::on_LoadProgression()
{
    QString currentPath = QDir::currentPath() + "/Data/ProgressionSaves";
    QString filePath = QFileDialog::getOpenFileName(this,"Open File",currentPath);
    if(!filePath.isEmpty()){
        qDebug() << "Selected File: " << filePath;
        m_player.Load(filePath);
    }
    else{
        qDebug() << "No File Selected";
    }

    qDebug() << "Load Clicked";
}

void mainMenu::on_OpenCardsPage()
{
    ui->stackedWidget->setCurrentIndex(1);
}
