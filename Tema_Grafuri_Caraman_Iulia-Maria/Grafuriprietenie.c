#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct {
    int id;
    char nume[50];
} utilizator;
void adauga_coada(int* coada, int* n, int element);
int extrage_coada(int* coada, int* n);
void afiseaza_nume(utilizator* ut, int n, int ind);
void verif_prietenie_directa(int** a, int u1, int u2, utilizator* ut, int n);
void nr_prieteni(int** a, int n, int u, utilizator* ut);
void utilizatori_fara_prieteni(int** a, int n, utilizator* ut);
void Roy_Warshall(int** a, int n, int u1, int u2, utilizator* ut);
void salveaza_in_fisier(int** a, int n, const char* numef);
void adauga_prietenie(int** a, int n, int u1, int u2, const char* numef);
void sterge_prietenie(int** a, int n, int u1, int u2, const char* numef);
void simulare_bfs(int v0, int** a, int n, utilizator* ut);

void adauga_coada(int* coada, int* n, int element)
{
    coada[*n] = element;
    (*n)++;
}

int extrage_coada(int* coada, int* n)
{
    int element;
    element = coada[0];
    for (int i = 0; i < (*n) - 1; i++)
        coada[i] = coada[i + 1];
    (*n)--;
    return element;
}

void afiseaza_nume(utilizator* ut, int n, int ind) {
    for (int i = 0; i < n; i++) {
        if (ut[i].id == ind + 1) {
            printf("%s", ut[i].nume);
            return;
        }
    }
    printf("utilizator %d", ind + 1);
}

void verif_prietenie_directa(int** a, int u1, int u2, utilizator* ut, int n) {
    if (a[u1][u2] == 1) {
        printf("Da, "); afiseaza_nume(ut, n, u1);
        printf(" si "); afiseaza_nume(ut, n, u2);
        printf(" sunt prieteni directi\n");
    }
    else {
        printf("Nu, "); afiseaza_nume(ut, n, u1);
        printf(" si "); afiseaza_nume(ut, n, u2);
        printf(" nu sunt prieteni directi\n");
    }
}

void nr_prieteni(int** a, int n, int u, utilizator* ut) {
    int cnt = 0;
    for (int j = 0; j < n; j++) {
        if (a[u][j] == 1) {
            cnt++;
        }
    }
    printf("utilizatorul "); afiseaza_nume(ut, n, u);
    printf(" are %d prieteni\n", cnt);
}

void utilizatori_fara_prieteni(int** a, int n, utilizator* ut) {
    int ok = 0;
    printf("Utilizatorii fara nicio relatie de prietenie sunt:\n");
    for (int i = 0; i < n; i++) {
        int are_prieteni = 0;
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1) {
                are_prieteni = 1;
                break;
            }
        }
        if (are_prieteni == 0) {
            printf("- "); afiseaza_nume(ut, n, i);
            printf("\n");
            ok = 1;
        }
    }
    if (!ok) printf("nu exista utilizatori singuratici\n");
}

void Roy_Warshall(int** a, int n, int u1, int u2, utilizator* ut) {
    int** p = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        p[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            p[i][j] = a[i][j];
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (p[i][j] == 0 && i != j)
                {
                    if (p[i][k] == 1 && p[k][j] == 1)
                    {
                        p[i][j] = 1;
                    }
                }
            }
        }
    }

    if (p[u1][u2] == 1) {
        printf("Exista o legatura intre "); afiseaza_nume(ut, n, u1);
        printf(" si "); afiseaza_nume(ut, n, u2);
        printf(".\n");
    }
    else {
        printf("nu exista nicio legatura intre "); afiseaza_nume(ut, n, u1);
        printf(" si "); afiseaza_nume(ut, n, u2);
        printf("\n");
    }

    for (int i = 0; i < n; i++)
        free(p[i]);
    free(p);
}

void salveaza_in_fisier(int** a, int n, const char* numef) {
    FILE* f = fopen(numef, "w");
    if (!f) return;

    int m = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] == 1) m++;
        }
    }

    fprintf(f, "%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] == 1) {
                fprintf(f, "%d %d\n", i + 1, j + 1);
            }
        }
    }
    fclose(f);
}

void adauga_prietenie(int** a, int n, int u1, int u2, const char* numef) {
    if (a[u1][u2] == 1) {
        printf("aceasta legatura exista deja\n");
    }
    else {
        a[u1][u2] = 1;
        a[u2][u1] = 1;
        salveaza_in_fisier(a, n, numef);
        printf("Legatura a fost adaugata si fisierul a fost actualizat\n");
    }
}

void sterge_prietenie(int** a, int n, int u1, int u2, const char* numef) {
    if (a[u1][u2] == 0) {
        printf("Aceasta legatura nu exista\n");
    }
    else {
        a[u1][u2] = 0;
        a[u2][u1] = 0;
        salveaza_in_fisier(a, n, numef);
        printf("Legatura a fost stearsa si fisierul a fost actualizat\n");
    }
}

void simulare_bfs(int v0, int** a, int n, utilizator* ut) {
    int nr_coada = 0, vf_curent;
    int* coada = (int*)malloc(n * sizeof(int));
    int* vizitat = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        coada[i] = 0;
        vizitat[i] = 0;
    }

    adauga_coada(coada, &nr_coada, v0);
    vizitat[v0] = 1;

    printf("\nStart postare creata de "); afiseaza_nume(ut, n, v0);
    printf("\n");

    while (nr_coada > 0) {
        vf_curent = extrage_coada(coada, &nr_coada);
        if (vf_curent != v0) {
            printf("Postarea a fost vazuta de ");
            afiseaza_nume(ut, n, vf_curent);
            printf("\n");
        }

        for (int i = 0; i < n; i++) {
            if (a[vf_curent][i] == 1 && vizitat[i] == 0) {
                adauga_coada(coada, &nr_coada, i);
                vizitat[i] = 1;
            }
        }
    }

    free(coada);
    free(vizitat);
}

int main() {
    int n = 0, m = 0;
    FILE* f_retea = fopen("retea.txt", "r");
    if (!f_retea) {
        printf("eroare la deschiderea fisierului retea.txt\n");
        return 1;
    }
    fscanf(f_retea, "%d %d", &n, &m);

    int** a = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        a[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;

    int vi, vf;
    for (int i = 0; i < m; i++) {
        fscanf(f_retea, "%d %d", &vi, &vf);
        a[vi - 1][vf - 1] = 1;
        a[vf - 1][vi - 1] = 1;
    }
    fclose(f_retea);

    utilizator* ut = (utilizator*)malloc(n * sizeof(utilizator));
    FILE* f_utilizatori = fopen("utilizatori.txt", "r");
    if (!f_utilizatori) {
        printf("eroare la deschiderea fisierului utilizatori.txt\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fscanf(f_utilizatori, "%d %s", &ut[i].id, ut[i].nume);
    }
    fclose(f_utilizatori);

    int optiune;
    do {
        printf("\nMeniu retea sociala\n");
        printf("1 existenta legaturii de prietenie directa dintre 2 utilizatori\n");
        printf("2 afisarea numarului de prieteni ai unui utilizator\n");
        printf("3 afisarea utilizatorilor fara relatii de prietenie\n");
        printf("4 existenta unei legaturi directe/indirecte (Roy-Warshall)\n");
        printf("5 adaugarea unei noi legaturi de prietenie\n");
        printf("6 stergerea unei legaturi de prietenie\n");
        printf("7 simularea propagarii unei postari\n");
        printf("0 iesire\n");
        printf("Alegeti optiunea: ");
        scanf("%d", &optiune);

        int u1, u2, u_start;

        if (optiune == 1) {
            printf("introduceti ID-ul primului utilizator (1-%d): ", n); scanf("%d", &u1);
            printf("introduceti ID-ul celui de al doilea utilizator (1-%d): ", n); scanf("%d", &u2);
            if (u1 >= 1 && u1 <= n && u2 >= 1 && u2 <= n) {
                verif_prietenie_directa(a, u1 - 1, u2 - 1, ut, n);
            }
            else printf("ID-uri invslide\n");
        }

        if (optiune == 2) {
            printf("introduceti ID-ul utilizatorului (1-%d): ", n); scanf("%d", &u1);
            if (u1 >= 1 && u1 <= n) {
                nr_prieteni(a, n, u1 - 1, ut);
            }
            else printf("ID invalid\n");
        }

        if (optiune == 3) {
            utilizatori_fara_prieteni(a, n, ut);
        }

        if (optiune == 4) {
            printf("introduceti ID-ul primului utilizator (1-%d): ", n); scanf("%d", &u1);
            printf("introduceti ID-ul celui de al doilea utilizator (1-%d): ", n); scanf("%d", &u2);
            if (u1 >= 1 && u1 <= n && u2 >= 1 && u2 <= n) {
                Roy_Warshall(a, n, u1 - 1, u2 - 1, ut);
            }
            else printf("ID-uri invalide\n");
        }

        if (optiune == 5) {
            printf("introduceti ID-ul primului utilizator (1-%d): ", n); scanf("%d", &u1);
            printf("introduceti ID-ul celui de al doilea utilizator (1-%d): ", n); scanf("%d", &u2);
            if (u1 >= 1 && u1 <= n && u2 >= 1 && u2 <= n && u1 != u2) {
                adauga_prietenie(a, n, u1 - 1, u2 - 1, "retea.txt");
            }
            else printf("ID-uri invalide sau identice\n");
        }

        if (optiune == 6) {
            printf("introduceti ID-ul primului utilizator (1-%d): ", n); scanf("%d", &u1);
            printf("introduceti ID-ul celui de al doilea utilizator (1-%d): ", n); scanf("%d", &u2);
            if (u1 >= 1 && u1 <= n && u2 >= 1 && u2 <= n) {
                sterge_prietenie(a, n, u1 - 1, u2 - 1, "retea.txt");
            }
            else printf("ID-uri invalide\n");
        }

        if (optiune == 7) {
            printf("introduceti ID-ul utilizatorului care creeaza postarea (1-%d): ", n); scanf("%d", &u_start);
            if (u_start >= 1 && u_start <= n) {
                simulare_bfs(u_start - 1, a, n, ut);
            }
            else printf("ID invalid\n");
        }

        if (optiune == 0) {
            printf("iesire din aplicatie\n");
        }

        if (optiune < 0 || optiune > 7) {
            printf("optiune invalida\n");
        }

    } while (optiune != 0);

    for (int i = 0; i < n; i++)
        free(a[i]);
    free(a);
    free(ut);

    return 0;
}