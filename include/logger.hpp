
#pragma once
#include <fstream>
#include<iostream>
#include <string>

class Logger {
private:
    std::ofstream out;
public:
    Logger(const std::string &filename) {
        out.open(filename, std::ios::out | std::ios::trunc);
    }
    ~Logger() {
        if (out.is_open()) out.close();
    }
    void Log(const std::string &msg) {
        std::cout << msg;
        if (out.is_open()) out << msg;
    }
};
// global logger declaration
extern Logger logger;

// macro to print + log
#define PRINT(x) logger.Log(x)
