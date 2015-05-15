#!/bin/bash
#
#
# Builds and runs default version of project
make remake
IFILE="test.ccgen"
OFILE="test.c"

./build/ccgen $IFILE $OFILE