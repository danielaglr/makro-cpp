#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class GenerateAST {
public:
  int main(int argc, char* argv[]) {
    if (argc != 2) {
      std::cerr << "USAGE: generate_ast <output dir>" << std::endl;
      return 1;
    }

    std::string outputDir = argv[1];

    defineAst(outputDir, "Expr", std::vector<std::string> {
      "Binary   : Expr left, Token operator, Expr right",
      "Grouping : Expr expression",
      "Literal  : Object value",
      "Unary    : Token operator, Expr right"
    });
    return 0;
  }

  void defineAst(std::string outputDir, std::string baseName, const std::vector<std::string>& types) {
    std::string path = outputDir + "/" + baseName + ".h";
    std::ofstream file(path);

    file << "#ifndef " << baseName << "_H" << std::endl;
    file << "#define " << baseName << "_H" << std::endl;
    file << "\n";
    file << "class " << baseName << " {" << std::endl;

    defineVisitor(file, baseName, types);

    for (const std::string& type : types) {
      size_t colonIndex = type.find(":");
      std::string className = type.substr(0, colonIndex);
      std::string fields = type.substr(colonIndex + 2);

      file << "  class " << className << ": public " << baseName << " {" << std::endl;
      file << "  public:" << std::endl;

      size_t start = 0;
      while (start < fields.size()) {
        size_t commaIndex = fields.find(",", start);
        std::string field = fields.substr(start, commaIndex - start);
        size_t spaceIndex = field.rfind(" ");
        std::string typeName = field.substr(0, spaceIndex);
        std::string fieldName = field.substr(spaceIndex + 1);

        file << "    " << typeName << " " << fieldName << ";" << std::endl;

        start = commaIndex != std::string::npos ? commaIndex + 2 : fields.size();
      }

      file << " };" << std::endl;
    }

    file << "};" << std::endl;
    file << "\n";
    file << "#endif";

    file.close();

    std::cout << "Generated AST!! :3" << std::endl;
  }

  void defineVisitor(std::ofstream& file, std::string baseName, const std::vector<std::string>& types) {
    file << "  class Visitor;" << std::endl;
    file << "  public:" << std::endl;
    file << "    virtual ~Visitor() = default;" << std::endl;

    for (const std::string& type : types) {
      size_t colonIndex = type.find(":");
      std::string typeName = type.substr(0, colonIndex);

      file << "    virtual R visit" << typeName << baseName << "(" << typeName << "& " << baseName << ") = 0;" << std::endl;
    }
  }
};

int main(int argc, char* argv[]) {
  GenerateAST generator;
  return generator.main(argc, argv);
}
