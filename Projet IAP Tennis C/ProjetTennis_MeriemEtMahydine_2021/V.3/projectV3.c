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
	int k=0;
	int c = !(strcmp(t[0].nom, nom) == 0 && t[0].date == date);
	for (k = 0; k < idT && c; k++) {
		c = !(strcmp(t[k + 1].nom, nom) == 0 && date == t[k + 1].date);
	}
	return k;
}
int idJMin(const int id1, const int id2, char* nom1, char* nom2) {
	int c = strcmp(nom1, nom2);
	assert(c != 0);
	if (c > 0)return id2;
	else return id1;
}
void affichage_joueuses_tournoi(TournoiWTA* T) {
	char nom_t[lgMot + 1];
	scanf("%s", nom_t);
	unsigned int date_t;
	scanf("%d", &date_t);
	int idxT = idTournoi(T->dataTournois, T->idxT, nom_t, date_t);
	assert(idxT < T->idxT);
	printf("%s %d\n", nom_t, date_t);
	Tournoi* t = &T->dataTournois[idxT];
	Joueuse* dataJ = &T->dataJoueuses;
	int class[nbJoueuses];
	unsigned int score[8] = { 2000,1200,720,360,180,90,45,10 };
	int m = 0;
	for (int i = 6; i > -1; --i) {
		for (int j = 0; j < pow(2, i); j++) {
			dataJ[t->dataMatch[m].idxPerdante].points = score[i + 1];
			class[m] = t->dataMatch[m].idxPerdante;
			m++;
		}
	}
	dataJ[t->dataMatch[nbMatchsTournoi - 1].idxGagnante].points = score[0];
	class[m] = t->dataMatch[nbMatchsTournoi-1].idxGagnante;

	for (int i = 0; i < nbJoueuses; i++) {
		int m = i;
		for (int j = nbJoueuses - 1; j > i; --j) {
			int c = idJMin(m, j, dataJ[class[m]].nom, dataJ[class[j]].nom);
			if (c == j)m=j;
		}
		int temp=class[m];
		class[m] = class[i];
		class[i] = temp;
		printf("%s %d\n",dataJ[class[i]].nom, dataJ[class[i]].points);
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
		if (strcmp(mot, "affichage_joueuses_tournoi") == 0) {
			affichage_joueuses_tournoi(&t);
		}
		if (strcmp(mot, "exit") == 0) {
			exit(0);
		}

	}
}