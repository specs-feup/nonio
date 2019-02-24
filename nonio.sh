#!/usr/bin/env bash

# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")

# Set environment variable with location of Nonio
export NONIO_HOME=$SCRIPTPATH

#args="laradFoldername:"
args="dummy:"
args2=$args\'$SCRIPTPATH\'


for var in "$@"
do
    args2+=","
    args2+=$var
    #args3=$args2","
    #args4=$args3$var
done
#echo "$args2"

#echo clava $SCRIPTPATH/LaradLauncher.lara --argv=\"{$args2}\" -nw  -b 2 -s
#clava $SCRIPTPATH/LaradLauncher.lara --argv=\"{$args2}\" -nw  -b 2 -s

echo clava $SCRIPTPATH/LaradLauncher.lara --argv=$1 -nw  -b 2 -s
clava $SCRIPTPATH/LaradLauncher.lara --argv=$1 -nw  -b 2 -s
