#ifndef TEST_PRIMITIVES__H_
#define TEST_PRIMITIVES__H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestPrimitives : public CppUnit::TestFixture
{
public:
    TestPrimitives() {}
    virtual ~TestPrimitives() {}
    virtual void setUp() {}
    virtual void tearDown() {}

    void t_PlusZeroArgsReturnsZero();
    void t_OnePlusOneIsTwo();
    
    CPPUNIT_TEST_SUITE(TestPrimitives);
    CPPUNIT_TEST(t_PlusZeroArgsReturnsZero);
    CPPUNIT_TEST(t_OnePlusOneIsTwo);
    CPPUNIT_TEST_SUITE_END();
};

#endif // TEST_PRIMITIVES__H_
