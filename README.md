# Proiect-sincretic
## Temă proiect nr. 23


Cerința temei de proiect este următoarea:

**Problema celor 8 turnuri**: să se scrie un program care plasează 8 turnuri pe tabla de șah, fără ca acestea să se atace reciproc.

1. Introducere

Scopul programului este de a verifica atunci când opt turnuri așezate pe tabla de șah, să nu se atace reciproc. 
În șah, turnurile pot să se deplaseze pe tablă orizontal sau vertical pe toată lungimea tablei. 
Implementarea este realizată în limbajul de programare C și utilizează un algoritm de backtracking pentru a găsi soluția.
Există *92* de moduri unice de a plasa opt turnuri pe tabla de șah (8x8) astfel încât să nu se atace reciproc. 
Este important de menționat că acest număr include toate permutările distincte și rotirile pentru fiecare configurație. 
Acest rezultat este cunoscut sub numele de ,,Soluțiile celor opt regine" și a fost demonstrat pentru prima dată de către matematicianul Carl Friedrich Gauss. 
Aceasta este o problemă bine-cunoscută în teoria combinatorică și este rezolvată printr-o combinație de metode de programare și matematică.

2. Structura codului 

- Biblioteci

`#include <stdio.h>`
`#include <stdbool.h>`

Proiectul include bibliotecile standard pentru intrare/ieșire și pentru lucrul cu valori logice (adevărat/fals).

- Macrodefiniții

`#define N 8 // Dimensiunea tablei de șah`

Macrodefiniția *N* reprezintă dimensiunea tablei de șah și este setată la valoarea 8, corespunzătoare șahului standard de (8x8).

- Variabile Globale

`int tabla[N][N];`

Matricea tabla reprezintă tabla de șah și este folosită pentru a urmări poziționarea turnurilor.

- Funcții 