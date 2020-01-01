#!/bin/bash

while [ -n "$1" ]; do
    {
        echo "#ifndef __${1^^}_H__"
        echo -e "#define __${1^^}_H__\n"
        echo "#endif"
    } > "headers/$1.h"
    
    { 
        echo "#include \"../headers/$1.h\" "
    } > "src/$1.c"
    
    {
        echo -e "#include \"../headers/$1.h\""
    } >> src/main.c

    shift
done
