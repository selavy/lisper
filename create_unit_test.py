#!/usr/bin/env python

import optparse
import sys

if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option('--name', help='Class name to test')
    options, _ = parser.parse_args()

    if not options.name:
        print "--name required"
        sys.exit(0)

    print "Creating unit test skeleton for:", options.name


