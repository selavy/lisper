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

    void t_IsSingleDigit();
    void t_IsNumber();
    void t_IsSignedNumber();
    void t_ParseDigit();
    void t_ParseNumber();
    void t_ParseSignedNumber();

    CPPUNIT_TEST_SUITE(TestParseNumber);
    CPPUNIT_TEST(t_IsSingleDigit);
    CPPUNIT_TEST(t_IsNumber);
    CPPUNIT_TEST(t_IsSignedNumber);
    CPPUNIT_TEST(t_ParseDigit);
    CPPUNIT_TEST(t_ParseNumber);
    CPPUNIT_TEST(t_ParseSignedNumber);
    CPPUNIT_TEST_SUITE_END();
};

#endif // TEST_PARSE_NUMBER__H_