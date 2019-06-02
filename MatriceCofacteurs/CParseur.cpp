#include "CParseur.h"
#include <iostream>




/*************************************************************************
**** Nom: PARComparerChaine                                           ****
**************************************************************************
**** Permet de comparer deux chaines de caractere                     ****
**************************************************************************
**** Pr�condition:                                                    ****
**** Entr�e:                                                          ****
****    pcChaine1 : const char* => Premiere chaine a comparer         ****
****    pcChaine2 : const char* => Seconde chaine a comparer          ****
**** Entra�ne:                                                        ****
**** Sortie: bool => Vrai si les deux chaines sont equivalentes, faux ****
****    sinon                                                         ****
*************************************************************************/
bool CParseur::PARComparerChaine(const char* pcChaine1, const char* pcChaine2) {
	unsigned int uiBoucleCaractere; // It�rateur sur les chaines de caract�re

	//Parcours des chaines de caract�res
	for (uiBoucleCaractere = 0; pcChaine1[uiBoucleCaractere] != '\0' || pcChaine2[uiBoucleCaractere] != '\0'; uiBoucleCaractere++) {
		if (pcChaine1[uiBoucleCaractere] != pcChaine2[uiBoucleCaractere]) // Si on observe une diff�rence on retourne faux
			return false;
	}
	//Si les 2 chaines ne se terminent pas en m�me temps on retourne faux, sinon on retourne vrai
	if (pcChaine1[uiBoucleCaractere] != '\0' && pcChaine2[uiBoucleCaractere] != '\0')
		return false;
	return true;
}


/************************************************************************
**** Nom: PARLireVariable                                            ****
*************************************************************************
**** Permet de lire une variable a partir d'une chaine de caracteres ****
****    au format "NomVariable=ValeurVariable"                       ****
*************************************************************************
**** Pr�condition:                                                   ****
**** Entr�e:                                                         ****
****    pcChaineParam : const char * => Chaine a lire                ****
****    pcNomVariable : char * => Chaine affect�e par la m�thode     ****
****    correspondant au nom de la variable lue                      ****
****    pcValeurVariable : char * => Chaine affect�e par la m�thode  ****
****    correspondat � la valeur de la variable lue                  ****
**** Entra�ne: Peut lever une CParseurException si il n'y a pas de   ****
****    signe = dans pc ChaineParam                                  ****
**** Sortie:                                                         ****
************************************************************************/
#define ERROR_MISSING_EQUAL 8
void CParseur::PARLireVariable(const char* pcChaineParam, char* pcNomVariable, char* pcValeurVariable) {
	unsigned int uiBoucleCaractere; // It�rateur de la chaine de caractere
	unsigned int uiPositionValeurVariable; // Position de la premiere lettre de la valeur de la variable dans la chaine
	unsigned int uiCptCaractereNomVariable = 0;

	// Parcours de la chaine jusqu'au signe '='
	for (uiBoucleCaractere = 0; pcChaineParam[uiBoucleCaractere] != '='; uiBoucleCaractere++) {
		if (pcChaineParam[uiBoucleCaractere] != ' ') {
			pcNomVariable[uiCptCaractereNomVariable] = pcChaineParam[uiBoucleCaractere]; // Affectation du buffer de nom de variable
			uiCptCaractereNomVariable++;
		}
		if (pcChaineParam[uiBoucleCaractere] == '\0')
			throw CParseurException(ERROR_MISSING_EQUAL, "Pas de signe �gal dans la chaine entr�e");
	}
	pcNomVariable[uiCptCaractereNomVariable] = '\0'; // Signe de fin de chaine a la fin du nom de la variable
	uiBoucleCaractere++; //Incrementation de l'iterateur pour ignorer le signe '='

	//On ignore les espaces apres le signe '='
	while (pcChaineParam[uiBoucleCaractere] == ' ') {
		uiBoucleCaractere++;
	}

	uiPositionValeurVariable = uiBoucleCaractere; // Affectation la position de la premiere lettre de la valeur de variable

	// Parcours de la chaine jusqu'� la fin ou jusqu'au prochain espace 
	for (; pcChaineParam[uiBoucleCaractere] != '\0' && pcChaineParam[uiBoucleCaractere] != ' '; uiBoucleCaractere++) {
		pcValeurVariable[uiBoucleCaractere - uiPositionValeurVariable] = pcChaineParam[uiBoucleCaractere];
	}
	pcValeurVariable[uiBoucleCaractere - uiPositionValeurVariable] = '\0'; // Signe de fin de chaine a la fin de la valeur de variable
}


/*************************************************************************
**** Nom: PARLireListeDouble                                          ****
**************************************************************************
**** Permet de lire une liste de double et de la stocker dans un      ****
****    tableau                                                       ****
**************************************************************************
**** Pr�condition:                                                    ****
**** Entr�e:                                                          ****
****    pcChaineParam : char* => Chaine d'entr�                       ****
****    pdTableauDouble : double* => Tableau dans lequel sont stock�s ****
****    les nombres lus                                               ****
****    uiNbDoubles : unsigned int => Nombre de nombres � lire dans   ****
****    la cha�ne                                                     ****
**** Entra�ne: Peut lever une CParseurException si il n'y a pas assez ****
****    de nombres dans la ligne                                      ****
**** Sortie:                                                          ****
*************************************************************************/
#define TAILLE_MAX_NOMBRE 15
#define ZERO_ASCII 48
#define NEUF_ASCII 57
#define MOINS_ASCII 45
#define POINT_ASCII 46
#define ERROR_NOT_ENOUGH_ELEMENT 9
void CParseur::PARLireListeDouble(const char* pcChaineParam, double* pdTableauDouble, unsigned int uiNbDoubles) {
	char *pcNombreLu = new char[TAILLE_MAX_NOMBRE];
	unsigned int uiIndexDebutNombre = 0; //Index dans la chaine a partir duquel on peut debuter un nombre
	unsigned int uiCompteurDouble = 0;
	unsigned int uiCaractereBoucle = 0;

	//Parcours de la chaine de caractere pcLigne jusqu'a la fin ou jusqu'a avoir atteint le nombre de nombre attendu
	for (unsigned int uiCaractereBoucle = 0; pcChaineParam[uiCaractereBoucle] != '\0' && uiCompteurDouble < uiNbDoubles; uiCaractereBoucle++)
	{
		uiIndexDebutNombre = uiCaractereBoucle;
		//Tant qu'on ne trouve pas un caractere qui peut se trouver dans un nombre on continue de parcourir la chaine
		while ((pcChaineParam[uiCaractereBoucle] >= ZERO_ASCII && pcChaineParam[uiCaractereBoucle] <= NEUF_ASCII) || pcChaineParam[uiCaractereBoucle] == MOINS_ASCII || pcChaineParam[uiCaractereBoucle] == POINT_ASCII)
		{
			//Lorsque l'on trouve un nombre on le parcourt
			pcNombreLu[uiCaractereBoucle - uiIndexDebutNombre] = pcChaineParam[uiCaractereBoucle]; //On affecte pcNombreLu par les caracteres correspondant au nombre trouv�
			uiCaractereBoucle++;
		}
		if (uiIndexDebutNombre < uiCaractereBoucle) // A la fin de la lecture du nombre
		{
			pcNombreLu[uiCaractereBoucle - uiIndexDebutNombre ] = '\0'; //Affectation du caractere de fin de chaine
			pdTableauDouble[uiCompteurDouble] = atof(pcNombreLu); //On remplit le tableau par le nombre lu
			uiCompteurDouble++;
		}
	}
	delete pcNombreLu;

	//Si on n'a pas trouve suffisament de nombres dans la chaine
	if (uiCompteurDouble < uiNbDoubles)
	{
		throw CParseurException(ERROR_NOT_ENOUGH_ELEMENT, "Pas assez d'�l�ments dans la matrice"); //On g�n�re une exception
	}
}