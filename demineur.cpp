#include <iostream>
#include <random>
#include "time.h"

using namespace std;

int** t;
char** bombes;
int nCol = 0;
int nLig = 0;
int nBombes = 0;
int nFlags = 0;
char chiffres[10] = {'0','1','2','3','4','5','6','7','8','9'};

void Free_Tab(){
	for(int i = 0; i< nLig;i++) {
		delete[] t[i];
	}
	delete[] t;

}

void afficherLigne(char a, int nombre, bool fin = true){
	for (int k = 0; k<nombre+2;k++) cout << a;
	if (fin == true) {
		cout << endl;
	}
}

void afficherTab(){
	afficherLigne(' ', 20, false);
	afficherLigne('_',2*nCol);
	for (int i = 0; i < nLig;i++){
		afficherLigne(' ', 20, false);
		cout << "| ";
		for(int j = 0;j < nCol;j++){
			cout << bombes[i][j] << " ";
		}
		cout << "|" << endl;
	}
	afficherLigne(' ', 20, false);
	afficherLigne('-', 2*nCol);
}

void afficherT(){
	afficherLigne(' ', 20, false);
	afficherLigne('_',2*nCol);
	for (int i = 0;i < nLig; i++) {
		afficherLigne(' ',20, false);
		cout << "| ";
		for (int j = 0; j < nCol; j++) {
			if (t[i][j] == -1) {
				cout << "b ";
			}
			else {
				cout << t[i][j] << " ";
			}
		}
		cout << "|" << endl;
	}
	afficherLigne(' ',20,false);
	afficherLigne('-', 2*nCol);
}

void init() {
	cout << "X--------------------------------X" << endl;
	cout << "|             DEMINEUR           |" << endl;
	cout << "X--------------------------------X" << endl;
	cout << "          (par GcBrothers)        " << endl;
	cout << endl << endl << endl;
	cout << "Combien de lignes voulez-vous ?" << endl;
	while (nLig < 2) cin >> nLig;
	cout << "Combien de colonnes ?" << endl;
	while (nCol < 2) cin >> nCol;
	cout << "Combien de bombes ?" << endl;
	while (nBombes < 1 || nBombes > nCol * nLig) cin >> nBombes;
	nFlags = nBombes;
	cout << "Have fun ;)" << endl;
}

void remplirT(){
	int c = 0;
	int i,j;
	//On place les bombes au hasard
	while (c<nBombes){
		i = rand()%nLig;
		j = rand()%nCol;
		if (t[i][j] == 0)
		{
			t[i][j] = -1;
			//bombes[i][j] = 'b'; // C'était le test
			c++;
		}
	}
	//On remplit le nombre de bombes à côté d'un case
	c = 0;
	//D'abord au milieu
	for(int i =1; i< nLig-1; i ++) {
		for (int j = 1;j<nCol-1;j++) {
			//Si on n'est pas sur une bombe
			if (t[i][j] != -1) {
				for (int k = i-1;k<=i+1;k++) {
					for (int e = j-1;e <= j+1;e++) {
						if (t[k][e] == -1) {
							c+=1;
						}
					}
				}
			t[i][j] = c;
			c = 0;
			}
		}
	}
	c = 0;
	//On s'occupe de la ligne 0
	for (int j = 1; j < nCol-1; j++) {
		if (t[0][j] != -1) {
			for (int k = 0;k<=1;k++) {
				for (int e = j-1; e <= j+1; e++) {
					if (t[k][e] == -1) {
						c += 1;
					}
				}
			}
		t[0][j] = c;
		c = 0;
		}
	}
	//De la dernière ligne
	for (int j = 1; j < nCol-1;j++) {
		if (t[nLig-1][j] != -1) {
			for (int k = nLig -2; k <= nLig -1;k++) {
				for (int e = j-1;e <= j+1; e++) {
					if (t[k][e] == -1) {
						c += 1;
					}
				}
			}
		t[nLig-1][j] = c;
		c = 0;
		}
	}
	c=0;
	//De la première colonne
	for (int i = 1; i < nLig -1; i++) {
		if(t[i][0] != -1) {
			for (int k = i-1; k <= i+1; k++) {
				for (int e = 0; e <= 1; e++) {
					if (t[k][e] == -1) {
						c+=1;
					}
				}
			}
		t[i][0] = c;
		c = 0;
		}
	}
	c = 0;
	//De la dernière colonne
	for (int i = 1; i < nLig -1;i++) {
		if (t[i][nCol -1] != -1) {
			for (int k = i-1; k <= i+1; k++) {
				for (int e = nCol-2; e<= nCol-1; e++) {
					if (t[k][e] == -1) {
						c += 1;
					}
				}
			}
		t[i][nCol-1] = c;
		c = 0;
		}
	}
	c = 0;
	//Des 4 coins
	if (t[0][0] != -1) {
		if (t[0][1] == -1) c += 1;
		if (t[1][1] == -1) c += 1;
		if (t[1][0] == -1) c += 1;
		t[0][0] =c;
		c = 0;
	}
	if (t[0][nCol-1] != -1) {
		if(t[0][nCol-2] == -1) c+=1;
		if(t[1][nCol-2] == -1) c+=1;
		if(t[1][nCol-1] == -1) c+=1;
		t[0][nCol-1] = c;
		c = 0;
	}
	if (t[nLig-1][0] != -1) {
		if (t[nLig-2][0] == -1) c+=1;
		if (t[nLig-2][1] == -1) c+=1;
		if (t[nLig-1][1] == -1) c+=1;
		t[nLig-1][0] = c;
		c = 0;
	}
	if (t[nLig-1][nCol-1] != -1) {
		if (t[nLig-2][nCol-1] == -1) c+=1;
		if (t[nLig-2][nCol-2] == -1) c+=1;
		if (t[nLig-1][nCol-2] == -1) c+=1;
		t[nLig-1][nCol-1] = c;
		c = 0;
	}

}

void deminer(int i, int j) {
	if (nFlags <= 0) {
		cout << "Vous n'avez plus de drapeaux D:" << endl;
	}
	if (bombes[i][j] == 'X' && nFlags > 0) {
		bombes[i][j] = 'd';
		nFlags -= 1;
	}
}

void enlever(int i, int j) {
	if (bombes[i][j] == 'd') {
		bombes[i][j] = 'X';
		nFlags += 1;
	}
}

bool verifier() {
	bool perdu = true;
	for (int i =0; i < nLig; i++) {
		for (int j = 0; j < nCol;j++) {
			if (bombes[i][j] == 'X') {
				perdu = false;
			}
		}
	}
	return perdu;
}

int essayer(int i, int j) {
	if (bombes[i][j] == 'd') {
		cout << "Vous avez déminé cette case ! " << endl;
		return 0;
	}
	if (t[i][j] == -1) {
		cout << "BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUM" << endl;
		cout << "(il y avait une bombe D:)" << endl;
		return -1;
	}
	if (t[i][j] != -1) {
		bombes[i][j] = chiffres[t[i][j]];
		return 0;
	}
}


int main()
{
	srand(time(NULL));
	init();
	//Déclaration des tableaux, t stocke l'emplacement des bombes, bombes l'affichage
	t = new int* [nLig];
	bombes = new char*[nLig];
	//On les déclare
	for (int i=0;i<nLig;i++)
	{
		t[i] = new int[nCol];
		bombes[i] = new char[nCol];
	}
	//on les remplit (0 pour t, X pour bombes)
	for (int i=0;i<nLig;i++)
	{
		for(int j=0;j<nCol;j++)
		{
			t[i][j] = 0;
			bombes[i][j] = 'X';
			//cout << i*j << endl;
		}
	}
	remplirT();
	//afficherTab();
	bool termine = false;
	int term = 0,lig,col;
	char choix = 'a';
	while (termine == false && term == 0) {
		cout << "*************************************************" << endl;
		cout << "****************** Début du tour ! **************" << endl;
		cout << "*************************************************" << endl;
		afficherTab();
		cout << "Que voulez-vous faire : essayer (w), deminer(d) ou enlever (e) un marqueur  ?" << endl;
		while (choix != 'd' && choix != 'e' && choix != 'w') cin >> choix;
		cout << "Où ? : Ligne :" << endl;
		while (lig<0 || lig > nLig) cin >> lig;
		cout << "Colonne ?" << endl;
		while (col < 0 || col > nCol) cin >> col;;
		switch (choix) {
			case 'w':
				term = essayer(lig,col);
				break;
			case 'd':
				deminer(lig,col);
				break;
			case 'e':
				enlever(lig,col);
		}
		termine = verifier();
		lig = -1;
		col = -1;
		choix = 'a';
	}
	if (termine == true) {
		cout << "Vous avez GAAAAAAAAAAAAGGGGGNNNNNNNNNNNEEEEEEEEE !" << endl;
	}
	if (term == -1) {
		cout << "Vous avez donc perdu D:" << endl;
	}
	afficherT();
	Free_Tab();
	return 0;
}
