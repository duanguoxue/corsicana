#include "catch.hpp"
#include "corsicana/trie.hpp"
#include <iostream>

using namespace Catch::Matchers;

TEST_CASE("Match All", "[corsicana.match.all]") {
    corsicana::trie t;
    t.insert("hers").insert("his").insert("she").insert("he").freeze();
    SECTION("matches") {
        std::vector<std::string> expected = { "she", "he", "hers" };
        auto all = t.match("ushers").all();
        REQUIRE_THAT(all, Equals(expected));
    }
    SECTION("no matches") {
        auto all = t.match("santamaria").all();
        REQUIRE(all.empty());
    }
}

TEST_CASE("Match Count", "[corsicana.match.count]") {
    corsicana::trie t;
    t.insert("hers").insert("his").insert("she").insert("he").freeze();
    SECTION("matches") {
        std::vector<std::string> expected = { "she", "he", "hers" };
        REQUIRE(t.match("ushers").count() == 3);
    }
    SECTION("no matches") {
        REQUIRE(t.match("santamaria").count() == 0);
    }
}

TEST_CASE("Match Iterator", "[corsicana.match.iterator]") {
    corsicana::trie t;
    t.insert("hers").insert("his").insert("she").insert("he").freeze();
    SECTION("matches") {
        std::vector<std::string> expected = { "she", "he", "hers" };
        auto match = t.match("ushers");
        std::vector<std::string> actual(match.begin(), match.end());
        REQUIRE_THAT(actual, Equals(expected));
    }
    SECTION("matches - std methods") {
        std::vector<std::string> expected = { "she", "he", "hers" };
        auto match = t.match("ushers");
        std::vector<std::string> actual(std::begin(match), std::end(match));
        REQUIRE_THAT(actual, Equals(expected));
    }
    SECTION("no matches") {
        auto match = t.match("santamaria");
        REQUIRE(match.begin() == match.end());
    }
    SECTION("iterator dereference") {
        auto match = t.match("ushers");
        auto it = match.begin();
        REQUIRE(*it == "she");
        REQUIRE(it->compare("she") == 0);
    }
    SECTION("iterator copy") {
        auto match = t.match("ushers");
        auto it = match.begin();
        corsicana::match<std::string>::iterator copy = it;
        REQUIRE(it == copy);
    }
    SECTION("iterator copy assignment") {
        auto match = t.match("ushers");
        auto it = match.begin();
        corsicana::match<std::string>::iterator copy(it);
        REQUIRE(it == copy);
    }
}

// Test specifically for heavy overlap
TEST_CASE("Match Overlap") {
    corsicana::trie t;
    t.insert("he").insert("hehehehe").freeze();
    std::vector<std::string> expected = { "he", "he", "he", "hehehehe", "he", "hehehehe", "he" };
    REQUIRE_THAT(t.match("hehehehehe").all(), Equals(expected));
}
