#!/bin/bash

: this is single line comment
: 'this is a multiline comment,
second line
end of comments'

if [ "1" == "1" ]; then
    echo "yes"
else
    :
fi

cat <<<"hello" > ./test
echo "test file:"
cat ./test
: > ./test
echo "after : > test"
cat ./test
