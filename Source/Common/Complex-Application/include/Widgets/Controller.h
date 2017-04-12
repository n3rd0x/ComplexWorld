/**
 * Complex World - Research & Educational Project
 * Copyright (C) T.Sang Tran aka "Nerdox" <t.sang.tran@outlook.com>
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


#ifndef _Controller_h_
#define _Controller_h_


// Local includes
#include <ui_Controller.h>


namespace ndx {

 
/**
 * Controller widget.
 */
class Controller : public QWidget, public Ui::Controller {
	Q_OBJECT

public:
	// ************************************************************
	// Member Declarations
	// ************************************************************
    /**
     * Default constructor.
     * @param parent Parent widget.
     */
	Controller(QWidget* parent = nullptr);
    
	
	/**
	 * Default destructor.
	 */
	~Controller();


    /**
     * Set speed value.
     * @param ms Value in milliseconds.
     */
    void setSpeedValue(const int ms);


    /**
     * Timer.
     */
    QTimer* mTimer;




public slots:
    /**
     * Forward button clicked.
     */
    void forwardClicked();


    /**
     * Start button clicked.
     */
    void startClicked();


    /**
     * Stop button clicked.
     */
    void stopClicked();



protected:
    /**
     * @return Speed value.
     */
    int getSpeedValue();


    /**
     * Toggle enabling states based on start button.
     * @param state State of the start button.
     */
    void toggleButtons(const bool state);


    /**
     * Minimum speed in milliseconds.
     */
    int mMinimumSpeed;




}; // End class Controller


} // End namespace ndx


#endif // _Controller_h_
