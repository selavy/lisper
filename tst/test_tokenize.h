#ifndef TEST_TOKENIZE__H_
#define TEST_TOKENIZE__H_

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestTokenize : public CppUnit::TestFixture
{
public:
    TestTokenize();
    virtual ~TestTokenize() {}
    virtual void setUp();
    virtual void tearDown();

    void t_EmptyStringReturnsEmptyList();
    void t_SpacesIgnored();

    CPPUNIT_TEST_SUITE(TestTokenize);
    CPPUNIT_TEST(t_EmptyStringReturnsEmptyList);
    CPPUNIT_TEST(t_SpacesIgnored);
    CPPUNIT_TEST_SUITE_END();
};

#endif // TEST_TOKENIZE__H_
