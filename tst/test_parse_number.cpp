#include "test_parse_number.h"
#include "parse_number.h"
#include <vector>

TestParseNumber::TestParseNumber()
{
}

void TestParseNumber::setUp()
{
}

void TestParseNumber::tearDown()
{
}

void TestParseNumber::t_ParseIsSingleDigit()
{
    std::vector<char> good = {'0','1','2','3','4','5','6','7','8','9'};

    for (const auto c : good)
        CPPUNIT_ASSERT(is_digit(c));

    std::vector<char> bad = {'a', 'b', 'c', ' ', '-', '+', 'Z' };
    for (const auto c : bad)
        CPPUNIT_ASSERT(!is_digit(c));
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestParseNumber);
