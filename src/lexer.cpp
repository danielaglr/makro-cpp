

std::vector<Token> Lexer::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.push_back(Token(EoF, "", line));
  return tokens;
}

void Lexer::scanToken() {
  char c = advance();

  switch(c) {
    case '(': addToken(LEFT_PAREN); break;
    case ')': addToken(RIGHT_PAREN); break;
    case '{': addToken(LEFT_BRACK); break;
    case '}': addToken(RIGHT_BRACK); break;
    case ';': addToken(SEMICOLON); break;

    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      break;

    case '"': handleString(); break;

    default:
      if (isDigit(c)) {
        handleNumber();
      } else if (isAlpha(c)) {
        handleIdentifier();
      } else {
        Error(line, "Unexpected character.");
      }
      break;
  }
}

void Lexer::handleString() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    advance();
  }

  if (isAtEnd()) {
    Error(line, "Unterminated string.");
    return;
  }

  advance();

  std::string value = source.substr(start + 1, current - start - 2);
  addToken(STRING, value);
}

void Lexer::handleNumber() {
  while (isDigit(peek())) advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek())) advance();
  };

  addToken(NUMBER, source.substr(start, current - start));
}

void Lexer::handleIdentifier() {
  while (isAlphaNumeric(peek())) advance();

  std::string text = source.substr(start, current - start);
  TokenType type;

  auto it = keywords.find(text);
  if (it != keywords.end()) {
    type = keywords.at(text);
  } else {
    type = IDENTIFIER;
  };

  addToken(type);
};