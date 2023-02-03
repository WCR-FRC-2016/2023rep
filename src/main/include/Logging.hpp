#pragma once

#include <string>
#include <sstream>
#include "wpi/raw_ostream.h"

namespace wcr::logging {
    enum LogLevel {
        Info = 1,
        Utility = 1 << 1,
        Important = 1 << 2
    };

    enum class LoggerCommand {
        Flush // Adds "\n" and wpi::outs().flush()'s
    };

    class Logger {
    public:
        Logger& operator<<(const std::string&);
        Logger& operator<<(const std::string&&);
        Logger& operator<<(const int&);
        Logger& operator<<(const int&&);
        Logger& operator<<(const float&);
        Logger& operator<<(const float&&);
        Logger& operator<<(const double&);
        Logger& operator<<(const double&&);
        Logger& operator<<(const char&);
        Logger& operator<<(const char&&);
        Logger& operator<<(const LoggerCommand&);
        Logger& operator<<(const LoggerCommand&&);

    private:
        uint32_t m_global_level;
        
        uint32_t m_level = 0;
        bool m_new_line = false;

        static Logger& getLogger() {
            static Logger logger;
            return logger;
        }

        static std::string getMappedValue(const uint32_t value) {
            switch (value)
            {
            case 0:
                return "None";
            case 1:
                return "Test";
            case 1 << 1:
                return "Test2";
            default:
                return "Invalid";
            }
        }

        std::string constructName();
        bool checkLevel();
    
    public:
        static Logger& log(const int log_level)
        {
            auto& logger = getLogger();
            logger.m_level = log_level;

            return logger;
        }
        static Logger& log(const LogLevel log_level)
        {
            auto& logger = getLogger();
            logger.m_level = log_level;

            return logger;
        }

        static void setGlobalLevel(const int level) {
            getLogger().m_global_level = level;
        }
        static void setGlobalLevel(const LogLevel log_level) {
            getLogger().m_global_level = log_level;
        }
    };
}