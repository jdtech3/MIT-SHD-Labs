#!/bin/bash

if [ -z "$*" ]; then 
    echo "Executable argument required!"
    exit 0
fi


rm -f log/${1}.log log/${1}.error log/${1}.out

condor_submit log=log/${1}.log error=log/${1}.error output=log/${1}.out \
              executable=bin/${1} launch.condor

condor_wait log/${1}.log
