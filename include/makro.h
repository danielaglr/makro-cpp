#ifndef MAKRO_H
#define MAKRO_H

#include <string>

class Makro {
  std::string source;

  void runFile(std::string path);

public:
  Makro(std::string path);
};

#endif