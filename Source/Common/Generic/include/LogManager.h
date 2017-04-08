/**
 * Copyright (C) Augmenti AS
 *
 * Filename:    partLogManager.h
 * Author:      T.Sang Tran
 * Created:     2010-12-15
 * Modified:    2017-04-07 (Update to Poco library)
 *
 */


#ifndef _partLogManager_h_
#define _partLogManager_h_


// Local includes
#include "partPrerequisites.h"

// OGRE includes
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreSingleton.h>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Message.h>

// Json includes
#include <json/json.h>


namespace Augmenti {
namespace Part {


/**
 * A logging manager.
 */
class _PartExport LogManager : Ogre::Singleton<LogManager> {
public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    LogManager();


    /**
     * Default destructor.
     */
    virtual ~LogManager();


    /**
     * Create an independent logger.
     * @param id ID to identify the logger.
     * @param fName File name.
     * @param timestamp Enable timestamp.
     * @param level Set logging level.
     * @return A Poco::Logger object.
     */
    Poco::Logger* createLogger(
        const std::string& id,
        const std::string& fName,
        const bool consoleOutput            = false,
        const bool timestamp                = false,
        const Poco::Message::Priority level = Poco::Message::PRIO_INFORMATION);


    /**
     * @return The Poco::Logger is exists, otherwise return nullptr.
     */
    Poco::Logger* getLogger(const std::string& id);


    /**
     * Log message with critical message level.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logCritical(const std::string& msg, const std::string& prefix = "");


    /**
     * Log message with critical message level.
     * @param logger Logger to process.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logCritical(
        Poco::Logger* logger,
        const std::string& msg,
        const std::string& prefix = "");


    /**
     * Log message as OGRE related with critical message level.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logCriticalOgre(
        const std::string& msg, const std::string& prefix = "");


    /**
     * Log message with normal message level.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logNormal(const std::string& msg, const std::string& prefix = "");


    /**
     * Log message with normal message level.
     * @param logger Logger to process.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logNormal(
        Poco::Logger* logger,
        const std::string& msg,
        const std::string& prefix = "");


    /**
     * Log message as OGRE related with normal message level.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logNormalOgre(const std::string& msg, const std::string& prefix = "");


    /**
     * Log the message at message level.
     * @param msg Message to log.
     * @param level Log message level. Default is PRIO_INFORMATION.
     * @param prefix Prefix to apply. Default is "".
     */
    void logMessage(
        const std::string& msg,
        const Poco::Message::Priority level = Poco::Message::PRIO_INFORMATION,
        const std::string& prefix           = "");


    /**
     * Log the message at message level.
     * @param logger Logger to process.
     * @param msg Message to log.
     * @param level Log message level. Default is PRIO_INFORMATION.
     * @param prefix Prefix to apply. Default is "".
     */
    void logMessage(
        Poco::Logger* logger,
        const std::string& msg,
        const Poco::Message::Priority level = Poco::Message::PRIO_INFORMATION,
        const std::string& prefix           = "");


    /**
     * Log message as OGRE related with specified message level..
     * @param logger Logger to process.
     * @param msg Message to log.
     * @param level Log message level. Default is LML_NORMAL.
     * @param prefix Prefix to apply. Default is "".
     */
    void logMessageOgre(
        const std::string& msg,
        const Ogre::LogMessageLevel level = Ogre::LML_NORMAL,
        const std::string& prefix         = "");


    /**
     * Log message with trivial message level.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logTrivial(const std::string& msg, const std::string& prefix = "");


    /**
     * Log message with trivial message level.
     * @param logger Logger to process.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logTrivial(
        Poco::Logger* logger,
        const std::string& msg,
        const std::string& prefix = "");


    /**
     * Log message as OGRE related with trivial message level.
     * @param msg Message to log.
     * @param prefix Prefix to apply.
     */
    void logTrivialOgre(const std::string& msg, const std::string& prefix = "");


    /**
     * Remove logger.
     * @param id ID to identify.
     */
    void removeLogger(const std::string& id);


    /**
     * Shutdown the manager.
     */
    void shutDown();


    /**
     * Start up the manager.
     * @param opts List of options.
     * <pre>
     * <b>Global:</b>
     * [Prefix]             = (Boolean)     Enable prefix in the log.
     * [UniqueFile]         = (Boolean)     Create the file based on timestamp.
     * <b>DefaultLogger:</b>
     * [FileName]           = (String)      File name.
     * [ConsoleOutput]      = (Boolean)     Enable console output.
     * [TimestampEnable]    = (Boolean)     Enable date and time.
     * [LoggingLevel]       = (String)      Logging level value.
     *      Available values:
     *          * PRIO_FATAL        A fatal error.
     *          * PRIO_CRITICAL     A critical error.
     *          * PRIO_ERROR        An error.
     *          * PRIO_WARNING      A warning.
     *          * PRIO_NOTICE       A notice.
     *          * PRIO_INFORMATION  An informational message (default).
     *          * PRIO_DEBUG        A debugging message.
     *          * PRIO_TRACE        A tracing message.
     * <b>OgreLogger:</b>
     * [ConsoleOutput]      = (Boolean)     Enable console output.
     * [LoggingLevel]       = (String)      Logging level value.
     *      Available values:
     *          * LL_BOREME     Maximum level.
     *          * LL_LOW        Minimum level.
     *          * LL_NORMAL     Normal level (default).
     * </pre>
     * @return True on success.
     */
    bool startUp(const Json::Value& opts);




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @copy Singleton::getSingleton()
     */
    static LogManager& getSingleton();


    /**
     * @copy Singleton::getSingletonPtr()
     */
    static LogManager* getSingletonPtr();




protected:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Apply prefix to the message.
     * @param msg Origin message.
     * @param prefix Prefix to apply.
     * @return Message with the prefix.
     */
    std::string applyPrefix(
        const std::string& msg, const std::string& prefix = "");


    /**
     * Our main Poco::Logger.
     */
    Poco::Logger* mLogger;


    /**
     * An Ogre::LogManager object.
     */
    Ogre::LogManager* mLogManager;


    /**
     * Flag for using prefix.
     */
    bool mPrefixEnabled;


    /**
     * Flag that indicates the manager is successfully started up.
     */
    bool mSuccessStarted;


    /**
     * Flag for using unique file.
     */
    bool mUniqueFile;


};  // End class LogManager




// ************************************************************
// Macro Definition Declarations
// ************************************************************
// clang-format off
#define LOG_MANAGER Augmenti::Part::LogManager::getSingletonPtr()
#define LOG_CRITICAL_LEVEL(msg)                         LOG_MANAGER->logCritical(msg);
#define LOG_CRITICAL_LEVEL_PREFIX(msg, prefix)          LOG_MANAGER->logCritical(msg, prefix);
#define LOG_NORMAL_LEVEL(msg)                           LOG_MANAGER->logNormal(msg);
#define LOG_NORMAL_LEVEL_PREFIX(msg, prefix)            LOG_MANAGER->logNormal(msg, prefix);
#define LOG_TRIVIAL_LEVEL(msg)                          LOG_MANAGER->logTrivial(msg);
#define LOG_TRIVIAL_LEVEL_PREFIX(msg, prefix)           LOG_MANAGER->logTrivial(msg, prefix);
#define LOG_MESSAGE_CRITICAL(log, msg)                  LOG_MANAGER->logCritical(log, msg);
#define LOG_MESSAGE_CRITICAL_PREFIX(log, msg, prefix)   LOG_MANAGER->logCritical(log, msg, prefix);
#define LOG_MESSAGE_NORMAL(log, msg)                    LOG_MANAGER->logNormal(log, msg);
#define LOG_MESSAGE_NORMAL_PREFIX(log, msg, prefix)     LOG_MANAGER->logNormal(log, msg, prefix);
#define LOG_MESSAGE_TRIVIAL(log, msg)                   LOG_MANAGER->logTrivial(log, msg);
#define LOG_MESSAGE_TRIVIAL_PREFIX(log, msg, prefix)    LOG_MANAGER->logTrivial(log, msg, prefix);
#define LOG_OGRE_CRITICAL(msg)                          LOG_MANAGER->logCriticalOgre(msg);
#define LOG_OGRE_CRITICAL_PREFIX(msg, prefix)           LOG_MANAGER->logCriticalOgre(msg, prefix);
#define LOG_OGRE_NORMAL(msg)                            LOG_MANAGER->logNormalOgre(msg);
#define LOG_OGRE_NORMAL_PREFIX(msg, prefix)             LOG_MANAGER->logNormalOgre(msg, prefix);
#define LOG_OGRE_TRIVIAL(msg)                           LOG_MANAGER->logTrivialOgre(msg);
#define LOG_OGRE_TRIVIAL_PREFIX(msg, prefix)            LOG_MANAGER->logTrivialOgre(msg, prefix);
// clang-format on


}  // End namespace Part
}  // End namespace Augmenti


#endif  // _partLogManager_h_
