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


#ifndef ndxGameView_h
#define ndxGameView_h


// Local includes
#include "Cell.h"

// Qt includes
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>


namespace ndx {


/**
 * Game graphics view.
 */
class GameView : public QGraphicsView {
    Q_OBJECT

public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    GameView(QWidget* parent = nullptr);


    /**
     * @brief Default destructor.
     */
    virtual ~GameView() override;


    /**
     * @brief New round.
     */
    void newRound();


    /**
     * @brief Run MiniMAx.
     */
    void runMiniMax();


    /**
     * Shutdown the scene.
     */
    void shutDown();


    /**
     * Start up the scene.
     * @return True on success.
     */
    bool startUp();


protected:
    // ************************************************************
    // Inherited Member Declarations (QGraphicsView)
    // ************************************************************
    /**
     * @see QGraphicsView::mouseDoubleClickEvent(QMouseEvent*)
     */
    void mouseDoubleClickEvent(QMouseEvent* evt) override;


    /**
     * @see QGraphicsView::mouseMoveEvent(QMouseEvent*)
     */
    void mouseMoveEvent(QMouseEvent* evt) override;




    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * @brief Check winner condition.
     * @return Result value:
     *         -1  => Nothing
     *          0  => Tie
     *          1  => Player A
     *          2  => Player B
     */
    qint32 checkWinner();


    /**
     * @return Current state.
     */
    Cell::State currentState() const;


    /**
     * @brief Draw current board state.
     */
    void drawBoardState();



    QPair<qint32, qint32> minimax(const Cell::State state, const qint32 depth = 0);


    /**
     * @brief References.
     */
    QList<Cell*> mCells;
    qint32 mCellMarked;
    Cell* mCellMarking;
    bool mDebug;
    bool mGameOver;
    bool mPlayerX;
    qint32 mSize;
    QScopedPointer<QGraphicsScene> mScene;



    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @brief Logging tag.
     */
    static const std::string TAG;


signals:
    void sWinner(qint32 winner);


};  // End class GameView


}  // End namespace ndx


#endif  // ndxGameView_h
