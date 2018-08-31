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
#include "PluginMetaData.h"


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
PluginMetaData::PluginMetaData() {
    mDescription = "";
    mName        = "";
}


PluginMetaData::PluginMetaData(const QJsonObject& meta) {
    if(!meta.isEmpty()) {
        const QJsonObject& data = meta.value("MetaData").toObject();
        if(!data.isEmpty()) {
            mDescription = getString(data, "Description");
            mName        = getString(data, "Name");
        }
    }
}


PluginMetaData::PluginMetaData(const PluginMetaData& cpy) {
    mDescription = cpy.mDescription;
    mName        = cpy.mName;
}


QString PluginMetaData::getString(
    const QJsonObject& meta, const QString& keyword) {
    const QJsonValue& value = meta.value(keyword);
    if(value.isString()) {
        return value.toString();
    }
    return QString("");
}


}  // End namespace ndx
