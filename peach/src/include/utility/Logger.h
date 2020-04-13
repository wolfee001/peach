#pragma once

#include <spdlog/spdlog.h>

#include <memory>

namespace peach {

class Logger {
public:
    Logger(const std::string& name, spdlog::sink_ptr sink);

    template <typename... Args> void Trace(Args... args) { mLogger->trace(args...); }

    template <typename... Args> void Info(Args... args) { mLogger->info(args...); }

    template <typename... Args> void Warn(Args... args) { mLogger->warn(args...); }

    template <typename... Args> void Error(Args... args) { mLogger->error(args...); }

private:
    std::shared_ptr<spdlog::logger> mLogger;
};

}