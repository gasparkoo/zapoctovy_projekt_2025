# TYPE RACER
Tento program slúži na skúšanie rýchlopisu. Užívatel si vie vyskúšať prepísať zadaný vygenerovaný text, ktorý bude neskôr ohodnotený. Program vyhodnotí rychlosť a aj správnosť prepísaného textu. 
## Užívateľská časť

### Spustenie programu
Na spustenie treba mať nainštalovaný kompilátor jazyka C++. Program sa dá skompilovať nasledovným príkazom: 

```bash
g++ .\main.cpp .\levenshtein.cpp .\generovanie.cpp .\editacna_vzdialenost.cpp -o main.exe
```
Po spustený programu `.\main.exe` sa spýta, aký dlhý má vygenerovať text a následne sa mu spustí časovač. Po prepísaní textu a stlačeník klávesy ENTER sa časovač vypne a vypíše sa čas, chybovosť a WPM (počet slov za minútu).

Takto vyzerá priebeh programu. `>` značí vstup od užívateľa. 
```
Napis dlzku vygenerovaneho textu: > 20
doing gym. It rains.
Mozes pisat
> doing gym. Ot mains.
cas: 12
chybovost: 6
WPM: 20
```

### Konfigurácia
V súbore `text.txt` sú uložené texty, z ktorých program vygeneruje vzorku na precvičenie rýchlopisu. Viacero neviditeľných znakov (medzera, odsek, tabulátor,...) za sebou sa ignoruje. Preto text môže obsahovať aj odseky. Odporúčané je zadávať anglický text.

V súbore `konfiguracia.txt` sa nachádza zoznam povolených operácii pri zistovaní chybovosti textu a ich konkrétna cena. Operácie sú:
- mazanie - vymazanie jedného písmenka z prepísaného textu,
- transpozicia - vymenenie dvoch susedných písmen v prepísanom texte,
- substitucia - zmena jedného písmenka na iné v rámci prepísaného textu,
- pridavanie - pridanie nového písmenka do prepísaného textu.

Takto napríklad môže vyzerať konfiguračný súbor:
```
mazanie 3
transpozicia 2
substitucia 3
pridavanie 3
```

## Programátorský časť
### Zvolený algoritmus
#### Generovanie textu
Na generovanie textu program používa metódu **Markovských reťazcov**. Program si pre každú k-ticu znakov (k = 4) zo vstupného textu pamätá multimnožinu nasledujúcich znakov. Teda je to nejaká distribúcia znakov v texte. Pri generovaní sa pozrie na poslednú k-ticu a vyberie náhodne k+1 znak zo zapamätanej multimnožiny a pokračuje ďalej. 

#### Vyhodnotenie chybovosti textu
Základ algoritmu je Levenshteinov algoritmus na počítanie editačnej vzdialenosti. 
##### Popis algoritmus
Majme vzorové slovo $v$ a napísané slovo $n$. Chcem si vyplniť tabuľku veľkosti $|n|+1 × |v|+1. Bunka $i, j$ v tabuľke hovorí o chybovosti pre prvých $i$ a $j$ znakov napísaného a vzorového slova. Algoritmus je založený na dynamickom programovaní. Keď chcem zistiť hodnotu políčka $i,j$, zoberiem si minimum z nasledujúcich operácií:

- mazanie - pozriem sa na hodnotu o 1 vyššie a pripočítam cenu mazania.
- transpozicia - pozriem sa, či transpozíciou posledných dvoch písmen dostanem posledné dve písmená prvých $j$ znakov vzorového slova.   
  Ak áno, pozriem sa diagonálne o 2. Ak nie, pozriem sa diagonálne o 1. Následne pripočítam cenu transpozície. 
- substitucia - pozriem sa na hodnotu o 1 diagonálne a pripočítam cenu substitúcie.
- pridavanie - pozriem sa na hodnotu o 1 doľava a pripočítam cenu pridavania.



