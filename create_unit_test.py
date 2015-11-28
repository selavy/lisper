#!/usr/bin/env python

import optparse
import sys
import os

HEADER_SKELETON = """#ifndef {include_guard}
#define {include_guard}

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class {class_name} : public CppUnit::TestFixture
{{
public:
    {class_name}();
    virtual ~{class_name}() {{}}
    virtual void setUp();
    virtual void tearDown();

    void t_EmptyTest();

    CPPUNIT_TEST_SUITE({class_name});
    CPPUNIT_TEST(t_EmptyTest);
    CPPUNIT_TEST_SUITE_END();
    
}};

#endif // {include_guard}
"""

IMPL_SKELETON = """#include "{filename}.h"
#include <sstream>
#include <iostream>

{name}::{name}()
{{
}}

void {name}::setUp()
{{
}}

void {name}::tearDown()
{{
}}

void {name}::t_EmptyTest()
{{
    CPPUNIT_ASSERT(false); // fix test
}}

CPPUNIT_TEST_SUITE_REGISTRATION({name});
"""

def header_file(fin, name, include_guard):
    print >> fin, HEADER_SKELETON.format(
            class_name=name, include_guard=include_guard)

def impl_file(fin, name, filename):
    print >> fin, IMPL_SKELETON.format(
            name=name, filename=filename)

if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option('--name', help='Class name to test.')
    parser.add_option('--test-dir', help='Specify test directory.')
    options, _ = parser.parse_args()

    if not options.name:
        print "--name required"
        sys.exit(0)

    print "Creating unit test skeleton for:", options.name
    if not options.name[0].isupper():
        print "Class name should be CamelCase beginning with an uppercase letter"
        sys.exit(0)
    class_name = "Test" + options.name
    print "Test class name:", class_name

    include_guard = "TEST_{name}__H_".format(name=options.name.upper())
    print "Include guard: ", include_guard


    #print "HEADER FILE\n-------------------------------"
    #header_file(sys.stdout, name=class_name, include_guard=include_guard)

    filename = "test_" + options.name.lower()
    #print "IMPL FILE\n---------------------------------"
    #impl_file(sys.stdout, name=class_name, filename=filename)

    directory = options.test_dir or './tst'
    os.chdir(directory)
    print os.getcwd()

    with open(filename + '.h', 'w') as fout:
        header_file(fout, name=class_name, include_guard=include_guard)
    with open(filename + '.cpp', 'w') as fout:
        impl_file(fout, name=class_name, filename=filename)

    with open('unittest.cpp') as fin:
        lines = fin.readlines()
        num = 0
        for i, line in enumerate(lines):
            if 'END TESTS' in line:
                num = i
                break
        if num == 0:
            raise RuntimeError("Unable to find where to insert header file line!")
        lines.insert(num, '''#include "{filename}.h"\n'''.format(filename=filename))

    with open('unittest.cpp', 'w') as fout:
        print >> fout, ''.join(lines)

    with open('CMakeLists.txt') as fin:
        lines = fin.readlines()
        num = 0
        for i, line in enumerate(lines):
            if 'END TESTS' in line:
                num = i
                break
        if num == 0:
            raise RuntimeError("Unable to find where to insert file into CMakeLists.txt!")
        lines.insert(num, '''  {filename}.cpp\n'''.format(filename=filename))

    with open('CMakeLists.txt', 'w') as fout:
        print >> fout, ''.join(lines)

