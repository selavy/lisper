#ifndef TEST_BOOLEAN__H_
#define TEST_BOOLEAN__H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestBoolean : public CppUnit::TestFixture
{
public:
    TestBoolean();
    virtual ~TestBoolean() {}
    virtual void setUp();
    virtual void tearDown();

    void t_EmptyTest();
    void t_TrueTest();
    void t_EverythingTrueExceptFalseString();

    CPPUNIT_TEST_SUITE(TestBoolean);
    CPPUNIT_TEST(t_EmptyTest);
    CPPUNIT_TEST(t_TrueTest);
    CPPUNIT_TEST(t_EverythingTrueExceptFalseString);
    CPPUNIT_TEST_SUITE_END();
    
};

#endif // TEST_BOOLEAN__H_

