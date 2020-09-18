/**
 * Complex World - Research & Educational Project
 * Copyright (C) T.Sang Tran aka "n3rd0x" <nerdox.tranit@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef ndxWidget_h
#define ndxWidget_h


// Local includes
#include "Plugin.h"
#include "GameView.h"
#include "Cell.h"
#include <ui_Widget.h>

// ndxLibrary includes
#include <ndxPrerequisites.h>
#include <ndxNumberGenerator.h>

// STL includes
#include <string>

// Qt includes
#include <QList>
#include <QScopedPointer>


namespace ndx {


/**
 * Widget sample.
 */
class Widget : public Plugin, public Ui::uiWidget {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ndx.Algorithms.MiniMax" FILE "Description.json")
    Q_INTERFACES(ndx::Plugin)

public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    Widget();


    /**
     * Default destructor.
     */
    ~Widget();


    /**
     * Shutdown the plug-in.
     */
    void shutDown();


    /**
     * Start up the plug-in.
     * @return True on success.
     */
    bool startUp(QWidget* parent);


protected:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * @brief References.
     */
    QList<Cell*> mGameNodes;



    /**
     * @brief Logging tag.
     */
    static const std::string TAG;


protected slots:
    /**
     * @brief Clear.
     */
    void clear();


    /**
     * @brief Generate depth.
     */
    void generateDepth(const qint32 depth, Cell* parent);


    /**
     * @brief Generate values.
     */
    void generateValues();


    /**
     * @brief Item double clicked.
     * @param item Selected item.
     */
    void itemDoubleClicked(QListWidgetItem* item);


    /**
     * @brief New round.
     */
    void gameNewRound();


    /**
     * @brief Reset game.
     */
    void gameReset();


    /**
     * @brief Result the winner.
     * @param winner ID.
     */
    void gameWinner(qint32 winner);


    /**
     * @brief Proceed calcualtion.
     */
    void proceedCalcualtion();


    /**
     * @brief Restart calculation.
     */
    void restartCalculation();


    /**
     * Widget changed in the tab.
     */
    void tabChanged(int idx);


};  // End class Widget


}  // End namespace ndx


#endif  // ndxWidget_h
