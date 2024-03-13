#ifndef MAINMENUPAGE_H
#define MAINMENUPAGE_H
#include "playerdata.h"

#include <QFrame>
#include <QObject>
#include <QPushButton>
#include <QWidget>

class MainMenuPage : public QFrame
{
    Q_OBJECT
public:
    explicit MainMenuPage(PlayerData &playerData, QWidget *parent = nullptr);

private slots:
    void on_CreateProgression();
    void on_LoadProgression();
    void on_OpenPacks();
    void on_OpenEditor();

signals:
    void OpenPacksPageClicked(int i);
    void OpenEditorPageClicked(int i);
    void LoadCardInfo();

private:
    PlayerData &m_playerData;
    std::multimap<QString, QString> packs;
    QPushButton *openPacks;
    QPushButton *openEditor;
    void enableDeckAndPacks();
};

#endif // MAINMENUPAGE_H
