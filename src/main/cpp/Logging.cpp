#include "Logging.hpp"

namespace wcr::logging
{
    bool Logger::checkLevel()
    {
        const auto log = (m_global_level & m_level) != 0;

        if (log && m_new_line)
            wpi::outs() << constructName();

        return log;
    }

    std::string Logger::constructName()
    {
        std::stringstream value;

        for (auto i = 0; i < 32; i++)
        {
            if (((m_global_level & m_level) & (1 << i)) != 0)
                value << getMappedValue(1 << i);
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

        if (command == LoggerCommand::Flush)
        {
            wpi::outs().flush();
        }
        return *this;
    }
}