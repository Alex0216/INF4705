#!/bin/bash
set +C
#Merge sort
echo "Merge sort Seuil"
for i in 1000 5000 10000 50000 100000 500000
do
for file in ./tp1-H10-donnees/testset_${i}_{0..29}.txt;
do
    read -ra values <<< $(./Build/mergeSeuil $file $i)
    echo $file";"$values
done
done