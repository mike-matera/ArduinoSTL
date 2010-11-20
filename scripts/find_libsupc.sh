#!/bin/sh

#This purpose of this file is to return the filename for libsupc++.a to be used.  We use the script so that it
#can be easily replaced by system developers and cross-compilers so that the user doesn't require an installed
#instance of libstdc++ on their system to use the library - just point at the appropriate location in the
#gcc build directory and rip it apart.

$CC -print-file-name=libsupc++.a

