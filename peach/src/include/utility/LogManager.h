#pragma once

#include <utility/Logger.h>

#include <string>
#include <unordered_map>

namespace peach {

class LogManager {
    friend std::unique_ptr<LogManager> std::make_unique<LogManager>();

public:
    static LogManager& GetInstance();
    Logger& GetLogger(const std::string& name);

private:
    LogManager() = default;

private:
    std::unordered_map<std::string, std::shared_ptr<Logger>> mLogs;
};

}