#include <climits>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " INPUT OUTPUT" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream ifs(argv[1], std::ios::binary);
  if (!ifs) {
    std::cerr << "Failed to open input file" << std::endl;
    return EXIT_FAILURE;
  }
  std::ofstream ofs(argv[2]);
  if (!ofs) {
    std::cerr << "Failed to open output file" << std::endl;
    return EXIT_FAILURE;
  }
  std::string res;
  while (!ifs.eof()) {
    char code;
    if (ifs.read(&code, sizeof(char))) {
      for (std::size_t i = 0; i < CHAR_BIT; ++i) {
        res += '0' + ((code >> i) & 1);
      }
    }
  }
  ofs << res << std::endl;
  ofs << res << std::endl;
}
