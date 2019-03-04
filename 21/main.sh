#!/bin/bash

LET=let
NUM=num

read path

if [ -r $path ]
then
    echo ""
    echo "Start conf:"
else
    echo "Файла $path не существует"
    exit
fi

countConf=1

for Conf in $(cat config.conf | awk -F"=" '{ print $1; }')
do
    case "$Conf" in
        type) type=$(cat config.conf | awk -F"=" NR\ ==\ $countConf\{print\ \$2\})
        echo "type = $type";;
        number) number=$(cat config.conf | awk -F"=" NR\ ==\ $countConf\{print\ \$2\})
        echo "number = $number";;
        startnum) startnum=$(cat config.conf | awk -F"=" NR\ ==\ $countConf\{print\ \$2\})
        echo "startnum = $startnum";;
        startlet) startlet=$(cat config.conf | awk -F"=" NR\ ==\ $countConf\{print\ \$2\})
        echo "startlet = $startlet";;
    esac
    countConf=$(($countConf + 1))
done


#Info
echo ""
echo ""
echo "Введите:"
echo "path - для изменения пути к файлу клонирования."
echo "number - для изменения количества клонов."
echo "type - для  изменения способа нумерации файлов."
echo "startnum - изменения номера с которого начнется наименование клонирования (для let)."
echo "startnlet - изменения номера с которого начнется наименование клонирования (для num)."
echo "clone - для начала процесса клонирования"
echo ""

while read Upref arg
do
    case "$Upref" in
        path) path=$arg
        echo "path = $path";;
        type) type=$arg
        echo "type = $type";;
        number) number=$arg
        echo "number = $number";;
        startnum) startnum=$arg
        echo "startnum = $startnum";;
        startlet) startlet=$arg
        echo "startlet = $startlet";;
        clone) break;;
        *) echo "Неизвестная команда.";;
    esac
done


for (( i = 0; i < $number; i++ ))
do

    if [ $type = $LET ]
    then
        if [ $startlet = $(echo "$startlet" | tr "a-yA-Y" "b-zB-Z") ]
        then
            echo "Maximum amount of letter-type clones"
            break
        fi
        cp $path $(echo "$path" | awk -F"." '{ print $1; }')'_'$startlet'.'$(echo "$path" | awk -F"." '{ print $2; }')
        startlet=$(echo "$startlet" | tr "a-yA-Y" "b-zB-Z")
    elif [ $type = $NUM ]
    then
        cp $path $(echo "$path" | awk -F"." '{ print $1; }')'_'$startnum'.'$(echo "$path" | awk -F"." '{ print $2; }')
    fi

done
echo "Done"
