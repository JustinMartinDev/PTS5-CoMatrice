#include "CMatriceFichier.h"



/*************************************************************************
**** Nom: MAFLireFichier                                              ****
**************************************************************************
**** Permet de lire, d'interpreter et de construire une matrice a     ****
****    partir d'un fichier                                           ****
**************************************************************************
**** Pr�condition:                                                    ****
**** Entr�e:                                                          ****
****    pcChemin : const char* => Chemin d'acc�s au fichier � lire.   ****
**** Entra�ne: Peut lever une CMatriceException si :                  ****
****    - le fichier n'a pas �t� trouv�                               ****
****    - une ligne est jug�e incorrecte                              ****
****    - le nombre de lignes ou le nombre de colonnes est jug�       ****
****    incorrecte                                                    ****
****    Peut lever une CParseurException si :                         ****
****    - il manque un signe d'�galit� dans la d�claration d'une      ****
****    variable                                                      ****
**** Sortie: CMatrice<double>* => Matrice lue � partir du fichier     ****
*************************************************************************/
#define MAX_TAILLE_LIGNE 50
#define MAX_TAILLE_NOM_VARIABLE 20
#define MAX_TAILLE_VALEUR_VARIABLE 10
#define ERROR_FILE_PATH 5
#define FILE_LINE_ERROR 6
#define ERROR_NB_LIGNES_COLONNES 7
CMatrice<double>* CMatriceFichier::MAFLireFichier(const char* pcChemin) {
	CParseur* pPARParseur = new CParseur(); // Instance du cParseur utilis�e pour lire le fichier
	CMatrice<double>* pdMATMatriceFichier; // Matrice � retourner g�n�r� par le fichier
	char* pcLigne = new char[MAX_TAILLE_LIGNE]; // Ligne lue dans le fichier
	char* pcNomVariable = new char[MAX_TAILLE_NOM_VARIABLE]; //Nom d'une variable du fichier
	char* pcValeurVariable = new char[MAX_TAILLE_VALEUR_VARIABLE]; //Valeur d'une variable du fichier
	unsigned int uiNbLignes; //Nombre de lignes de la matrice
	unsigned int uiNbColonnes; // Nombre de colonnes de la matrice
	unsigned int uiNbLignesBoucle; // It�rateur sur la liste des lignes de la matrice
	unsigned int uiNbColonnesBoucle; // It�rateur sur la liste des colonnes de la matrice
	double* pdListeDoubleLigne; // Liste de double dans une ligne de la matrice

	char *pcErreurMessage = new char[ERROR_MAX_SIZE]; // Message d'erreur pour les exception

	std::ifstream fichier(pcChemin, std::ios::in); // Ouverture du fichier
	std::cout << "Fichier : " << pcChemin << std::endl;

	//Si le fichier a �t� trouv� on commence � le lire
	if (fichier) {
		fichier.getline(pcLigne, MAX_TAILLE_LIGNE); //R�cup�ration de la ligne correspondant au type de la matrice
		pPARParseur->PARLireVariable(pcLigne, pcNomVariable, pcValeurVariable); //Lecture de la variable correspondant au type de la matrice

		//Si le nom de la variable ou sa valeur est incorrect on g�n�re une exception
		if (pPARParseur->PARComparerChaine(pcNomVariable, "TypeMatrice") == false || pPARParseur->PARComparerChaine(pcValeurVariable, "double") == false) {
			sprintf_s(pcErreurMessage, ERROR_MAX_SIZE, "ERREUR %d \nLa ligne %s est invalide\0", FILE_LINE_ERROR, pcLigne);
			throw CMatriceException(FILE_LINE_ERROR, pcErreurMessage);
		}

		//Lecture du nombre de ligne dans la matrice

		fichier.getline(pcLigne, MAX_TAILLE_LIGNE); //R�cup�ration de la ligne correspondant au nombre de lignes de la matrice
		pPARParseur->PARLireVariable(pcLigne, pcNomVariable, pcValeurVariable); //Lecture de la variable correspondant au nombre de lignes

		//Si le nom de la variable est correct on lit sa valeur
		if (pPARParseur->PARComparerChaine(pcNomVariable, "NBLignes")) {
			uiNbLignes = atoi(pcValeurVariable); //On convertit la valeur de char* vers int
			//Si le nombre de sommets est inf�rieur � 1 on g�n�re une exception
			if (uiNbLignes < 1) {
				sprintf_s(pcErreurMessage, ERROR_MAX_SIZE, "ERREUR %d \nLe nombre de lignes %d est invalide\0", ERROR_NB_LIGNES_COLONNES, uiNbLignes);
				throw CMatriceException(ERROR_NB_LIGNES_COLONNES, pcErreurMessage);
			}
		}

		//Lecture du nombre de ligne dans la matrice

		fichier.getline(pcLigne, MAX_TAILLE_LIGNE); //R�cup�ration de la ligne correspondant au nombre de colonnes de la matrice
		pPARParseur->PARLireVariable(pcLigne, pcNomVariable, pcValeurVariable); //Lecture de la variable correspondant au nombre de colonnes

		//Si le nom de la variable est correct on lit sa valeur
		if (pPARParseur->PARComparerChaine(pcNomVariable, "NBColonnes")) {
			uiNbColonnes = atoi(pcValeurVariable); //On convertit la valeur de char* vers int
			//Si le nombre de sommets est inf�rieur � 1 on g�n�re une exception
			if (uiNbColonnes < 1) {
				sprintf_s(pcErreurMessage, ERROR_MAX_SIZE, "ERREUR %d \nLe nombre de colonnes %d est invalide\0", ERROR_NB_LIGNES_COLONNES, uiNbColonnes);
				throw CMatriceException(ERROR_NB_LIGNES_COLONNES, pcErreurMessage);
			}
		}

		pdMATMatriceFichier = new CMatrice<double>(uiNbLignes, uiNbColonnes);
		fichier.getline(pcLigne, MAX_TAILLE_LIGNE); //Lecture de la ligne "Matrice=["
		//On v�rifie que la ligne est correcte sinon on g�n�re une exception
		if (pPARParseur->PARComparerChaine(pcLigne, "Matrice=[") == false) {
			sprintf_s(pcErreurMessage, ERROR_MAX_SIZE, "ERREUR %d \nLa ligne %s est invalide\0", FILE_LINE_ERROR, pcLigne);
			throw CMatriceException(FILE_LINE_ERROR, pcErreurMessage);
		}

		pdListeDoubleLigne = new double[uiNbColonnes];

		//Lecture des lignes de la matrice
		for (uiNbLignesBoucle = 0; uiNbLignesBoucle < uiNbLignes; uiNbLignesBoucle++) {
			fichier.getline(pcLigne, MAX_TAILLE_LIGNE); //Lecture d'une ligne de la matrice
			pPARParseur->PARLireListeDouble(pcLigne, pdListeDoubleLigne, uiNbColonnes); //Affectation de pdListeDoubleLigne � partir de la ligne lue

			for (uiNbColonnesBoucle = 0; uiNbColonnesBoucle < uiNbColonnes; uiNbColonnesBoucle++) {
				// On affecte les valeurs de la matrice par celles lues dans le fichier
				pdMATMatriceFichier->MATModifierElement(uiNbLignesBoucle, uiNbColonnesBoucle, pdListeDoubleLigne[uiNbColonnesBoucle]);
			}
		}

		//Lecture de la derniere ligne du fichier
		fichier.getline(pcLigne, MAX_TAILLE_LIGNE); //Lecture d'une ligne de la matrice

		pPARParseur->PARComparerChaine(pcLigne, "]");
		fichier.close(); //Fermeture du fichier
	}
	else {
		// Si le fichier n'a pas �t� trouv� on g�n�re une exception
		sprintf_s(pcErreurMessage, ERROR_MAX_SIZE, "ERREUR %d \nLe fichier %s n'a pas ete trouve\0", ERROR_FILE_PATH, pcChemin);
		throw CMatriceException(ERROR_FILE_PATH, pcErreurMessage);
	}


	return pdMATMatriceFichier; //On retourne la matrice g�n�r�e
}