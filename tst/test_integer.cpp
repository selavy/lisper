#include "test_integer.h"
#include "integer.h"

TestInteger::TestInteger()
{
}

void TestInteger::setUp()
{
}

void TestInteger::tearDown()
{
}

void TestInteger::t_ParseDigit()
{
    typedef std::pair<std::string, typename Integer::value_type> Case;
    std::vector<Case> cases = {
        { "0", 0 },
        { "1", 1 },
        { "2", 2 },
        { "3", 3 },
        { "4", 4 },
        { "5", 5 },
        { "6", 6 },
        { "7", 7 },
        { "8", 8 },
        { "9", 9 }
    };
    for (const auto& it : cases) {
        Integer i(it.first.c_str());
        CPPUNIT_ASSERT_EQUAL(it.second, i.value());
    }

    for (int64_t val = 0LL; val < 10; ++val) {
        Integer i(val);
        CPPUNIT_ASSERT_EQUAL(val, i.value());
    }
}

void t_ParseTwoDigit()
{
    
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestInteger);

