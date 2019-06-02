#pragma once

#ifndef CPARSEUR_H
#define CPARSEUR_H

#include "CParseurException.h"

class CParseur
{

public:

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
	bool PARComparerChaine(const char* pcChaine1, const char* pcChaine2);

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
	void PARLireVariable(const char* pcChaineParam, char* pcNomVariable, char* pcValeurVariable);


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
	void PARLireListeDouble(const char* pcChaineParam, double* pdTableauDouble, unsigned int uiNbDoubles);
};

#endif // !CPARSEUR_H
