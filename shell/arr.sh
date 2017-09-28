#!/bin/bash
hosts=("fabric1" "fabric2")
container_fabric1=("peer0.org1.cib.com")

for host in ${hosts[@]}
do
    echo ${host}
    container=container_$host
    echo `eval echo '$'$container`
done
