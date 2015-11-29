#include "test_pair.h"
#include <sstream>
#include <iostream>
#include "pair.h"
#include "integer.h"

TestPair::TestPair()
{
}

void TestPair::setUp()
{
}

void TestPair::tearDown()
{
}

void TestPair::t_EmptyTest()
{
    Pair p;
    CPPUNIT_ASSERT(!p.first());
    CPPUNIT_ASSERT(!p.second());
}

void TestPair::t_TwoIntegers()
{
    ObjectPtr a(new Integer("100"));
    ObjectPtr b(new Integer("200"));

    Pair p(a.release(), b.release());

    CPPUNIT_ASSERT(p.first()->isNumber());
    CPPUNIT_ASSERT(p.second()->isNumber());
    CPPUNIT_ASSERT_EQUAL(100L, dynamic_cast<Integer const&>(*p.first()).value());
    CPPUNIT_ASSERT_EQUAL(200L, dynamic_cast<Integer const&>(*p.second()).value());
}

void TestPair::t_Cons()
{
    ObjectPtr a(new Integer("100"));
    ObjectPtr b(new Integer("200"));
    ObjectPtr p = CONS(a, b);

    Pair const* pp = dynamic_cast<Pair const*>(p.get());
    CPPUNIT_ASSERT(pp->first()->isNumber());
    CPPUNIT_ASSERT(pp->second()->isNumber());
    CPPUNIT_ASSERT_EQUAL(100L, dynamic_cast<Integer const&>(*pp->first()).value());
    CPPUNIT_ASSERT_EQUAL(200L, dynamic_cast<Integer const&>(*pp->second()).value());
}

void TestPair::t_ListFromPairs()
{
    ObjectPtr a(new Integer("100"));
    ObjectPtr b(new Integer("200"));
    ObjectPtr c(new Integer("300"));

    ObjectPtr tail(new Pair(c.release(), nullptr));
    ObjectPtr myPair = CONS(CONS(a, b), tail);

    
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestPair);

