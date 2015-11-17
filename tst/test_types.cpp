#include "test_types.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include "empty.h"
#include "boolean.h"
#include "str.h"
#include "vec.h"
#include "number.h"

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

void TestTypes::t_PrintVector()
{
    std::vector<std::unique_ptr<Object>> objs;
    typedef std::pair<std::string, std::string> Case;
    std::vector<Case> vals = {
        {"string", "\"Hello\""},
        {"string", "\"World\""},
        {"boolean", "#t"},
        {"empty", ""}
    };
        
    for (const auto& it : vals) {
        if (it.first == "string") {
            objs.emplace_back(new String(it.second.c_str()));
        }
        else if (it.first == "boolean") {
            objs.emplace_back(new Boolean(it.second.c_str()));
        }
        else if (it.first == "empty") {
            objs.emplace_back(new Empty);
        }
    }

    std::unique_ptr<Vector> vec(new Vector);
    for (const auto& it : objs) {
        vec->push_back(*(it.get()));
    }

    std::ostringstream oss;
    oss << *vec;
    std::string expected = "( 'Hello', 'World', '#t', '()' )";
    CPPUNIT_ASSERT_EQUAL(expected, oss.str());
}

void TestTypes::t_PrintNumber()
{
    Number num;
    CPPUNIT_ASSERT_EQUAL(num.value(), 0L);
    std::ostringstream oss;
    oss << num;
    CPPUNIT_ASSERT_EQUAL(std::string("0"), oss.str());

    typedef std::pair<std::string, int64_t> Case;
    std::vector<Case> cases = {
        {"0", 0L},
        {"100", 100L},
        {"100000", 100000L},
        {"2", 2L}
    };

    for (const auto& c : cases) {
        Number n(c.first.c_str());
        std::ostringstream oss;
        oss << n;
        CPPUNIT_ASSERT_EQUAL(c.second, n.value());
        CPPUNIT_ASSERT_EQUAL(c.first, oss.str());
    }
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestTypes);

