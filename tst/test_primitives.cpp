#include "test_primitives.h"
#include "primitive.h"
#include "number.h"
#include <vector>
#include <string>

void TestPrimitives::t_PlusZeroArgsReturnsZero()
{
    Primitive prim("+");
    const auto ret = prim.execute(Procedure::Arguments{});
    if (Number* num = dynamic_cast<Number*>(ret.get())) {
        CPPUNIT_ASSERT_EQUAL(0l, num->value());
    }
    else {
        CPPUNIT_ASSERT(false);
    }    
}

void TestPrimitives::t_OnePlusOneIsTwo()
{
    Primitive prim("+");
    std::unique_ptr<Object> num1(new Number("1"));
    std::unique_ptr<Object> num2(new Number("1"));
    Procedure::Arguments args{*num1.get(), *num2.get()};
    const auto ret = prim.execute(args);
    if (Number* num = dynamic_cast<Number*>(ret.get())) {
        CPPUNIT_ASSERT_EQUAL(2l, num->value());
    }
    else {
        CPPUNIT_ASSERT(false);
    }
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestPrimitives);
