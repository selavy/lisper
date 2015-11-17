#include "test_types.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include "empty.h"
#include "boolean.h"
#include "str.h"

TestTypes::TestTypes()
{
}

void TestTypes::setUp()
{
}

void TestTypes::tearDown()
{
}

void TestTypes::t_PrintEmpty()
{
    std::unique_ptr<Object> obj(new Empty);
    std::ostringstream oss;
    oss << *obj;
    CPPUNIT_ASSERT_EQUAL(oss.str(), std::string("()"));
}

void TestTypes::t_PrintBoolean()
{
    {
        std::unique_ptr<Object> obj(new Boolean("#t"));
        std::ostringstream oss;
        oss << *obj;
        CPPUNIT_ASSERT_EQUAL(oss.str(), std::string("#t"));
    }
    {
        std::unique_ptr<Object> obj(new Boolean("#f"));
        std::ostringstream oss;
        oss << *obj;
        CPPUNIT_ASSERT_EQUAL(oss.str(), std::string("#f"));
    }

    std::vector<std::string> all_true = {
        "TRUE",
        "1",
        "#t",
        "tRuE",
        "26"
    };
    for (const auto& it : all_true) {
        std::unique_ptr<Object> obj(new Boolean(it.c_str()));
        std::ostringstream oss;
        oss << *obj;
        CPPUNIT_ASSERT_EQUAL(oss.str(), std::string("#t"));
    }        
}

void TestTypes::t_PrintString()
{
    std::vector<std::string> cases = {
        "Hello World",
        "STRING",
        "",
    };

    for (const auto& c : cases) {
        std::string tmp = "\"" + c + "\"";
        std::unique_ptr<Object> obj(new String(tmp.c_str()));
        std::ostringstream oss;
        oss << *obj;
        CPPUNIT_ASSERT_EQUAL(c, oss.str());
    }
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestTypes);

