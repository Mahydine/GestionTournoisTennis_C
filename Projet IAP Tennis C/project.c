#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#define maxTournois 10 // nombre maximum de tournois
#define nbMatchsTournoi 127 // nombre de matchs par tournoi
#define nbJoueusesTournoi 128 // nombre de joueuses par tournoi
#define lgMot 30 // taille maximum pour une chaine de caractères

/*
    structure qui permet de crée une joueuse
    nom: un tableau de char qui contient le nom de la joueuse 
    points: entier positif qui corespond au nombre de points de la joueuse
*/
typedef struct
{
    char nom[lgMot+1];
    unsigned int points;
} Joueuse;

/*
    structure qui permet de crée un match
    idxGagnante: entier positif qui est l'index de la gagnante 
    idxPerdante: entier positif qui est l'index de la perdante
*/
typedef struct
{
    unsigned int idxGagnante;
    unsigned int idxPerdante;
} Match;

/*
    structure qui permet de crée un tournoi
    nom: tableau de char qui permet de stocker le nom de tournoi  
    date: tableau de char qui permet de stocker la date du tournoi
    data_match: tableau de match qui permet de stocker les numéros des matchs
*/
typedef struct
{
    char nom[lgMot+1];
    char date[5];
    Match dataMatch[nbMatchsTournoi];
} Tournoi;

/*
    structure qui permet de crée un tournoi WTA
    dataTournois: tableau de Tournoi qui permet de stocker les numéros des tournois
    dataJoueuses: tableau de Joueuse qui permet de stocker les numéros des joueuses de chaques tournois 
    dataMatch: tableau de Match qui permet de stocker les numéros des matchs 
*/
typedef struct
{
    Tournoi dataTournois[maxTournois];
    Joueuse dataJoueuses[maxTournois*nbJoueusesTournoi];
    unsigned int nbTournois;
    unsigned int idxT;
    unsigned int idxJ;
} TournoiWTA;

/*
    fonction qui permet de définir le nombre de tournois
    mot [in/out] unsigned char : mot qui est lu
    enregistrementTournoi [in/out] TournoiWTA
*/
void definir_nombre_tournois(unsigned char *mot, TournoiWTA *enregistrementTournoi)
{
    scanf("%d", mot);

    if (*mot >= 1 && *mot <= 10)    
        enregistrementTournoi->nbTournois = *mot;
    else
    {
        printf("Nombre de tournoi invalide.\n");
        exit(0);        
    }
    scanf("%s", mot); 
}

/*
    fonction qui enregistre les tournois
    mot [in/out] unsigned char : mot qui est lu
    enregistrementTournoi [in/out] TournoiWTA
*/
void enregistrement_tournoi(unsigned char *mot, TournoiWTA *enregistrementTournoi)
{
    int aux = 0;

    scanf("%s", mot);
    strcpy(enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].nom, mot); // copie du nom du tournoi

    scanf("%s", mot);
    strcpy(enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].date, mot); // copie de la date du tournoi
    
    for (int j = 0; j < nbJoueusesTournoi; j++) // enregistrement des joueuses 
    {
        scanf("%s", mot);
        strcpy(enregistrementTournoi->dataJoueuses[enregistrementTournoi->idxJ+j].nom, mot);    
    }

    for (int j = 0; j < 64; j++) // boucle qui permet d'enregistrer l'index des gagnantes, perdantes
    {
        enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxGagnante = j+aux;
        aux++;
        enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante = j+aux;
    }

    for (int j = 64; j < nbMatchsTournoi; j++) // boucle qui permet d'enregistrer l'index des gagnantes, perdantes
    {
        scanf("%s", mot);
        for (int k = 0; k < nbJoueusesTournoi; k++)
        {
            if (strcmp(mot, enregistrementTournoi->dataJoueuses[enregistrementTournoi->idxJ+k].nom) == 0)
            {
                enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxGagnante = k;
                scanf("%s", mot);
                for (int l = 0; l < nbJoueusesTournoi; l++)
                {
                    if (strcmp(mot, enregistrementTournoi->dataJoueuses[enregistrementTournoi->idxJ+l].nom) == 0)
                        enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante = l;
                }
                break;
            }
        } 
    }
    
    for (int j = 0; j < nbJoueusesTournoi; j++) // boucle qui permet d'enregistrer les points des joueuses
    {
        if (j < 64)
            enregistrementTournoi->dataJoueuses[nbJoueusesTournoi*enregistrementTournoi->idxT+enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante].points = 10;
        else if (j >= 64 && j < 96)
            enregistrementTournoi->dataJoueuses[nbJoueusesTournoi*enregistrementTournoi->idxT+enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante].points = 45;
        else if (j >= 96 && j < 112)
            enregistrementTournoi->dataJoueuses[nbJoueusesTournoi*enregistrementTournoi->idxT+enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante].points = 90;
        else if (j >= 112 && j < 120)
            enregistrementTournoi->dataJoueuses[nbJoueusesTournoi*enregistrementTournoi->idxT+enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante].points = 180;
        else if (j >= 120 && j < 124)
            enregistrementTournoi->dataJoueuses[nbJoueusesTournoi*enregistrementTournoi->idxT+enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante].points = 360;
        else if (j >= 124 && j < 126)
            enregistrementTournoi->dataJoueuses[nbJoueusesTournoi*enregistrementTournoi->idxT+enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante].points = 720;
        else if (j == 126)
            enregistrementTournoi->dataJoueuses[nbJoueusesTournoi*enregistrementTournoi->idxT+enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j].idxPerdante].points = 1200;
        else if (j == 127)
            enregistrementTournoi->dataJoueuses[nbJoueusesTournoi*enregistrementTournoi->idxT+enregistrementTournoi->dataTournois[enregistrementTournoi->idxT].dataMatch[j-1].idxGagnante].points = 2000;        
    } 
    scanf("%s", mot);        
    enregistrementTournoi->idxT++;
    enregistrementTournoi->idxJ += 128;  
}

/*
    fonction qui permet l'affichage des informations des tournois
    mot [in/out] unsigned char : mot qui est lu
    enregistrementTournoi [in] TournoiWTA
*/
void affichage_matchs_tournoi(unsigned char *mot, TournoiWTA *enregistrementTournoi)
{
    int tmp = enregistrementTournoi->idxT;
    
    scanf("%s", mot);

    for (int i = 0; i <= enregistrementTournoi->idxT; i++)
    {
        if (strcmp(mot, enregistrementTournoi->dataTournois[tmp].nom) == 0) // comparaison pour savoir si c'est le même nom de tournoi
        {
            printf("%s ", mot);
            scanf("%s", mot);

            if (strcmp(mot, enregistrementTournoi->dataTournois[tmp].date) == 0) // comparaison pour savoir si c'est la même date de tournoi
            {
                printf("%s\n", mot);

                for (int j = 0; j < nbMatchsTournoi; j++) // boucle qui affiche les matchs
                { 
                    if (j == 0)
                        printf("64emes de finale\n");
                    else if (j == 64)
                        printf("32emes de finale\n");
                    else if (j == 96)
                        printf("16emes de finale\n");
                    else if (j == 112)
                        printf("8emes de finale\n");
                    else if (j == 120)
                        printf("quarts de finale\n");
                    else if (j == 124)
                        printf("demi-finales\n");
                    else if (j == 126)
                        printf("finale\n");

                    printf("%s ", enregistrementTournoi->dataJoueuses[enregistrementTournoi->dataTournois[tmp].dataMatch[j].idxGagnante+tmp*nbJoueusesTournoi].nom);
                    printf("%s\n", enregistrementTournoi->dataJoueuses[enregistrementTournoi->dataTournois[tmp].dataMatch[j].idxPerdante+tmp*nbJoueusesTournoi].nom);
                } 
                break;                
            } 
            else 
                tmp--;          
        }
        else
            tmp--;
    }

    if (tmp == -1) // si tournoi est inconnu on quitte le programme
        // printf("Tournoi inconnu\n");
    scanf("%s", mot);
}

/*
    fonction qui affiche tous les matchs d'une joueuses dans un tournoi donné
    mot [in/out] unsigned char : mot qui est lu
    enregistrementTournoi [in] TournoiWTA
*/
void afficher_matchs_joueuse(unsigned char *mot, TournoiWTA *enregistrementTournoi)
{  
    scanf("%s", mot);
    int tmp1 = enregistrementTournoi->idxT;
    int tmp2 = 0;

    for (int i = 0; i <= enregistrementTournoi->idxT; i++)
    {
        if (strcmp(mot, enregistrementTournoi->dataTournois[tmp1].nom) == 0) // comparaison pour savoir si c'est le même nom de tournoi
        {  
            scanf("%s", mot);

            if (strcmp(mot, enregistrementTournoi->dataTournois[tmp1].date) == 0) // comparaison pour savoir si c'est la même date de tournoi
            {
                scanf("%s", mot);

                for (int j = 0; j < nbJoueusesTournoi; j++)
                {
                    if (strcmp(mot, enregistrementTournoi->dataJoueuses[j+tmp1*nbJoueusesTournoi].nom) == 0)
                        tmp2++;   
                }

                if(1)
                {
                    for (int j = 0; j < nbMatchsTournoi; j++) // boucle qui affiche les matchs de la joueuse voulus
                    {
                        if (strcmp(mot, enregistrementTournoi->dataJoueuses[enregistrementTournoi->dataTournois[tmp1].dataMatch[j].idxGagnante+tmp1*nbJoueusesTournoi].nom) == 0)
                            printf("%s %s\n", enregistrementTournoi->dataJoueuses[enregistrementTournoi->dataTournois[tmp1].dataMatch[j].idxGagnante+tmp1*nbJoueusesTournoi].nom, enregistrementTournoi->dataJoueuses[enregistrementTournoi->dataTournois[tmp1].dataMatch[j].idxPerdante+tmp1*nbJoueusesTournoi].nom);
                        else if (strcmp(mot, enregistrementTournoi->dataJoueuses[enregistrementTournoi->dataTournois[tmp1].dataMatch[j].idxPerdante+tmp1*nbJoueusesTournoi].nom) == 0)
                            printf("%s %s\n", enregistrementTournoi->dataJoueuses[enregistrementTournoi->dataTournois[tmp1].dataMatch[j].idxGagnante+tmp1*nbJoueusesTournoi].nom, enregistrementTournoi->dataJoueuses[enregistrementTournoi->dataTournois[tmp1].dataMatch[j].idxPerdante+tmp1*nbJoueusesTournoi].nom);
                    }                    
                } 

            }
            else
                tmp1--;
        }   
        else
            tmp1--;   
    }      
    if (tmp1 == -1) // si tournoi inconnu on quitte le programme
        printf("Tournoi inconnu\n");
    scanf("%s", mot);
}

/*
    fonction qui tri les noms des joueuses par ordre lexicographique
    nomJoueuseTri [in/out] tableau char : tableau avec les noms des joueuses
*/
void nom_joueuse_tri(char nomJoueuseTri[][lgMot+1])
{
    char nomTemp[lgMot+1];
    unsigned int cpt = 1;

    for (int i = 0; i < nbJoueusesTournoi; i++)
    {
        for (int j = cpt; j < nbJoueusesTournoi; j++)
        {
            if (strcmp(nomJoueuseTri[i], nomJoueuseTri[j]) > 0)
            {
                strcpy(nomTemp, nomJoueuseTri[i]);
                strcpy(nomJoueuseTri[i], nomJoueuseTri[j]); 
                strcpy(nomJoueuseTri[j], nomTemp);               
            }
        }
        cpt++;
    }
}

/*
    fonction qui affiche toutes les joueuses avec leur points dans un tournoi donné
    mot [in/out] unsigned char : mot qui est lu
    enregistrementTournoi [in] TournoiWTA
*/
void affichage_joueuses_tournoi(unsigned char *mot, TournoiWTA *enregistrementTournoi)
{
    char nomJoueuseTri[nbJoueusesTournoi][lgMot+1];
    int tmp = enregistrementTournoi->idxT;

    scanf("%s", mot);

    for (int i = 0; i <= enregistrementTournoi->idxT; i++)
    {
        if (strcmp(mot, enregistrementTournoi->dataTournois[tmp].nom) == 0) // comparaison pour savoir si c'est le même nom de tournoi
        {
            printf("%s ", mot);
            scanf("%s", mot);

            if (strcmp(mot, enregistrementTournoi->dataTournois[tmp].date) == 0) // comparaison pour savoir si c'est la même date de tournoi
            {
                printf("%s\n", mot);

                for (int j = 0; j < nbJoueusesTournoi; j++)
                    strcpy(nomJoueuseTri[j], enregistrementTournoi->dataJoueuses[j+tmp*nbJoueusesTournoi].nom);

                nom_joueuse_tri(nomJoueuseTri);

                for (int j = 0; j < nbJoueusesTournoi; j++)
                {
                    for (int i = 0; i < nbJoueusesTournoi; i++)
                    {
                        if (strcmp(nomJoueuseTri[j], enregistrementTournoi->dataJoueuses[i+tmp*nbJoueusesTournoi].nom) == 0)
                            printf("%s %d\n", nomJoueuseTri[j], enregistrementTournoi->dataJoueuses[i+tmp*nbJoueusesTournoi].points); 
                    }
                }                    
            }  
            else
                tmp--; 
        }
        else
            tmp--;
    }
    if (tmp == -1) // si tournoi inconnu on quitte le programme
        printf("Tournoi inconnu\n");
    scanf("%s", mot); 
}

/*
    fonction qui tri les points (ordre décroisant) et les noms en fonction du changement fait aux points
    nbPointsCumules [in/out] unsigned int : nombre de points total (pour chaque joueuses)
    nomJoueuseTri [in/out] tableau char : tableau avec les noms des joueuses triés
    enregistrementTournoi [in] TournoiWTA
    joueusesDifferente [in] unsigned int : nombre de joueuses différentes
*/
void points_nom_joueuses_tri(unsigned int *nbPointsCumules, char nomJoueuseTri[][lgMot+1], TournoiWTA *enregistrementTournoi, unsigned int joueusesDifferente)
{
    unsigned int nbTemp;
    char nomTemp[lgMot+1];
    int cpt = 1;

    for (int i = 0; i < joueusesDifferente; i++)
    {
        for (int j = cpt; j < joueusesDifferente; j++)
        {
            if (nbPointsCumules[i] < nbPointsCumules[j])
            {
                nbTemp = nbPointsCumules[i];
                nbPointsCumules[i] = nbPointsCumules[j];
                nbPointsCumules[j] = nbTemp;
                strcpy(nomTemp, nomJoueuseTri[i]);
                strcpy(nomJoueuseTri[i], nomJoueuseTri[j]); 
                strcpy(nomJoueuseTri[j], nomTemp); 
            }
        }
        cpt++;
    }
}

/*
    fonction qui tri les noms en fonction des points
    nbPointsCumules [in/out] unsigned int : nombre de points total (pour chaque joueuses)
    nomJoueuseTri [in/out] tableau char : tableau avec les noms des joueuses triés
    enregistrementTournoi [in] TournoiWTA
    joueusesDifferente [in] unsigned int : nombre de joueuses différentes
*/
void nom_joueuse_tri_v2(char nomJoueuseTri[][lgMot+1], unsigned int *nbPointsCumules, TournoiWTA *enregistrementTournoi, unsigned int joueusesDifferente)
{
    char nomTemp[lgMot+1];
    unsigned int nbTemp;
    int cpt = 1;

    for (int i = 0; i < joueusesDifferente; i++)
    {
        for (int j = cpt; j < joueusesDifferente; j++)
        {
            if (nbPointsCumules[i] == nbPointsCumules[j])
            {
                if (strcmp(nomJoueuseTri[i], nomJoueuseTri[j]) > 0)
                {
                    strcpy(nomTemp, nomJoueuseTri[i]);
                    strcpy(nomJoueuseTri[i], nomJoueuseTri[j]); 
                    strcpy(nomJoueuseTri[j], nomTemp);                    
                }
            }
            else
                break;
        }
        cpt++;   
    }
}

/*
    permet d'afficher le classement de 4 tournois max (nombres de points par joueuses dans les tournois)
    mot [in] unsigned char : mot qui est lu
    enregistrementTournoi [in/out] TournoiWTA
*/
void afficher_classement(unsigned char *mot, TournoiWTA *enregistrementTournoi)
{
    unsigned int nbPointsCumules[nbJoueusesTournoi*enregistrementTournoi->nbTournois]; // Permet de stocker tout les points cumulés
    char nomJoueuseTri[nbJoueusesTournoi*enregistrementTournoi->nbTournois][lgMot+1]; // Permet de stocker toutes les joueuses triées
    unsigned int joueusesDifferente = nbJoueusesTournoi;
    unsigned int joueusesCompare = joueusesDifferente;
    unsigned int cpt = 0;

    if (enregistrementTournoi->idxT <= 4) // Si moins de 4 tournois
    {    
        for (int i = 0; i < nbJoueusesTournoi*enregistrementTournoi->nbTournois; i++)
            nbPointsCumules[i] = 0;

        for (int i = 0; i < nbJoueusesTournoi; i++)
        {
            nbPointsCumules[i] += enregistrementTournoi->dataJoueuses[i].points;
            strcpy(nomJoueuseTri[i], enregistrementTournoi->dataJoueuses[i].nom);
        }

        for (int i = 1; i < enregistrementTournoi->idxT; i++)
        {
            for (int j = 0; j < nbJoueusesTournoi; j++)
            {
                for (int k = 0; k < joueusesDifferente; k++)
                { 
                    if (strcmp(nomJoueuseTri[k], enregistrementTournoi->dataJoueuses[j+nbJoueusesTournoi*i].nom) != 0)
                    {
                        cpt++;
                        if (cpt == joueusesCompare)
                        {
                            nbPointsCumules[joueusesDifferente] += enregistrementTournoi->dataJoueuses[j+nbJoueusesTournoi*i].points;
                            strcpy(nomJoueuseTri[joueusesDifferente], enregistrementTournoi->dataJoueuses[j+nbJoueusesTournoi*i].nom);
                            joueusesDifferente++; 
                            cpt = 0;
                            break;                     
                        }   
                    } 
                    else
                    {
                        nbPointsCumules[k] += enregistrementTournoi->dataJoueuses[j+nbJoueusesTournoi*i].points; 
                        cpt = 0;
                        break;
                    }     
                }
            }
            joueusesCompare = joueusesDifferente;
        }        
    
        points_nom_joueuses_tri(nbPointsCumules, nomJoueuseTri, enregistrementTournoi, joueusesDifferente);
        nom_joueuse_tri_v2(nomJoueuseTri, nbPointsCumules, enregistrementTournoi, joueusesDifferente);
        
        for (int i = 0; i < joueusesDifferente; i++)
            printf("%s %d\n", nomJoueuseTri[i], nbPointsCumules[i]);
    }
    else // Si plus de 4 tournois
    {
        for (int i = 0; i < nbJoueusesTournoi*enregistrementTournoi->nbTournois; i++)
            nbPointsCumules[i] = 0;

        for (int i = 0; i < nbJoueusesTournoi; i++)
        {
            nbPointsCumules[i] += enregistrementTournoi->dataJoueuses[(enregistrementTournoi->idxT-4)*nbJoueusesTournoi+i].points;
            strcpy(nomJoueuseTri[i], enregistrementTournoi->dataJoueuses[(enregistrementTournoi->idxT-4)*nbJoueusesTournoi+i].nom);
        }

        for (int i = enregistrementTournoi->idxT-3; i < enregistrementTournoi->idxT; i++)
        {
            for (int j = 0; j < nbJoueusesTournoi; j++)
            {
                for (int k = 0; k < joueusesDifferente; k++)
                { 
                    if (strcmp(nomJoueuseTri[k], enregistrementTournoi->dataJoueuses[j+nbJoueusesTournoi*i].nom) != 0)
                    {
                        cpt++;
                        if (cpt == joueusesCompare)
                        {
                            nbPointsCumules[joueusesDifferente] += enregistrementTournoi->dataJoueuses[j+nbJoueusesTournoi*i].points;
                            strcpy(nomJoueuseTri[joueusesDifferente], enregistrementTournoi->dataJoueuses[j+nbJoueusesTournoi*i].nom);
                            joueusesDifferente++; 
                            cpt = 0;
                            break;                     
                        }   
                    } 
                    else
                    {
                        nbPointsCumules[k] += enregistrementTournoi->dataJoueuses[j+nbJoueusesTournoi*i].points; 
                        cpt = 0;
                        break;
                    }     
                }
            }
            joueusesCompare = joueusesDifferente;
        }

        points_nom_joueuses_tri(nbPointsCumules, nomJoueuseTri, enregistrementTournoi, joueusesDifferente);
        nom_joueuse_tri_v2(nomJoueuseTri, nbPointsCumules, enregistrementTournoi, joueusesDifferente);

        for (int i = 0; i < joueusesDifferente; i++)
            printf("%s %d\n", nomJoueuseTri[i], nbPointsCumules[i]);   
    }
    scanf("%s", mot);   
}
    
int main()
{
    unsigned char mot[lgMot+1]; // chaine de caractères (mot) de taille lgMot
    TournoiWTA enregistrementTournoi;

    enregistrementTournoi.idxJ = 0;
    enregistrementTournoi.idxT = 0;

    scanf("%s", &mot);

    while (1)
    { 
        if (strcmp(mot, "definir_nombre_tournois") == 0)
            definir_nombre_tournois(mot, &enregistrementTournoi);
        else if (strcmp(mot, "enregistrement_tournoi") == 0)
            enregistrement_tournoi(mot, &enregistrementTournoi);
        else if (strcmp(mot, "affichage_matchs_tournoi") == 0)
            affichage_matchs_tournoi(mot, &enregistrementTournoi);
        else if (strcmp(mot, "afficher_matchs_joueuse") == 0)
            afficher_matchs_joueuse(mot, &enregistrementTournoi);
        else if (strcmp(mot, "affichage_joueuses_tournoi") == 0)
            affichage_joueuses_tournoi(mot, &enregistrementTournoi);
        else if (strcmp(mot, "afficher_classement") == 0)
            afficher_classement(mot, &enregistrementTournoi);
        else if (strcmp(mot, "exit") == 0) 
            exit(0);
    }
    system("pause");

    return 0;
}