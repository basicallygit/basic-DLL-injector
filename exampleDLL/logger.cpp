#include "logger.h"

std::string getDateTime()
{
    using namespace std::chrono;
    time_point<system_clock> now = system_clock::now();
    std::time_t start = system_clock::to_time_t(now);
    char timedisplay[50];
    struct tm buf;
    errno_t err = localtime_s(&buf, &start);
    if (std::strftime(timedisplay, sizeof(timedisplay), "%d/%m/%y - %H.%M.%S", &buf))
    {
        return timedisplay;
    }
    else {
        return "??:??:??";
    }
}

class Log {
    public:
        std::string time;
        std::string type; //info || warning || error
        std::string message;
};


const std::string logFilePath = "injectlog.log";

void logger(Log loginfo)
{
    using namespace std;
    ofstream logFile;
    logFile.open(logFilePath, ios_base::app); //open in append mode
    logFile << "[" << loginfo.time << "] [" << loginfo.type << "]: " << loginfo.message;
    logFile.close();
}