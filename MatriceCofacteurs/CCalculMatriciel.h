#pragma once
#ifndef CCalculMatriciel_H
#define CCalculMatriciel_H

#include "CMatrice.h"
#include <cmath>

template <class MType>
class CCalculMatriciel {
	public :
		/************************************************
		**** Nom: CALTranspose                       ****
		*************************************************
		**** Calcul et retourne la transpos� le la   ****
		****    matrice pass� en param�tre           ****
		*************************************************
		**** Pr�condition:                           ****
		**** Entr�e: pMATParam : CMatrice, matrice � ****
		****    transposer                           ****
		**** Entra�ne:                               ****
		**** Sortie: CMatrice, matrice contenant la  ****
		****    transpos�                            ****
		************************************************/
		CMatrice<MType> CALTranspose(CMatrice<MType> MATParam);

		/**************************************************************************************************
		**** Nom: CALDeterminantMatrice(CMatrice<MType> MATParam)                                      ****
		***************************************************************************************************
		**** Permet de calculer le d�terminant d'une matrice carr�e pass�e en param�tre                ****
		***************************************************************************************************
		**** Pr�condition: Si MType est une classe d'Objet alors elle doit surcharger l'op�rateur "*"  ****
		****    La matrice doit �tre carr�e                                                            ****
		**** Entr�e: CMatrice<MType> : MATParam => Matrice sujet au calcul du d�terminant              ****
		**** Entra�ne: L�ve une CMatriceException si la matrice pass� en param�tre n'est pas carr�e    ****
		**** Sortie: double : d�terminant de la matrice pass� en param�tre                             ****
		**************************************************************************************************/
		double CALCalculerDeterminant(CMatrice<MType> MATParam);
	
		CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam);

	private :
		int* CALTrouverMeilleurCibleDeterminant(CMatrice<MType> MATParam, MType valeurRecherchee);

		double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible);

		CMatrice<MType> CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int uiLigne, unsigned int uiColonne);

		int* CALComparerCible(unsigned int* piNbLigne, unsigned int* piNbColonne, unsigned int uiTaille);
};


#include "CCalculMatriciel.cpp"
#endif // CCalculMatriciel_H
