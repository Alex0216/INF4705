#!/bin/bash

set +C
#Selection sort
echo "Selection Sort"
for i in 1000 5000 10000 50000 100000 500000
do
for file in ./tp1-H10-donnees/testset_${i}_{0..29}.txt;
do
    read -ra values <<< $(./Build/selection $file $i)
    echo $file";"$values
done
done


#Couting sort
echo "Counting Sort"
for i in 1000 5000 10000 50000 100000 500000
do
for file in ./tp1-H10-donnees/testset_${i}_{0..29}.txt;
do
    read -ra values <<< $(./Build/couting $file $i)
    echo $file";"$values
done
done

#Merge sort
echo "Merge sort"
for i in 1000 5000 10000 50000 100000 500000
do
for file in ./tp1-H10-donnees/testset_${i}_{0..29}.txt;
do
    read -ra values <<< $(./Build/merge $file $i)
    echo $file";"$values
done
done

#Merge sort avec seuil
echo "Merge sort avec seuil"
for i in 1000 5000 10000 50000 100000 500000
do
for file in ./tp1-H10-donnees/testset_${i}_{0..29}.txt;
do
    read -ra values <<< $(./Build/mergeSeuil $file $i)
    echo $file";"$values
done
done
