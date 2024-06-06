#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

void createDatabase() {

    system("cls");
  char nazwa[100];
  leftpadding();
  printf("Podaj nazw\251 pliku bazy danych: ");
  scanf("%s", nazwa);

  for (int i = 0; i < sizeof(nazwa); i++) {
        aktyny[i] = nazwa[i];
  }

  FILE *file = fopen(nazwa, "w"); // Tworzenie nowego pliku
  if (file == NULL) {
        leftpadding();
    printf("Nie mo\276na utworzy\206 pliku.\n");
    return;
  }
  fclose(file);

  FILE *dyskip = fopen(nazwa, "a");
  if (dyskip == NULL) {
        leftpadding();
    printf("Nie mo\276na otworzy\206 pliku.\n");
    return;
  }

  fprintf(dyskip, "1 Kingston Intel SSD 240.00 99.99\n");
  fprintf(dyskip, "2 Seagate WD HDD 1000.00 59.99\n");
  fprintf(dyskip, "3 Samsung Samsung SSD 500.00 129.99\n");

  fclose(dyskip);

  leftpadding();
  printf(
      "Utworzono baz\251 danych o nazwie \"%s\" i dodano przyk\210adowe rekordy.\n",
      nazwa);
  printf("\n");

leftpadding();
  printf("Naci\230nij dowolny klawisz, aby wróci\206 do menu g\210ównego.\n");
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
      printf("Podaj nazwę pliku: ");
      scanf("%s", nazwa);

      for (int i = 0; i < sizeof(nazwa); i++) {
        aktyny[i] = nazwa[i];
      }

      file = fopen(nazwa, "r");
      if (file == NULL) {
            leftpadding();
        printf("Nie można otworzyć pliku.\n");
      }
    } else {
      file = fopen(aktyny, "r");
      if (file == NULL) {
            leftpadding();
        printf("Nie można otworzyć pliku.\n");
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
  printf("Mod - Podaj nowe warto\230ci rekordu:\n");
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
  printf("Pojemno\230\206: ");
  scanf("%lf", &rekord->pojemnosc);
  leftpadding();
  printf("Cena: ");
  scanf("%lf", &rekord->cena);

    leftpadding();
  printf("Rekord zosta\210 zmodyfikowany.\n");
}

void dodajRekord(const char *nazwaPliku)
{

    system("cls");
    leftpadding();
      printf("Dodaj - Podaj nowe warto\230ci rekordu:\n");

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
      printf("Pojemno\230\206: ");
      scanf("%lf", &pojemnosc);


      leftpadding();
      double cena;
      printf("Cena: ");
      scanf("%lf", &cena);

      FILE *file = fopen(nazwaPliku, "a");  // Otworzenie pliku w trybie dopisania
    if (file == NULL) {
        printf("Nie mo\276na otworzy\206 pliku.\n");
        return;
    }

    fprintf(file, "%d %s %s %s %.2lf %.2lf\n", id, nazwa, producent, typ , pojemnosc , cena );  // Zapisanie rekordu do pliku

    fclose(file);

        leftpadding();
  printf("Rekord zosta\210 dodany.\n");
}

void zapiszPlik(struct Rekord *baza, int liczbaRekordow, const char *nazwaPliku) {
  FILE *plik = fopen(nazwaPliku, "w");
  if (plik == NULL) {
        leftpadding();
    printf("Nie mo\276na otworzy\206 pliku.\n");
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
    printf("5. Sortowanie wg Pojemno\230ci\n");
    leftpadding();
    printf("6. Sortowanie wg Ceny\n");
    leftpadding();
    printf("7. Nieprawid\210owy numer pola\n");
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
    printf("\nSortowanie wg Pojemno\230ci\n");
    break;
  case 6:
      leftpadding();
    printf("\nSortowanie wg Ceny\n");
    break;
  default:
      leftpadding();
    printf("\nNieprawid\210owy numer pola\n");
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
  printf("Sortowanie zako\344czone.\n");
}

void przeglad() {

  system("cls");
  FILE *file = otworzPlik();
  if (file == NULL) {
        leftpadding();
    printf("Nie mo\276na otworzy\206 pliku.\n");
    return;
  }

  struct Rekord baza[100]; // Tablica rekordów
  int liczbaRekordow = 0;  // Liczba rekordów w bazie

  char line[100];
  while (fgets(line, sizeof(line), file)) {
    struct Rekord rekord;
    sscanf(line, "%d %s %s %s %lf %lf", &rekord.Id, rekord.nazwa,
           rekord.producent, rekord.typ, &rekord.pojemnosc, &rekord.cena);

    baza[liczbaRekordow] = rekord;
    liczbaRekordow++;
  }

  fclose(file);

  int aktualnyRekord = 0; // Indeks bie\276\245cego rekordu

  while (1) {
    system("cls");

    leftpadding();
    printf("===== Bie\276\245cy rekord: %d =====\n", aktualnyRekord + 1);
    leftpadding();
    printf("Id: %d\n", baza[aktualnyRekord].Id);
    leftpadding();
    printf("Nazwa: %s\n", baza[aktualnyRekord].nazwa);
    leftpadding();
    printf("Producent: %s\n", baza[aktualnyRekord].producent);
    leftpadding();
    printf("Typ: %s\n", baza[aktualnyRekord].typ);
    leftpadding();
    printf("Pojemno\230\206: %.2lf\n", baza[aktualnyRekord].pojemnosc);
    leftpadding();
    printf("Cena: %.2lf\n", baza[aktualnyRekord].cena);

    /*
      printf("\nNaci\230nij B aby przej\230\206 do kolejnego rekordu (dó\210)\n");
      printf("Naci\230nij Y aby przej\230\206 do poprzedniego rekordu (góra)\n");
      printf("Naci\230nij G aby przej\230\206 na pocz\245tek bazy\n");
      printf("Naci\230nij H aby przej\230\206 na koniec bazy\n");
      printf("Naci\230nij D aby usun\245\206 rekord z bazy\n");
      printf("Naci\230nij M aby zmodyfikowa\206 rekord w bazie\n");
      printf("Naci\230nij S aby posortowa\206 rekordy\n");
      printf("Naci\230nij X aby zako\344czy\206 przegl\245danie\n");
      printf("Naci\230nij P aby zapisa\206 plik\n");
    */

    int pad2 = centerText("B - Dó\210 , Y - Góra , G - Pocz\245tek , H - Koniec , D - usuwanie rekordu\n");
    int pad3 = centerText("M - Modyfikacja , A - Dodowanie, S - Sortowanie , P - Zapis , X - Koniec\n");
    leftpadding();
    printf("Wybierz opcj\251: ");

    char option;
    scanf(" %c", &option);

    switch (option) {
    case 'b':
      if (aktualnyRekord < liczbaRekordow - 1) {
        aktualnyRekord++;
      } else {
          leftpadding();
        printf("Jeste\230 ju\276 na ostatnim rekordzie.\n");
      }
      break;
    case 'y':
      if (aktualnyRekord > 0) {
        aktualnyRekord--;
      } else {
          leftpadding();
        printf("Jeste\230 ju\276 na pierwszym rekordzie.\n");
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
        printf("Usunięcie rekordu.\n");
        usuwanieRekordu(baza, &liczbaRekordow, aktualnyRekord);
        break;
    case 'm':
        leftpadding();
      printf("Modyfikacja rekordu.\n");
      modyfikujRekord(&baza[aktualnyRekord]);
      break;
    case 'a':
        leftpadding();
      printf("Dodowanie rekordów.\n");
      dodajRekord(aktyny);
      przeglad();
        break;
    case 's':
        leftpadding();
      printf("Sortowanie rekordów.\n");
      sortuj(baza, liczbaRekordow);
      break;
    case 'p':
        leftpadding();
      printf("Zapisywanie pliku.\n");
      zapiszPlik(baza, liczbaRekordow, aktyny);
      break;
    case 'x':
        leftpadding();
      printf("Zako\344czono przegl\245danie.\n");
      return;
    default:
        leftpadding();
      printf("Nieprawid\210owa opcja.\n");
    }
  }
}

int main() {
  int opcja;
  pad = centerText("===============================\n");
  leftpadding();
  printf("1 - Utworzenie bazy danych\n");
  leftpadding();
  printf("2 - Przegl\245danie bazy danych\n");
  leftpadding();
  printf("0 - Zako\344czenie programu\n");
  leftpadding();
  printf("Wybierz opcj\251: ");
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
    printf("Zako\344czono program.\n");
    return 0;
  default:
      leftpadding();
    printf("Nieprawid\210owa opcja.\n");
    break;
  }

  return 0;
}
