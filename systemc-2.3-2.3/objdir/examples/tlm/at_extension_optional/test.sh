#!/bin/sh
## ****************************************************************************
##
##  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
##  more contributor license agreements.  See the NOTICE file distributed
##  with this work for additional information regarding copyright ownership.
##  Accellera licenses this file to you under the Apache License, Version 2.0
##  (the "License"); you may not use this file except in compliance with the
##  License.  You may obtain a copy of the License at
##
##   http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
##  implied.  See the License for the specific language governing
##  permissions and limitations under the License.
##
## ****************************************************************************
##
##  test.sh.in --
##  Process this file (during `make check') to produce a test.sh file.
##
##  Original Author: Philipp A. Hartmann, 2013-05-20
##
## ****************************************************************************
##
##  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
##  changes you are making here.
##
##      Name, Affiliation, Date:
##  Description of Modification:
##
## ****************************************************************************

#set -x
#set -e

# override user's SHELL (e.g. for SHELL=/bin/tcsh)
SHELL=/bin/sh
export SHELL

## SystemC / TLM example test to run
TEST=at_extension_optional/test
INPUT=results/input.txt
GOLDEN=results/expected.log
FILTER=

# prepare environment
TESTDIR=`dirname "$0"`
TESTEXE=`basename "${TEST}"`
export TEST TESTDIR TESTEXE

# switch to test directory and restart
if test ! x"$TESTDIR" = x. ; then
  cd "$TESTDIR"
  exec ${SHELL} `basename "$0"` "$@"
fi

if test ! -f "${INPUT}" ; then INPUT="" ; fi
if test "x${INPUT}"  != x ; then INPUT="< '${INPUT}'" ; fi
if test "x${FILTER}" != x ; then FILTER="| grep '${FILTER}'" ; fi

# run test executable
eval "./${TESTEXE} ${INPUT} ${FILTER} > run.log"
result=$?

# no golden -> return exit status
if test ! -e "${GOLDEN}" ; then exit $result ; fi

cat run.log | grep -v "stopped by user" |  \
  awk '{if($0!="") print $0}' > run_trimmed.log
cat ${GOLDEN} | grep -v "stopped by user" | \
  awk '{if($0!="") print $0}' > ./expected_trimmed.log

diff ./run_trimmed.log ./expected_trimmed.log > diff.log 2>&1;
result=$?

if test -s diff.log ; then
  echo "***ERROR:"
  cat diff.log
else
  echo "OK"
fi

rm -f *_trimmed.log run.log diff.log
exit $result
