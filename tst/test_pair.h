#ifndef TEST_PAIR__H_
#define TEST_PAIR__H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestPair : public CppUnit::TestFixture
{
public:
    TestPair();
    virtual ~TestPair() {}
    virtual void setUp();
    virtual void tearDown();

    void t_EmptyTest();
    void t_TwoIntegers();
    void t_Cons();
    void t_ListFromPairs();

    CPPUNIT_TEST_SUITE(TestPair);
    CPPUNIT_TEST(t_EmptyTest);
    CPPUNIT_TEST(t_TwoIntegers);
    CPPUNIT_TEST(t_Cons);
    CPPUNIT_TEST(t_ListFromPairs);
    CPPUNIT_TEST_SUITE_END();
    
};

#endif // TEST_PAIR__H_

