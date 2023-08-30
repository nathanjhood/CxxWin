#!/usr/bin/sh

##
# rccompiler.sh
# author StoneyDSP (nathanjhood@googlemail.com)
# brief: 'windres.exe' is essentially a front-end for the preprocessor
# with a definition - 'RC_INVOKED' - added to include 'ifdef'd code.
# version 1.0.0-init
# date 2023-08-23
#
# copyright Copyright (c) 2023
##

this=$0
input=$1
output=$2

echo ""
echo "Running $this on $input"

cc -E -xc -DRC_INVOKED ${input} -o ${output}

echo ""
echo "Completed $this on $output"
