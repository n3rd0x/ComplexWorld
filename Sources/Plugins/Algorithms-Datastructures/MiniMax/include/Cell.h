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


#ifndef ndxCell_h
#define ndxCell_h


// Qt includes
#include <QGraphicsItem>


namespace ndx {


/**
 * Cell node.
 */
class Cell : public QGraphicsItem {
public:
    // ************************************************************
    // Enumerator Declarations
    // ************************************************************
    enum class State : qint32 { NONE, X, O };



    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    Cell(const qint32 id = -1, const State state = State::NONE, QGraphicsItem* parent = nullptr);


    /**
     * Default destructor.
     */
    virtual ~Cell() override;


    /**
     * @brief Compare state.
     * @return True if state is equals.
     */
    bool isEquals(const Cell* other) const;


    /**
     * @return Occupied if selected as X or O.
     */
    bool isOccupied() const;


    /**
     * @return ID of this cell.
     */
    qint32 id() const;


    /**
     * @return Layout of current state.
     */
    std::string layout() const;


    /**
     * @return MiniMax value.
     */
    qint32 minimax() const;


    /**
     * @return Name of this cell.
     */
    QString name() const;


    /**
     * @brief Bounding box of current position.
     * @return Bounding box value.
     */
    QRectF posRect();


    /**
     * @brief Reset.
     */
    void reset();


    /**
     * @brief Set the MiniMax value.
     * @param value MiniMax value.
     */
    void setMiniMax(const qint32 value);


    /**
     * @brief Enable display MiniMax value.
     * @param value State value.
     */
    void setMiniMaxEnabled(const bool value);


    /**
     * @brief Set marking state.
     * @param state The marking state.
     */
    void setMarking(const bool state);


    /**
     * @brief Set occupied state.
     * @param state The occupied state.
     */
    void setOccupied(const bool state);


    /**
     * @brief Set state.
     * @param state State value.
     */
    void setState(const State state);


    /**
     * @return State.
     */
    State state() const;



    // ************************************************************
    // Inherited Member Declarations (QGraphicsItem)
    // ************************************************************
    /**
     * @see QGraphicsItem::boundingRect()
     */
    QRectF boundingRect() const override;


    /**
     * @see QGraphicsItem::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @brief Size of the cell.
     */
    static const qint32 SIZE;


    /**
     * @brief Parse the state.
     * @param state State to parse.
     * @return String presentation.
     */
    static std::string parseState(Cell::State state);


protected:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * @brief References.
     */
    qint32 mID;
    bool mMarking;
    qint32 mMiniMax;
    bool mMiniMaxEnabled;
    bool mOccupied;
    State mState;



    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @brief Logging tag.
     */
    static const std::string TAG;



protected slots:



};  // End class Cell


}  // End namespace ndx


#endif  // ndxCell_h
