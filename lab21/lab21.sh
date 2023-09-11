#! /usr/bin/bash

function help {
    echo "$0 dir=[ПАПКА],length=[КОЛИЧЕСТВО],symbol=[СИМВОЛ]"
}

function get_string_length {
    echo -n $1 | wc -m
}

function rename_file {
    abs_filename=$1 # abs_filename has to be an absolute path to file 
    length=$2
    symbol=$3 

    abs_filedir=$(dirname $abs_filename) 
    filename=$(basename $abs_filename)
    filename_no_ext=$(echo "$filename" | sed 's/\.[^.]*$//') # Все что идет после последней точки удаляем *****
    filename_ext=$(echo "$filename" | sed -r "s/^$filename_no_ext\.?//") # Удаляет имя файла без расширения => остается только расширение 

    cur_length=$(get_string_length $filename_no_ext)  #Текущая длинна
    add_symbols_cnt=$(($length - $cur_length))

    if [[ add_symbols_cnt -le 0 ]]; then 
        return
    fi 

    result_filename_no_ext=$filename_no_ext
    for i in $(seq 1 $add_symbols_cnt); do    
        result_filename_no_ext+=$symbol
    done

    if [[ $filename_ext != '' ]]; then
        mv $abs_filename $abs_filedir/$result_filename_no_ext.$filename_ext
    else 
        mv $abs_filename $abs_filedir/$result_filename_no_ext
    fi
}

dir=""
length=""
symbol=""

if [[ $1 == '--help' ]]; then
    help
    exit 0
fi

for i in ; do
    key=$(echo $i | cut -d '=' -f 1) 
    value=$(echo $i | cut -d '=' -f 2)

    if [[ "$key" == "dir" ]]; then
        if [[ ! -d "$value" ]]; then
            echo "$value does not exist."
            exit 0
        fi
        dir=$value
    elif [[ "$key" == "length" ]]; then
        if [[ $value -le 0 ]]; then
            echo "$key has to be greater than zero!"
            exit 0
        fi
        length=$value
    elif [[ "$key" == "symbol" ]]; then
        if [[ $(get_string_length $value) -ne  1 ]]; then
            echo "$key has to contain only one charector!"
            exit 0
        fi
        symbol=$value
    else 
        echo "Wrong parameter - $key!"
        help
        exit 1 
    fi  
done

if [[ $dir == '' || $length == '' || $symbol == '' ]]; then
    echo "Please, enter all parameters!"
    echo "You can use this example:"
    help
    exit 1
fi

for fname in $(find $dir -type f); do 
    rename_file $fname $length $symbol
done

echo 'Done!'