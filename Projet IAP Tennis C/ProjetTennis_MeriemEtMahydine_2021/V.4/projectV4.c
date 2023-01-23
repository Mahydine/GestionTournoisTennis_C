#define lgMot 30
#define nbMatchsTournoi 127
#define maxTournois 10
#define nbJoueuses 128
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#pragma warning(disable:4996)


typedef struct {
	char nom[lgMot + 1];
	unsigned int points;
}Joueuse;

typedef struct {
	unsigned int idxGagnante;
	unsigned int idxPerdante;
}Match;

typedef struct {
	char nom[lgMot + 1];
	unsigned int date;
	Match dataMatch[nbMatchsTournoi];
}Tournoi;

typedef struct {
	unsigned int nbTournois;
	unsigned int idxJ;
	unsigned int idxT;
	Tournoi dataTournois[maxTournois];
	Joueuse dataJoueuses[nbJoueuses * maxTournois];
}TournoiWTA;

void definir_nombre_tournois(TournoiWTA* t) {
	unsigned int nbTournois;
	scanf("%d", &nbTournois);
	assert(nbTournois > 0 && nbTournois <= 10);
	(*t).nbTournois = nbTournois;
	(*t).idxJ = 0;
	(*t).idxT = 0;
}
int idJ(Joueuse* dataJ, const char* nom, unsigned int* idxJ) {
	int i;
	for (i = 0; i < *idxJ && strcmp(dataJ[i].nom, nom) != 0; i++);
	if (i == *idxJ) {
		strcpy(dataJ[*idxJ].nom, nom);
		dataJ[*idxJ].points = 0;
		++* idxJ;
	}
	return i;
}
void enregistrement_tournoi(TournoiWTA* T) {
	assert((*T).idxT < (*T).nbTournois);
	Tournoi* t = &(*T).dataTournois[(*T).idxT];
	Joueuse* dataJ = (*T).dataJoueuses;
	scanf("%s", (*t).nom);
	scanf("%d", &((*t).date));
	char j_temp[lgMot + 1];
	for (int i = 0; i < nbMatchsTournoi; ++i) {
		scanf("%s", j_temp);
		t->dataMatch[i].idxGagnante = idJ(T->dataJoueuses, j_temp, &(*T).idxJ);
		scanf("%s", j_temp);
		t->dataMatch[i].idxPerdante = idJ(T->dataJoueuses, j_temp, &(*T).idxJ);
	}
	++(*T).idxT;

}
int idTournoi(const Tournoi* t, const int idT, const char* nom, const int date) {
	int k = 0;
	int c = !(strcmp(t[0].nom, nom) == 0 && t[0].date == date);
	for (k = 0; k < idT && c; k++) {
		c = !(strcmp(t[k + 1].nom, nom) == 0 && date == t[k + 1].date);
	}
	return k;
}
int idJMin(const int id1, const int id2, Joueuse*J1,Joueuse*J2) {
	if (J1->points > J2->points)return id1;
	else if (J1->points == J2->points) {
		int c = strcmp(J1->nom, J2->nom);
		assert(c != 0);
		if (c > 0)return id2;
		else return id1;
	}
	else return id2;
}
void afficher_classement(TournoiWTA* T) {
	int classement[nbJoueuses * maxTournois];
	Joueuse* dataJ = &T->dataJoueuses;
	for (int i = 0; i < T->idxJ; ++i) {
		dataJ[i].points = 0;
		classement[i] = i;
	}
	for (int i = 0; i < T->idxT; ++i) {
		Match* M = &T->dataTournois[i].dataMatch;
		unsigned int score[8] = { 2000,1200,720,360,180,90,45,10 };
		int m = 0;
		for (int i = 6; i > -1; --i) {
			for (int j = 0; j < pow(2, i); j++) {
				dataJ[M[m].idxPerdante].points += score[i + 1];
				m++;
			}
		}
		dataJ[M[nbMatchsTournoi - 1].idxGagnante].points += score[0];
	}

	for (int i = 0; i < T->idxJ; i++) {
		int m = i;
		for (int j = T->idxJ - 1; j > i; --j) {
			int c = idJMin(m, j,&dataJ[classement[m]] , &dataJ[classement[j]]);
			if (c == j)m = j;
		}
		int temp = classement[m];
		classement[m] = classement[i];
		classement[i] = temp;
		printf("%s %d\n", dataJ[classement[i]].nom, dataJ[classement[i]].points);
	}
}

int main() {
	char mot[lgMot + 1];
	TournoiWTA t;
	while (1) {
		scanf("%s", mot);
		if (strcmp(mot, "definir_nombre_tournois") == 0) {
			definir_nombre_tournois(&t);
		}
		if (strcmp(mot, "enregistrement_tournoi") == 0) {
			enregistrement_tournoi(&t);
		}
		if (strcmp(mot, "afficher_classement") == 0) {
			afficher_classement(&t);
		}
		if (strcmp(mot, "exit") == 0) {
			exit(0);
		}

	}
}