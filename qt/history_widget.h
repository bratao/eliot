/*****************************************************************************
 * Eliot
 * Copyright (C) 2008 Olivier Teulière
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

#ifndef HISTORY_WIDGET_H_
#define HISTORY_WIDGET_H_

#include <QtGui/QTreeView>
#include <QtGui/QTabWidget>


class History;
class Game;
class QStandardItemModel;
class QTabWidget;

class HistoryWidget: public QTreeView
{
    Q_OBJECT;

public:
    explicit HistoryWidget(QWidget *parent = 0);

    void setHistory(const History *iHistory = NULL,
                    bool iIsForPlayer = false);

public slots:
    void refresh();

private:
    /// Encapsulated history, can be NULL
    const History *m_history;

    /**
     * Flag to avoid displaying the "players" column when the History object
     * is precisely associated to a Player
     */
    bool m_forPlayer;

    /// Model of the history
    QStandardItemModel *m_model;

    /// Force synchronizing the model with the contents of the history
    void updateModel();
};


class HistoryTabWidget: public QTabWidget
{
    Q_OBJECT;

public:
    explicit HistoryTabWidget(QWidget *parent = NULL);

public slots:
    void setGame(const Game *iGame);
    void refresh();

signals:
    void refreshSignal();

protected:
    virtual QSize sizeHint() const;

private:
    /// Encapsulated game, can be NULL
    const Game *m_game;

    /**
     * HistoryWidget for the game: we reuse it instead of creating and
     * destroying it every time
     */
    HistoryWidget *m_gameHistoryWidget;
};

#endif
