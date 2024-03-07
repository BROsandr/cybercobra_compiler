#include "cobra_algos.hpp"
#include "compiler.hpp"
#include "exception.hpp"
#include "reader.hpp"
#include "preprocessor.hpp"

#include <iostream>
#include <vector>
#include <bitset>

int main() {
  auto &out_stream = std::cout;
  auto &error_stream = std::cerr;
  Reader reader{std::cin};
  std::string line{};
  std::vector<std::vector<std::string>> token_lines{};
  while (getline(reader, line)) {
    token_lines.push_back(line2tokens(std::move(line)));
  }

  try {
    preprocess(token_lines);
  } catch (const Errors::Syntax_error &exc) {
    error_stream << "ERROR while preprocessing:\n"
        << "  " << "Error type: Syntax error\n"
        << "  " << "what: " << exc.what() << "\n";
  }
  auto &preprocessed = token_lines;

  Compiler compiler{};
  for (auto current_line_it = preprocessed.begin(); current_line_it != preprocessed.end(); ++current_line_it) {
      if (is_empty_line(*current_line_it)) continue;

      const char* const delim = " ";
      std::stringstream imploded;
      std::copy(current_line_it->begin(), current_line_it->end(),
                std::ostream_iterator<std::string>(imploded, delim));

      std::string str;
      getline(imploded, str);

      try {
        out_stream << std::bitset<32>(compiler.compile_str(str)) << "\n";
      } catch (const Errors::Syntax_error &exc) {
        error_stream << "ERROR. Compile at line " << std::to_string(current_line_it - token_lines.begin() + 1) + ":\n"
            << "  " << "Error type: Syntax error\n"
            << "  " << "instr after preprocessor: " << str << "\n"
            << "  " << "what: " << exc.what();
        break;
      } catch (const Errors::Illegal_instruction &exc) {
        error_stream << "ERROR. Compile at line " << std::to_string(current_line_it - token_lines.begin() + 1) + ":\n"
            << "  " << "Error type: Illegal instruction: " << exc.m_instruction << "\n"
            << "  " << "instr after preprocessor: " << str << "\n"
            << "  " << "what: " << exc.what();
        break;
      } catch (const Errors::Range_error &exc) {
        error_stream << "ERROR. Compile at line " << std::to_string(current_line_it - token_lines.begin() + 1) + ":\n"
            << "  " << "Error type: Range error\n"
            << "  " << "instr after preprocessor: " << str << "\n"
            << "  " << "what: " << exc.what();
        break;
      }
  }
}
