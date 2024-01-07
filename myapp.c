#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <microhttpd.h>

#define N 8 // Dimensiunea tablei de șah

int tabla[N][N];

// Funcție pentru rezolvarea problemei celor 8 turnuri
bool rezolva(int col);

// Verifică dacă o mutare este validă
bool mutare_valida(int row, int col);

// Funcție pentru afișarea tablei de șah
void afiseaza_tabla();

// Funcție de gestionare a cererilor HTTP
int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls);

int main() {
    // Inițializează tabla de șah cu 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabla[i][j] = 0;
        }
    }

    // Configurați serverul HTTP
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                                                 &handle_request, NULL, MHD_OPTION_END);

    if (!daemon) {
        fprintf(stderr, "Eroare la pornirea serverului HTTP.\n");
        return 1;
    }

    printf("Serverul HTTP rulează pe portul 8080. Deschideți http://localhost:8080 în browser pentru a vedea tabla de șah.\n");
    getchar();

    // Opriți serverul HTTP
    MHD_stop_daemon(daemon);

    return 0;
}

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

void afiseaza_tabla() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", tabla[i][j]);
        }
        printf("\n");
    }
}

int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    // Ignorați conținutul corpului cererii pentru acest exemplu
    (void)upload_data;
    (void)upload_data_size;

    // Rezolvați problema celor 8 turnuri
    rezolva(0);

    // Construiți răspunsul HTML cu tabla de șah
    char response_content[500];
    sprintf(response_content, "<html><body><h1>Tabla de șah:</h1><pre>");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sprintf(response_content + strlen(response_content), "%2d ", tabla[i][j]);
        }
        sprintf(response_content + strlen(response_content), "\n");
    }
    sprintf(response_content + strlen(response_content), "</pre></body></html>");

    // Creare răspuns HTTP
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_content),
                                                                    (void *)response_content,
                                                                    MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}
