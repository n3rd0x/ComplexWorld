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
     * @param enablePrefix Flag for enable prefix in the logging message.
     */
    LogManager(const bool enablePrefix = false);


    /**
     * Default destructor.
     */
    virtual ~LogManager();


    /**
     * Create an independent logger.
     * @param id ID to identify the logger.
     * @param fName File name.
     * @param level Set logging level.
     * @return A Poco::Logger object.
     */
    Poco::Logger* createLogger(
        const std::string& id,
        const std::string& fName,
        const bool consoleOutput            = false,
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
     * Enable prefix name in the logging message.
     */
    bool mPrefixEnabled;


};  // End class LogManager




// ************************************************************
// Macro Definition Declarations
// ************************************************************
// clang-format off
#define LOG_MANAGER ndx::LogManager::getSingleton()
#define LOG_CRITICAL_LEVEL(msg)                             LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_CRITICAL);
#define LOG_CRITICAL_LEVEL_PREFIX(msg, prefix)              LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_CRITICAL, prefix);
#define LOG_DEBUG_LEVEL(msg)                                LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_DEBUG);
#define LOG_DEBUG_LEVEL_PREFIX(msg, prefix)                 LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_DEBUG, prefix);
#define LOG_ERROR_LEVEL(msg)                                LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_ERROR);
#define LOG_ERROR_LEVEL_PREFIX(msg, prefix)                 LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_ERROR, prefix);
#define LOG_FATAL_LEVEL(msg)                                LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_FATAL);
#define LOG_FATAL_LEVEL_PREFIX(msg, prefix)                 LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_FATAL, prefix);
#define LOG_INFO_LEVEL(msg)                                 LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_INFORMATION);
#define LOG_INFO_LEVEL_PREFIX(msg, prefix)                  LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_INFORMATION, prefix);
#define LOG_NOTICE_LEVEL(msg)                               LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_NOTICE);
#define LOG_NOTICE_LEVEL_PREFIX(msg, prefix)                LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_NOTICE, prefix);
#define LOG_TRACE_LEVEL(msg)                                LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_TRACE);
#define LOG_TRACE_LEVEL_PREFIX(msg, prefix)                 LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_TRACE, prefix);
#define LOG_WARNING_LEVEL(msg)                              LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_WARNING);
#define LOG_WARNING_LEVEL_PREFIX(msg, prefix)               LOG_MANAGER->logMessage(msg, Poco::Message::PRIO_WARNING, prefix);
#define LOG_MESSAGE_CRITICAL(logger, msg)                   LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_CRITICAL);
#define LOG_MESSAGE_CRITICAL_PREFIX(logger, msg, prefix)    LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_CRITICAL, prefix);
#define LOG_MESSAGE_DEBUG(logger, msg)                      LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_DEBUG);
#define LOG_MESSAGE_DEBUG_PREFIX(logger, msg, prefix)       LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_DEBUG, prefix);
#define LOG_MESSAGE_ERROR(logger, msg)                      LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_ERROR);
#define LOG_MESSAGE_ERROR_PREFIX(logger, msg, prefix)       LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_ERROR, prefix);
#define LOG_MESSAGE_FATAL(logger, msg)                      LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_FATAL);
#define LOG_MESSAGE_FATAL_PREFIX(logger, msg, prefix)       LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_FATAL, prefix);
#define LOG_MESSAGE_INFO(logger, msg)                       LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_INFORMATION);
#define LOG_MESSAGE_INFO_PREFIX(logger, msg, prefix)        LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_INFORMATION, prefix);
#define LOG_MESSAGE_NOTICE(logger, msg)                     LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_NOTICE);
#define LOG_MESSAGE_NOTICE_PREFIX(logger, msg, prefix)      LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_NOTICE, prefix);
#define LOG_MESSAGE_TRACE(logger, msg)                      LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_TRACE);
#define LOG_MESSAGE_TRACE_PREFIX(logger, msg, prefix)       LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_TRACE, prefix);
#define LOG_MESSAGE_WARNING(logger, msg)                    LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_WARNING);
#define LOG_MESSAGE_WARNING_PREFIX(logger, msg, prefix)     LOG_MANAGER->logMessage(logger, msg, Poco::Message::PRIO_WARNING, prefix);
// clang-format on


}  // End namespace ndx


#endif  // _ndxLogManager_h_
