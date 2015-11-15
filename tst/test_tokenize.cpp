#include "test_tokenize.h"
#include "tokenize.h"
#include <sstream>

TestTokenize::TestTokenize()
{
}

void TestTokenize::setUp()
{
}

void TestTokenize::tearDown()
{
}

void TestTokenize::t_EmptyStringReturnsEmptyList()
{
    std::stringstream iss;
    const auto ret = tokenize(iss);
    CPPUNIT_ASSERT(ret.empty());
}

void TestTokenize::t_SpacesIgnored()
{
    typedef std::pair<std::string, Tokens> Case;
    std::vector<Case> cases = {
        // [test case]     , [expected result]
        //---------------------------------------------
        {"      \t\n"      , {}                       },
        {"     ("          , {"("}                    },
        {"(     + 1 \n\t2)", {"(", "+", "1", "2", ")"}}
    };

    int num = 0;
    for (const auto& c : cases) {
        std::cout << "Case #" << num++ << "\n";
        std::stringstream iss;
        iss << c.first;
        const auto ret = tokenize(iss);
        CPPUNIT_ASSERT_EQUAL(c.second, ret);
    }
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenize);
