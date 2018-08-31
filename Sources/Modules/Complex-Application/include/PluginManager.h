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


#ifndef _PluginManager_h_
#define _PluginManager_h_


// Qt includes
#include <QPluginLoader>
#include <QtCore>


namespace ndx {


// ************************************************************
// Class Forward Declarations
// ************************************************************
class PluginMetaData;
class Plugin;


/**
 * Plug-in manager.
 */
class PluginManager : public QObject {
    Q_OBJECT

public:
    // ************************************************************
    // Structure Declarations
    // ************************************************************
    /**
     * Current loaded plug-in.
     */
    struct PluginPair {
        /**
         * Plug-in loader.
         */
        QPluginLoader* mLoader;


        /**
         * Current plug-in.
         */
        Plugin* mPlugin;
    } mCurrentPlugin;




    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    PluginManager();


    /**
     * Default destructor.
     */
    ~PluginManager();


    /**
     * @return Name of the current loaded plug-in.
     */
    QString getCurrentLoaded() const;


    /**
     * Load plug-in.
     * @param widget Widget to display into.
     * @param name Name of the plug-ins to load.
     * @return True if succeeded loaded.
     */
    bool load(QWidget* widget, const QString& name);


    /**
     * Scan for plug-ins.
     * @param Path to scan.
     * @return True if there's some plug-in to load..
     */
    bool scan(const QString& path);


    /**
     * Unload the plug-in.
     */
    void unload();




private:
    /**
     * List of plug-ins.
     */
    QHash<QString, QPluginLoader*> mPlugins;




signals:
    /**
     * Signal to populate scanned plug-in.
     * @param metaData Meta data of the plug-in.
     */
    void sPopulatePlugin(const PluginMetaData& metaData);


    /**
     * Signal that current plug-in has been removed.
     * @param name Name of the plug-in.
     */
    void sRemovePlugin(const QString& name);


    /**
     * Signal to sort the list.
     * @param state State for sorting.
     */
    void sSortPlugin(const bool state);


};  // End class PluginManager


}  // End namespace ndx


#endif  // _PluginManager_h_
