
# APC - zadanie 3

# Príkazy

## Write
Príkaz w. Zapíše aktuálny stav súboru na disk.

## Quit
Príkaz q.

Ukončí program, pokiaľ nie je rozdiel medzi aktuálnym stavom a tým, čo je zapísané na disku. Inak vypíše chybovú hlášku (You have unsaved changes) a vráti sa do príkazového stavu, čiže zmeny zostanú zachované. 

Príkaz q!.

Ukončí program bez ohľadu na to, či došlo k zmenám, alebo nie.

## Append
Príkaz a. Dopíše na koniec súboru to, čo mu bude zadané na vstupe.

Príkaz a [line]. Dopíše to čo bude zadané na vstupe za daný riadok. Ostatné riadky posunie nižšie. Ak je zadané neexistujúce číslo riadku, neexistujúce riadky vytvoríme a budú prázdne.

## Print
Príkaz p. Vypíš celý obsah súboru na výstup.

Príkaz p [range]. Vypíše iba range na výstup.

## Delete
Príkaz d. Zmaže všetky riadky.

Príkaz d [range]. Zmaže riadky v danom rozsahu.

## Change
Príkaz c. Nahradí celý súbor dátami zo vstupu.

Príkaz c [range]. Nahradí daný rozsah dátami zo vstupu.

## Oneliners
Príkazy append a change majú možnosť zapisovať zmeny bez vstupného módu. Ak za príkazom nasledujú iné znaky, tieto budú použité ako riadok, ktorý bude použítý namiesto vstupu zo vstupného módu.


