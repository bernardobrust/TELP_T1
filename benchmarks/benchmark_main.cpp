//
// Custom benchmark main: supports --append-results=<path> to append output
// with date and version to a file (any format; human-readable by default).
//

#include <benchmark/benchmark.h>

#include <chrono>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#ifndef TELP_BENCHMARK_VERSION
#define TELP_BENCHMARK_VERSION "1.0"
#endif

namespace {

// Streambuf that writes each character to two streambufs (tee).
class TeeBuf : public std::streambuf {
 public:
  TeeBuf(std::streambuf* a, std::streambuf* b) : a_(a), b_(b) {}

 protected:
  int overflow(int c) override {
    if (c == traits_type::eof()) return traits_type::eof();
    if (a_) a_->sputc(static_cast<char>(c));
    if (b_) b_->sputc(static_cast<char>(c));
    return c;
  }

  std::streamsize xsputn(const char* s, std::streamsize n) override {
    if (a_) a_->sputn(s, n);
    if (b_) b_->sputn(s, n);
    return n;
  }

  int sync() override {
    int r = 0;
    if (a_ && a_->pubsync() != 0) r = -1;
    if (b_ && b_->pubsync() != 0) r = -1;
    return r;
  }

 private:
  std::streambuf* a_;
  std::streambuf* b_;
};

// Remove one argument from argv (the one that matches prefix=).
// Returns the value after '=' or empty if not found.
std::string parse_and_remove_arg(int* argc, char*** argv, const char* prefix) {
  const std::size_t pre_len = std::strlen(prefix);
  int n = *argc;
  std::string value;
  for (int i = 1; i < n; ++i) {
    if (std::strncmp((*argv)[i], prefix, pre_len) == 0 &&
        (*argv)[i][pre_len] == '=') {
      value = (*argv)[i] + pre_len + 1;
      for (int j = i; j + 1 < n; ++j) (*argv)[j] = (*argv)[j + 1];
      (*argc)--;
      (*argv)[*argc] = nullptr;  // keep argv null-terminated for consumers
      break;
    }
  }
  return value;
}

std::string current_iso_date() {
  auto now = std::chrono::system_clock::now();
  auto t = std::chrono::system_clock::to_time_t(now);
  std::ostringstream os;
  os << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
  return os.str();
}

}  // namespace

int main(int argc, char** argv) {
  std::string append_path =
      parse_and_remove_arg(&argc, &argv, "--append-results");

  std::streambuf* cout_orig = std::cout.rdbuf();
  std::ofstream append_file;
  TeeBuf* tee_buf = nullptr;

  if (!append_path.empty()) {
    append_file.open(append_path, std::ios::app);
    if (!append_file) {
      std::cerr << "Cannot open for append: " << append_path << "\n";
      return 1;
    }
    append_file << "\n--- " << current_iso_date()
                << "  version=" << TELP_BENCHMARK_VERSION << " ---\n";
    append_file.flush();
    tee_buf = new TeeBuf(cout_orig, append_file.rdbuf());
    std::cout.rdbuf(tee_buf);
  }

  ::benchmark::Initialize(&argc, argv);
  if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
  ::benchmark::RunSpecifiedBenchmarks();

  if (tee_buf) {
    std::cout.rdbuf(cout_orig);
    delete tee_buf;
    append_file.close();
  }

  return 0;
}
