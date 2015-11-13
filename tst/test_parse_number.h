#ifndef TEST_PARSE_NUMBER__H_
#define TEST_PARSE_NUMBER__H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestParseNumber : public CppUnit::TestFixture
{
public:
    TestParseNumber();
    virtual ~TestParseNumber() {}
    virtual void setUp();
    virtual void tearDown();

    void t_ParseIsSingleDigit();

    CPPUNIT_TEST_SUITE(TestParseNumber);
    CPPUNIT_TEST(t_ParseIsSingleDigit);
    CPPUNIT_TEST_SUITE_END();
};

#endif // TEST_PARSE_NUMBER__H_
