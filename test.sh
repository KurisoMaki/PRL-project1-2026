# test.sh 

# PRL 2024/2025 - Projekt c. 1
# Autor: Sofiia Kucherenko, xkucer0v
#!/bin/bash

# $1 - pocet cisel v souboru numbers
# kontrola na pocet argumentu
if [ $# -ne 1 ]; then
  echo "Pouziti: $0 <pocet_cisel>"
  exit 1;
fi;

# kontrola, zda je zadany pocet cisel alespon 1
if [ "$1" -lt 1 ]; then
  echo "Chyba: Pocet cisel musi byt alespon 1." >&2
  exit 1;
fi;

# Vypocet poctu procesoru: p(n) = 2n - 1
numProc=$((2 * $1 - 1))

# preklad
mpic++ -o mes mes.cpp

# vygenerovani nahodne posloupnosti cisel, pocet dan prvnim parametrem skriptu
dd if=/dev/random bs=1 count=$1 of=numbers 2>/dev/null

# spusteni aplikace (oversubscribe - vice procesu nez fyzicky k dispozici)
mpirun --oversubscribe -np $numProc mes

# uklid
rm -f mes numbers