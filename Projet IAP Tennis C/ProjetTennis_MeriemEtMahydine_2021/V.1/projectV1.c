#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define maxTournois 10
#define nbMatchsTournoi 127
#define nbJoueusesTournoi 128
#define lgMot 30

typedef struct {
    char nom[lgMot+1];
    unsigned int points;
}Joueuse;

typedef struct {
    unsigned int idxGagnante; 
    unsigned int idxPerdante; 
}Match;

typedef struct {
    char nomTournoi[lgMot+1];
    char dateTournoi[4];
    Match dataMatch[nbMatchsTournoi+1];
}Tournoi;

typedef struct {
    Tournoi dataTournois[maxTournois];
    Joueuse dataJoueuse[maxTournois * nbJoueusesTournoi];
    unsigned int nbTournois;
    unsigned int idxT;
    unsigned int idxJ;
}TournoisWTA;

void Definir_nombre_tournois(TournoisWTA *t){
    // Crée une variable temporaire de stockage
    unsigned int nbTournoisTemp;
    // Demander et stocker dans nbtournois le nombre de tournois
    scanf("%d", &nbTournoisTemp);
    // Si nbtournois n'est pas compris entre 1 et 10 alors le programme plante
    assert(nbTournoisTemp > 0 && nbTournoisTemp <= 10);
    // Si le programme ne plante pas alors...
    (*t).nbTournois = nbTournoisTemp;
    (*t).idxT = 0;
    (*t).idxJ = 0;
}

void Enregistrement_tournoi(TournoisWTA *t){
    // Vérifie que le nombres de tournois défini n'es pas déjà atteint
    assert(t->idxT < t->nbTournois);
    // Scanne le nom et la date du tournois dans la structure
    scanf("%s", t->dataTournois[t->idxT].nomTournoi);
    scanf("%s", t->dataTournois[t->idxT].dateTournoi);
    printf("%s %s\n", t->dataTournois[t->idxT].nomTournoi, t->dataTournois[t->idxT].dateTournoi);
    // Crée une variable temporaire de stockage
    char JoueuseTemp[lgMot+1]; 
    // Scanner les résultat des matchs dans la variable temporaire
    for (int i = 0 ; i < nbMatchsTournoi ; i++){
        scanf("%s", JoueuseTemp);
        int k;
        for(k = 0; k < t->idxJ && strcmp(t->dataJoueuse[k].nom, JoueuseTemp) != 0 ; k++);
            if(k == t->idxJ){
                strcpy (t->dataJoueuse[k].nom, JoueuseTemp);
                ++(*t).idxJ;
                (*t).dataJoueuse[k].points=0;
            }
        t->dataTournois[t->idxT].dataMatch[i].idxGagnante=k;
        scanf("%s", JoueuseTemp);
        for(k = 0; k < t->idxJ && strcmp(t->dataJoueuse[k].nom, JoueuseTemp) != 0 ; k++);
            if(k == t->idxJ){ // ouiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii faut juste lui dire va dans cette case COMPARE avec ce qu'on veut et si c bon c ok !!!!!!
                strcpy (t->dataJoueuse[k].nom, JoueuseTemp);
                ++(*t).idxJ;
                (*t).dataJoueuse[k].points=0; // non je gard epour le compte rendu ça explique les difficultés tqt 
            }
        t->dataTournois[t->idxT].dataMatch[i].idxPerdante=k;
    } // bah ok ça ft quoi ? on prend le code qu'on a ft là là avec perdante et gagnante pffffff bvvv
    (*t).idxT++;
}

void Affichage_matchs_tournoi (TournoisWTA *t){ //printf("tournoi inconnu"); //idxPerdante idxGagnante
    char nomtournoi[lgMot+1];
    char date [4];
    scanf("%s", nomtournoi);
    scanf("%s", date);
    unsigned int w;
    for (w = 0 ; w < t->idxT && strcmp(t->dataTournois[w].nomTournoi, nomtournoi) == 0 && strcmp(t->dataTournois[w].dateTournoi, date) == 0 ; w++);
    unsigned int idMatch=0;
    for(int i = 6; i >= 0; --i){
        if(i==6) printf("%.0femes de finale\n", pow(2, i));

        else if(i==5) printf("%.0femes de finale\n", pow(2, i));
        
        else if (i==4) printf("%.0femes de finale\n", pow(2, i));

        else if (i==3) printf("%.0femes de finale\n", pow(2, i));
        
        else if (i==2) printf("quarts de finale\n");

        else if (i==1) printf("demi-finales\n");

        else if (i==0) printf("finale\n");
        
        for (int m = 0; m < pow(2,i); ++m){
            unsigned int idxG = t->dataTournois[w].dataMatch[idMatch].idxGagnante;
            unsigned int idxP = t->dataTournois[w].dataMatch[idMatch].idxPerdante;
            printf("%s %s\n", t->dataJoueuse[idxG].nom, t->dataJoueuse[idxP].nom);
            ++idMatch;
        }
    }
} 

int main(){
    char Commande[lgMot+1];
    TournoisWTA t;
    while (1){  // Cette boucle tourne à l'infini pour que l'on puisse rentrer le nombre de commande que l'on veut
        scanf("%s", Commande);
            if (strcmp(Commande, "definir_nombre_tournois") == 0){
                Definir_nombre_tournois(&t);
            }else if(strcmp(Commande, "enregistrement_tournoi") == 0){
                Enregistrement_tournoi(&t);
            }else if(strcmp(Commande, "affichage_matchs_tournoi") == 0){
                Affichage_matchs_tournoi(&t);
            }else if(strcmp(Commande, "exit") == 0){
                exit(0);
            }
    }
    return 0;
}