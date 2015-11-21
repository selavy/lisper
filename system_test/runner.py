#!/usr/bin/env python

def test_case(line):
    inn, out = line.split('=>')
    print "INPUT: ", inn
    print "OUTPUT: ", out

if __name__ == '__main__':
    with open('cases.in') as fin:
        for line in fin:
            test_case(line.strip())
