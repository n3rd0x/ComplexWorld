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
#include "ndxLogManager.h"

// POCO includes
#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/SplitterChannel.h>
#if _WIN32
    #include <Poco/Version.h>
#else
    #include <Poco/Foundation.h>
#endif



namespace ndx {


// ************************************************************
// Static Implementations
// ************************************************************
template<> LogManager* Singleton<LogManager>::mSingleton = nullptr;
LogManager* LogManager::getSingleton() {
    return mSingleton;
}




// ************************************************************
// Class Implementations
// ************************************************************
LogManager::LogManager() {
    mLogger = nullptr;
    mPrefixEnabled  = false;
}


LogManager::~LogManager() {

}


std::string LogManager::applyPrefix(
    const std::string& msg, const std::string& prefix) {
    if(!prefix.empty()) {
        return std::string("[" + prefix + "] " + msg);
    }
    return msg;
}


Poco::Logger* LogManager::createLogger(
    const std::string& id,
    const std::string& fName,
    const bool consoleOutput,
    const bool timestamp,
    const Poco::Message::Priority level) {
    if(fName.empty()) {
        return nullptr;
    }

    if(mLogger && id.empty()) {
        return mLogger;
    }

    Poco::AutoPtr<Poco::FileChannel> fc(new Poco::FileChannel());
    fc->setProperty("path", fName);
    fc->setProperty("rotation", "5 M");
    fc->setProperty("archive", "number");
    fc->setProperty("purgeCount", "2");
#if POCO_VERSION >= 0x01070700
    fc->setProperty("rotateOnOpen", "true");
#endif

    Poco::AutoPtr<Poco::PatternFormatter> pf(new Poco::PatternFormatter());
    pf->setProperty("pattern", "%Y-%m-%dT%H:%M:%S %t");

    Poco::AutoPtr<Poco::FormattingChannel> pfc(new Poco::FormattingChannel(pf, fc));

    if(consoleOutput) {
        Poco::AutoPtr<Poco::ConsoleChannel> cc(new Poco::ConsoleChannel());
        Poco::AutoPtr<Poco::SplitterChannel> sc(new Poco::SplitterChannel());
        sc->addChannel(cc);
        sc->addChannel(pfc);

        return &(Poco::Logger::create(id, sc, level));
    }
    
    return &(Poco::Logger::create(id, fc, level));
}


Poco::Logger* LogManager::getLogger(const std::string& id) {
    return Poco::Logger::has(id);
}


void LogManager::logMessage(
    const std::string& msg,
    const Poco::Message::Priority level,
    const std::string& prefix) {
    logMessage(mLogger, msg, level, prefix);
}


void LogManager::logMessage(
    Poco::Logger* logger,
    const std::string& msg,
    const Poco::Message::Priority level,
    const std::string& prefix) {
    auto mMsg = msg;
    if(mPrefixEnabled && !prefix.empty()) {
        mMsg = applyPrefix(msg, prefix);
    }
    switch(level) {
    case Poco::Message::Priority::PRIO_CRITICAL:
        logger->critical(mMsg);
    break;
    default:
        logger->information(mMsg);
    }
}


void LogManager::removeLogger(const std::string& id) {
    //if((id == ID_LOGGER_DEFAULT) || (id == ID_LOGGER_OGRE)) {
    //    return;
    //}

    //auto itr = mLoggers.find(id);
    //if(itr != mLoggers.end()) {
    //    mLogManager->destroyLog(itr->second);
    //    mLoggers.erase(itr);
    //}
}


}  // End namespace ndx

