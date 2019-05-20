#ifndef CFileMatrice_H
#define CFileMatrice_H

#include "CMatrice.h"
#include "CMatriceException.h"

class CFileMatrice
{
private:

	/*************************************************************************
	**** Nom: FILComparerLigne                                            ****
	**************************************************************************
	**** Permet de comparer 2 chaînes de caractères et détermine si elles ****
	****    sont identiques ou non en sautant les espaces de pcLigne      ****
	**************************************************************************
	**** Précondition:                                                    ****
	**** Entrée:                                                          ****
	****     - pcLigne : char* => Chaine de caractère que l'on souhaite   ****
	****     comparer dans laquelle les espaces seront ignorés            ****
	****     - uiTaille : unsigned int => Nombre de caractère a comparer  ****
	****     à partir du début de la chaîne                               ****
	****     - pcLigneAComparer : const char* => Chaine de caractère      ****
	****    référence qui sert de comparaison pour uiLigne                ****
	**** Entraîne: uiTaille est incrémenté du nombre d'espace retrouvés   ****
	****    dans la chaîne                                                ****
	**** Sortie: bool => Retourne vrai si les chaînes sont similaires,    ****
	****    faux sinon                                                    ****
	*************************************************************************/
	static bool FILComparerLigne(char* pcLigne, unsigned int &uiTaille, const char* pcLigneAComparer);


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
	static char* FILLireFinLigne(char* pcLigne, unsigned int uiPosistionDepart);


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
	static char* FILLireLigne(char *pcLigne, unsigned int uiTaille, const char *pcDebut);



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
	static void FILLireLigneMatrice(char* pcLigne, unsigned int uiNumLigne, unsigned int uiNbColonnes, CMatrice<double> &pMATParam);

public:

	//Destructeur virtuel pure permettant de rendre la classe abstraite et non instanciable
	virtual ~CFileMatrice() = 0;

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
	static void FILLireFichier(const char* pcChemin, CMatrice<double>& MATParam);

};


#endif