#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "ERROR: No subcommand provided" << std::endl;
    return 1;
  } else {
    Makro mkro(argv[1]);
  };
}

Makro::Makro(std::string path) { runFile(path); };

void Makro::runFile(std::string path) {
  std::ifstream sourceFile(path);

  std::stringstream strStream;
  strStream << sourceFile.rdbuf();
  source = strStream.str();
  std::cout << source << std::endl;
}