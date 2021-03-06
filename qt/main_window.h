/*****************************************************************************
 * Eliot
 * Copyright (C) 2008-2012 Olivier Teulière
 * Authors: Olivier Teulière <ipkiss @@ gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *****************************************************************************/

#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <string>
#include <QMainWindow>

#include <ui/main_window.ui.h>
#include "logging.h"
#include "play_model.h"


using std::string;


class GameSignals;
class Dictionary;
class Bag;
class Board;
class History;
class PublicGame;
class HistoryTabWidget;
class RackWidget;
class PlayerTabWidget;
class ScoreWidget;
class TrainingWidget;
class ToppingWidget;
class ArbitrationWidget;
class AuxWindow;
class TimerModel;
class QLabel;
class QAction;
class QPrinter;

class MainWindow: public QMainWindow
{
    DEFINE_LOGGER();
    Q_OBJECT;

public:
    MainWindow(QWidget *iParent = 0);
    ~MainWindow();

signals:
    void dicChanged(const Dictionary *iDic);

public slots:
    /// Display an error message to the user
    void displayErrorMsg(QString iMsg, QString iContext = "");
    void displayInfoMsg(QString iMsg);

protected:
    /// Handler for close events
    virtual void closeEvent(QCloseEvent * e);

private slots:
    void onGameNew();
    void onGameLoad();
    void onGameLoadAutoSave();
    void onGameSaveAs();
    void onGamePrintPreview();
    void onGamePrint();
    void onGameQuit();
    void onSettingsChooseDic();
    void onSettingsCreateDic();
    void onSettingsFavPlayers();
    void onSettingsDefineTables();
    void onSettingsPreferences();
    void onWindowsToolbar();
    void onWindowsBag();
    void onWindowsBoard();
    void onWindowsHistory();
    void onWindowsStatistics();
    void onWindowsTimer();
    void onWindowsDicTools();
    void onHelpAbout();

    void onHistoryFirstTurn();
    void onHistoryPrevTurn();
    void onHistoryNextTurn();
    void onHistoryLastTurn();
    void onHistoryReplayTurn();

    /// Print the game using the given printer
    void print(QPrinter *printer);

    /// Simply emit a beep with the system speakers
    void beep();

    /** Load a new dictionary */
    void changeDictionary(QString);

    /// Play the given word (all modes except topping)
    void playWord(const wstring &iWord, const wstring &iCoord);

    /** Perform some updates when the game is updated */
    void refresh();

    /** Perform work when the preferences were updated */
    void prefsUpdated();

    /** Select the correct tab in the history widget when the player changes */
    void onPlayerSelected(unsigned iPlayerId);

    /**
     * Perform several updates when the game changes (title bar, status bar,
     * grey out some menu items, ...)
     */
    void updateForGame(PublicGame *iGame);

    /// Update the status bar contents
    void updateStatusBar(const Dictionary *iDic);

    /** Show the definition of the given word */
    void showDefinition(QString iWord);

private:
    /// Current dictionary
    const Dictionary *m_dic;

    /// Current game
    PublicGame *m_game;

    GameSignals *m_gameSignals;

    /// The UI file generated with Qt Designer
    Ui::MainWindow m_ui;

    /// Widget for the game history
    HistoryTabWidget *m_historyTabWidget;

    /// Widget for the visual rack
    RackWidget *m_rackWidget;

    /// Widget for the players
    PlayerTabWidget *m_playersWidget;

    /// Widget for the training mode
    TrainingWidget *m_trainingWidget;

    /// Widget for the topping mode
    ToppingWidget *m_toppingWidget;

    /// Widget for the arbitration mode
    ArbitrationWidget *m_arbitrationWidget;

    /// Widget for the scores
    ScoreWidget *m_scoresWidget;

    /// Actions enabled or disabled depending on the game state
    QAction *m_actionGamePrintPreview;
    QAction *m_actionGamePrint;
    QAction *m_actionGameSaveAs;
    QAction *m_actionHistoryPrevTurn;
    QAction *m_actionHistoryNextTurn;
    QAction *m_actionHistoryFirstTurn;
    QAction *m_actionHistoryLastTurn;
    QAction *m_actionHistoryReplayTurn;
    QAction *m_actionWindowsToolbar;
    QAction *m_actionSettingsDefineTables;

    static const char * m_windowName;

    string m_autoSaveGame;

    /// Auxiliary windows
    //@{
    QAction *m_actionWindowsBag;
    AuxWindow *m_bagWindow;
    QAction *m_actionWindowsBoard;
    AuxWindow *m_boardWindow;
    QAction *m_actionWindowsHistory;
    AuxWindow *m_historyWindow;
    QAction *m_actionWindowsStats;
    AuxWindow *m_statsWindow;
    QAction *m_actionWindowsTimer;
    AuxWindow *m_timerWindow;
    QAction *m_actionWindowsDicTools;
    AuxWindow *m_dicToolsWindow;
    //@}

    /// Status bar label indicating the current turn (when there is a game)
    QLabel *m_turnLabel;
    /// Status bar label indicating the remaining letters (when there is a game)
    QLabel *m_lettersLabel;
    /// Status bar label indicating the name of the current dictionary
    QLabel *m_dicNameLabel;

    /// Model for the coordinates of the word to play
    PlayModel m_playModel;

    /// Model for the timer widgets
    TimerModel *m_timerModel;

    /// Save window state
    void writeSettings() const;
    /// Restore window state
    void readSettings();

    /// Helper function to easemenu creation
    QAction * addMenuAction(QMenu *menu, QString iText,
                            const QKeySequence &iShortcut,
                            QString iStatusTip, const char *iMember,
                            bool iCheckable = false, QIcon icon = QIcon());

    /// Create the menu bar and the actions
    void createMenu();

    /// Destroy the current game (if any) and the associated widgets
    void destroyCurrentGame();

    /**
     * Handle correctly the signal/slot connection between the Arbitration
     * widget and the 7+1 dictionary tool
     */
    void linkArbitrationAnd7P1();

    /// Handle the timer auto-start mechanism, depending on the preferences
    void linkRackChangesAndTimer();

    /**
     * Load the game saved in the given file. If iFileName is an empty string,
     * the auto-saved game will be loaded.
     */
    void loadGame(QString iFileName);

};

#endif

