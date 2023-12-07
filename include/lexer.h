#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>


class Lexer {
  std::string source;
  std::vector<Token> tokens;

  int start = 0;
  int current = 0;
  int line = 1;

  inline bool isAtEnd() { return current >= source.length(); };
  inline char advance() { return source[current++]; };

  inline bool match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;

    current ++;
    return true;
  }

  inline char peek() {
    if (isAtEnd()) return '\0';
    return source[current];
  };

  inline void addToken(TokenType type) {
    std::string lexeme = source.substr(start, current - start);
    tokens.push_back(Token(type, lexeme, line));
  }
  
public:
  Lexer();
  Lexer(std::string source) : source(source) {};

  std::vector<Token> scanTokens();
  void scanToken();
};

#endif