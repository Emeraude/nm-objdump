#!/bin/sh

[ $# -eq 0 ] && echo "Usage: $0 commands..." && exit 1
cd $(dirname $0)
for cmd in $@
do
    echo -e "\033[35mTesting file $cmd\033[0m"
    nm "$cmd" > .__real_nm
    ../my_nm "$cmd" > .__my_nm
    diff .__my_nm .__real_nm && {
	echo -e "\033[32mNo diff\033[0m"
    } || {
	echo -e "\033[31mOutput differs\033[0m"
	echo -e "\033[31mUser file is on the left\033[0m"
    }
    rm -f .__real_nm .__my_nm
done
