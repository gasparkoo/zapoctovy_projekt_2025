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
- transpozicia - pozriem sa, či transpozíciou posledných dvoch písmen dostanem posledné dve písmená prvých $j$ znakov vzorového slova. Ak áno, pozriem sa diagonálne o 2. Ak nie, pozriem sa diagonálne o 1. Následne pripočítam cenu transpozície. 
- substitucia - pozriem sa na hodnotu o 1 diagonálne a pripočítam cenu substitúcie.
- pridavanie - pozriem sa na hodnotu o 1 doľava a pripočítam cenu pridavania.

### Diskusia o voľbe algoritmu
Použila som základný algoritmus na výpočet editačnej vzdialenosti. Jednotlivé operácie na slovách som abstrahovala do abstraktnej triedy Operacia. Ako konkrétne operácie na slovách som si určila mazanie, pridávanie, substitúciu a transpozíciu. Je to najčastejší typ operácii na slovách. Zložitosť tohto prístupu je O(n^2), čo je pre texty týchto veľkostí v poriadku. Ako ďalšie možné operácie som uvažovala počítanie chybovosti už počas prepisovania užívateľom, ale to sa ukázalo ako zbytočne zložité. 

Pre generovanie textu som uvažovala nad pár ďalšími spôsobmi generovania. Jeden z nich bolo výber vzorky z viacerých dopredu zvolených anglických textov. Toto mi neprišlo z programovacieho hľadiska zaujímavé. Druhá zavrhnutá možnosť bola zobrať si anglický slovník a z neho náhodne vybrať slová, ktoré vytvoria text. V tomto prípade vznikne neprirodzený text a ani to nie je ničím zaujímavé. Môj algoritmus založený na Markovských reťazcoch je pomerne jednoduchý a zaujímavý na implementáciu. Už z malej vzorky vytvára síce nezmyselný, ale prirodzene vyzerajúci text. Presne také niečo sa mi pre Type racer hodilo.

### Popis kódu
Môj program sa nachádza v siedmich súboroch. Hlavičkové súbory s príponou .h obsahujú definície verejných funkcí a štruktúr. Ich implementácia sa nachádza v príslučných .cpp súboroch.
Súbor main.cpp obsahuje základnú logiku programu a interakciu s užívateľom. Logika generovania textu (class GeneratorTextu) sa nachádza v súboroch generovanie.h a generovanie.cpp. Povolené operácie na slovách sú zadefinované v súboroch editacna_vzdialenost.cpp a editacna_vzdialenost.h. Algoritmus editačnej vzidalenosti (class CountingDistance) je v súboroch levenshtein.h a levenshtein.cpp.

Takéto rozdelenie programu mi prišlo prirodzené. Oddelila som tak logicky nezávislé časti do rôznych súborov. Ďalšia alternatíva bola spojiť súbory editacna_vzdialenost a levenshtein, v tomto prípade sa mi ale nepáčilo, že by pridávaním nových operácii veľmi narástol počet riadkov.

### Postup práce
Ako prvé som začala s implementovaním levenshteina s fixnými operáciami. Až neskôr som na to použila abstraktnú classu. Okrem toho mi dlho trvalo rozvrhnúť jednotlivé časti programu do konkrétnych súborov tak, aby to fungovalo. Od kedy mi program prvýkrát začal fungovať a bola som s ním dosť spokojná, aby som ho zavesila na GitHub, vidno môj postup práce aj tam.

### Možné rozšírenie
- Grafické rozhranie, 
- live reportovanie výsledkov počas písania, 
- nové operácie na slovách (cena podľa vzdialenosti na klávasnici), 
- počítanie VPM pre český/slovenský jazyk (v tomto prípade napríklad aj ohodnotiť písmená s diakritikov viacerými bodmi).

### Záver
Písanie tohto programu bolo o dosť zložitejšie ako som si predstavovala. Jediné, čo som sa naučila na Programovaní 3 a použila v programe, sú abstraktné classy. Okrem toho mi prišlo zaujímavé (a tažké) vedieť si rozvrhnúť program do jednotlivých súborov tak, aby sa v tom dalo vyznať. To je asi to najdôležitejšie, čo mi tento zápočták dal.



