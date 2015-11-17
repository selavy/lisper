#ifndef TEST_TYPES__H_
#define TEST_TYPES__H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestTypes : public CppUnit::TestFixture
{
public:
    TestTypes();
    virtual ~TestTypes() {}
    virtual void setUp();
    virtual void tearDown();

    void t_PrintEmpty();
    void t_PrintBoolean();
    void t_PrintString();
    void t_PrintVector();
    void t_PrintNumber();
    void t_PrintSymbol();

    CPPUNIT_TEST_SUITE(TestTypes);
    CPPUNIT_TEST(t_PrintEmpty);
    CPPUNIT_TEST(t_PrintBoolean);
    CPPUNIT_TEST(t_PrintString);
    CPPUNIT_TEST(t_PrintVector);
    CPPUNIT_TEST(t_PrintNumber);
    CPPUNIT_TEST(t_PrintSymbol);
    CPPUNIT_TEST_SUITE_END();
};

#endif // TEST_TYPES__H_
