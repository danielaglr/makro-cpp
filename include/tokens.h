#ifndef TOKENS_H
#define TOKENS_H

#include <string>

enum TokenType {
  // Single-Character Tokens
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACK, RIGHT_BRACK, SEMICOLON,

  // Literals
  IDENTIFIER, STRING, NUMBER,

  // Keywords
  ELSE, FALSE, FOR, FUNCTION, IF, PRINT, RETURN, TRUE, VAR, WHILE,

  EoF
};

struct Token {
  TokenType type;
  std::string lexeme;
  int line;

  Token(TokenType type, std::string lexeme, int line) : type(type), lexeme(lexeme), line(line) {};

  inline std::string toString() { 
    return type + " " + lexeme; 
  }
};

#endif