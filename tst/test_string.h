#ifndef TEST_STRING__H_
#define TEST_STRING__H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestString : public CppUnit::TestFixture
{
public:
    TestString();
    virtual ~TestString() {}
    virtual void setUp();
    virtual void tearDown();

    void t_EmptyString();
    void t_BasicStrings();

    CPPUNIT_TEST_SUITE(TestString);
    CPPUNIT_TEST(t_EmptyString);
    CPPUNIT_TEST(t_BasicStrings);    
    CPPUNIT_TEST_SUITE_END();
};

#endif // TEST_STRING__H_
