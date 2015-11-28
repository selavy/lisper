#include "test_boolean.h"
#include "boolean.h"
#include <sstream>
#include <iostream>

TestBoolean::TestBoolean()
{
}

void TestBoolean::setUp()
{
}

void TestBoolean::tearDown()
{
}

void TestBoolean::t_EmptyTest()
{
    Boolean b;
    CPPUNIT_ASSERT_EQUAL(std::string("Boolean"), b.typeToString());
    CPPUNIT_ASSERT_EQUAL(std::string("#f"), b.toString());
    CPPUNIT_ASSERT_EQUAL(false, b.value());
}

void TestBoolean::t_TrueTest()
{
    Boolean b("#t");
    CPPUNIT_ASSERT_EQUAL(true, b.value());
}

void TestBoolean::t_EverythingTrueExceptFalseString()
{
    std::vector<std::string> cases = {
        "#t",
        "false",
        "FALSE",
        "0",
        "1",
        "TRUE",
        "true"
    };

    for (const auto& c : cases) {
        Boolean b(c.c_str());
        CPPUNIT_ASSERT_EQUAL(true, b.value());
    }
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestBoolean);

