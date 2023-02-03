#include "Logging.hpp"

namespace wcr::logging
{
    bool Logger::checkLevel()
    {
        const auto log = (m_global_level & m_level) != 0;

        //wpi::outs() << "Is Valid Level: " << std::to_string(log) << "\n";
        //wpi::outs() << "Global Level: " << std::to_string(m_global_level) << ", Listening Level: " << std::to_string(m_level) << "\n";
        //wpi::outs().flush(); 

        if (log && m_new_line && m_construct_name) {
            wpi::outs() << "[" << constructName() << "]: ";
            m_new_line = false;
        }

        return log;
    }

    // Internal function for constructing channels
    std::string Logger::constructName()
    {
        std::stringstream value;
        auto levels = (m_global_level & m_level);
        uint32_t level_count = 0;

        for (auto i = 0; i < 32; i++)
        {
            if ((levels & (1 << i)) != 0) {
                if (level_count != 0 ) value << " | ";
                
                value << getMappedValue(1 << i);
                level_count++;
            }
        }

        if (level_count > 0) {
            
        }

        return value.str();
    }

    Logger &Logger::operator<<(const std::string &message)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << message;
        return *this;
    }
    // R-Value Support
    Logger &Logger::operator<<(const std::string &&message)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << message;
        return *this;
    }

    Logger &Logger::operator<<(const int &number)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << std::to_string(number);
        return *this;
    }
    // R-Value Support
    Logger &Logger::operator<<(const int &&number)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << std::to_string(number);
        return *this;
    }

    Logger &Logger::operator<<(const float &number)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << std::to_string(number);
        return *this;
    }
    // R-Value Support
    Logger &Logger::operator<<(const float &&number)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << std::to_string(number);
        return *this;
    }

    Logger &Logger::operator<<(const double &number)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << std::to_string(number);
        return *this;
    }
    // R-Value Support
    Logger &Logger::operator<<(const double &&number)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << std::to_string(number);
        return *this;
    }

    Logger &Logger::operator<<(const char &number)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << std::to_string(number);
        return *this;
    }
    // R-Value Support
    Logger &Logger::operator<<(const char &&number)
    {
        if (!checkLevel())
            return *this;
        wpi::outs() << std::to_string(number);
        return *this;
    }

    Logger &Logger::operator<<(const LoggerCommand &command)
    {
        if (!checkLevel())
            return *this;

        if (command == LoggerCommand::Flush)
        {
            wpi::outs() << "\n";
            wpi::outs().flush();
        }
        return *this;
    }
    // R-Value Support
    Logger &Logger::operator<<(const LoggerCommand &&command)
    {
        if (!checkLevel())
            return *this;

        switch (command)
        {
        case LoggerCommand::Flush:
            wpi::outs() << "\n";
            wpi::outs().flush();
            this->m_new_line = true;

            break;
        default:
            break;
        }

        return *this;
    }
}