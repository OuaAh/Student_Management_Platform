#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

typedef struct{
    char* NOM;
    char* PRENOM;
    char CIN[9];
    float MOYENNE;
}ETUDIANT;

typedef struct ARBRE{
    ETUDIANT E;
    struct ARBRE *FG,*FD;
}ARBRE;

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
     if (!(isalpha(Tx[i]))) B=0;
        else i++;
    return(B);
}

void SAISIR(ARBRE **A,char *CIN){
    (*A)=(ARBRE*)malloc(sizeof(ARBRE));
    (*A)->FD=NULL;
    (*A)->FG=NULL;
    strcpy(((*A)->E).CIN,CIN);

    char Tx[25];

    do{
        fflush(stdin);
        printf("\n  NOM: ");
        gets(Tx);
    } while (!EST_MOT(Tx));
    ((*A)->E).NOM=(char*)malloc(strlen(Tx)+1);
    strcpy(((*A)->E).NOM,Tx);

    do{
        fflush(stdin);
        printf("\n  PRENOM: ");
        gets(Tx);
    } while (!EST_MOT(Tx));
    ((*A)->E).PRENOM=(char*)malloc(strlen(Tx)+1);
    strcpy(((*A)->E).PRENOM,Tx);

    do{
        printf("\n  MOYENNE: ");
        scanf("%f",&(((*A)->E).MOYENNE));
    } while ((((*A)->E).MOYENNE>20)||(((*A)->E).MOYENNE<0));
}

void AJOUTER(ARBRE **A,char *CIN){
    if (!(*A)) {SAISIR(A,CIN);}
    else if (strcmp(CIN,((*A)->E).CIN)<0) AJOUTER(&((*A)->FG),CIN);
         else AJOUTER(&((*A)->FD),CIN);
}

void REMPLIR(ARBRE **A){
    int N;

    do{
        printf("\n NOMBRE D'ETUDIANT: ");
        scanf("%d",&N);
    }
    while (N<0);

    int i;
    char CIN[9];

    for(i=0;i<N;i++){
        system("cls");
        do{
            fflush(stdin);
            printf("\n  ETUDIANT N°%d",i+1);
            printf("\n\n  CIN: ");
            gets(CIN);
        } while (!EST_CIN(CIN));
        AJOUTER(A,CIN);
    }
}

void SAUVGARDER(ARBRE *A){
    FILE *F;
    int G,D;
    F=fopen("ETUDIANT.txt","a");
    if (A){
        if (A->FG) G=1;else G=0;
        if (A->FD) D=1;else D=0;
        fprintf(F,"%d %d\t%s\t%s\t%s\t%2.2f\n",G,D,(A->E).NOM,(A->E).PRENOM,(A->E).CIN,(A->E).MOYENNE);
        fclose(F);
        if (A->FG) SAUVGARDER(A->FG);
        if (A->FD) SAUVGARDER(A->FD);
    }
}

void PROTEGER(ARBRE *A){
    FILE *F;
    F=fopen("ETUDIANT.txt","w");
    fclose(F);
    SAUVGARDER(A);
}

void RESTORER(ARBRE **A,FILE *F){
    int G,D;
    float MOYENNE;
    char NOM[25],PRENOM[25],CIN[9];
    FILE *H;
    H=fopen("ETUDIANT.txt","r");
    fseek(H,0,SEEK_END);
    if(ftell(H)!=ftell(F)){
    (*A)=NULL;
        fscanf(F,"%d %d\t%s\t%s\t%s\t%f\n",&G,&D,NOM,PRENOM,CIN,&MOYENNE);
        (*A)=(ARBRE*)malloc(sizeof(ARBRE));
        ((*A)->E).NOM=(char*)malloc(strlen(NOM)+1);
        strcpy(((*A)->E).NOM,NOM);
        ((*A)->E).PRENOM=(char*)malloc(strlen(PRENOM)+1);
        strcpy(((*A)->E).PRENOM,PRENOM);
        strcpy(((*A)->E).CIN,CIN);
        ((*A)->E).MOYENNE=MOYENNE;
        if (G) RESTORER(&((*A)->FG),F);else (*A)->FG =NULL;
        if (D) RESTORER(&((*A)->FD),F);else (*A)->FD =NULL;
    }
}

void AFFICHAGE_PREFIXE(ARBRE* A){
    if (A){
        printf("\n NOM: %s\tPRENOM: %s\tCIN: %s\tMOYENNE: %2.2f",(A->E).NOM,(A->E).PRENOM,(A->E).CIN,(A->E).MOYENNE);
        AFFICHAGE_PREFIXE(A->FG);
        AFFICHAGE_PREFIXE(A->FD);
    }
}

void AFFICHAGE_INFIXE(ARBRE* A){
    if (A){
        AFFICHAGE_INFIXE(A->FG);
        printf("\n NOM: %s\tPRENOM: %s\tCIN: %s\tMOYENNE: %2.2f",(A->E).NOM,(A->E).PRENOM,(A->E).CIN,(A->E).MOYENNE);
        AFFICHAGE_INFIXE(A->FD);
    }
}

void AFFICHAGE_POSTFIXE(ARBRE* A){
    if (A){
        AFFICHAGE_POSTFIXE(A->FG);
        AFFICHAGE_POSTFIXE(A->FD);
        printf("\n NOM: %s\tPRENOM: %s\tCIN: %s\tMOYENNE: %2.2f",(A->E).NOM,(A->E).PRENOM,(A->E).CIN,(A->E).MOYENNE);
    }
}

void AJOUTER_ETUDIANT(ARBRE **A){
    char CIN[9];
    system("cls");
    printf("\n AJOUTER:");
    do{
            fflush(stdin);
            printf("\n\n  CIN: ");
            gets(CIN);
        } while (!EST_CIN(CIN));
    AJOUTER(A,CIN);
    system("cls");
    printf("\n ETUDIANT AJOUTE.");

}

void MODIFIER(ARBRE **A,int *B,char* CIN){
    if (!(*A)) *B=0;
    else {if (!strcmp(((*A)->E).CIN,CIN)) {
                char Tx[25];
                int i;
                *B=1;
                system("cls");
                printf("\n 1.NOM\n 2.PRENOM\n 3.MOYENNE\n 4.SORTIR\n ");
                scanf("%d",&i);
                system("cls");
                switch(i){
                case 1: {do{
                    fflush(stdin);
                    printf("\n NOM: ");
                    gets(Tx);
                } while (!EST_MOT(Tx));
                ((*A)->E).NOM=(char*)malloc(strlen(Tx)+1);
                strcpy(((*A)->E).NOM,Tx);};break;

                case 2: {do{
                fflush(stdin);
                printf("\n PRENOM: ");
                gets(Tx);
                } while (!EST_MOT(Tx));
                ((*A)->E).PRENOM=(char*)malloc(strlen(Tx)+1);
                strcpy(((*A)->E).PRENOM,Tx);}break;

                case 3: {do{
                printf("\n MOYENNE: ");
                scanf("%f",&(((*A)->E).MOYENNE));
                } while ((((*A)->E).MOYENNE>20)||(((*A)->E).MOYENNE<0));}break;

                case 4 :{PROTEGER(*A);exit(EXIT_SUCCESS);}break;

                default : {printf("\n CHOIX INCORRECT.");PROTEGER(*A);exit(EXIT_SUCCESS);}
                }
    }
    else if (strcmp(((*A)->E).CIN,CIN)<0) MODIFIER(&((*A)->FD),B,CIN);
            else MODIFIER(&((*A)->FG),B,CIN);
    }
}

void MODIFIER_ETUDIANT(ARBRE **A){
    char CIN[9];
    int B;
    REESSAYER:
    system("cls");
    printf("\n MODIFIER:");
    do{
            fflush(stdin);
            printf("\n\n  CIN: ");
            gets(CIN);
        } while (!EST_CIN(CIN));
    MODIFIER(A,&B,CIN);
    system("cls");
    printf("\n ETUDIANT MODIFIE.");
    if (!B){
        int i;
        system("cls");
        printf("\n CIN INEXISITANT.\n ");
        getch();
        system("cls");
        printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
        scanf("%d",&i);
        switch (i){
            case 1 : goto REESSAYER;break;
            case 2 :;break;
            case 3 : {PROTEGER(*A);exit(EXIT_SUCCESS);}break;
            default : {printf("\n CHOIX INCORRECT.");PROTEGER(*A);exit(EXIT_SUCCESS);}
        }
    }
}

ARBRE** PPD(ARBRE *A){
    if (!(A->FG)) return(A);
    else return(PPD(A->FG));
}

void SUPPRIMER(ARBRE **A,int *B,char* CIN){
    ARBRE *P, *Q, *H;
    if (!(*A)) *B=0;
    else {if (!strcmp(((*A)->E).CIN,CIN)) {
            *B=1;
        if ((!((*A)->FG))&&(!((*A)->FD))) {free(*A);(*A)=NULL;}
        else if (((*A)->FG)&&(!((*A)->FD))) {(*A)=(*A)->FG;}
        else if (((*A)->FD)&&(!((*A)->FG))) {(*A)=(*A)->FD;}
        else if (((*A)->FG)&&((*A)->FD)) {
                P=(*A)->FD;
                while (P->FG) P=P->FG;
                Q=malloc(sizeof(ARBRE));
                Q->E=P->E;
                Q->FG=(*A)->FG;
                if (P==(*A)->FD) {(*A)->FD=P->FD;free(P);}
                else {H=(*A)->FD; while((H->FG)->FG) H=H->FG; H->FG=P->FD; free(P);}
                Q->FD=(*A)->FD;
                free(*A);
                (*A)=Q;
                }
    }
    else if (strcmp(((*A)->E).CIN,CIN)<0) SUPPRIMER(&((*A)->FD),B,CIN);
            else SUPPRIMER(&((*A)->FG),B,CIN);
    }
}

void SUPPRIMER_ETUDIANT(ARBRE **A){
    char CIN[9];
    int B;
    REESSAYER:
    system("cls");
    printf("\n SUPPRIMER:");
    do{
            fflush(stdin);
            printf("\n\n  CIN: ");
            gets(CIN);
        } while (!EST_CIN(CIN));
    SUPPRIMER(A,&B,CIN);
    system("cls");
    printf("\n ETUDIANT SUPPRIME.");
    if (!B){
    int i;
    system("cls");
    printf("\n CIN INEXISITANT.\n ");
    getch();
    system("cls");
    printf("\n 1.REESSAYER\n 2.RETOUR\n 3.SORTIR\n ");
    scanf("%d",&i);
    switch (i){
        case 1 : goto REESSAYER;break;
        case 2 :;break;
        case 3 : {PROTEGER(*A);exit(EXIT_SUCCESS);}break;
        default : {printf("\n CHOIX INCORRECT.");PROTEGER(*A);exit(EXIT_SUCCESS);}
    }
   }
}

int main()
{
    ARBRE *A;
    A=NULL;
    REMPLIR(&A);
    SAUVGARDER(A);
    FILE *F;
    F=fopen("ETUDIANT.txt","r");
    RESTORER(&A,F);
    fclose(F);

    MENU:
    system("cls");
    int i;
    printf("\n 1.AJOUTER\n 2.MODIFIER\n 3.SUPPRIMER\n 4.AFFICHIER\n 5.SORTIR\n ");
    scanf("%d",&i);
    switch (i){
        case 1 :{
            AJOUTER_ETUDIANT(&A);
            getch();goto MENU;
        }break;
        case 2 :{
            MODIFIER_ETUDIANT(&A);
            getch();goto MENU;
        }break;
        case 3 :{
            SUPPRIMER_ETUDIANT(&A);
            getch();goto MENU;
        }break;
        case 4 : {
            system("cls");
            printf("\n 1.AFFICHAGE PREFIXE\n 2.AFFICHAGE INFIXE\n 3.AFFICHAGE POSTFIXE\n 4.SORTIR\n 5.RETOUR\n ");
            scanf("%d",&i);

            switch (i){
            case 1 : {system("cls");AFFICHAGE_PREFIXE(A);getch();goto MENU;}break;
            case 2 : {system("cls");AFFICHAGE_INFIXE(A);getch();goto MENU;}break;
            case 3 : {system("cls");AFFICHAGE_POSTFIXE(A);getch();goto MENU;}break;
            case 4 : {PROTEGER(A);exit(EXIT_SUCCESS);}break;
            case 5 : goto MENU;
            default: {
                PROTEGER(A);
                printf("\n CHOIX INCORRECT.");
                exit(EXIT_SUCCESS);
                }
            }
        }break;
        case 5 : {PROTEGER(A);exit(EXIT_SUCCESS);}break;
        default : {
            PROTEGER(A);
            printf("\n CHOIX INCORRECT.");
            exit(EXIT_SUCCESS);
        }
    }
    PROTEGER(A);
    return 0;
}
