#include "util.hpp"

void log(const char* message, int line, const char* file, bool error) {
  if (error)
      std::cerr << message << "\n";
  else
      std::cout << message << "\n"; 
}
