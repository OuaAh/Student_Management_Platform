#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#define N 5

int main();

typedef struct{
    char* NOM;
    char* PRENOM;
    char CIN[9];
    float MOYENNE;
}ETUDIANT;

typedef struct LISTE LISTE;
struct LISTE{
    ETUDIANT E;
    LISTE* LIEN;
};

int FONCTION(ETUDIANT E){
    return(atoi(E.CIN)%N);
}

int EST_CIN(char* Tx){
    int i=0,B=1;
    if (strlen(Tx)!=8) B=0;
    while ((B)&&(Tx[i]))
     if (!(isdigit(Tx[i]))) B=0;
        else i++;
    return(B);
}

int EST_MOT(char* Tx){
    int i=0,B=1;
    while ((B)&&(Tx[i]))
     if ((!(isalpha(Tx[i])))&&!(isspace(Tx[i]))) B=0;
        else i++;
    return(B);
}

void SAISIR_ETUDIANT(ETUDIANT** E){
    char Tx[20];
    system("cls");
    (*E)=malloc(sizeof(ETUDIANT));

    do {
    fflush(stdin);
    printf("\n NOM: ");
    gets(Tx);
    (*E)->NOM=(char*)malloc(strlen(Tx)+1);
    strcpy((*E)->NOM,Tx);
    } while (!(EST_MOT((*E)->NOM)));

    do {
    fflush(stdin);
    printf("\n PRENOM: ");
    gets(Tx);
    (*E)->PRENOM=(char*)malloc(strlen(Tx)+1);
    strcpy((*E)->PRENOM,Tx);
    } while (!(EST_MOT((*E)->PRENOM)));

    do {printf("\n MOYENNE: ");scanf("%f",&((*E)->MOYENNE));}
    while (((*E)->MOYENNE>20)||((*E)->MOYENNE<0));

    do {fflush(stdin);printf("\n CIN: ");gets((*E)->CIN);}
    while (!(EST_CIN((*E)->CIN)));
    FILE* F;
    F=fopen("ETUDIANT.txt","a");
    fprintf(F," %s\t%s\t%s\t%2.2f\n",(*E)->NOM,(*E)->PRENOM,(*E)->CIN,(*E)->MOYENNE);
    fclose(F);
}

void INITIALIZER(LISTE*** T){
    int i;
    (*T)=(LISTE*)calloc(N,sizeof(LISTE*));
}

void AJOUTER(LISTE** L,ETUDIANT E){
    LISTE* AUX;
    AUX=malloc(sizeof(LISTE));
    AUX->E=E;
    AUX->LIEN=(*L);
    (*L)=AUX;
}

void SOMMET(LISTE** L,ETUDIANT E){
    (*L)=malloc(sizeof(LISTE));
    (*L)->E=E;
    (*L)->LIEN=NULL;
}

void REMPLIR(LISTE** T){
    system("cls");
    ETUDIANT *E;
    SAISIR_ETUDIANT(&E);
    if (T[FONCTION(*E)]) AJOUTER(&(T[FONCTION(*E)]),*E);
    else SOMMET(&(T[FONCTION(*E)]),*E);
}

void AFFICHIER(LISTE** T){
 int i;
 LISTE *L;
 system("cls");
 for(i=0;i<N;i++){
 L=T[i];
 while (L) {
        printf("\n %s\t%s\t%2.2f\t%s ",(L->E).NOM,(L->E).PRENOM,(L->E).MOYENNE,(L->E).CIN);

   L=L->LIEN;}
}
}

void SUPPRIMER(LISTE** T){
    char Tx[9];
    REESSAYER:
    system("cls");
    do {fflush(stdin);printf("\n SUPPRIMER L'ETUDIANT DE CIN: ");gets(Tx);}
    while (!(EST_CIN(Tx)));

    system("cls");
    LISTE* L;
    LISTE* A;
    int B=1;
    L=T[atoi(Tx)%N];
    A=NULL;

    if (L){
    B=strcmp((L->E).CIN,Tx);
    if (!B) T[atoi(Tx)%5]=T[atoi(Tx)%5]->LIEN;
    else
    do{
    if (!B) A->LIEN=L->LIEN;
    A=L;
    L=L->LIEN;
    } while(L&&B);
    }
    if (B!=0) {printf("\n CIN INCORRECT.");getch();
               system("cls");
               printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
               int i;
               scanf("%d",&i);
               switch (i){
                   case 1 : goto REESSAYER;break;
                   case 2 :;break;
                   case 3 : exit(EXIT_SUCCESS);break;
               }
              }
}

void MODIFIER(LISTE** T){
    char Tx[9];

    REESSAYER:
    system("cls");
    do {fflush(stdin);printf("\n MODIFIER l'ETUDIANT DE CIN: ");gets(Tx);}
    while (!(EST_CIN(Tx)));

    system("cls");
    LISTE* L;
    int B=1;
    L=T[atoi(Tx)%N];
    if (L){
    do{
        B=strcmp((L->E).CIN,Tx);
        if (!B) {
            int i;
            SOUSREESSAYER:
            system("cls");
            printf("\n MODIFIER:\n\n 1.NOM:\n 2.PRENOM:\n 3.MOYENNE:\n 4.RETOUR\n 5.SORTIR\n ");
            scanf("%d",&i);
            switch (i){
                case 1 :{
                    system("cls");
                    char T[20];
                    do {
                    fflush(stdin);
                    printf("\n NOM: ");
                    gets(T);
                    } while (!(EST_MOT(T)));
                    strcpy((L->E).NOM,T);
                }break;
                case 2 :{
                    system("cls");
                    char T[20];
                    do {
                    fflush(stdin);
                    printf("\n PRENOM: ");
                    gets(T);
                    } while (!(EST_MOT(T)));
                    strcpy((L->E).PRENOM,T);
                }break;
                case 3 :{
                    system("cls");
                    do {printf("\n MOYENNE: ");scanf("%f",&((L->E).MOYENNE));}
                    while (((L->E).MOYENNE>20)||((L->E).MOYENNE<0));
                }break;
                case 4 : ;break;
                case 5 : exit(EXIT_SUCCESS);break;
                default : {system("cls");
                           printf("\n CHOIX INCORRECT.");getch();
                           system("cls");
                           printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
                           int i;
                           scanf("%d",&i);
                           switch (i){
                           case 1 : goto SOUSREESSAYER;break;
                           case 2 : goto REESSAYER;break;
                           case 3 : exit(EXIT_SUCCESS);break;
               }
              }
            }

        };
    L=L->LIEN;
    } while(L&&B);
    }
    if (B!=0) {printf("\n CIN INCORRECT.");getch();
               system("cls");
               printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
               int i;
               scanf("%d",&i);
               switch (i){
                   case 1 : goto REESSAYER;break;
                   case 2 : ;break;
                   case 3 : exit(EXIT_SUCCESS);break;
               }
              }
}

void RECHERCHER(LISTE** T){
    char Tx[9];

    REESSAYER:
    system("cls");
    do {fflush(stdin);printf("\n CIN: ");gets(Tx);}
    while (!(EST_CIN(Tx)));

    system("cls");
    LISTE* L;
    int B=1;
    L=T[atoi(Tx)%N];
    if (L){
    do{
        B=strcmp((L->E).CIN,Tx);
        if (!B) printf("\n PROFIL DE ETUDIANT\n NOM: %s\n PRENOM: %s\n MOYENNE: %2.2f\n CIN: %s\n ",(L->E).NOM,(L->E).PRENOM,(L->E).MOYENNE,(L->E).CIN);
        L=L->LIEN;
    }while(L&&B);
    }
    if (B!=0) {printf("\n CIN INEXISTANT.");getch();
               system("cls");
               printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
               int i;
               scanf("%d",&i);
               switch (i){
                   case 1 : goto REESSAYER;break;
                   case 2 :;break;
                   case 3 : exit(EXIT_SUCCESS);break;
               }
              }
}

void FAFFICHIER(FILE* F){
    char x;
    system("cls");
    F=fopen("ETUDIANT.txt","r");
    do{
        x=fgetc(F);
        printf("%c",x);
    } while (x!=EOF);
    fclose(F);
}

void FRECHERCHER(FILE* F){
    char Tx[9];
    char NOM[25],PRENOM[25],CIN[9];
    float MOYENNE;
    int B=1;
    FILE* G;
    F=fopen("ETUDIANT.txt","r");

    REESSAYER:
    system("cls");
    do {fflush(stdin);printf("\n CIN: ");gets(Tx);}
    while (!(EST_CIN(Tx)));
    system("cls");
    G=fopen("ETUDIANT.txt","r");
    fseek(G,0,SEEK_END);

    if (ftell(F)!=ftell(G)){
    do{
    fscanf(F," %s\t%s\t%s\t%f\n",NOM,PRENOM,CIN,&MOYENNE);
    B=strcmp(CIN,Tx);
    }while(B&&(ftell(F)<ftell(G)));
    fclose(F);}

    if (B) {printf("\n CIN INEXISTANT.");getch();
               system("cls");
               printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
               int i;
               scanf("%d",&i);
               switch (i){
                   case 1 : goto REESSAYER;break;
                   case 2 :;break;
                   case 3 : exit(EXIT_SUCCESS);break;
               }
              }
    else printf("\n PROFIL DE ETUDIANT\n NOM: %s\n PRENOM: %s\n MOYENNE: %2.2f\n CIN: %s\n ",NOM,PRENOM,MOYENNE,CIN);
}

/*void FSUPPRIMER(FILE* F){
    char Tx[9];
    char NOM[25],PRENOM[25],CIN[9];
    float MOYENNE;
    int B=1,x;
    F=fopen("ETUDIANT.txt","r");
    FILE* G;
    FILE* H;

    REESSAYER:
    system("cls");
    do {fflush(stdin);printf("\n CIN: ");gets(Tx);}
    while (!(EST_CIN(Tx)));
    system("cls");

    H=fopen("ETUDIANT.txt","r");
    fseek(H,0,SEEK_END);

    if (ftell(F)!=ftell(H)){
    do{
    x=ftell(F);
    fscanf(F," %s\t%s\t%s\t%f\n",NOM,PRENOM,CIN,&MOYENNE);
    B=strcmp(CIN,Tx);
    if (!(B)){G=fopen("ETUDIANT.txt","r+");
              fseek(G,x+1,SEEK_SET);
              char y=1;
              while (y!=EOF){y=fgetc(F);if (y!=EOF) fputc(y,G);}
              fclose(G);
              }
    }while(B&&(ftell(F)<ftell(H)));
    fclose(F);}

    if (B) {printf("\n CIN INEXISTANT.");getch();
               system("cls");
               printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
               int i;
               scanf("%d",&i);
               switch (i){
                   case 1 : goto REESSAYER;break;
                   case 2 :;break;
                   case 3 : exit(EXIT_SUCCESS);break;
               }
              }
}

void FMODIFIER(FILE* F){
    char Tx[9];
    char NOM[25],PRENOM[25],CIN[9];
    float MOYENNE;
    int B=1,x;
    F=fopen("ETUDIANT.txt","r");
    FILE* G;
    FILE* H;

    REESSAYER:
    system("cls");
    do {fflush(stdin);printf("\n CIN: ");gets(Tx);}
    while (!(EST_CIN(Tx)));
    system("cls");

    H=fopen("ETUDIANT.txt","r");
    fseek(H,0,SEEK_END);

    if (ftell(F)!=ftell(H)){
    do{
    x=ftell(F);
    fscanf(F," %s\t%s\t%s\t%f\n",NOM,PRENOM,CIN,&MOYENNE);
    B=strcmp(CIN,Tx);
    if (!(B)){G=fopen("ETUDIANT.txt","r+");
              fseek(G,x-1,SEEK_SET);
              char y='a',z='a';
              while (y!=EOF){y=fgetc(F);fputc(y,G);}
              fclose(G);
              }
    }while(B&&(ftell(F)<ftell(H)));
    fclose(F);}

    if (B) {printf("\n CIN INEXISTANT.");getch();
               system("cls");
               printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
               int i;
               scanf("%d",&i);
               switch (i){
                   case 1 : goto REESSAYER;break;
                   case 2 :;break;
                   case 3 : exit(EXIT_SUCCESS);break;
               }
              }
}*/

int main()
{
    LISTE** T;
    INITIALIZER(&T);
    int i;
    MENU:
    system("cls");
    printf("\n 1.AJOUTER\n 2.MODIFIER\n 3.SUPPRIMER\n 4.AFFICHIER\n 5.RECHERCHER\n 6.SORTIR\n ");
    scanf("%d",&i);
    switch (i){
        case 1 : {REMPLIR(T);goto MENU;};break;
        case 2 : {MODIFIER(T);getch();goto MENU;};break;
        case 3 : {SUPPRIMER(T);goto MENU;};break;
        case 4 : {AFFICHIER(T);getch();goto MENU;};break;
        case 5 : {RECHERCHER(T);getch();goto MENU;};break;
        case 6 : exit(EXIT_SUCCESS);break;
        default : {printf("\n CHOIX INCORRECT.");exit(EXIT_SUCCESS);}
    }
    return(0);
}
