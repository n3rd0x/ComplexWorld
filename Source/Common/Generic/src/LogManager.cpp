/**
 * Copyright (C) Augmenti AS
 *
 * Filename:    partLogManager.cpp
 * Author:      T.Sang Tran
 * Created:     2010-12-15
 *
 */


// Local includes
#include "partLogManager.h"
#include "partJsonUtil.h"
#include "partMacros.h"
#include "partStringConverter.h"
#include "partTimestamp.h"

// POCO includes
#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/SplitterChannel.h>
#if PART_PLATFORM == PART_PLATFORM_WINDOWS
    #include <Poco/Version.h>
#else
    #include <Poco/Foundation.h>
#endif


// Implementation from OGRE Singleton.
template <>
Augmenti::Part::LogManager*
    Ogre::Singleton<Augmenti::Part::LogManager>::msSingleton
    = nullptr;


namespace Augmenti {
namespace Part {


// ************************************************************
// Using Namespace
// ************************************************************
using Augmenti::Part::Utility::StringConverter;
using Augmenti::Part::Utility::Json::JsonUtil;




// ************************************************************
// Static Implementations
// ************************************************************
LogManager& LogManager::getSingleton() {
    return (*msSingleton);
}


LogManager* LogManager::getSingletonPtr() {
    return msSingleton;
}




// ************************************************************
// Class Implementations
// ************************************************************
LogManager::LogManager() : Singleton<LogManager>() {
    mLogger = nullptr;
    mLogManager     = nullptr;
    mPrefixEnabled  = false;
    mSuccessStarted = false;
    mUniqueFile     = false;
}


LogManager::~LogManager() {
    SAFE_CLEAN_POINTER(mLogManager);
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


void LogManager::logCritical(
    const std::string& msg, const std::string& prefix) {
    logCritical(mLogger, msg, prefix);
}


void LogManager::logCritical(
    Poco::Logger* logger, const std::string& msg, const std::string& prefix) {
    logMessage(logger, msg, Poco::Message::PRIO_CRITICAL, prefix);
}


void LogManager::logCriticalOgre(
    const std::string& msg, const std::string& prefix) {
    logMessageOgre(msg, Ogre::LogMessageLevel::LML_CRITICAL, prefix);
}


void LogManager::logNormal(const std::string& msg, const std::string& prefix) {
    logNormal(mLogger, msg, prefix);
}


void LogManager::logNormal(
    Poco::Logger* logger, const std::string& msg, const std::string& prefix) {
    logMessage(logger, msg, Poco::Message::PRIO_INFORMATION, prefix);
}


void LogManager::logNormalOgre(
    const std::string& msg, const std::string& prefix) {
    logMessageOgre(msg, Ogre::LogMessageLevel::LML_NORMAL, prefix);
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


void LogManager::logMessage(
    Poco::Logger* logger,
    const std::string& msg,
    Ogre::LogMessageLevel level,
    const std::string& prefix) {
    std::string mMsg = msg;
    if(mPrefixEnabled && !prefix.empty()) {
        mMsg = applyPrefix(msg, prefix);
    }
    logger->logMessage(mMsg, level);

    // TST 2014-03-05
    // As OGRE v1.9.0, in Windows, the debug output is now directed to the
    // console output of
    // Visual Studio and not the actual console. We makes the output also
    // directed to the
    // actual console window.
    //#if OGRE_DEBUG_MODE && OGRE_COMPILER == OGRE_COMPILER_MSVC
    // if(logger->isDebugOutputEnabled()) {
    //    std::lock_guard<std::mutex> lock(mConsoleMutex);
    //    level == Ogre::LML_CRITICAL ? std::cerr << mMsg << std::endl :
    //    std::cout << mMsg << std::endl;
    //}
    //#endif
}


void LogManager::logTrivial(const std::string& msg, const std::string& prefix) {
    logTrivial(mDefaultData.mLogger, msg, prefix);
}


void LogManager::logTrivial(
    Ogre::Log* logger, const std::string& msg, const std::string& prefix) {
    logMessage(logger, msg, Ogre::LML_TRIVIAL, prefix);
}


void LogManager::logTrivialOgre(
    const std::string& msg, const std::string& prefix) {
    if(mOgreData.mLogger) {
        logTrivial(mOgreData.mLogger, msg, prefix);
    }
}


void LogManager::removeLogger(const std::string& id) {
    if((id == ID_LOGGER_DEFAULT) || (id == ID_LOGGER_OGRE)) {
        return;
    }

    auto itr = mLoggers.find(id);
    if(itr != mLoggers.end()) {
        mLogManager->destroyLog(itr->second);
        mLoggers.erase(itr);
    }
}


void LogManager::shutDown() {
    if(!mSuccessStarted) {
        return;
    }

    // Clean up all created loggers.
    for(auto itr : mLoggers) {
        mLogManager->destroyLog(itr.second);
    }
    mLoggers.clear();

    // Clean up the OGRE logger if necessary.
    if(mOgreData.mLogger && mCreateOgreLogger) {
        mLogManager->destroyLog(mOgreData.mLogger);
    }

    // Delete default logger, only if not a default OGRE logger.
    if(mDefaultData.mLogger && (mDefaultData.mLogger != mOgreData.mLogger)) {
        mLogManager->destroyLog(mDefaultData.mLogger);
    }

    mDefaultData.mLogger = nullptr;
    mOgreData.mLogger    = nullptr;
    mSuccessStarted      = false;
}


bool LogManager::startUp(const Json::Value& opts) {
    if(mLogger) {
        return true;
    }

    // ----------------------------------------
    // Global
    // ----------------------------------------
    JsonUtil::getValue(opts, "OwnOgreLogger", mCreateOgreLogger);
    JsonUtil::getValue(opts, "PrefixEnable", mPrefixEnabled);
    JsonUtil::getValue(opts, "UniqueName", mUniqueFile);


    // ----------------------------------------
    // Default Logger
    // ----------------------------------------
    const Json::Value& oLog = opts["DefaultLogger"];
    if(oLog.isObject()) {
        JsonUtil::getValue(oLog, "FileName", mDefaultData.mFileName);
        JsonUtil::getValue(oLog, "ConsoleOutput", mDefaultData.mConsoleOutput);
        JsonUtil::getValue(
            oLog, "TimestampEnable", mDefaultData.mTimestampEnabled);
        JsonUtil::getValue(oLog, "ConsoleOutput", mDefaultData.mConsoleOutput);
        auto value = oLog["LoggingLevel"];
        if(value.isInt()) {
            mDefaultData.mLoggingLevel = (Ogre::LoggingLevel)value.asInt();
        }
    }


    // ----------------------------------------
    // OGRE Logger
    // ----------------------------------------
    const Json::Value& oOgre = opts["OgreLogger"];
    if(oOgre.isObject()) {
        JsonUtil::getValue(oOgre, "FileName", mOgreData.mFileName);
        JsonUtil::getValue(oOgre, "ConsoleOutput", mOgreData.mConsoleOutput);
        JsonUtil::getValue(
            oOgre, "TimestampEnable", mOgreData.mTimestampEnabled);
        JsonUtil::getValue(oOgre, "ConsoleOutput", mOgreData.mConsoleOutput);
        auto value = oOgre["LoggingLevel"];
        if(value.isInt()) {
            mOgreData.mLoggingLevel = (Ogre::LoggingLevel)value.asInt();
        }
    }
    
    
    
    if(mSuccessStarted) {
        return true;
    }

    // Determine whether the user has specified the file name.
    std::string dFileName = "";
    std::string baseName  = "";
    std::string extName   = "";

    // Extract base and extension of the file name.
    if(!mDefaultData.mFileName.empty()) {
        Ogre::StringUtil::splitBaseFilename(
            mDefaultData.mFileName, baseName, extName);

        // Should we create an unique log name?
        if(mUniqueFile) {
            dFileName = baseName + "_" + Timestamp::currentTime();
        }
        else {
            dFileName = baseName;
        }
    }



    // ----------------------------------------
    // OGRE Logger
    // ----------------------------------------
    // We create a new logger for OGRE related logging.
    if(mCreateOgreLogger || dFileName.empty()) {
        // First we find out whether we should the user specific file name or
        // we are going to use the default file name.
        std::string oFileName = mOgreData.mFileName;
        if(oFileName.empty()) {
            if(!dFileName.empty()) {
                oFileName
                    = dFileName + "_" + DEFAULT_FILENAME_OGRE + "." + extName;
            }
            else {
                oFileName = DEFAULT_FILENAME_OGRE;
                if(mUniqueFile) {
                    oFileName += "_" + Timestamp::currentTime();
                }
                oFileName += ".log";

                // If no "default logger" is specified by the user,
                // we will use the "default logger" settings.
                mOgreData.copyOptions(mDefaultData);
            }
        }

        // Create the logger for OGRE related message.
        mOgreData.create(ID_LOGGER_OGRE, oFileName, true, mLogManager);
    }


    // ----------------------------------------
    // Default Logger
    // ----------------------------------------
    // Create a new logger if necessary, otherwise use the OGRE logger.
    if(!dFileName.empty()) {
        // Find whether this should be the default logger or not.
        mDefaultData.create(
            ID_LOGGER_DEFAULT,
            dFileName + "." + extName,
            !mOgreData.mLogger,
            mLogManager);
    }
    else {
        mDefaultData.mLogger = mOgreData.mLogger;
    }

    // Flag for succeed.
    mSuccessStarted = true;
    return true;
}




// ************************************************************
// Class Member Implementations
// ************************************************************
LogManager::Data::Data() {
    mLogger           = nullptr;
    mTimestampEnabled = false;
    mFileName         = "";
    mId               = "";
    mLoggingLevel     = Ogre::LL_NORMAL;
    mConsoleOutput    = false;
}


void LogManager::Data::copyOptions(const Data& obj) {
    mTimestampEnabled = obj.mTimestampEnabled;
    mLoggingLevel     = obj.mLoggingLevel;
    mConsoleOutput    = obj.mConsoleOutput;
}


bool LogManager::Data::create(
    const std::string& id,
    const std::string& fName,
    const bool defaultLog,
    Ogre::LogManager* logMgr) {
    mId       = id;
    mFileName = fName;
    mLogger   = logMgr->createLog(fName, defaultLog, mConsoleOutput);
    if(mLogger) {
        mLogger->setTimeStampEnabled(mTimestampEnabled);
        mLogger->setLogDetail(mLoggingLevel);
        return true;
    }
    return false;
}


}  // End namespace Part
}  // End namespace Augmenti
