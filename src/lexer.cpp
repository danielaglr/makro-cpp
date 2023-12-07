

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

    default:
      Error(line, "Unexpected character.");
      break;
  }
}