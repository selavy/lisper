#include "test_string.h"
#include "str.h"
#include <sstream>
#include <vector>
#include <string>

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
    CPPUNIT_ASSERT_EQUAL(std::string("\"\""), str.toString());
}

void TestString::t_BasicStrings()
{
    std::vector<std::string> cases = {
        "Hello",
        "Hello World",
        "THiS iS a \n String\t\n%^",
        "\"Quoted String\"",
        "'\"\"'''''\"&&*&^%$%asdfjhasdfn"
    };

    for (const auto& c: cases) {
        std::string tmp = '"' + c + '"';
        String str(tmp.c_str());
        CPPUNIT_ASSERT_EQUAL(tmp, str.toString());
    }
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestString);
