#include "json.hpp"
#include <fstream>
#include <iostream>
#include <random>
// #include <string>
int main() {
  using json = nlohmann::json;
  std::ifstream file("quotes.json");
  if (!file.is_open()) {
    std::cerr << "Error: Could not open data.json" << std::endl;
    return 1;
  }
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  json data;
  try {
    file >> data;
  } catch (const json::parse_error &e) {
    std::cerr << "JSON parse error: " << e.what() << std::endl;
    return 1;
  }

  // Randomize Number Generator
  std::random_device rd;
  std::mt19937 engine(rd());

  int min_val = 1;
  int max_val = data.size();
  std::uniform_int_distribution<int> dist(min_val, max_val);
  int randomInRange = dist(engine);

  std::string quote = data[randomInRange]["text"].get<std::string>();
  quote = quote.substr(0, quote.length());

  std::string author = data[randomInRange]["author"].get<std::string>();
  author = author.substr(0, quote.length());

#ifdef _WIN32
#include <windows.h>
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, 5);
  std::cout << quote << " -- " << author << std::endl;
#elif __linux__
  std::cout << "\e[35m" << quote << "\033[0m" << " -- " << author << std::endl;
#else
  std::cout << quote << " -- " << author << std::endl;
#endif
  return 0;
}
