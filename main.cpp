#include <climits>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <vector>

struct domino {
  domino(const std::string& upper, const std::string& lower)
    : upper(upper), lower(lower) {}
  std::string upper;
  std::string lower;
};

bool comp(const std::string& lhs, const std::string& rhs) {
  using std::size;
  if (size(lhs) == size(rhs)) {
    return lhs < rhs;
  } else {
    return size(lhs) < size(rhs);
  }
}

bool operator<(const domino& lhs, const domino& rhs) {
  const auto lhs_longer = std::max(lhs.upper, lhs.lower, comp);
  const auto rhs_longer = std::max(rhs.upper, rhs.lower, comp);
  if (lhs_longer == rhs_longer) {
    return comp(std::min(lhs.upper, lhs.lower, comp),
        std::min(rhs.upper, rhs.lower, comp));
  } else {
    return comp(lhs_longer, rhs_longer);
  }
}

namespace std {

template <>
struct greater<domino> {
  bool operator()(const domino& lhs, const domino& rhs) {
    return lhs < rhs;
  }
};

} // namespace std

std::optional<std::string> solve_post(const std::vector<domino>& vd) {
  std::priority_queue<domino, std::vector<domino>, std::greater<domino>> q;
  for (const auto& d : vd) {
    q.push(d);
  }
  while (!q.empty()) {
    const auto d = q.top();
    q.pop();
    if (d.upper == d.lower) return d.upper;
    for (const auto& nx : vd) {
      const auto upper = d.upper + nx.upper;
      const auto lower = d.lower + nx.lower;
      const auto len = std::min(size(upper), size(lower));
      if (upper.substr(0, len) == lower.substr(0, len)) {
        q.emplace(upper, lower);
      }
    }
  }
  return std::nullopt;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " INPUT OUTPUT" << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs) {
    std::cerr << "Failed to open input file" << std::endl;
    return EXIT_FAILURE;
  }
  std::ofstream ofs(argv[2]);
  if (!ofs) {
    std::cerr << "Failed to open output file" << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<std::string> vs;
  for (std::string line; std::getline(ifs, line); ) {
    vs.push_back(line);
  }
  if ((vs.size() % 2) != 0) {
    std::cerr << "number of line must be even" << std::endl;
    return EXIT_FAILURE;
  }
  std::vector<domino> vd;
  for (std::size_t i = 0; i < vs.size() / 2; ++i) {
    vd.emplace_back(vs[2*i], vs[2*i+1]);
  }
  if (const auto res_opt = solve_post(vd)) {
    const auto res = *res_opt;
    std::vector<bool> vb;
    for (const auto& c : res) {
      switch (c) {
        case '0':
          vb.push_back(false);
          break;
        case '1':
          vb.push_back(true);
          break;
      }
    }
    if ((vb.size() % CHAR_BIT) != 0) {
      std::cerr << "Compile error: result size must be multiple of " << CHAR_BIT << std::endl;
      return EXIT_FAILURE;
    }
    std::vector<char> bitcode;
    for (std::size_t i = 0; i < vb.size() / CHAR_BIT; ++i) {
      char code = 0;
      for (std::size_t j = 0; j < CHAR_BIT; ++j) {
        code |= vb[CHAR_BIT*i + j] << j;
      }
      bitcode.push_back(code);
    }
    ofs.write(bitcode.data(), bitcode.size());
  } else {
    std::cerr << "Compile error: unsolvable input" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

