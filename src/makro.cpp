#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "D:\Desktop\All Desktop Folders\Coding\GitHub\makro-cpp\include\makro.h"
#include "D:\Desktop\All Desktop Folders\Coding\GitHub\makro-cpp\include\lexer.h"
#include "D:\Desktop\All Desktop Folders\Coding\GitHub\makro-cpp\include\tokens.h"

void Makro::runFile(std::string path) {
  std::ifstream sourceFile(path);

  std::stringstream strStream;
  strStream << sourceFile.rdbuf();
  source = strStream.str();
  std::cout << source << std::endl;

  run(source);
}

void Makro::run(std::string source) {
  Lexer lexer(source);
  std::vector<Token> tokens = lexer.scanTokens();

  for (Token token : tokens) {
    std::cout << token.type << ": " << token.lexeme << std::endl;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "ERROR: No source file provided!" << std::endl;
    return 1;
  } else {
    Makro mkro(argv[1]);
  };
}