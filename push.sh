#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Error: No commit message provided."
	exit 1
fi

git add .
git commit -m "$*"
git push
