#ifndef TEST_INTEGER__H_
#define TEST_INTEGER__H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestInteger : public CppUnit::TestFixture
{
public:
    TestInteger();
    virtual ~TestInteger() {}
    virtual void setUp();
    virtual void tearDown();

    void t_ParseDigit();
    void t_ParseTwoDigit();

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(t_ParseDigit);
    CPPUNIT_TEST_SUITE_END();
    
};

#endif // TEST_INTEGER__H_
