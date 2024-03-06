#include "compiler.hpp"

#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Compiler compile", "[COMPILE]") {

  SECTION("empty line") {
    std::stringstream in{
        R"""(add x1, x2, x3

        add x1, x2, x3)"""
    };

    std::stringstream out{};
    std::stringstream error{};

    compile(in, out, error);

    std::string line{};
    out >> line;
    REQUIRE(line == "00010000000010000110000000000001");
    line = {};
    out >> line;
    REQUIRE(line == "00010000000010000110000000000001");
    line = {};
    out >> line;
    REQUIRE(!out);
  }
}