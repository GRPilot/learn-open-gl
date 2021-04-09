#ifndef __LOGGER_H__
#define __LOGGER_H__

enum class Level {
    DEBUG,
    WARNING,
    ERROR,
    INFO,
};

class Logger {
    Logger();
public:
    static Logger &instance();

    void draw();
    void log(Level lvl, const std::string &format, ...);

private:
    const size_t max_logs_line;
    std::deque<std::string> logs;
    int wasUpdated;

    ImVec4 getLogColor(const std::string &line) const;

    void logv(Level lvl, const std::string &format, va_list params);
};

#ifndef LogD
#define LogD(format, ...) \
    Logger::instance().log(Level::DEBUG, (format), ##__VA_ARGS__)
#endif

#ifndef LogI
#define LogI(format, ...) \
    Logger::instance().log(Level::INFO, (format), ##__VA_ARGS__)
#endif

#ifndef LogW
#define LogW(format, ...) \
    Logger::instance().log(Level::WARNING, (format), ##__VA_ARGS__)
#endif

#ifndef LogE
#define LogE(format, ...) \
    Logger::instance().log(Level::ERROR, (format), ##__VA_ARGS__)
#endif

#endif // __LOGGER_H__
