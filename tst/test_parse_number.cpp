#include "test_parse_number.h"
#include "parse_number.h"
#include <vector>
#include <string>
#include <utility>

TestParseNumber::TestParseNumber()
{
}

void TestParseNumber::setUp()
{
}

void TestParseNumber::tearDown()
{
}

void TestParseNumber::t_IsSingleDigit()
{
    std::vector<char> good = {'0','1','2','3','4','5','6','7','8','9'};

    for (const auto c : good)
        CPPUNIT_ASSERT(is_digit(c));

    std::vector<char> bad = {'a', 'b', 'c', ' ', '-', '+', 'Z' };
    for (const auto c : bad)
        CPPUNIT_ASSERT(!is_digit(c));
}

void TestParseNumber::t_IsNumber()
{
    std::vector<std::string> good = {"0", "0000", "500", "600", "1000", "9999"};
    for (const auto& c : good)
        CPPUNIT_ASSERT(is_number(c));

    std::vector<std::string> bad = {"0a1234", "65A92", "-777", "00000a", ""};
    for (const auto c : bad)
        CPPUNIT_ASSERT(!is_number(c));    
}

void TestParseNumber::t_IsSignedNumber()
{
    std::vector<std::string> good = { "+5" };
    for (const auto& c : good)
        CPPUNIT_ASSERT(is_signed_number(c));
}

void TestParseNumber::t_ParseDigit()
{
    typedef std::pair<char, Number> Case;
    std::vector<Case> cases = { {'1', 1},
                                {'2', 2},
                                {'3', 3},
                                {'4', 4},
                                {'5', 5},
                                {'6', 6},
                                {'7', 7},
                                {'8', 8},
                                {'9', 9},
                                {'0', 0} };
    for (const auto& c : cases)
        CPPUNIT_ASSERT(*(parse_digit(c.first)) == c.second);
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParseNumber);
