#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Error: No branch name provided."
	exit 1
fi

branch_name=$1
git checkout -b $branch_name
git push -u origin $branch_name
