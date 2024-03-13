#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QStackedWidget>
#include "CardInfo.h"
#include "DeckEditorPage.h"
#include "MainMenuPage.h"
#include "PackOpeningPage.h"
#include "PacksMenuPage.h"
#include "playerdata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    PacksMenuPage *packsMenuPage;
    DeckEditorPage *deckEditorPage;
    MainMenuPage *mainMenuPage;
    PackOpeningPage *packOpeningPage;


private slots:


    void on_OpenPage(int i);
    void on_SaveCards();
    void on_BackToMainPage();
    void on_BackToPackPage();
    void on_LoadCardInfo();
    void on_MoveToPackOpeningPage(QList<Card> cards, QString setName);

private:
    Ui::MainWindow *ui;
    PlayerData m_player;
    QMap<int,CardInfo> m_cards;
    QStackedWidget *stackedWidget;

    void LoadCards();
};
#endif // MAINWINDOW_H
