#!/bin/bash
rm data.txt
for((i=1; i<31; i++)); do
  ./sim 1 $i 0.06 0.01
done
for((i=1; i<31; i++)); do
  ./sim 2 $i 0.06 0.01
done
for((i=1; i<31; i++)); do
  ./sim 3 $i 0.06 0.01
done
#for((i=1; i<31; i++)); do #RR yields Seg faults
#  ./sim 4 $i 0.06 0.01
#done
#for((i=1; i<31; i++)); do
#  ./sim 4 $i 0.06 0.2
#done
exit 0
