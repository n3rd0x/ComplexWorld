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
#include "MetaData.h"

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


bool PluginManager::load(QWidget* widget, const QString& name) {
	auto& itr = mPlugins.find(name);
	if(itr != mPlugins.end()) {
		// Try to load the plug-in. If failed to load the plug-in
		// we will remove it from the list.
		QPluginLoader* loader = itr.value();
		Plugin* plugin = qobject_cast<Plugin*>(loader->instance());
		if(plugin) {
            // Unload previous plug-in.
            unload();

            // Start the plug-in.
			plugin->setMetaData(MetaData(loader->metaData()));
			if(plugin->startUp(widget)) {
				mCurrentPlugin.mLoader = loader;
				mCurrentPlugin.mPlugin = plugin;
				return true;
			}
		}
		else {
			emit signalToRemovePlugin(itr.key());
			delete loader;
			mPlugins.erase(itr);
		}
	}
	return false;
}


void PluginManager::unload() {
	if(mCurrentPlugin.mPlugin) {
		mCurrentPlugin.mPlugin->shutDown();
		mCurrentPlugin.mLoader->unload();
		mCurrentPlugin.mLoader = nullptr;
		mCurrentPlugin.mPlugin = nullptr;
	}
}


bool PluginManager::scan(const QString& path) {
	QDir pPath(path);
	foreach(QFileInfo fileInfo, pPath.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
		QString fileName = fileInfo.absoluteFilePath();

		// Verify that the file is a dynamic library.
		if(QLibrary::isLibrary(fileName)) {
			QPluginLoader* loader = new QPluginLoader(fileName);

			// Retrieve name of the plug-in and add into the list.
			MetaData meta(loader->metaData());
			if(!meta.mName.isEmpty()) {
				mPlugins[meta.mName] = loader;
				emit signalToPopulatePlugin(meta);
			}
			else {
				delete loader;
			}
		}
	}

	bool res = (mPlugins.size() != 0);
    if(res) {
        emit signalToSort(true);
    }
    return res;
}


} // End namespace ndx
