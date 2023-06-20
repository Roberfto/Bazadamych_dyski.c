#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int Id;
    char nazwa[25];
    char producent[25];
    char typ[4];
    double pojemnosc;
    double cena;
} Dysk;

void createDatabase() {
    FILE *file = fopen("dyski.dat", "w");  // Tworzenie nowego pliku "dyski.dat"
    if (file == NULL) {
        printf("Nie mo\276na utworzy\206 pliku.\n");
        return;
    }
    fclose(file);

 FILE *dyskip = fopen("dyski.dat", "a");
    if (dyskip == NULL) {
        printf("Nie mo\276na otworzy\206 pliku.\n");
        return;
    }

    fprintf(dyskip, "1 SSD Kingston Intel SSD 240.00 99.99\n");
    fprintf(dyskip, "2 HDD Seagate WD HDD 1000.00 59.99\n");
    fprintf(dyskip, "3 SSD Samsung Samsung SSD 500.00 129.99\n");

    fclose(dyskip);

    printf("Utworzono baz\251 danych i dodano przyk\210adowe rekordy.\n");
   printf("\n");
}


void usuwaniebazy() {
    if (remove("dyski.dat") == 0) {
        printf("Baza danych zosta\210a usuni\251ta.\n");
       printf("\n");
    } else {
        printf("Nie mo\276na usun\245\206 bazy danych.\n");
       printf("\n");
    }
}

void bazawyswietlanie() {
   FILE *file = fopen("dyski.dat", "r");  // Otwarcie pliku "dyski.dat" w trybie odczytu
    if (file == NULL) {
        printf("Nie mo\276na otworzy\206 pliku.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  // Wy\230wietlanie kolejnych linii z pliku
    }

    fclose(file);

}
void ModyfikujRekord(FILE* file, int akrekord);

void dodawanierekordu() {
    int Id;
    char nazwa[25];
    char producent[25];
    char typ[4];
    double pojemnosc;
    double cena;

  printf("podaj numer Id ");
  scanf("%d",&Id);

  printf("podaj nazw\251 dysku ");
  scanf("%s",nazwa);

  printf("podaj producenta ");
  scanf("%s",producent);

  printf("podaj typ dysku ");
  scanf("%s",typ);

  printf("podaj pojemno\230\206 dysku ");
  scanf("%lf",&pojemnosc);

   printf("podaj cen\251 dysku ");
  scanf("%lf",&cena);

FILE *file = fopen("dyski.dat", "a");  // Otworzenie pliku w trybie dopisania
    if (file == NULL) {
        printf("Nie mo\276na otworzy\206 pliku.\n");
        return;
    }

    fprintf(file, "%d %s %s %s %.2lf %.2lf\n", Id, nazwa, producent, typ ,pojemnosc , cena );  // Zapisanie rekordu do pliku
    fclose(file);

    printf("Dodano rekord do bazy danych.\n");
   printf("\n");

}

void usuwanierekordu() {
    int Id;
    printf("Podaj numer Id rekordu do usuni\251cia: ");
    scanf("%d", &Id);

    FILE *file = fopen("dyski.dat", "r");
    if (file == NULL) {
        printf("Nie mo\276na otworzy\206 pliku.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "w");  // Tworzenie tymczasowego pliku

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int currentId;
        sscanf(line, "%d", &currentId);

        if (currentId != Id) {
            fprintf(tempFile, "%s", line);  // Kopiowanie rekord\242w z wyj\245tkiem tego o podanym Id
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove("dyski.dat") == 0) {
        if (rename("temp.dat", "dyski.dat") == 0) {
            printf("Rekord o numerze Id %d zosta\210 usuni251ty z bazy danych.\n", Id);
        } else {
            printf("Nie mo\276na zmieni\206 nazwy pliku tymczasowego.\n");
        }
    } else {
        printf("Nie mo\276na usun\245\206 pliku.\n");
    }
}



void Przeglad() {
    FILE* file = fopen("dyski.dat", "r");
    if (file == NULL) {
        printf("Nie mo\276na otworzy\206 pliku.\n");
        return;
    }

    char line[100];
    int akrekord = -1;  // Indeks bie\276\245cego rekordu
    int wszrekordy = 0;  // Ca\210kowita liczba rekord\242w

    while (fgets(line, sizeof(line), file)) {
        if (akrekord == -1) {
            printf("\n");
            printf("===== Bie\276\245cy rekord: %d =====\n", akrekord + 1);
        }
        printf("%s", line);  // Wy\230wietlanie rekordu

        wszrekordy++;  // Aktualizacja liczby rekord\242w

        printf("\nNaci\230nij B aby przej\230\206 do kolejnego rekordu (d\242\210)\n");
        printf("Naci\230nij Y aby przej\230\206 do poprzedniego rekordu (g\242ra)\n");
        printf("Naci\230nij G aby przej\230\206 na pocz\245tek bazy\n");
        printf("Naci\230nij H aby przej\230\206 na koniec bazy\n");
        printf("Naci\230nij X aby zako\344czy\206 przegl\245danie\n");
        printf("Wybierz opcj\251: ");

        char option;
        scanf(" %c", &option);

        switch (option) {
            case 'B':
            case 'b':
                if (akrekord < wszrekordy - 1) {
                    akrekord++;
                } else {
                    printf("Jeste\230 ju\276 na ostatnim rekordzie.\n");
                }
                printf("\n===== Bie\276\245cy rekord: %d =====\n", akrekord + 1);
                break;
            case 'Y':
            case 'y':
                if (akrekord > 0) {
                    akrekord--;
                } else {
                    printf("Jeste\230 ju\276 na pierwszym rekordzie.\n");
                }
                printf("\n===== Bie\276\245cy rekord: %d =====\n", akrekord + 1);
                break;
            case 'G':
            case 'g':
                akrekord = 0;
                printf("\n===== Bie\276\245cy rekord: %d =====\n", akrekord + 1);
                break;
            case 'H':
            case 'h':
                akrekord = wszrekordy - 1;
                printf("\n===== Bie\276\245cy rekord: %d =====\n", akrekord + 1);
                break;
            case 'X':
            case 'x':
                fclose(file);
                return;
            default:
                printf("Nieprawid\210owa opcja.\n");
                break;
        }
    }

    fclose(file);
}

void sortowaniebazy() {
    FILE *file = fopen("dyski.dat", "r");
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return;
    }

    int wszrekordy = 0;
    char line[100];

    while (fgets(line, sizeof(line), file)) {
        wszrekordy++;
    }

    fseek(file, 0, SEEK_SET);  // Przesunięcie na początek pliku

    Dysk *baza = (Dysk*)malloc(wszrekordy * sizeof(Dysk));
    if (baza == NULL) {
        printf("Nie można zaalokować pamięci.\n");
        fclose(file);
        return;
    }

    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %s %s %s %lf %lf", &baza[i].Id, baza[i].nazwa, baza[i].producent,
               baza[i].typ, &baza[i].pojemnosc, &baza[i].cena);
        i++;
    }

    fclose(file);

    int option3;
    printf("=== Opcje sortowania ===\n");
    printf("1. Sortuj według Id\n");
    printf("2. Sortuj według nazwy\n");
    printf("3. Sortuj według producenta\n");
    printf("4. Sortuj według typu\n");
    printf("5. Sortuj według pojemności\n");
    printf("6. Sortuj według ceny\n");
    printf("0. Powrót\n");
    printf("Wybierz opcję: ");
    scanf("%d", &option3);

    switch (option3) {
        case 1:
            // Sortuj według Id
            for (int i = 0; i < wszrekordy - 1; i++) {
                for (int j = 0; j < wszrekordy - i - 1; j++) {
                    if (baza[j].Id > baza[j + 1].Id) {
                        Dysk temp = baza[j];
                        baza[j] = baza[j + 1];
                        baza[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            // Sortuj według nazwy
            for (int i = 0; i < wszrekordy - 1; i++) {
                for (int j = 0; j < wszrekordy - i - 1; j++) {
                    if (strcmp(baza[j].nazwa, baza[j + 1].nazwa) > 0) {
                        Dysk temp = baza[j];
                        baza[j] = baza[j + 1];
                        baza[j + 1] = temp;
                    }
                }
            }
            break;
        case 3:
            // Sortuj według producenta
            for (int i = 0; i < wszrekordy - 1; i++) {
                for (int j = 0; j < wszrekordy - i - 1; j++) {
                    if (strcmp(baza[j].producent, baza[j + 1].producent) > 0) {
                        Dysk temp = baza[j];
                        baza[j] = baza[j + 1];
                        baza[j + 1] = temp;
                    }
                }
            }
            break;
        case 4:
            // Sortuj według typu
            for (int i = 0; i < wszrekordy - 1; i++) {
                for (int j = 0; j < wszrekordy - i - 1; j++) {
                    if (strcmp(baza[j].typ, baza[j + 1].typ) > 0) {
                        Dysk temp = baza[j];
                        baza[j] = baza[j + 1];
                        baza[j + 1] = temp;
                    }
                }
            }
            break;
        case 5:
            // Sortuj według pojemności
            for (int i = 0; i < wszrekordy - 1; i++) {
                for (int j = 0; j < wszrekordy - i - 1; j++) {
                    if (baza[j].pojemnosc > baza[j + 1].pojemnosc) {
                        Dysk temp = baza[j];
                        baza[j] = baza[j + 1];
                        baza[j + 1] = temp;
                    }
                }
            }
            break;
        case 6:
            // Sortuj według ceny
            for (int i = 0; i < wszrekordy - 1; i++) {
                for (int j = 0; j < wszrekordy - i - 1; j++) {
                    if (baza[j].cena > baza[j + 1].cena) {
                        Dysk temp = baza[j];
                        baza[j] = baza[j + 1];
                        baza[j + 1] = temp;
                    }
                }
            }
            break;
        case 0:
            free(baza);
            return;
        default:
            printf("Nieprawidłowa opcja.\n");
            free(baza);
            return;
    }

    // Wyświetlanie posortowanej bazy danych
    for (int i = 0; i < wszrekordy; i++) {
        printf("%d %s %s %s %.2lf %.2lf\n", baza[i].Id, baza[i].nazwa, baza[i].producent,
               baza[i].typ, baza[i].pojemnosc, baza[i].cena);
    }

    free(baza);
}

void menu2() {
    int option2;
    printf("=== Drugie menu ===\n");
    printf("1. Przegl\245daj baz\251 danych\n");
    printf("2. Dodaj rekord\n");
    printf("3. Usu\344 rekord\n");
    printf("4. Sortuj baz\251 danych\n");
    printf("0. Wyj\230cie\n");
    printf("Wybierz opcj\251: ");
    scanf("%d", &option2);

    switch (option2) {
        case 1:
            printf("Wybrano opcj\251: Przegl\245daj baz\251 danych\n");
            Przeglad();
          printf("\n");
            break;
        case 2:
            printf("Wybrano opcj\251: Dodaj rekord\n");
            dodawanierekordu();
          printf("\n");
            break;
        case 3:
            printf("Wybrano opcj\251: Usu\344 rekord\n");
            usuwanierekordu();
          printf("\n");
            break;
      case 4:
            printf("Wybrano opcj\251: Sortowanie bazy\n");
            sortowaniebazy();
        printf("\n");
            break;
        case 0:
            printf("Wybrano opcj\251: Wyj\230cie\n");
            return;
         printf("\n");
        default:
            printf("Nieprawid\210owa opcja.\n");
            break;

    }

    menu2();

}

void menu1() {
    int option1;
    printf("=== Pierwsze menu ===\n");
    printf("1. Utw\242rz baz\251\n");
    printf("2. Usu\344 baz\251\n");
    printf("3. Wy\230wietl baz\251\n");
    printf("0. Wyj\230cie\n");
    printf("Wybierz opcj\251: ");
    scanf("%d", &option1);

    switch (option1) {
        case 1:
            printf("Wybrano opcj\251: Utw\242rz baz\251\n");
            createDatabase();
            menu2();
            break;
        case 2:
            printf("Wybrano opcj\251: Usu\344 baz\251\n");
            usuwaniebazy();
          printf("\n");
            break;
        case 3:
            printf("Wybrano opcj\251: Wy\230wietl baz\251\n");
            bazawyswietlanie();
          printf("\n");
            break;
        case 0:
            printf("Wybrano opcj\251: Wyj\230cie\n");
          printf("\n");
            return;
        default:
            printf("Nieprawid\210owa opcja.\n");
            break;
    }

    menu1();
}

int main() {
    menu1();

    return 0;
}
