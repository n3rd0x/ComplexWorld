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


#ifndef __Util_h__
#define __Util_h__


// Qt includes
#include <QtCore>


namespace ndx {


/**
 * Utility.
 */
class Util {
public:
	// ************************************************************
	// Member Declarations
	// ************************************************************







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


}; // End class Util


} // End namespace ndx


#endif // __Util_h__
