#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Logger {
   private:
    std::ofstream logfile;

   public:
    Logger(const std::string &filename) {
        logfile.open(filename, std::ios::app);
        if (!logfile.is_open()) {
            std::cerr << "Error opening logfile";
        }
    }

    ~Logger() {
        logfile.close();
    }

    void log(const std::string &message) {
        std::ostringstream logentry;
        logentry << message << '\n';
        std::cout << logentry.str();
        if (logfile.is_open()) {
            logfile << logentry.str();
            logfile.flush();
        }
    }
};
#endif