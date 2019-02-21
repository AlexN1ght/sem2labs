#!/bin/bash

LET=let
NUM=num

read path

if [ -r $path ]
then
    continue 
else
    echo "Файла $path не существует"
    exit
fi

echo ""
echo "Start conf:"
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

while read Upref
do
    case "$Upref" in
        path) read path
        echo "path = $path";;
        type) read type
        echo "type = $type";;
        number) read number
        echo "number = $number";;
        startnum) read startnum
        echo "startnum = $startnum";;
        startlet) read startlet
        echo "startlet = $startlet";;
        clone) break;;
        *) echo "Неизвестная команда.";;
    esac
done


for (( i = 0; i < $number; i++ ))
do

    if [ $type = $LET ]
    then
        if [ $startlet = $(echo "$startlet" | tr "a-yA-Y" "b-zB-Z")]
        then
            echo "Maximum amount of letter-type clones"
            break
        fi
        cp $path $path'_'$startlet
        startlet=$(echo "$startlet" | tr "a-yA-Y" "b-zB-Z")
    elif [ $type = $NUM ]
    then
        cp $path $path'_'$(($startnum + $i))
    fi

done
echo "Done"
