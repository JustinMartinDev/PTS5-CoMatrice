#include "CFileMatrice.h"
#include <fstream>

/*************************************************************************
**** Nom: FILComparerLigne                                            ****
**************************************************************************
**** Permet de comparer 2 chaînes de caractères et détermine si elles ****
****    sont identiques ou non en sautant les espaces de pcLigne      ****
**************************************************************************
**** Précondition:                                                    ****
**** Entrée:                                                          ****
****     - pcLigne : Chaine de caractère que l'on souhaite comparer   ****
****    dans laquelle les espaces seront ignorés                      ****
****     - uiTaille : Nombre de caractère a comparer à partir du      ****
****    début de la chaîne                                            ****
****     - pcLigneAComparer : Chaine de caractère référence qui sert  ****
****    de comparaison pour uiLigne                                   ****
**** Entraîne: uiTaille est incrémenté du nombre d'espace retrouvés   ****
****    dans la chaîne                                                ****
**** Sortie: bool => Retourne vrai si les chaînes sont similaires,    ****
****    faux sinon                                                    ****
*************************************************************************/
#ifndef FILE_LINE_ERROR
#define FILE_LINE_ERROR 2
#endif
bool CFileMatrice::FILComparerLigne(char *pcLigne, unsigned int &uiTaille, const char *pcLigneAComparer)
{
	int nbEspace = 0;

	//Parcours des chaines de caractère
	for (int caractereBoucle = 0; caractereBoucle < uiTaille;)
	{
		//Si on trouve une différence autre qu'un caractere espace
		if (pcLigne[caractereBoucle + nbEspace] != ' ' && pcLigne[caractereBoucle + nbEspace] != pcLigneAComparer[caractereBoucle])
		{
			throw CMatriceException(FILE_LINE_ERROR, "Ligne du fichier erronée"); //Renvoi d'une exception
			return false;
		}
		//Si on trouve un caractere espace dans pcLigne
		if (pcLigne[caractereBoucle + nbEspace] == ' ')
		{
			nbEspace++; //On incrémente nbEspace pour pouvoir sauter ce caractère
		}
		//Si on ne trouve pas d'espace dans pcLigne
		else
		{
			caractereBoucle++;//On incrémente caractereBoucle pour passer au prochain caractere
		}
	}
	uiTaille += nbEspace; //On incrémente uiTaille du nombre d'espaces retrouvés dans la chaine
	return true;
}


/*************************************************************************
	**** Nom: FILLireFinLigne                                             ****
	**************************************************************************
	**** Retourne la fin de la ligne à partir d'un position de départ     ****
	**************************************************************************
	**** Précondition:                                                    ****
	**** Entrée:                                                          ****
	****     - pcLigne : char* => Chaine de caractère dont on souhaite    ****
	****    avoir la fin de la ligne                                      ****
	****     - uiPositionDepart : unsigned int => Position dans la chaine ****
	****    a partir de laquelle on souhaite recuperer le contenu         ****
	**** Entraîne:                                                        ****
	**** Sortie: char* => Chaine de caractère corresponsdant à la fin de  ****
	****    la ligne                                                      ****
	*************************************************************************/
char *CFileMatrice::FILLireFinLigne(char *pcLigne, unsigned int uiPositionDepart)
{
	//Compte le nombre de caractère avant la fin de la chaine
	unsigned int uiCompteurCaractere = 0;
	while (pcLigne[uiPositionDepart + uiCompteurCaractere] != '\0')
	{
		uiCompteurCaractere++;
	}
	char* pcFinLigne = new char[uiCompteurCaractere + 1]; //Allocation de la variable de retour finLigne

	//Parcours de la chaine à partir de la position de depart pour remplir finLigne
	for (unsigned int uiCaractereBoucle = 0; uiCaractereBoucle < uiCompteurCaractere; uiCaractereBoucle++)
	{
		pcFinLigne[uiCaractereBoucle] = pcLigne[uiPositionDepart + uiCaractereBoucle];
	}
	pcFinLigne[uiCompteurCaractere] = '\0'; //Caractere de fin de chaine

	return pcFinLigne;
}


/*************************************************************************
**** Nom: FILLireLigne                                                ****
**************************************************************************
**** Compare le debut de la chaine jusqu'a pcDebut et retourne la fin ****
****    de la chaine a partir de uiTaille                             ****
**************************************************************************
**** Précondition:                                                    ****
**** Entrée:                                                          ****
****     - pcLigne : char* => Chaine a traiter                        ****
****     - uiTaille : unsigned int => Taille jusqu'a laquelle         ****
****    comparer la chaine avec pcDebut et a partir de laquelle       ****
****    renvoyer la fin de la ligne                                   ****
****     - pcDebut : const char* => Chaine de caractere de référence  ****
****    a comparer avec pcLigne                                       ****
**** Entraîne:                                                        ****
**** Sortie: char* => Chaine de caractère corresponsdant à la fin de  ****
****    pcLigne                                                       ****
*************************************************************************/
char *CFileMatrice::FILLireLigne(char *pcLigne, unsigned int uiTaille, const char *pcDebut) {
	if (CFileMatrice::FILComparerLigne(pcLigne, uiTaille, pcDebut)) //Comparaison de la chaine avec pcDebut
	{
		return CFileMatrice::FILLireFinLigne(pcLigne, uiTaille); //Lecture de la fin de la chaine
	}
	return NULL;
}


/************************************************************************
	**** Nom: FILLireLigneMatrice                                        ****
	*************************************************************************
	**** Permet de lire la ligne d'une matrice et de d'affecter ces      ****
	****    valeurs a pMATParam                                          ****
	*************************************************************************
	**** Précondition: Dimensions pMATParam correspondant aux attributs  ****
	****    passés en parametre                                          ****
	**** Entrée:                                                         ****
	****     - pcLigne : char* => Chaine de caractere dans laquelle se   ****
	****    trouve les valeurs de la matrice                             ****
	****     - uiNumLigne : unsigned int => Numero de la ligne à traiter ****
	****    de la matrice                                                ****
	****     - uiNbColonnes : unsigned int => Nombre de colonnes dans la ****
	****    matrice                                                      ****
	****     - pMATParam : CMatrice<double> => Référence vers la matrice ****
	****    à remplir                                                    ****
	**** Entraîne: Affectation des valeurs de la ligne lue de pMATParam  ****
	**** Sortie:                                                         ****
	************************************************************************/
#ifndef ERROR_NOT_ENOUGH_ELEMENT
#define TAILLE_MAX_NOMBRE 20
#define ZERO_ASCII 48
#define NEUF_ASCII 57
#define MOINS_ASCII 45
#define POINT_ASCII 46
#define ERROR_NOT_ENOUGH_ELEMENT 3
#endif // DEBUG
void CFileMatrice::FILLireLigneMatrice(char *pcLigne, unsigned int uiNumLigne, unsigned int uiNbColonnes, CMatrice<double> &pMATParam)
{

	char *pcNombreLu = new char[TAILLE_MAX_NOMBRE];
	unsigned int uiIndexDebutNombre = 0; //Index dans la chaine a partir duquel on peut debuter un nombre
	unsigned int uiCompteurElement = 0;

	//Parcours de la chaine de caractere pcLigne jusqu'a la fin ou jusqu'a avoir atteint le nombre de nombre attendu
	for (unsigned int uiCaractereBoucle = 0; pcLigne[uiCaractereBoucle] != '\0' && uiCompteurElement < uiNbColonnes; uiCaractereBoucle++)
	{
		uiIndexDebutNombre = uiCaractereBoucle;
		//Tant qu'on ne trouve pas un caractere qui peut se trouver dans un nombre on continue de parcourir la chaine
		while ((pcLigne[uiCaractereBoucle] >= ZERO_ASCII && pcLigne[uiCaractereBoucle] <= NEUF_ASCII) || pcLigne[uiCaractereBoucle] == MOINS_ASCII || pcLigne[uiCaractereBoucle] == POINT_ASCII)
		{
			//Lorsque l'on trouve un nombre on le parcours
			pcNombreLu[uiCaractereBoucle - uiIndexDebutNombre] = pcLigne[uiCaractereBoucle]; //On affecte pcNombreLu par les caracteres correspondant au nombre trouvé
			uiCaractereBoucle++;
		}
		if (uiIndexDebutNombre < uiCaractereBoucle) // A la fin de la lecture du nombre
		{
			pcNombreLu[uiCaractereBoucle - uiIndexDebutNombre + 1] = '\0'; //Affectation du caractere de fin de chaine

			pMATParam.MATModifierElement(uiNumLigne, uiCompteurElement, atof(pcNombreLu)); //Affectation de la valeur lu a un element de pMATParam
			uiCompteurElement++;
		}
	}
	delete pcNombreLu;

	//Si on a pas trouve suffisament de nombres dans la chaine
	if (uiCompteurElement < uiNbColonnes)
	{
		throw CMatriceException(ERROR_NOT_ENOUGH_ELEMENT, "Pas assez d'éléments dans la matrice");
	}
}




/************************************************************************
	**** Nom: FILLireFichier                                             ****
	*************************************************************************
	****                                                                 ****
	*************************************************************************
	**** Précondition:                                                   ****
	**** Entrée: pcChemin : char* => Chemin d'accès du fichier à lire    ****
	**** Entraîne:                                                       ****
	**** Sortie: CMatrice<double> => Matrice générée à partir du fichier ****
	************************************************************************/
#ifndef TAILLE_DERNIERE_LIGNE
#define ERROR_TYPE_MATRICE 1
#define ERROR_NB_ROW_COLUMN 4
#define ERROR_FILE_PATH 5
#define MAX_TAILLE_LIGNE 100
#define TAILLE_LIGNE_1 18
#define TAILLE_LIGNE_2 9
#define TAILLE_LIGNE_3 11
#define TAILLE_LIGNE_4 9
#define TAILLE_DERNIERE_LIGNE 1
#endif
void CFileMatrice::FILLireFichier(const char *pcChemin, CMatrice<double>& MATParam) {
	std::ifstream fichier(pcChemin, std::ios::in); //Ouverture du fichier

	//Si l'ouverture du fichier a réussi
	if (fichier)
	{
		//Lecture de la premiere ligne du fichier
		char *pcLigne = new char[MAX_TAILLE_LIGNE];
		fichier.getline(pcLigne, MAX_TAILLE_LIGNE);


		unsigned int uiTailleComparaison = TAILLE_LIGNE_1;
		//On compare la premiere ligne du fichier avec la chaine "TypeMatrice=double"
		if (CFileMatrice::FILComparerLigne(pcLigne, uiTailleComparaison, "TypeMatrice=double")) //Si les deux chaines sont similaires
		{
			//Lecture de la deuxieme ligne du fichier (nombre de ligne dans la matrice)
			fichier.getline(pcLigne, MAX_TAILLE_LIGNE);
			uiTailleComparaison = TAILLE_LIGNE_2;
			int iNbLignes = atoi(CFileMatrice::FILLireLigne(pcLigne, uiTailleComparaison, "NBLignes="));
			//Si le nombre de lignes est inferieur a 1, on renvoi une exception
			if (iNbLignes < 1)
			{
				throw CMatriceException(ERROR_NB_ROW_COLUMN, "Nombre de lignes invalide");
			}

			//Lecture de la troisieme ligne (nombre de colonnes de la matrice)
			fichier.getline(pcLigne, MAX_TAILLE_LIGNE);
			uiTailleComparaison = TAILLE_LIGNE_3;
			int iNbColonnes = atoi(CFileMatrice::FILLireLigne(pcLigne, uiTailleComparaison, "NBColonnes="));

			//Si le nombre de colonnes est inférieur a 1, on renvoi une exception
			if (iNbColonnes < 1)
			{
				throw CMatriceException(ERROR_NB_ROW_COLUMN, "Nombre de colonnes invalide");
			}

			fichier.getline(pcLigne, MAX_TAILLE_LIGNE);
			uiTailleComparaison = TAILLE_LIGNE_4;

			//On verifie que la quatrieme ligne du fichier est bien similaire a la chaine "Matrice=["
			if (CFileMatrice::FILComparerLigne(pcLigne, uiTailleComparaison, "Matrice=["))
			{
				//On instancie un objet CMatrice avec le nombre de lignes, et colonnes lus precedemment
				MATParam.MATAllouer(iNbLignes, iNbColonnes);

				//On parcours les lignes suivantes correspondants aux valeurs des element de la matrice
				for (unsigned int uiLigneBoucle = 0; uiLigneBoucle < iNbLignes; uiLigneBoucle++)
				{
					fichier.getline(pcLigne, MAX_TAILLE_LIGNE); //Lecture d'une ligne du fichier

					//Affectation des valeurs des elements lus à la matrice
					CFileMatrice::FILLireLigneMatrice(pcLigne, uiLigneBoucle, iNbColonnes, MATParam);
				}

				//Lecture de la derniere ligne du fichier
				fichier.getline(pcLigne, MAX_TAILLE_LIGNE);
				uiTailleComparaison = TAILLE_DERNIERE_LIGNE;
				//On verifie bien que la derniere ligne est similaire a la chaine "]"
				if (CFileMatrice::FILComparerLigne(pcLigne, uiTailleComparaison, "]"))
				{
					delete pcLigne;
					fichier.close(); //Fermeture du fichier
				}
			}
		}
		else
		{
			//Si la premiere ligne du fichier n'est pas similaire a la chaine "TypeMatrice=double" 
			delete pcLigne;
			throw CMatriceException(ERROR_TYPE_MATRICE, "Type de la matrice erronée"); //On renvoi une exception
		}
		delete pcLigne;
		fichier.close();
	}
	//Si on arrive pas a ouvrir le fichier
	else
	{
		throw CMatriceException(ERROR_FILE_PATH, "Chemin du fichier pour la lecture de matrice invalide"); //On renvoi une exception
	}
}
