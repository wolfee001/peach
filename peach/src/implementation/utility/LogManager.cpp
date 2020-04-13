#include <utility/LogManager.h>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace peach {

/* static */ LogManager& LogManager::GetInstance()
{
    static std::unique_ptr<LogManager> mInstance;

    if (mInstance == nullptr) {
        mInstance = std::make_unique<LogManager>();
    }
    return *mInstance;
}

Logger& LogManager::GetLogger(const std::string& name)
{
    static spdlog::sink_ptr mSink;
    if (!mSink) {
        mSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    }
    auto it = mLogs.find(name);
    if (it == mLogs.end()) {
        it = mLogs.emplace(name, std::make_shared<Logger>(name, mSink)).first;
    }

    return *(it->second);
}

} // namespace peach