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


#ifndef __EchoForm_h__
#define __EchoForm_h__


// Local includes
#include "Plugin.h"
#include <ui_EchoForm.h>


namespace ndx {

 
/**
 * Echo form sample.
 */
class EchoForm : public Plugin, public Ui::EchoForm {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "ndx.Algorithms.EchoForm" FILE "EchoForm.json")
	Q_INTERFACES(ndx::Plugin);

public:
	// ************************************************************
	// Member Declarations
	// ************************************************************
    /**
     * Default constructor.
     */
	EchoForm();
    
	
	/**
	 * Default destructor.
	 */
	~EchoForm();


	/**
	 * Shutdown the plug-in.
	 */
    void shutDown();


	/**
	 * Start up the plug-in.
	 * @return True on success.
	 */
    bool startUp(QWidget* parent);



protected slots:
	/**
	 * Display message.
	 */
	void displayMessage();


}; // End class EchoForm


} // End namespace ndx


#endif // __EchoForm_h__
