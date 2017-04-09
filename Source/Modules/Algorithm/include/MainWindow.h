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


#ifndef _MainWindow_h_
#define _MainWindow_h_


// Qt includes
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

// Local includes
#include <ui_MainWindow.h>


namespace ndx {


// ************************************************************
// Class Forward Declarations
// ************************************************************
class PluginMetaData;
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
    MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = 0);


    /**
     * Default destructor.
     */
    virtual ~MainWindow();


    /**
     * Setup the window.
     * @param pDir Plug-in directory.
     * @return True on success.
     */
    bool setup(const QString& pDir);




signals:
    /**
     * Signal to close.
     */
    void signalToClose();




protected:
    /**
     * Initialise pointers.
     */
    void initPointers();


    /**
     * Initialise values.
     */
    void initValues();


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
     * Setup objects.
     * @return True on success.
     */
    bool setupObjects();


    /**
     * Current loaded plug-in.
     */
    QString mCurrentPlugin;


    /**
     * Plug-in manager.
     */
    PluginManager* mPluginManager;




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @param item Item to process.
     * @param highlight Flag highlighting the item.
     * @return Font for display plug-ins.
     */
    static QFont setFont(QListWidgetItem* item, bool highlight);



private slots:
    /**
     * Check selected plug-in.
     */
    void checkPlugin(QListWidgetItem* item);


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
    void populatePlugin(const PluginMetaData& meta);


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


};  // End class MainWindow


}  // End namespace ndx


#endif  // _MainWindow_h_
