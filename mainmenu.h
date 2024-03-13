#ifndef MAINMENU_H
#define MAINMENU_H

#include "playerdata.h"

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include <QDir>

namespace Ui {
class mainMenu;
}

class mainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr, PlayerData &playerData);
    ~mainMenu();

private:
    Ui::mainMenu *ui;

    PlayerData &m_player;

private slots:
    void on_CreateProgression();
    void on_LoadProgression();
    void on_OpenCardsPage();
};

#endif // MAINMENU_H
