#ifndef MAKRO_H
#define MAKRO_H

#include <string>

class Makro {
  std::string source;

  void runFile(std::string path);
  void run(std::string source);

public:
  Makro(std::string path) { runFile(path); };

};

#endif