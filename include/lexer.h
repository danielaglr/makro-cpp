#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <unordered_map>


class Lexer {
  std::string source;
  std::vector<Token> tokens;

  int start = 0;
  int current = 0;
  int line = 1;

  const std::unordered_map<std::string, TokenType> keywords = { 
    {"else", ELSE}, {"false", FALSE}, {"for", FOR}, 
    {"function", FUNCTION}, {"if", IF}, {"print", PRINT}, 
    {"return", RETURN},{"true", TRUE}, {"var", VAR}, 
    {"while", WHILE} 
  };

  inline bool isAtEnd() { return current >= source.length(); };
  inline bool isDigit(char c) { return c >= '0' && c <= '9'; };
  inline bool isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; };
  inline bool isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); };

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

  inline char peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
  };

  inline void addToken(TokenType type) {
    std::string lexeme = source.substr(start, current - start);
    tokens.push_back(Token(type, lexeme, line));
  }
  
  inline void addToken(TokenType type, std::string lexeme) {
    tokens.push_back(Token(type, lexeme, line));
  };

public:

  Lexer();
  Lexer(std::string source) : source(source) {};

  std::vector<Token> scanTokens();
  void scanToken();
  void handleString();
  void handleNumber();
  void handleIdentifier();
};

#endif