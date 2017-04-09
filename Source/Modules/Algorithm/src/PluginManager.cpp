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


// Local includes
#include "PluginManager.h"
#include "Plugin.h"
#include "PluginMetaData.h"

// ndxLib includes
#include <ndxLogManager.h>

// Qt includes
#include <QLibrary>


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
PluginManager::PluginManager() {
    mCurrentPlugin.mLoader = nullptr;
    mCurrentPlugin.mPlugin = nullptr;
}


PluginManager::~PluginManager() {
    // Unload current plug-in if necessary and clean up.
    unload();

    for(auto& itr : mPlugins) {
        delete itr;
    }
    mPlugins.clear();
}


QString PluginManager::getCurrentLoaded() const {
    if(mCurrentPlugin.mPlugin) {
        return mCurrentPlugin.mPlugin->getMetaData().mName;
    }
    return QString();
}


bool PluginManager::load(QWidget* widget, const QString& name) {
    LOG_DEBUG_LEVEL_PREFIX(
        "Loading plug-in (" + name.toStdString() + ").", "PluginManager");

    auto& itr = mPlugins.find(name);
    if(itr != mPlugins.end()) {
        // Try to load the plug-in. If failed to load the plug-in
        // we will remove it from the list.
        QPluginLoader* loader = itr.value();
        Plugin* plugin        = qobject_cast<Plugin*>(loader->instance());
        if(plugin) {
            // Unload previous plug-in.
            unload();

            // Start the plug-in.
            plugin->setMetaData(PluginMetaData(loader->metaData()));
            if(plugin->startUp(widget)) {
                mCurrentPlugin.mLoader = loader;
                mCurrentPlugin.mPlugin = plugin;
                LOG_DEBUG_LEVEL_PREFIX(
                    "Successfully loading the plug-in.", "PluginManager");
                return true;
            }
        }
        else {
            emit sRemovePlugin(itr.key());
            delete loader;
            mPlugins.erase(itr);
            LOG_DEBUG_LEVEL_PREFIX("Plug-in is not valid.", "PluginManager");
        }
    }
    LOG_DEBUG_LEVEL_PREFIX("Failed loading the plug-in.", "PluginManager");
    return false;
}


void PluginManager::unload() {
    if(mCurrentPlugin.mPlugin) {
        LOG_DEBUG_LEVEL_PREFIX(
            "Unloading plug-in ("
                + mCurrentPlugin.mPlugin->getMetaData().mName.toStdString()
                + ").",
            "PluginManager");
        mCurrentPlugin.mPlugin->shutDown();
        mCurrentPlugin.mLoader->unload();
        mCurrentPlugin.mLoader = nullptr;
        mCurrentPlugin.mPlugin = nullptr;
    }
}


bool PluginManager::scan(const QString& path) {
    LOG_DEBUG_LEVEL_PREFIX(
        "Scanning for plug-ins in " + path.toStdString(), "PluginManager");

    QDir pPath(path);
    foreach(
        QFileInfo fileInfo,
        pPath.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
        QString fileName = fileInfo.absoluteFilePath();

        // Verify that the file is a dynamic library.
        LOG_DEBUG_LEVEL_PREFIX(
            "Checking current file: " + fileInfo.fileName().toStdString(),
            "PluginManager");
        if(QLibrary::isLibrary(fileName)) {
            QPluginLoader* loader = new QPluginLoader(fileName);

            // Retrieve name of the plug-in and add into the list.
            PluginMetaData meta(loader->metaData());
            if(!meta.mName.isEmpty()) {
                mPlugins[meta.mName] = loader;
                emit sPopulatePlugin(meta);
                LOG_DEBUG_LEVEL_PREFIX(
                    "Adding plug-in into the list.", "PluginManager");
            }
            else {
                LOG_WARNING_LEVEL_PREFIX(
                    "Plug-in missing name description.", "PluginManager");
                delete loader;
            }
        }
        else {
            LOG_DEBUG_LEVEL_PREFIX(
                "Skipping due to not valid plug-in file.", "PluginManager");
        }
    }

    bool res = (mPlugins.size() != 0);
    if(res) {
        emit sSortPlugin(true);
    }
    return res;
}


}  // End namespace ndx
