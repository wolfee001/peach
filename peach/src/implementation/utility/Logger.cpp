#include <utility/Logger.h>

namespace peach {

Logger::Logger(const std::string& name, spdlog::sink_ptr sink)
    : mLogger(std::make_shared<spdlog::logger>(name, sink))
{
    mLogger->set_level(spdlog::level::trace);
}

} // namespace peach