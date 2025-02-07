#include "log.hh"

// std::time_t io::now = std::chrono::system_clock::now();

std::time_t io::currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

std::tm* io::localTime = std::localtime(&currentTime);
