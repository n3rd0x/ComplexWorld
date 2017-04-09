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


#ifndef _ndxLogManager_h_
#define _ndxLogManager_h_


// Local includes
#include "ndxPrerequisites.h"
#include "ndxSingleton.h"

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Message.h>


namespace ndx {


/**
 * A logging manager.
 */
class _ndxLibExport LogManager : public Singleton<LogManager> {
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
     * Remove logger.
     * @param id ID to identify.
     */
    void removeLogger(const std::string& id);




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @return LogManager instance.
     */
    static LogManager* getSingleton();



    
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
     * Flag for using prefix.
     */
    bool mPrefixEnabled;


    /**
     * Flag for using unique file.
     */
    bool mUniqueFile;


};  // End class LogManager




// ************************************************************
// Macro Definition Declarations
// ************************************************************
// clang-format off
//#define LOG_MANAGER Augmenti::Part::LogManager::getSingletonPtr()
//#define LOG_CRITICAL_LEVEL(msg)                         LOG_MANAGER->logCritical(msg);
//#define LOG_CRITICAL_LEVEL_PREFIX(msg, prefix)          LOG_MANAGER->logCritical(msg, prefix);
//#define LOG_NORMAL_LEVEL(msg)                           LOG_MANAGER->logNormal(msg);
//#define LOG_NORMAL_LEVEL_PREFIX(msg, prefix)            LOG_MANAGER->logNormal(msg, prefix);
//#define LOG_TRIVIAL_LEVEL(msg)                          LOG_MANAGER->logTrivial(msg);
//#define LOG_TRIVIAL_LEVEL_PREFIX(msg, prefix)           LOG_MANAGER->logTrivial(msg, prefix);
//#define LOG_MESSAGE_CRITICAL(log, msg)                  LOG_MANAGER->logCritical(log, msg);
//#define LOG_MESSAGE_CRITICAL_PREFIX(log, msg, prefix)   LOG_MANAGER->logCritical(log, msg, prefix);
//#define LOG_MESSAGE_NORMAL(log, msg)                    LOG_MANAGER->logNormal(log, msg);
//#define LOG_MESSAGE_NORMAL_PREFIX(log, msg, prefix)     LOG_MANAGER->logNormal(log, msg, prefix);
//#define LOG_MESSAGE_TRIVIAL(log, msg)                   LOG_MANAGER->logTrivial(log, msg);
//#define LOG_MESSAGE_TRIVIAL_PREFIX(log, msg, prefix)    LOG_MANAGER->logTrivial(log, msg, prefix);
//#define LOG_OGRE_CRITICAL(msg)                          LOG_MANAGER->logCriticalOgre(msg);
//#define LOG_OGRE_CRITICAL_PREFIX(msg, prefix)           LOG_MANAGER->logCriticalOgre(msg, prefix);
//#define LOG_OGRE_NORMAL(msg)                            LOG_MANAGER->logNormalOgre(msg);
//#define LOG_OGRE_NORMAL_PREFIX(msg, prefix)             LOG_MANAGER->logNormalOgre(msg, prefix);
//#define LOG_OGRE_TRIVIAL(msg)                           LOG_MANAGER->logTrivialOgre(msg);
//#define LOG_OGRE_TRIVIAL_PREFIX(msg, prefix)            LOG_MANAGER->logTrivialOgre(msg, prefix);
// clang-format on


}  // End namespace ndx


#endif  // _ndxLogManager_h_

