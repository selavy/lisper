#include "test_types.h"
#include "empty.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>

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

CPPUNIT_TEST_SUITE_REGISTRATION(TestTypes);

