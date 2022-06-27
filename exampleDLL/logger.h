#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
std::string getDateTime();

class Log {
    public:
        static std::string time;
        static std::string type; //info || warning || error
        static std::string message;
};

void logger(Log loginfo);

#endif
