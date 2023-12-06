#include <iostream>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "ERROR: No subcommand provided" << std::endl;
    return 1;
  }
}