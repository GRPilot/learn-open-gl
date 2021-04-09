#include "incs.hpp"

#include "logger.hpp"

namespace std {
    string to_string(Level lvl) {
        switch(lvl) {
            case Level::DEBUG: return "DEBUG";
            case Level::WARNING: return "WARN ";
            case Level::INFO: return "INFO ";
            case Level::ERROR: return "ERROR";
        }
        return "DEBUG";
    }
}

Logger::Logger() : max_logs_line(1024), wasUpdated(false) {}

Logger &Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::draw() {
    ImGui::Begin("Logs");
        for(const auto &line : logs) {
            ImGui::TextColored(getLogColor(line), line.c_str());
        }
        if(wasUpdated) {
            ImGui::SetScrollY(ImGui::GetScrollMaxY());
            --wasUpdated;
        }
    ImGui::End();
}

void Logger::log(Level lvl, const std::string &format, ...) {
    va_list list;
    va_start(list, format.c_str());
    logv(lvl, format, list);
    va_end(list);

    wasUpdated = 2;
}

ImVec4 Logger::getLogColor(const std::string &line) const {
    size_t npos = std::string::npos;
    if(line.find(std::to_string(Level::ERROR)) != npos) {
        return ImVec4{0.9, 0.0, 0.1, 1.0};
    }
    if(line.find(std::to_string(Level::INFO)) != npos) {
        return ImVec4{0.0, 0.9, 0.0, 1.0};
    }
    if(line.find(std::to_string(Level::WARNING)) != npos) {
        return ImVec4{0.9, 0.5, 0.1, 1.0};
    }
    return ImVec4{0.9, 0.9, 0.9, 1.0};
}

void Logger::logv(Level lvl, const std::string &format, va_list params) {
    constexpr size_t MAX_LINE_WIDTH = 2048;
    constexpr char CRLF = '\n';

    char buffer[MAX_LINE_WIDTH]{};
    vsnprintf(buffer, MAX_LINE_WIDTH, format.c_str(), params);

    time_t now = time(nullptr);

    std::stringstream out;
    out << std::put_time(localtime(&now), "[%F %T] ")
        << "[" << std::to_string(lvl) << "] "
        << buffer << CRLF;

    const std::string &line = out.str();
    logs.push_back(line);
    if(logs.size() > max_logs_line) {
        logs.pop_front();
    }
    printf("%.*s", static_cast<int>(line.size()), line.c_str());
}

