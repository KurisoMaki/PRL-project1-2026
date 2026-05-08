1. projekt
Požadavky na absolvování
První projekt - Minimum extraction sort
Pomocí knihovny Open MPI implementujte v jazyce C++ algoritmus Minimum extraction sort podle přednášek. 

Aktualizace zadání
Případné aktualizace zadání budou vždy uvedeny zde a publikovány na fóru k projektu.

22.2.2026: upravena ukázka výstupu, algoritmus seřadí celou vstupní posloupnost
25.2.2026: doplněna poznámka o načítaní vstupu, můžete ho načítat jedním procesem
7.3.2026: doplněna loňská verze algoritmu
Odevzdání
Projekt odevzdejte nejpozději 29. 3. 2026, 23:59:59 do StudISu. Odevzdává se:

dobře okomentovaný zdrojový soubor mes.cpp a
testovací skript test.sh (viz dále).
Projekty budou hodnoceny a testovány na serveru merlin.
Zadání
Implementuje algoritmus Minimum extraction sort tak, jak byl prezentován na přednáškách. Na vstupu předpokládejte neseřazenou posloupnost celých čísel. Vstupní posloupnost načítejte ze souboru numbers (lze jedním procesem).

Algoritmus z loňských přednášek
Vzhledem k tomu, že bylo zadání zveřejněno dříve, než letošní přednáška, můžete použít i loňskou verzi algoritmu. 

Soubor numbers
Soubor numbers obsahující čísla velikosti 1 byte, která jdou bez mezery za sebou. Pro příklad vytvoření tohoto souboru uvádíme kód níže. ve kterém je ukázáno vytvoření takovéto posloupnosti náhodných čísel a její uložení do souboru pomocí utility dd. Tato utilita generuje náhodná čísla v rozsahu určeném velikostí bloku. Při bloku 1B jsou hodnoty v rozsahu 0-255. Vygenerovaná čísla jsou pak přesměrována do souboru. Vznikne tedy další soubor s náhodnými znaky jdoucími bez mezery za sebou. Po otevření v libovolném textovém editoru se hodnoty tváří jako náhodné ascii znaky, které by však měly být chápany jako celá čísla. Soubor je v tomto případě chápan jako binární.

Generování testovacích dat, testování programu
Pro generování testovacích dat a testování můžete použít následující skript (doplňte označené chybějící části). Přijímá jeden parametr - počet čísel v souboru numbers:

#!/bin/bash

# $1 - pocet cisel v souboru numbers
# kontrola na pocet argumentu
if [ $# -ne 1 ]; then
  exit 1;
fi;
# TODO: pridejte vypocet poctu procesoru dle prednasek a kontrolu, zda je zadany pocet procesu dostatecny
$numProc=... 
# preklad
mpic++ --prefix /usr/local/share/OpenMPI -o mes mes.cpp

# vygenerovani nahodne posloupnosti cisel, pocet dan prvnim parametrem skriptu
dd if=/dev/random bs=1 count=$1 of=numbers 2>/dev/null
# spusteni aplikace (oversubscribe - vice procesu nez fyzicky k dispozici)
mpirun --oversubscribe --prefix /usr/local/share/OpenMPI -np $numProc mes

# uklid
rm -f mes numbers
Výstup
Program na standardní výstup (stdout) vypíše:

posloupnost na vstupu (čísla budou odděleny jednou mezerou), 
na dalším řádku vypíše celou seřazenou posloupnost od nemenšího prvku
Pokud se vyskytne chyba, vypište ji na standardní chybový výstup (stderr). Pro 4 prvky může výstup vypadat např. takto:

54 53 70 25 
25
53
54
70

Hodnocení
V rámci hodnocení se zaměřím na

dodržení zadání (tj. aby program dělal co má dle zadání, a vypisoval co má na stdout),
funkčnost programu, dodržení předepsaného algoritmu (za nedodržení algoritmu lze očekávat  výrazné bodové srážky) a 
kvalitu zdrojového kódu (komentáře, pojmenování proměnných a konstant, ...) 
Použití AI v projektu
Nástroje umělé inteligence můžete použít jako konzultanty při řešení projektu. Je přísně zakázáno odevzdat zdrojový kód zcela (nebo z větší části) vygenerovaný nástroji umělé inteligence.

Diskuse, dotazy
S dotazy se obracejte na veigend@fit.vut.cz , případně lze využít i diskusní fórum pro dotazy.
