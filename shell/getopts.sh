#!/bin/bash

# Create apps
function create-apps() {
    local OPTIND
    cmd="rhc app create -p $OPENSHIFT_PASSWD"
    while getopts a:t:sn x
    do
        case $x in
            a) cmd=$cmd" -a $OPTARG" ;;
            t) cmd=$cmd" -t $OPTARG" ;;
            s) cmd=$cmd" -s" ;;
            n) cmd=$cmd" -n --no-dns" ;;
            \?) echo Invalid Params ;;
        esac
    done
    echo $cmd
}

create-apps -a aaa -t ttt -s -n
