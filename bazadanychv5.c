#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include<fcntl.h>


#define ESC 27

struct Dysk{
    int Id;
    char nazwa[20];
    char producent[20];
    char typ [5];
    double pojemnosc;
    double cena;
};

struct Dysk p1={1, "Kingston" , "Intel" , "SSD" , 1000 , 259.99};
struct Dysk p2={2, "Seagate" , "WD" , "HDD" , 250 , 180.72};
struct Dysk p3={3, "Samsung" , "Samsung" , "SSD" , 1500 , 469.99};

void gotoxy(short x , short y);
FILE *fp1=NULL,*fp2=NULL;
char *tryb1, *tryb2;
char nazwaBazy[11]="";
char nazwaBazyotwartej[11]="";


void gotoxy(short x, short y){
    COORD pos ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void menu(){
    char ch;
    int x=20 , y=8;
    gotoxy(x,y);
    printf("=========================");

    gotoxy(x,y+1);
    printf("1. Utworz baze");

    gotoxy(x,y+2);
    printf("2. Otworz baze");

    gotoxy(x,y+3);
    printf("3. Usun baze");

    gotoxy(x,y+4);
    printf("4. Zakoncz program");

    fflush(stdin);
    ch=getchar();

    do{
        while ( ch!='1' && ch!='2'&& ch!='3'&& ch!='4');
        switch(ch){

        case '1':
        gotoxy(20 , 18);
         printf(" Wybrano opcja 1 - Enter");
         getchar();
         utworzbaze();
         przeglad(1);
        break;

        case '2':
        gotoxy(20 , 18);
         printf(" Wybrano opcja 2 - Enter");
         getchar();
         otworzbaze();
         przeglad(2);
        break;

        case '3':
        gotoxy(20 , 18);
         printf(" Wybrano opcja 3 - Enter");
         getchar();
         usunbaze();
        break;

        case '4':
        gotoxy(20 , 18);
         printf(" Wybrano opcja 4 - Enter");
         getchar();
         exit(0);
        break;
        }
    }
    while(1);

}

void utworzbaze(void){
    char nazwa[20];
    int x=20 , y=20;
    system("cls");
    gotoxy(x,y);
    printf("Utworz baze ");
    wczytywanieNazwyBazy();
    if(fp1!=NULL){
        printf("\n Nowego pliku minibazy %s nie mozna utworzyc ",nazwaBazy);
        printf("\njesli inny plik minibazy jest otwarty");
        getchar();
        return;
    }
    fp1=fopen(nazwaBazy,"w+b");
    if(fp1==NULL)
    printf("\n Plik %s nie zostal utworzony", nazwaBazy);
    else
    printf("\n Nowy plik %s zostal utworzony", nazwaBazy);
    getchar();
    return;
}

void otworzbaze(void){
    char nazwaBazy[11];
     int x=20,y=20;
     system("cls");
     gotoxy(x,y);
     printf(" Otworz baze");
     wczytywanieNazwyBazy();
     if(fp1!=NULL){
        printf("\n Pliku minibazy %s nie mozna otworzyc ",nazwaBazy);
        printf("\n Inny plik minibazy jest otworzony");
        getchar();
        return;
     }
    fp1=fopen(nazwaBazy,"a+b");
    if(fp1==NULL)
    printf("\n Plik %s nie zostal utworzony", nazwaBazy);
    else
     printf("\n Nowy plik %s zostal utworzony", nazwaBazy);
    getchar();
}

void usunbaze(void){
    char nazwa[5];
    int x=20,y=20,wynik;
    system("cls");
    gotoxy(x,y);
    printf(" Usun baze");
    wczytywanieNazwyBazy();
    gotoxy(x,22);
    fp1=fopen(nazwaBazy,"rb");
    if(fp1==NULL)
    printf("\n Plik %s nie moze byc usuniety", nazwaBazy);
    else{
        fclose(fp1);
        wynik=remove(nazwaBazy);
        if (wynik) printf(" Plik zostal usuniety");
        else
        printf(" Plik nie zostal usuniety");
     }
return ;
}

void przeglad(void){
    struct Dysk st;
    int x=1,y=24;
     char ch;
    system("cls");
    gotoxy(x,y);
    printf(" Przeglad Bazy");
    Status();

    while (1)
    {
        Status();
        do{
            fflush(stdin);
            ch=toupper(getch());
        }
        while (ch!='Y' && ch!='B'&& ch!='G'&& ch!='H'&&ch!='R'&& ch!='M'&&ch!='S'&&ch!='D'&&ch!=ESC);
        {
            switch (ch)
            {
            case 'Y':
             gotoxy(20,18);
             printf(" Wybrano opcja Y ");
                break;
            case 'B':
             gotoxy(20,18);
             printf(" Wybrano opcja B ");
                break;
            case 'G':
             gotoxy(20,18);
             printf(" Wybrano opcja G ");
                break;

            case 'H':
             gotoxy(20,18);
             printf(" Wybrano opcja H ");
             getchar();
                break;

            case 'S':
             gotoxy(20,18);
             printf(" Wybrano opcja S - sortowanie  ");
             getchar();
             break;

            case 'R':
             gotoxy(20,18);
             printf(" Wybrano opcja R - Enter ");
             wczytajStrukt();
             drukujStruktury();
             Status();
             getchar();
             break;

            case 'M':
             gotoxy(20,18);
             printf(" Wybrano opcja M - Enter ");
             getchar();
             break;

            case 'D':
             gotoxy(20,18);
             printf(" Wybrano opcja D - Enter ");
             break;

             case ESC:
             gotoxy(20,18);
             printf(" Wybrano opcja ESC - Menu ");
             return;

            default:
                break;
            }
        }
        return;

    }

}

void sortowanie(FILE *fp,int np){
    printf("\n Sortowanie");
    struct Dysk bufs1, bufs2;
    int i,n=4,zam;
    char s1[20],s2[20];

    int Id;
    char nazwa[20];
    char producent[20];
    char typ [5];
    double pojemnosc;
    double cena;

    switch (np)
    {
    case 1: printf("\n Sortowanie wg ID");//int
     break;

    case 2: printf("\n Sortowanie wg nazwy");//char
     break;

    case 3: printf("\n Sortowanie wg producenta");//char
     break;

    case 4: printf("\n Sortowanie wg typu");//char
     break;

    case 5: printf("\n Sortowanie wg pojemosci");//double
     break;

    case 6: printf("\n Sortowanie wg ceny");//dpuble
     break;
    }
    if(np==2 || np==3 || np==4){
        do{
           zam=0;
            for(i=0;i<n-1;i++){
                fseek(fp, i*sizeof(struct Dysk), SEEK_SET);
                fread(&bufs1,sizeof(struct Dysk),1,fp);
                fread(&bufs2,sizeof(struct Dysk),1,fp);
                zwrocPoleStruktLan(np,bufs1, s1 );
                zwrocPoleStruktLan(np,bufs1, s2 );
                if (strcmp(s1, s2)>0){
                    fseek(fp, i*sizeof(struct Dysk), SEEK_SET);
                    fwrite(&bufs2,sizeof(struct Dysk),1,fp);
                    fwrite(&bufs1,sizeof(struct Dysk),1,fp);
                    zam=1;
                }
            }
        }
        while (zam);
    }
    int p1,p2;
    if (np==1 ){
        do{
        zam=0;
        for(i=0;i<n-1;i++){
            fseek(fp, i*sizeof(struct Dysk), SEEK_SET);
            fread(&bufs1,sizeof(struct Dysk),1,fp);
            fread(&bufs2,sizeof(struct Dysk),1,fp);
            p1=zwrocPoleStruktInt(np,bufs1);
            p2=zwrocPoleStruktInt(np,bufs2);
            if (p1>p2){
                fseek(fp, i*sizeof(struct Dysk), SEEK_SET);
                fwrite(&bufs2,sizeof(struct Dysk),1,fp);
                fwrite(&bufs1,sizeof(struct Dysk),1,fp);
                zam=1;
            }
        }
    }
    while(zam);
    }
    return;
}

void drukStruktury(struct Dysk st){
    int x=20,y=8;
    system("cls");

    gotoxy(x,y);
    printf("Id:%d", st.Id);

    gotoxy(x,y+1);
    printf("Nazwa:%s", st.nazwa);

    gotoxy(x,y+2);
    printf("Producent:%s", st.producent);

    gotoxy(x,y+3);
    printf("Typ:%s", st.typ);

    gotoxy(x,y+4);
    printf("Pojemnosc:%f",st.pojemnosc);

    gotoxy(x,y+3);
    printf("Cena:%f",st.cena);

}

void wczytajStrukt(){
    struct Dysk st;
    fflush(stdin);
    int x=20,y=8;
    system("cls");

    gotoxy(x,y);
    fflush(stdin);
    printf("Id:");
    scanf("%d",&st.Id);
    Status();

    gotoxy(x,y+1);
    printf("Nazwa:");
    scanf("%s",st.nazwa);
    fflush(stdin);

    gotoxy(x,y+2);
    printf("Producent:");
    scanf("%s",st.producent);
    fflush(stdin);

    gotoxy(x,y+3);
    printf("Typ:");
    scanf("%s",st.typ);
    fflush(stdin);

    gotoxy(x,y+4);
    printf("Pojemnosc:");
    scanf("%lf",&st.pojemnosc);


    gotoxy(x,y+5);
    printf("Cena:");
    scanf("%lf",&st.cena);

    return st;
}

void Status(void){
    gotoxy(1,24);
    printf(" Y-up B-down G-Home H-End R-read M-modify S-sort D-del ESC-exit");
}

void wczytywanieNazwyBazy(void){
    char nazwa[11];
    printf("\n Podaj nazwe bazy format XXXXXX.dat:");
    scanf("%11s",nazwaBazy);
    strcpy(nazwaBazyotwartej, nazwaBazy);
}

void zwrocPoleStruktLan(int np, struct Dysk st,char s[]){
    if (np==2) strcpy(s,st.nazwa);
    if (np==3) strcpy(s,st.producent);
    if (np==4) strcpy(s,st.typ);
}

void zwrocPoleStruktInt(int np, struct Dysk st){
    if (np==1) return st.Id;
}

void zwrocPoleStruktDouble(int np, struct Dysk st){
    if (np==5) return st.pojemnosc;
    if (np==6) return st.cena;
}

void usuwanieStrukturyZbazy(void){
struct Dysk bufs;// definicja pomocniczej struktury bufs
 fpos_t nrRek;
 int aktPozycjaWskaznikaPliku;
 int rozmiarPlikBajty;
 fgetpos(fp1, &nrRek);
 //zapis aktualnej pozycji wskaźnika pliku przed
 // ustawieniem wskaźnika pliku przed ostatnią strukturą w pliku
 //-------------------------------------------------------

 fseek (fp1,-1*sizeof(struct Dysk),SEEK_END);
//ustawienie wskaźnika pliku
 //przed ostatnią strukturą w pliku

 fread(&bufs,sizeof(struct Dysk),1,fp1);

 // odczyt ostatniej struktury

 fsetpos(fp1, &nrRek);
 //ustawienie wskaźnika pliku po usuwanej strukturze

 fseek(fp1, -sizeof(struct Dysk),SEEK_CUR);
 // cofnięcie wskaźnika

 fwrite(&bufs,sizeof(struct Dysk),1,fp1);
 // zapis ostatniej struktury w miejsce usuwanej

 aktPozycjaWskaznikaPliku=ftell(fp1);
 // Wyznaczenie aktualnego rozmiaru pliku

 fseek(fp1,0,SEEK_END);
 rozmiarPlikBajty=ftell(fp1);
 fclose(fp1);


int handle;
handle=open(nazwaBazyotwartej, O_RDWR);
if (handle!=-1) printf("\n Plik zostal otwarty ");
else {
printf("\n Plik nie zostal otwarty");
chsize(handle, rozmiarPlikBajty-sizeof(struct Dysk));
close(handle);
}
//Funkcja chsize obcina plik do zadanej długości w bajtach.
fp1=fopen(nazwaBazyotwartej,"r+b");
fseek(fp1,aktPozycjaWskaznikaPliku,SEEK_SET);

}

int main(int argc , char *argv[]){
    while(1){
        system("cls");
        menu();
    }
    if(fp1) fclose(fp1);
    if(fp2) fclose(fp2);
    printf("\n Zakonczenie programu");
    getchar();
    return 0;

}
