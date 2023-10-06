#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Structure pour contenir une cellue braille //
struct braille{
	char cellule[3][2];
	char lettre;
}; typedef struct braille BRAILLE;
//////// Initialisation de la structure ///////
BRAILLE init(){
	BRAILLE b;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			b.cellule[i][j] = ' ';
		}
	}
	b.lettre = ' ';
	return b;
}
////////////////////////////////////////////////

// Fonction pour calculer la puissance d'un nombre //
int puissance(int x, int exp){
	int res = x;
	if (!exp) return 1;
	for(int i = 0; i < exp-1; i++){
		res *= x;
	}
	return res;
}
/////////////////////////////////////////////////////

// Transformer du noir en braille : //
// 1. Passage de la numérotation de la cellule à un vecteur base 2 //
bool* inttobool(int* cellule){
	int taille = 6;
	bool* vecteur = malloc(sizeof(bool)*taille);
	for(int i = 0; i < taille; i++)
		vecteur[i] = false;
	for(int i = 0; i < taille; i++)
		vecteur[cellule[i]-1] = true;
	return vecteur;
}
// 2. Associer à un caractère le vecteur en base 2 associé
bool* noirtovect(char c){
	bool* vect = malloc(sizeof(bool)*6);
	vect = (bool []){false,false,false,false,false,false};
	switch (c){
	case 'a':
	case'k':
	case'u':
		vect = (bool []){1, 0, 0, 0, 0, 0};
		if(c != 'a') {vect[2] = 1;}
		if(c == 'u') {vect[5] = 1;}
		break;
	case 'b':
	case'l':
	case'v':
		vect = (bool []){1, 1, 0, 0, 0, 0};
		if(c != 'b') {vect[2] = 1;}
		if(c == 'v') {vect[5] = 1;}
		break;
	case 'c':case'm':case'x':
		vect = (bool []){1, 0, 0, 1, 0, 0};
		if(c != 'c') vect[2] = 1;
		if(c == 'x') vect[5] = 1;
		break;
	case 'd':case'n':case'y':
		vect = (bool []){1, 0, 0, 1, 1, 0};
		if(c != 'd') vect[2] = 1;
		if(c == 'y') vect[5] = 1;
		break;
	case 'e':case'o':case'z':
		vect = (bool []){1, 0, 0, 0, 1, 0};
		if(c != 'e') vect[2] = 1;
		if(c == 'z') vect[5] = 1;
		break;
	case 'f':case'p':
		vect = (bool []){1, 1, 0, 1, 0, 0};
		if(c=='p') vect[2] = 1;
		break;
	case 'g': case 'q':
		vect = (bool []){1, 1, 0, 1, 1, 0};
		if(c=='q') vect[2] = 1;
		break;
	case 'h': case 'r':
		vect = (bool []){1, 1, 0, 0, 1, 0};
		if(c=='r') vect[2] = 1;
		break;
	case 'i': case 's':
		vect = (bool []){0, 1, 0, 1, 0, 0};
		if(c=='s') vect[2] = 1;
		break;
	case 'j': case 't': case 'w':
		vect = (bool []){0, 1, 0, 1, 1, 0};
		if(c=='t') vect[2] = 1;
		if(c=='w') vect[5] = 1;
		break;
	default:
		vect = (bool []){0, 0, 0, 0, 0, 0};
		break;
	}
	return vect;
}
// 3. Un vecteur de base 2 vers cellule braille //
BRAILLE ntobchar(bool* vecteur){
	BRAILLE b = init();
	for(int i = 0; i < 6; i++){
		if(vecteur[i] == true){
			b.cellule[i/3][i%3] = '*';
		}
	}
	return b;
}
///////////////////////////////////////////////

// Transformer du braille en noir : //
// x. Vecteur base 2 vers un entier base 10
int vecttoint(bool* vecteur){
	int res = 0;
	for(int i = 0; i < 4; i++)
		res += vecteur[i]*puissance(2, 3-i);
	return res;
}

BRAILLE vecttobraille(bool* vect){
	BRAILLE b = init();
	int point = 0;
	for(int j = 0; j < 2; j++){
		for(int i = 0; i < 3; i++){
			if(vect[point])
				b.cellule[i][j] = '*';
			point++;
		}
	}
	return b;
}

/// vecteur vers lettre
char brailletonoir(bool* vecteur){
	char lettre = ' ';
	bool v[4];
	int trucla = 0;
	bool bg = vecteur[2];
	printf("hey%d\n", bg);

	bool bd = vecteur[5];
	v[0] = vecteur[0];
	v[1] = vecteur[1];
	v[2] = vecteur[3];
	v[3] = vecteur[4];
	trucla = vecttoint(v) - 5;
	switch(trucla){
	case 1 :
		if(vecteur[2] == true){
			lettre = 's';
		}
		else{
			lettre = 'i';
		}
		break;
	case 2:
		if(vecteur[5] == true){
			lettre = 'w';
		}
		else if(vecteur[2] == true){
			lettre = 't';
		}
		else{
			lettre = 'j';
		}
		break;
	case 3:
		if(bd) lettre = 'u';
		else if(bg) lettre = 'k';
		else lettre = 'a';
		break;
	case 4:
		if(bd) lettre = 'z';
		else if(bg) lettre = 'o';
		else lettre = 'e';
		break;
	case 5:
		if(bd) lettre = 'x';
		else if(bg) lettre = 'm';
		else lettre = 'c';
		break;
	case 6:
		if(bd) lettre = 'y';
		else if(bg) lettre = 'n';
		else lettre = 'd';
		break;
	case 7:
		if(bd) lettre = 'v';
		else if(bg) lettre = 'l';
		else lettre = 'b';
		break;
	case 8:
		if(bg) lettre = 'r';
		else lettre = 'h';
		break;
	case 9:
		if(bg) lettre = 'p';
		else lettre = 'f';
		break;
	case 10:
		if(bg) lettre = 'q';
		else lettre = 'g';
		break;
	default: lettre = ' ';
	}
	return lettre;
}

BRAILLE lettre(char c){
	BRAILLE b = init();
	b.lettre = c;
	b = vecttobraille(noirtovect(c));
	return b;
}

// Ecrit en braille depuis des lettres
void noirtobraille(char* str){
	BRAILLE b;
	for(int i = 0; i < 3; i++){
		for(int k = 0; k < strlen(str); k++){
			b = lettre(str[k]);
			for (int j =0; j < 2; j++){
				printf("%c", b.cellule[i][j]);
			}
			printf(" ");
		}
		printf("\n");
	}
	printf("%s\n", str);
}

int* chartotab(char* chaine){
	int* inttab = malloc(sizeof(int)*6);
	for(int i =0; i < 6; i++){
		inttab[i] = chaine[i]-48;
		printf("%d - %c\n", inttab[i], chaine[i]);
	}
	return inttab;
}

int main(int argc, char *argv[]){
	char lettre = ' ';
	int tab[6] = {0, 0, 0, 0, 0, 0};
	char* chaine = malloc(sizeof(char)*255);
	if(strcmp(argv[1], "lettre") == 0){
		printf("Ecrire une lettre en braille : ");
		scanf("%s", chaine);
		lettre = brailletonoir(inttobool(chartotab(chaine)));
		printf("La lettre correspondante : %c\n", lettre);
	}
	else if(strcmp(argv[1], "braille") == 0){
		printf("Ecrire un mot : ");
		scanf("%s", chaine);
		noirtobraille(chaine);
	}
	else{
		for (int i = 0; i < argc; i++)
        	printf("argv[%d] = %s\n", i, argv[i]);
		printf("Erreur...\n");
	}

	return 0;
}
```
