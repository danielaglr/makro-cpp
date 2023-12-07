#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>

struct Error {
  int line;
  std::string where;
  std::string message;

  Error(int line, std::string message) : line(line), message(message) {
    report(line, "", message);
  };
  Error(int line, std::string where, std::string message) : line(line), where(where), message(message) {
    report(line, where, message);
  };

  void report(int line, std::string where, std::string message) {
    std::cerr << "ERROR: Line " << line << " " << where << ": " << message << std::endl;
  }
};

#endif