#include <stdio.h>
#include <stdbool.h>
#include <microhttpd.h>

#define N 8

int tabla[N][N];

bool mutare_valida(int row, int col) {
    for (int i = 0; i < col; i++) {
        if (tabla[row][i] == 1) {
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (tabla[i][j] == 1) {
            return false;
        }
    }

    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (tabla[i][j] == 1) {
            return false;
        }
    }

    return true;
}

bool rezolva(int col) {
    if (col >= N) {
        return true;
    }

    for (int i = 0; i < N; i++) {
        if (mutare_valida(i, col)) {
            tabla[i][col] = 1;

            if (rezolva(col + 1)) {
                return true;
            }

            tabla[i][col] = 0;
        }
    }

    return false;
}

void afiseaza_tabla() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", tabla[i][j]);
        }
        printf("\n");
    }
}

// Funcție de gestionare a cererilor HTTP
int handle_request(void *cls, struct MHD_Connection *connection, const char *url,
                   const char *method, const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    // Ignorați conținutul corpului cererii pentru acest exemplu
    (void)upload_data;
    (void)upload_data_size;

    const char *page = "<html><body><h1>Hello, world!</h1></body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    // Inițializați tabla de șah cu 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabla[i][j] = 0;
        }
    }

    if (rezolva(0)) {
        printf("Solutia gasita:\n");
        afiseaza_tabla();
    } else {
        printf("Nu exista o solutie.\n");
    }

    // Configurați serverul HTTP
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                                                 &handle_request, NULL, MHD_OPTION_END);

    if (!daemon) {
        fprintf(stderr, "Eroare la pornirea serverului HTTP.\n");
        return 1;
    }

    printf("Serverul HTTP rulează pe portul 8080. Apasati Enter pentru a opri serverul.\n");
    getchar();

    // Opriți serverul HTTP
    MHD_stop_daemon(daemon);

    return 0;
}
