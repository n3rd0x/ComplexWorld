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


#ifndef __MainWindow_h__
#define __MainWindow_h__


// Qt includes
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>

// Local includes
#include <ui_MainWindow.h>


namespace ndx {


// ************************************************************
// Class Forward Declarations
// ************************************************************
class MetaData;
class PluginManager;




/**
 * Main window.
 */
class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT

public:
	// ************************************************************
	// Member Declarations
	// ************************************************************
	/**
	 * Default destructor.
	 * @param parent Parent of this window.
	 * @param flags Window flags.
	 */
    MainWindow(QWidget* parent = 0x0, Qt::WindowFlags flags = 0);
    
	
	/**
	 * Default destructor.
	 */
	virtual ~MainWindow();


	/**
	 * Setup the window.
	 * @param aLangs Available languages.
	 * @param pDir Plug-in directory.
	 * @return True on success.
	 */
    bool setup(const QStringList& aLangs, const QString& pDir);


signals:
	/**
	 * Signal to close.
	 */
    void signalToClose();


	/**
	 * Signal to retranslate.
	 */
    void signalToRetranslate();


	/**
	 * Signal to change the language.
	 * @param language Language to change to.
	 */
    void signalToLanguageChanged(QAction* language);


private:
	/**
	 * @see QWidget::changeEvent(QEvent*)
	 * Retranslate if necessary.
	 */
	//void changeEvent(QEvent* evt);


	/**
	 * @see QWidget::closeEvent(QCloseEvent*)
	 */
	//void closeEvent(QCloseEvent* evt);


	/**
	 * Initialise pointers.
	 */
    void initPointers();


	/**
	 * Initialise values.
	 */
    void initValues();


	/**
	 * Retranslate.
	 */
    void retranslate();


	/**
	 * Setup connections.
	 * @return True on success.
	 */
    bool setupConnections();


	/**
	 * Setup default settings.
	 * @return True on success.
	 */
    bool setupDefaultSettings();


	/**
	 * Setup languages.
	 * @param list List of available languages.
	 * @param dLang Desired language.
	 * @return True on success.
	 */
    //bool setupLanguages(const QStringList& list, const QString& dLang = "");


	/**
	 * Setup objects.
	 * @return True on success.
	 */
    bool setupObjects();


	/**
	 * Translate for this window.
	 * @param str String to translate.
	 * @return The translated string.
	 */
    QString translate(const QString& str);


    /**
     * Current loaded plug-in.
     */
    QString mCurrentPlugin;


	/**
	 * Group of languages.
	 */
    QActionGroup* mLanguages;


	/**
	 * Plug-in manager.
	 */
	PluginManager* mPluginManager;
    
        

private slots:
	/**
	 * Change language.
	 * @param language Language to change to.
	 */
    void changeLanguage(QAction* language);


	/**
	 * Load selected plug-in.
	 */
	void loadPlugin();


    /**
     * Load plug-in based on selected item.
     * @param item Selected item.
     */
    void loadPlugin(QListWidgetItem* item);


	/**
	 * Populate plug-in.
	 * @param meta Meta data of the plug-in.
	 */
	void populatePlugin(const MetaData& meta);


    /**
     * Remove plug-in.
     * @param name Name of the plug-in.
     */
    void removePlugin(const QString& name);


    /**
     * Sort the list of samples.
     * @param state State for sorting.
     */
    void sortSampleList(const bool state);


    /**
     * Toggle enabling state of the load / unload buttons.
     * @param state Enabling state of the load button.
     */
    void toggleLoadAndUnloadButtons(const bool state);


	/**
	 * Unload selected plug-in.
	 */
    void unloadPlugin();


}; // End class MainWindow


} // End namespace ndx


#endif // __MainWindow_h__