#include "test_string.h"
#include "str.h"
#include <sstream>

TestString::TestString()
{
}

void TestString::setUp()
{
}

void TestString::tearDown()
{
}

void TestString::t_EmptyString()
{
    String str;
    CPPUNIT_ASSERT_EQUAL(std::string("String"), str.typeToString());
    CPPUNIT_ASSERT_EQUAL(std::string(), str.toString());
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestString);
