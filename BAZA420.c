#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

char aktyny[100];

struct Rekord {
    int Id;
    char nazwa[20];
    char producent[20];
    char typ[5];
    double pojemnosc;
    double cena;
};

int pad = 0;

int centerText(const char *text) {
    int textLength = strlen(text);
    int consoleWidth;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int padding = (consoleWidth - textLength) / 2;

    // Print the padding spaces
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    // Print the text
    printf("%s", text);

    return padding;
}

void leftpadding() {
    // Print the padding spaces
    for (int i = 0; i < pad; i++) {
        printf(" ");
    }
}
const char *random_string(int length) {
    static char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *random_string = NULL;

    if (length) {
        random_string = malloc(sizeof(char) * (length + 1));

        if (random_string) {
            for (int n = 0; n < length; n++) {
                int key = rand() % (int)(sizeof(charset) - 1);
                random_string[n] = charset[key];
            }
            random_string[length] = '\0';
        }
    }
    return random_string;
}

const char *random_producent() {
    const char *producenci[] = {"Seagate", "Western Digital", "Samsung", "Kingston", "SanDisk", "Crucial", "Toshiba", "Adata"};
    return producenci[rand() % 8];
}

const char *random_typ() {
    const char *typy[] = {"SSD", "HDD", "M.2"};
    return typy[rand() % 3];
}

double random_pojemnosc() {
    return (double)(rand() % (8192 - 128 + 1) + 128);  // Pojemność od 128 do 8192
}

double random_cena() {
    return ((double)(rand() % (200000 - 5000 + 1) + 5000)) / 100;  // Cena od 50.00 do 2000.00
}

void createDatabase() {
    system("cls");
    char nazwa[100];
    leftpadding();
    printf("Podaj nazwe pliku bazy danych: ");
    scanf("%s", nazwa);

    FILE *file = fopen(nazwa, "w"); // Tworzenie nowego pliku
    if (file == NULL) {
        leftpadding();
        printf("Nie mozna utworzyc pliku.\n");
        return;
    }
    fclose(file);

    FILE *dyskip = fopen(nazwa, "a");
    if (dyskip == NULL) {
        leftpadding();
        printf("Nie mozna otworzyc pliku.\n");
        return;
    }

    srand(time(NULL)); // Inicjalizacja generatora liczb losowych

    for (int i = 1; i <= 10; i++) {
        const char *nazwa = random_string(10);  // Generowanie losowej nazwy
        const char *producent = random_producent();
        const char *typ = random_typ();
        double pojemnosc = random_pojemnosc();
        double cena = random_cena();
        fprintf(dyskip, "%d %s %s %s %.2f %.2f\n", i, nazwa, producent, typ, pojemnosc, cena);
        free((void*)nazwa);  // Zwolnienie pamięci
    }

    fclose(dyskip);

    leftpadding();
    printf("Utworzono baze danych o nazwie \"%s\" i dodano przykladowe rekordy.\n", nazwa);
    printf("\n");

    leftpadding();
    printf("Nacisnij dowolny klawisz, aby wrocic do menu glownego.\n");
    getchar();
    getchar();

    main();
}

FILE* otworzPlik() {
    FILE* file = NULL;
    char nazwa[100];

    while (file == NULL) {
        if (aktyny[0] == '\0') {
            leftpadding();
            printf("Podaj nazwe pliku: ");
            scanf("%s", nazwa);

            for (int i = 0; i < sizeof(nazwa); i++) {
                aktyny[i] = nazwa[i];
            }

            file = fopen(nazwa, "r");
            if (file == NULL) {
                leftpadding();
                printf("Nie mozna otworzyc pliku.\n");
            }
        } else {
            file = fopen(aktyny, "r");
            if (file == NULL) {
                leftpadding();
                printf("Nie mozna otworzyc pliku.\n");
            }
        }
    }

    return file;
}

void usuwanieRekordu(struct Rekord *baza, int *liczbaRekordow, int aktualnyRekord) {
    for (int i = aktualnyRekord; i < (*liczbaRekordow) - 1; i++) {
        baza[i] = baza[i + 1];
    }
    (*liczbaRekordow)--;
}

void modyfikujRekord(struct Rekord *rekord) {
    system("cls");
    leftpadding();
    printf("Mod - Podaj nowe wartosci rekordu:\n");
    leftpadding();
    printf("Id: ");
    scanf("%d", &rekord->Id);
    leftpadding();
    printf("Nazwa: ");
    scanf("%s", rekord->nazwa);
    leftpadding();
    printf("Producent: ");
    scanf("%s", rekord->producent);
    leftpadding();
    printf("Typ: ");
    scanf("%s", rekord->typ);
    leftpadding();
    printf("Pojemnosc: ");
    scanf("%lf", &rekord->pojemnosc);
    leftpadding();
    printf("Cena: ");
    scanf("%lf", &rekord->cena);

    leftpadding();
    printf("Rekord zostal zmodyfikowany.\n");
}

void dodajRekord(const char *nazwaPliku)
{

    system("cls");
    leftpadding();
    printf("Dodaj - Podaj nowe wartosci rekordu:\n");

    leftpadding();
    int id;
    printf("Id: ");
    scanf("%d", &id);

    leftpadding();
    char nazwa[20];
    printf("Nazwa: ");
    scanf("%s", &nazwa);

    leftpadding();
    char producent[20];
    printf("Producent: ");
    scanf("%s", &producent);


    leftpadding();
    char typ[4];
    printf("Typ: ");
    scanf("%s", &typ);

    leftpadding();
    double pojemnosc;
    printf("Pojemnosc: ");
    scanf("%lf", &pojemnosc);


    leftpadding();
    double cena;
    printf("Cena: ");
    scanf("%lf", &cena);

    FILE *file = fopen(nazwaPliku, "a");  // Otworzenie pliku w trybie dopisania
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku.\n");
        return;
    }

    fprintf(file, "%d %s %s %s %.2lf %.2lf\n", id, nazwa, producent, typ , pojemnosc , cena );  // Zapisanie rekordu do pliku

    fclose(file);

    leftpadding();
    printf("Rekord zostal dodany.\n");
}

void zapiszPlik(struct Rekord *baza, int liczbaRekordow, const char *nazwaPliku) {
    FILE *plik = fopen(nazwaPliku, "w");
    if (plik == NULL) {
        leftpadding();
        printf("Nie mozna otworzyc pliku.\n");
        return;
    }

    for (int i = 0; i < liczbaRekordow; i++) {
        fprintf(plik, "%d %s %s %s %.2lf %.2lf\n", baza[i].Id, baza[i].nazwa,
                baza[i].producent, baza[i].typ, baza[i].pojemnosc, baza[i].cena);
    }

    fclose(plik);
    leftpadding();
    printf("Plik zapisano.\n");
}

void sortuj(struct Rekord *baza, int liczbaRekordow) {

    leftpadding();
    printf("Sortowanie\n");

    int i, zam;
    struct Rekord temp;

    leftpadding();
    printf("1. Sortowanie wg Id\n");
    leftpadding();
    printf("2. Sortowanie wg Nazwy\n");
    leftpadding();
    printf("3. Sortowanie wg Producenta\n");
    leftpadding();
    printf("4. Sortowanie wg Typu\n");
    leftpadding();
    printf("5. Sortowanie wg Pojemnosci\n");
    leftpadding();
    printf("6. Sortowanie wg Ceny\n");
    leftpadding();
    printf("7. Nieprawidlowy numer pola\n");
    leftpadding();
    printf("Enter Sort: ");

    int opcja;
    scanf(" %d", &opcja);

    switch (opcja) {
        case 1:
            leftpadding();
            printf("\nSortowanie wg Id\n");
            break;
        case 2:
            leftpadding();
            printf("\nSortowanie wg Nazwy\n");
            break;
        case 3:
            leftpadding();
            printf("\nSortowanie wg Producenta\n");
            break;
        case 4:
            leftpadding();
            printf("\nSortowanie wg Typu\n");
            break;
        case 5:
            leftpadding();
            printf("\nSortowanie wg Pojemnosci\n");
            break;
        case 6:
            leftpadding();
            printf("\nSortowanie wg Ceny\n");
            break;
        default:
            leftpadding();
            printf("\nNieprawidlowy numer pola\n");
            return;
    }

    do {
        zam = 0;
        for (i = 0; i < liczbaRekordow - 1; i++) {
            switch (opcja) {
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
    printf("Sortowanie zakonczone.\n");
}

void przeglad() {

    system("cls");
    FILE *file = otworzPlik();
    if (file == NULL) {
        leftpadding();
        printf("Nie mozna otworzyc pliku.\n");
        return;
    }

    struct Rekord baza[100]; // Tablica rekordow
    int liczbaRekordow = 0;  // Liczba rekordow w bazie

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        struct Rekord rekord;
        sscanf(line, "%d %s %s %s %lf %lf", &rekord.Id, rekord.nazwa,
               rekord.producent, rekord.typ, &rekord.pojemnosc, &rekord.cena);

        baza[liczbaRekordow] = rekord;
        liczbaRekordow++;
    }

    fclose(file);

    int aktualnyRekord = 0; // Indeks biezacego rekordu

    while (1) {
        system("cls");

        leftpadding();
        printf("===== Biezacy rekord: %d =====\n", aktualnyRekord + 1);
        leftpadding();
        printf("Id: %d\n", baza[aktualnyRekord].Id);
        leftpadding();
        printf("Nazwa: %s\n", baza[aktualnyRekord].nazwa);
        leftpadding();
        printf("Producent: %s\n", baza[aktualnyRekord].producent);
        leftpadding();
        printf("Typ: %s\n", baza[aktualnyRekord].typ);
        leftpadding();
        printf("Pojemnosc: %.2lf\n", baza[aktualnyRekord].pojemnosc);
        leftpadding();
        printf("Cena: %.2lf\n", baza[aktualnyRekord].cena);

        /*
          printf("\nNacisnij B aby przejsc do kolejnego rekordu (dol)\n");
          printf("Nacisnij Y aby przejsc do poprzedniego rekordu (gora)\n");
          printf("Nacisnij G aby przejsc na poczatek bazy\n");
          printf("Nacisnij H aby przejsc na koniec bazy\n");
          printf("Nacisnij D aby usunac rekord z bazy\n");
          printf("Nacisnij M aby zmodyfikowac rekord w bazie\n");
          printf("Nacisnij S aby posortowac rekordy\n");
          printf("Nacisnij X aby zakonczyc przegladanie\n");
          printf("Nacisnij P aby zapisac plik\n");
        */

        int pad2 = centerText("B - Dol , Y - Gora , G - Poczatek , H - Koniec , D - usuwanie rekordu\n");
        int pad3 = centerText("M - Modyfikacja , A - Dodowanie, S - Sortowanie , P - Zapis , X - Koniec\n");
        leftpadding();
        printf("Wybierz opcje: ");

        char option;
        scanf(" %c", &option);

        switch (option) {
            case 'b':
                if (aktualnyRekord < liczbaRekordow - 1) {
                    aktualnyRekord++;
                } else {
                    leftpadding();
                    printf("Jestes juz na ostatnim rekordzie.\n");
                }
                break;
            case 'y':
                if (aktualnyRekord > 0) {
                    aktualnyRekord--;
                } else {
                    leftpadding();
                    printf("Jestes juz na pierwszym rekordzie.\n");
                }
                break;
            case 'g':
                aktualnyRekord = 0;
                break;
            case 'h':
                if (liczbaRekordow > 0) {
                    aktualnyRekord = liczbaRekordow - 1;
                } else {
                    leftpadding();
                    printf("Jestes na ostatnim rekordzie.\n");
                }
                break;
            case 'd':
                leftpadding();
                printf("Usuniecie rekordu.\n");
                usuwanieRekordu(baza, &liczbaRekordow, aktualnyRekord);
                break;
            case 'm':
                leftpadding();
                printf("Modyfikacja rekordu.\n");
                modyfikujRekord(&baza[aktualnyRekord]);
                break;
            case 'a':
                leftpadding();
                printf("Dodowanie rekordow.\n");
                dodajRekord(aktyny);
                przeglad();
                break;
            case 's':
                leftpadding();
                printf("Sortowanie rekordow.\n");
                sortuj(baza, liczbaRekordow);
                break;
            case 'p':
                leftpadding();
                printf("Zapisywanie pliku.\n");
                zapiszPlik(baza, liczbaRekordow, aktyny);
                break;
            case 'x':
                leftpadding();
                printf("Zakonczono przegladanie.\n");
                return;
            default:
                leftpadding();
                printf("Nieprawidlowa opcja.\n");
        }
    }
}

int main() {
    int opcja;
    pad = centerText("===============================\n");
    leftpadding();
    printf("1 - Utworzenie bazy danych\n");
    leftpadding();
    printf("2 - Przegladanie bazy danych\n");
    leftpadding();
    printf("0 - Zakonczenie programu\n");
    leftpadding();
    printf("Wybierz opcje: ");
    scanf("%d", &opcja);

    switch (opcja) {
        case 1:
            createDatabase();
            break;
        case 2:
            przeglad();
            break;
        case 0:
            leftpadding();
            printf("Zakonczono program.\n");
            return 0;
        default:
            leftpadding();
            printf("Nieprawidlowa opcja.\n");
            break;
    }

    return 0;
}
