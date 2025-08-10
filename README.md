# TYPE RACER
Tento program slúži na skúšanie rýchlopisu. 

## Spustenie programu
Na spustenie treba mať nainštalovaný kompilátor jazyka C++. Program sa dá skompilovať nasledovným príkazom: 

```bash
g++ .\main.cpp .\leveshtein.cpp .\generovanie.cpp .\editacna_vzdialenost.cpp -o main.exe
```
Po spustený programu `.\main.exe` sa spýta, aký dlhý má vygenerovať text a následne sa mu spustí časovač. Po prepísaní textu a stlačeník klávesy ENTER sa časovač vypne a vypíše sa čas, chybovosť a WPM (počet slov za minútu).

## Konfigurácia
V súbore `text.txt` sú uložené texty, z ktorých program vygeneruje vzorku na precvičenie rýchlopisu. 

V súbore `konfiguracia.txt` sa nachádza zoznam povolených operácii pri zistovaní chybovosti textu a ich konkrétna cena. Operácie sú:
- mazanie - vymazanie jedného písmenka z prepísaného textu,
- transpozicia - vymenenie dvoch susedných písmen v prepísanom texte,
- substitucia - zmena jedného písmenka na iné v rámci prepísaného textu,
- pridavanie - pridanie nového písmenka do prepísaného textu.

