#!/bin/bash
set +C
for file in ./tp1-H10-donnees/testset_1000_[0-9].txt;
do
read -ra values <<< $(./Build/Selection $file 1000)
echo $file";"$values
done
