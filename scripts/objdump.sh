#!/bin/sh

[ $# -eq 0 ] && echo "Usage: $0 commands..." && exit 1
cd $(dirname $0)
for cmd in $@
do
    echo -e "\033[35mTesting file $cmd\033[0m"
    objdump -fs "$cmd" > .__real_objdump
    ../my_objdump "$cmd" > .__my_objdump
    diff .__my_objdump .__real_objdump && {
	echo -e "\033[32mNo diff\033[0m"
    } || {
	echo -e "\033[31mOutput differs\033[0m"
	echo -e "\033[31mUser file is on the left\033[0m"
    }
    rm -f .__real_objdump .__my_objdump
done
