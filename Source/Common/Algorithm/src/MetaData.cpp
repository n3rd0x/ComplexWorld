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
#include "MetaData.h"


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
MetaData::MetaData() {
	mDescription = "";
	mName        = "";
}


MetaData::MetaData(const QJsonObject& meta) {
	if(!meta.isEmpty()) {
		const QJsonObject& data = meta.value("MetaData").toObject();
		if(!data.isEmpty()) {
			mDescription = getString(data, "Description");
			mName        = getString(data, "Name");
		}
	}
}


MetaData::MetaData(const MetaData& cpy) {
	mDescription = cpy.mDescription;
	mName        = cpy.mName;
}


MetaData::MetaData(MetaData&& mv) {
	mDescription = std::move(mDescription);
	mName        = std::move(mName);
}


QString MetaData::getString(const QJsonObject& meta, const QString& keyword) {
	const QJsonValue& value = meta.value(keyword);
	if(value.isString()) {
		return value.toString();
	}
	return QString("");
}


} // End namespace ndx

