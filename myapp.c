#include <stdio.h>
#include <stdbool.h>

#define N 8 // Dimensiunea tablei de șah

int tabla[N][N];

// Verifică dacă o mutare este validă
bool mutare_valida(int row, int col) {
    // Verifică rândul și coloana
    for (int i = 0; i < col; i++) {
        if (tabla[row][i] == 1) {
            return false;
        }
    }

    // Verifică diagonala stânga-sus
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (tabla[i][j] == 1) {
            return false;
        }
    }

    // Verifică diagonala stânga-jos
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (tabla[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Rezolvă problema celor 8 turnuri folosind backtracking
bool rezolva(int col) {
    if (col >= N) {
        return true; // Toate turnurile au fost plasate cu succes
    }

    for (int i = 0; i < N; i++) {
        if (mutare_valida(i, col)) {
            // Plasează un turn în poziția validă
            tabla[i][col] = 1;

            // Recursiv, plasează următorul turn
            if (rezolva(col + 1)) {
                return true;
            }

            // Dacă nu se poate plasa următorul turn, anulează mutarea
            tabla[i][col] = 0;
        }
    }

    return false; // Nu există o soluție validă
}

// Funcție pentru afișarea tablei de șah
void afiseaza_tabla() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", tabla[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inițializează tabla de șah cu 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabla[i][j] = 0;
        }
    }

    if (rezolva(0)) {
        printf("Solutia gasita:\n");
        afiseaza_tabla();
    }
    else {
        printf("Nu exista o solutie.\n");
    }

    return 0;
}
