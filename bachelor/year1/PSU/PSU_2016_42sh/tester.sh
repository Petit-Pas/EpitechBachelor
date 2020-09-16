#!/bin/bash

MYSHELL="$PWD/42sh"
REFER="/bin/tcsh -f"
TRAPSIG=0
note=0
sur=0
debug=1
CRASHED=0
if [ $# = 0 ]
then
    ARG="lol"
else
    ARG=$1
fi
CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`
DIFF=`which diff`

VERSION=`$GREP "VERSION=" tests | $SED s/'VERSION='// | $SED s/'"'//g`
BY=`$GREP "BY=" tests | $SED s/'BY='// | $SED s/'"'//g`
AT=`$GREP "AT=" tests | $SED s/'AT='// | $SED s/'"'//g`

rm -rf /tmp/test.*
rm -rf /tmp/.shell.*
rm -rf /tmp/.refer.*
rm -rf /tmp/.tester.*
rm -rf /tmp/.runner.*
make re
clear
cat /dev/urandom | tr -dc 'A-Za-z0-9\t ' | head -c 10000 > .tmp
cat /dev/urandom | tr -dc '\n' | head -c 10000 > .tmp2

disp_test()
{
  id=$1
  $CAT tests | $GREP -A1000 "^\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

run_script()
{
  SC="$1"
  echo "$SC" > /tmp/.tmp.$$
  . /tmp/.tmp.$$
  $RM -f /tmp/.tmp.$$
}

prepare_test()
{
  local testfn="/tmp/.tester.$$"
  local runnerfn="/tmp/.runner.$$"
  local refoutfn="/tmp/.refer.$$"
  local shoutfn="/tmp/.shell.$$"

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$CLEAN" >> $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$TCSHUPDATE" >> $runnerfn
  if [ \( "$ARG" = "-vi" \) -o \( "$ARG" = "-iv" \) ]
  then
      echo "/bin/bash -c '"$testfn" | env -i valgrind "$MYSHELL" ; echo Shell exit with code \$? '> "$shoutfn" 2>&1" >> $runnerfn
  else
      if [ "$ARG" = "-v" ]
      then
	  echo "/bin/bash -c '"$testfn" | valgrind "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
      else
	  if [ "$ARG" = "-i" ]
	  then
	      echo "/bin/bash -c '"$testfn" | env -i "$REFER" ; echo Shell exit with code \$?' > "$refoutfn" 2>&1" >> $runnerfn
	      echo "/bin/bash -c '"$testfn" | env -i "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
	  else
	      echo "/bin/bash -c '"$testfn" | "$REFER" ; echo Shell exit with code \$?' > "$refoutfn" 2>&1" >> $runnerfn
	      echo "/bin/bash -c '"$testfn" | "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
	  fi
      fi
  fi 
  echo "$CLEAN" >> $runnerfn

  echo "#!/bin/bash" > $testfn
  echo "$TESTS" | $TR "²" "\n" >> $testfn

  chmod 755 $testfn
  chmod 755 $runnerfn
}

load_test_valgrind()
{
    id=$1
    ((sur++))
    SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
    CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
    NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
    TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
    TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`
    prepare_test
    $WRAPPER
    Ir=`cat /tmp/.shell.$$ | $GREP "Invalid read" -2`
    Iw=`cat /tmp/.shell.$$ | $GREP "Invalid write" -2`
    Cond=`cat /tmp/.shell.$$ | $GREP Conditionnal -2`
    Iff=`cat /tmp/.shell.$$ | $GREP "Invalid free" -2`
    Termin=`cat /tmp/.shell.$$ | $GREP "Process terminating with default"`
    echo -ne "$Ir $Iw $Cond $Iff" > .lolilol 
    g=`cat .lolilol | $WC -l`
    crash=`$CAT /tmp/.shell.$$ | $GREP "core dumped" | wc -l`
    $MKDIR -p /tmp/test.$$/$id 2>/dev/null
    $CP /tmp/.shell.$$ /tmp/test.$$/$id/42sh.out
    ST=`$CAT /tmp/.shell.$$ | $GREP "Shell exit with code" | cut -d' '  -f 5`
    if [ $g -eq 0 ]
    then
	((note++))
	echo -e "Test $id ($NAME) : \033[32mOK\033[00m"
    else
	di=`$CAT .lolilol`
	if [ \( $crash -eq 0 \) ]
	then
	    echo -e "Test $id ($NAME) : \033[31mKO\033[00m - Check output in /tmp/test.$$/$id/"
	else
	    ((CRASHED++))
	    echo -e "Test $id ($NAME) : \033[41mCRASH\033[00m - Check output in /tmp/test.$$/$id/"
	fi 
	echo -e "\033[31m$di\033[00m"
    fi
    rm -rf .lolilol
}

load_test()
{
    id=$1
    ((sur++))
    SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
    CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
    NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
    TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
    TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`
    prepare_test
    $WRAPPER
    g=`$DIFF /tmp/.refer.$$ /tmp/.shell.$$ | $WC -l`
    crash=`$CAT /tmp/.shell.$$ | $GREP "core dumped" | wc -l`
    $MKDIR -p /tmp/test.$$/$id 2>/dev/null
    $CP /tmp/.shell.$$ /tmp/test.$$/$id/42sh.out
    $CP /tmp/.refer.$$ /tmp/test.$$/$id/tcsh.out
    if [ $g -eq 0 ]
    then
	((note++))
	echo -e "Test $id ($NAME) : \033[32mOK\033[00m"
    else
	di=`$DIFF /tmp/.shell.$$ /tmp/.refer.$$`
	if [ $crash -eq 0 ]
	then
	    echo -e "Test $id ($NAME) : \033[31mKO\033[00m - Check output in /tmp/test.$$/$id/"
	else
	    ((CRASHED++))
	    echo -e "Test $id ($NAME) : \033[41mCRASH\033[00m - Check output in /tmp/test.$$/$id/"
	fi 
	echo -e "\033[31m$di\033[00m"
    fi
}

if [ $TRAPSIG -eq 1 ]
then
    for sig in `trap -l`
    do
	echo "$sig" | grep "^SIG" >/dev/null 2>&1
	if [ $? -eq 0 ]
	then
	    trap "echo Received signal $sig !" $sig
	fi
    done
fi

if [ ! -f tests ]
then
    echo "No tests file. Please read README.ME" >&2
    exit 1
fi

if [ ! -f $MYSHELL ]
then
    echo "$MYSHELL not found" >&2
    exit 1
fi

for lst in `cat tests | grep "^\[.*\]$" | grep -vi end | sed s/'\['// | sed s/'\]'//`
do
    path_backup=$PATH
    if [ \( "$ARG" = "-v" \) -o \( "$ARG" = "-vi" \)  -o \( "$ARG" = "-iv" \) ]
    then
	load_test_valgrind $lst 1
    else
	load_test $lst 1
    fi
    export PATH=$path_backup
done
echo -e "\033[34mTester modifié par \033[32mSahel"
echo -e "\033[34mTests fourni par \033[32m$BY"
echo -e "\033[34mDe la ville de \033[32m$AT"
echo -e "\033[34mVersion : \033[32m$VERSION\033[00m"
if [ $note -eq $sur ]
then
    echo -e "\033[32mMark : $note / $sur\033[00m"
    echo -e "$CRASHED crash"
else
    echo -e "\033[31mMark : $note / $sur\033[00m"
    echo -e "$CRASHED crash"
fi
rm -rf .tmp
rm -rf .tmp2
