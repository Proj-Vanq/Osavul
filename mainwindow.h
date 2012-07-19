/*
* This file is part of Osavul.
*
* Osavul is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Osavul is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Osavul.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "channel.h"
#include "ircclient.h"
#include "unv.h"
#include "connectiondialog.h"
#include "richtextdelegate.h"
#include "settingsdialog.h"
#include <QMainWindow>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QProcess>
#include <QTableWidgetItem>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSignalMapper>
#include <QInputDialog>
#include <QTreeWidgetItem>
#include <QSignalMapper>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_refreshButton_clicked();
    void enableRefreshButton();
    void enableSyncButton();
    void on_joinButton_clicked();
    void on_syncButton_clicked();
    void on_serverTable_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *);

    void on_actionRestore_triggered();
    void on_actionQuit_triggered();
    void on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason);

    void on_showSpectatorsButton_clicked(bool checked);
    void on_playerFilterLineEdit_textEdited(const QString &arg1);
    void on_serverTable_itemChanged(QTableWidgetItem *item);

    void on_ircConnectButton_clicked();
    void on_ircJoinButton_clicked();
    void on_ircNickButton_clicked();
    void on_ircQueryButton_clicked();
    void on_ircTabWidget_tabCloseRequested(int index);
    void on_actionAdd_to_Favorites_triggered();
    void on_ircChat_addStringToChannel(Channel *channel, const QString &string);
    void on_filterBar_textEdited(const QString &arg1);
    void on_actionAbout_Osavul_triggered();
    void on_actionAbout_Qt_triggered();
    void connectTo(const QString &host);

    void on_actionPreferences_triggered();

public slots:
    void on_ircChat_serverCommMessage(const QString &s);
    void handle_unvanquished_queried(unv::GameServer *svNew);

private:
    void updateTeamTables(const QList<unv::Player> &playerList);

signals:
    void startIrcThread();
    void ircChangeNick(const QString &nick);
    void ircOpenQuery(const QString &user);

private:
    QList<unv::FavoriteEntry> favorites;
    QSettings settings;

    Ui::MainWindow *ui;
//    QThread *unvThread;
//    QThread *ircThread;
    QProcess *gameProc;
    QHash<unv::GameServer *, QTableWidgetItem *> gameServersShown;

    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;

    unv::MasterServer msv;
    IrcClient *chat;
};

#endif // MAINWINDOW_H
