#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Rekord {
    int Id;
    char nazwa[20];
    char producent[20];
    char typ[5];
    double pojemnosc;
    double cena;
};

void createDatabase() {
    char nazwa[100];
    printf("Podaj nazwę pliku bazy danych: ");
    scanf("%s", nazwa);

    FILE* file = fopen(nazwa, "w");  // Tworzenie nowego pliku
    if (file == NULL) {
        printf("Nie można utworzyć pliku.\n");
        return;
    }
    fclose(file);

    FILE* dyskip = fopen(nazwa, "a");
    if (dyskip == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return;
    }

    fprintf(dyskip, "1 Kingston Intel SSD 240.00 99.99\n");
    fprintf(dyskip, "2 Seagate WD HDD 1000.00 59.99\n");
    fprintf(dyskip, "3 Samsung Samsung SSD 500.00 129.99\n");

    fclose(dyskip);

    printf("Utworzono bazę danych o nazwie \"%s\" i dodano przykładowe rekordy.\n", nazwa);
    printf("\n");

    // Powrót do menu głównego
    printf("Naciśnij dowolny klawisz, aby wrócić do menu głównego.\n");
    getchar();  // Pobranie zbędnego znaku nowej linii
    getchar();  // Oczekiwanie na wciśnięcie dowolnego klawisza

    // Wywołanie funkcji main() ponownie
    main();
}

FILE* otworzPlik() {
    FILE* file = NULL;
    char nazwa[100];

    while (file == NULL) {
        printf("Podaj nazwę pliku: ");
        scanf("%s", nazwa);

        file = fopen(nazwa, "r");
        if (file == NULL) {
            printf("Nie można otworzyć pliku.\n");
        }
    }

    return file;
}

void usuwanieRekordu(struct Rekord* rekord, int liczbaRekordow) {
    int Id = rekord->Id;

    FILE* file = otworzPlik();
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return;
    }

    FILE* tempFile = fopen("temp.dat", "w");  // Tworzenie tymczasowego pliku

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int currentId;
        sscanf(line, "%d", &currentId);

        if (currentId != Id) {
            fprintf(tempFile, "%s", line);  // Kopiowanie rekordów z wyjątkiem tego o podanym Id
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove(otworzPlik()) == 0) {
        if (rename("temp.dat", otworzPlik()) == 0) {
            printf("Rekord o numerze Id %d został usunięty z bazy danych.\n", Id);
        } else {
            printf("Nie można zmienić nazwy pliku tymczasowego.\n");
        }
    } else {
        printf("Nie można usunąć pliku.\n");
    }
}

void modyfikujRekord(struct Rekord* rekord) {
    printf("Podaj nowe wartości rekordu:\n");
    printf("Id: ");
    scanf("%d", &rekord->Id);
    printf("Nazwa: ");
    scanf("%s", rekord->nazwa);
    printf("Producent: ");
    scanf("%s", rekord->producent);
    printf("Typ: ");
    scanf("%s", rekord->typ);
    printf("Pojemność: ");
    scanf("%lf", &rekord->pojemnosc);
    printf("Cena: ");
    scanf("%lf", &rekord->cena);

    printf("Rekord został zmodyfikowany.\n");
}

void zapiszPlik(struct Rekord* baza, int liczbaRekordow, const char* nazwaPliku) {
    FILE* plik = fopen(nazwaPliku, "w");
    if (plik == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return;
    }

    for (int i = 0; i < liczbaRekordow; i++) {
        fprintf(plik, "%d %s %s %s %.2lf %.2lf\n", baza[i].Id, baza[i].nazwa, baza[i].producent, baza[i].typ, baza[i].pojemnosc, baza[i].cena);
    }

    fclose(plik);
    printf("Plik zapisano.\n");
}

void sortuj(struct Rekord* baza, int liczbaRekordow, int nrPola) {
    printf("\nSortowanie\n");

    int i, zam;
    struct Rekord temp;

    switch (nrPola) {
        case 1:
            printf("\nSortowanie wg Id\n");
            break;
        case 2:
            printf("\nSortowanie wg Nazwy\n");
            break;
        case 3:
            printf("\nSortowanie wg Producenta\n");
            break;
        case 4:
            printf("\nSortowanie wg Typu\n");
            break;
        case 5:
            printf("\nSortowanie wg Pojemności\n");
            break;
        case 6:
            printf("\nSortowanie wg Ceny\n");
            break;
        default:
            printf("\nNieprawidłowy numer pola\n");
            return;
    }

    do {
        zam = 0;
        for (i = 0; i < liczbaRekordow - 1; i++) {
            switch (nrPola) {
                case 1:
                    if (baza[i].Id > baza[i + 1].Id) {
                        temp = baza[i];
                        baza[i] = baza[i + 1];
                        baza[i + 1] = temp;
                        zam = 1;
                    }
                    break;
                case 2:
                    if (strcmp(baza[i].nazwa, baza[i + 1].nazwa) > 0) {
                        temp = baza[i];
                        baza[i] = baza[i + 1];
                        baza[i + 1] = temp;
                        zam = 1;
                    }
                    break;
                case 3:
                    if (strcmp(baza[i].producent, baza[i + 1].producent) > 0) {
                        temp = baza[i];
                        baza[i] = baza[i + 1];
                        baza[i + 1] = temp;
                        zam = 1;
                    }
                    break;
                case 4:
                    if (strcmp(baza[i].typ, baza[i + 1].typ) > 0) {
                        temp = baza[i];
                        baza[i] = baza[i + 1];
                        baza[i + 1] = temp;
                        zam = 1;
                    }
                    break;
                case 5:
                    if (baza[i].pojemnosc > baza[i + 1].pojemnosc) {
                        temp = baza[i];
                        baza[i] = baza[i + 1];
                        baza[i + 1] = temp;
                        zam = 1;
                    }
                    break;
                case 6:
                    if (baza[i].cena > baza[i + 1].cena) {
                        temp = baza[i];
                        baza[i] = baza[i + 1];
                        baza[i + 1] = temp;
                        zam = 1;
                    }
                    break;
            }
        }
    } while (zam);
     printf("Sortowanie zakończone.\n");
}

void przeglad() {
    FILE* file = otworzPlik();
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return;
    }

    struct Rekord baza[100]; // Tablica rekordów
    int liczbaRekordow = 0;  // Liczba rekordów w bazie

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        struct Rekord rekord;
        sscanf(line, "%d %s %s %s %lf %lf", &rekord.Id, rekord.nazwa, rekord.producent, rekord.typ, &rekord.pojemnosc, &rekord.cena);

        baza[liczbaRekordow] = rekord;
        liczbaRekordow++;
    }

    fclose(file);

    int aktualnyRekord = 0;   // Indeks bieżącego rekordu

    while (1) {
        printf("\n===== Bieżący rekord: %d =====\n", aktualnyRekord + 1);
        printf("Id: %d\n", baza[aktualnyRekord].Id);
        printf("Nazwa: %s\n", baza[aktualnyRekord].nazwa);
        printf("Producent: %s\n", baza[aktualnyRekord].producent);
        printf("Typ: %s\n", baza[aktualnyRekord].typ);
        printf("Pojemność: %.2lf\n", baza[aktualnyRekord].pojemnosc);
        printf("Cena: %.2lf\n", baza[aktualnyRekord].cena);

        printf("\nNaciśnij B aby przejść do kolejnego rekordu (dół)\n");
        printf("Naciśnij Y aby przejść do poprzedniego rekordu (góra)\n");
        printf("Naciśnij G aby przejść na początek bazy\n");
        printf("Naciśnij H aby przejść na koniec bazy\n");
        printf("Naciśnij D aby usunąć rekord z bazy\n");
        printf("Naciśnij M aby zmodyfikować rekord w bazie\n");
        printf("Naciśnij S aby posortować rekordy\n");
        printf("Naciśnij X aby zakończyć przeglądanie\n");
        printf("Naciśnij P aby zapisać plik\n");
        printf("Wybierz opcję: ");

        char option;
        scanf(" %c", &option);

        switch (option) {
            case 'B':
            case 'b':
                if (aktualnyRekord < liczbaRekordow - 1) {
                    aktualnyRekord++;
                } else {
                    printf("Jesteś już na ostatnim rekordzie.\n");
                }
                break;
            case 'Y':
            case 'y':
                if (aktualnyRekord > 0) {
                    aktualnyRekord--;
                } else {
                    printf("Jesteś już na pierwszym rekordzie.\n");
                }
                break;
            case 'G':
            case 'g':
                aktualnyRekord = 0;
                break;
            case 'H':
            case 'h':
                aktualnyRekord = liczbaRekordow - 1;
                break;
            case 'D':
            case 'd':
                printf("Usunięcie rekordu.\n");
                usuwanieRekordu(&baza[aktualnyRekord], liczbaRekordow);
                liczbaRekordow--;
                break;
            case 'M':
            case 'm':
                printf("Modyfikacja rekordu.\n");
                modyfikujRekord(&baza[aktualnyRekord]);
                break;
            case 'S':
            case 's':
                printf("Sortowanie rekordów.\n");
                FILE* file = otworzPlik();
                if (file == NULL) {
                    printf("Nie można otworzyć pliku.\n");
                    break;
                }
                break;

            case 'P':
            case 'p':
                printf("Zapisywanie pliku.\n");
                zapiszPlik(baza, liczbaRekordow,otworzPlik );
                break;

            case 'X':
            case 'x':
                printf("Zakończono przeglądanie.\n");
                return;
            default:
                printf("Nieprawidłowa opcja.\n");
        }
    }
}

int main() {
    int opcja;
    printf("1 - Utworzenie bazy danych\n");
    printf("2 - Przeglądanie bazy danych\n");
    printf("0 - Zakończenie programu\n");
    printf("Wybierz opcję: ");
    scanf("%d", &opcja);

    switch (opcja) {
        case 1:
            createDatabase();
            break;
        case 2:
            przeglad();
            break;
        case 0:
            printf("Zakończono program.\n");
            return 0;
        default:
            printf("Nieprawidłowa opcja.\n");
            break;
    }

    return 0;
}
