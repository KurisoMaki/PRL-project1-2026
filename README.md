# Minimum Extraction Sort (Open MPI)

Tento projekt implementuje distribuovaný řadicí algoritmus **Minimum Extraction Sort** v jazyce C++ s využitím knihovny **Open MPI**. Projekt byl vytvořen v rámci předmětu zaměřeného na paralelní a distribuované výpočty.

## 📝 Zadání

Cílem je seřadit neseřazenou posloupnost celých čísel pomocí algoritmu Minimum Extraction Sort tak, jak byl prezentován na přednáškách. 
- Vstupní posloupnost je načítána ze souboru `numbers` (načítání může probíhat jedním procesem).
- Čísla v souboru `numbers` mají velikost 1 byte a jdou bez mezery za sebou (generováno např. utilitou `dd` z `/dev/random`).
- Program běží paralelně na více procesorech s využitím zpráv MPI.

## 🚀 Spuštění a testování

Pro generování testovacích dat, kompilaci a spuštění programu je připraven bash skript `test.sh`. Skript přijímá jeden parametr, kterým je počet čísel k seřazení.

### Použití skriptu:
```bash
./test.sh <pocet_cisel>
