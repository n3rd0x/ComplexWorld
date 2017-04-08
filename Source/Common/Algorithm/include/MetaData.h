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


#ifndef __MetaData_h__
#define __MetaData_h__


// Qt includes
#include <QtCore>


namespace ndx {


/**
 * Meta data.
 */
class MetaData {
public:
	// ************************************************************
	// Member Declarations
	// ************************************************************
	/**
	 * Default constructor.
	 */
	MetaData();


    /**
     * Initialise meta data.
	 * @param meta Meta data to parse.
     */
	MetaData(const QJsonObject& meta);


	/**
	 * Copy constructor.
	 * @param cpy MetaData to copy from.
	 */
	MetaData(const MetaData& cpy);


	/**
	 * Move constructor.
	 * @param mv MetaData to be moved.
	 */
	MetaData(MetaData&& mv);
    
	
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


}; // End class MetaData


} // End namespace ndx


#endif // __MetaData_h__
