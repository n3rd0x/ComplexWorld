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


#ifndef ndxPluginMetaData_h
#define ndxPluginMetaData_h


// Qt includes
#include <QtCore>


namespace ndx {


/**
 * Meta data for plugin.
 */
class PluginMetaData {
public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    PluginMetaData();


    /**
     * Initialise meta data.
     * @param meta Meta data to parse.
     */
    PluginMetaData(const QJsonObject& meta);


    /**
     * Description.
     */
    QString mDescription;


    /**
     * Long name.
     */
    QString mName;




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * Retrieve value.
     * @param meta Meta data.
     * @param keyword Keyword for the meta value.
     * @return Value of the meta data if exists. Otherwise return "".
     */
    static QString getString(const QJsonObject& meta, const QString& keyword);


};  // End class PluginMetaData


}  // End namespace ndx


#endif  // ndxPluginMetaData_h
