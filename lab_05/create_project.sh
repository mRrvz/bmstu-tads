#!/bin/bash

while [ -n "$1" ]; do
    {
        echo "#ifndef __${1^^}_H__"
        echo -e "#define __${1^^}_H__\n"
        echo "#endif"
    } > "$1.h"
    
    { 
        echo "#include \"$1.h\" "
    } > "$1.c"
    
    {
        echo -e "#include \"$1.h\""
    } >> main.c

    shift
done
