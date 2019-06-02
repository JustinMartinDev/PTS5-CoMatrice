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
		****   pour retourner un nombre et "==". Et la matrice doit �tre carr�e                         ****
		**** Entr�e: CMatrice<MType> : MATParam => Matrice sujet au calcul du d�terminant              ****
		****         MType : mValeurRechercheCalculDeterminant => Valeur de recherche permettant       ****
		****                 l'�x�cution de la version am�lior�e de la m�thode de Laplace (cf rapport) ****
		**** Entra�ne: L�ve une CMatriceException si la matrice pass�e en param�tre n'est pas carr�e   ****
		**** Sortie: double : d�terminant de la matrice pass�e en param�tre                            ****
		**************************************************************************************************/
		double CALCalculerDeterminant(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant);
	

		double CALCalculerDeterminant(CMatrice<MType> MATParam);

		/************************************************************************************************
		**** Nom: CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam)                    ****
		*************************************************************************************************
		**** Renvoie la Comatrice correspondante � la matrice pass�e en param�tre                    ****
		*************************************************************************************************
		**** Pr�condition: Si MType est une classe d'Object alors elle doit surcharger l'op�rateur   ****
		****    "*" pour retourner un nombre et "=". La matrice doit �tre carr�e                     ****
		**** Entr�e: MATParam : CMatrice<MType>  => Matrice � traiter pour renvoyer sa commatrice    ****
		****         MType : mValeurRechercheCalculDeterminant => Valeur de recherche permettant     ****
		****              l'�x�cution de la version am�lior�e de la m�thode de Laplace (cf rapport)  ****
		**** Entra�ne: L�ve une CMatriceException si la matrice pass�e en param�tre n'est pas carr�e ****
		**** Sortie: CMatrice<double> => Commatrice correspondant � la matrice pass� en param�tre    ****
		************************************************************************************************/
		CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant);
	
		/************************************************************************************************
		**** Nom: CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam)                    ****
		*************************************************************************************************
		**** Renvoie la Comatrice correspondante � la matrice pass�e en param�tre                    ****
		*************************************************************************************************
		**** Pr�condition: Si MType est une classe d'Object alors elle doit surcharger l'op�rateur   ****
		****    "*". La matrice doit �tre carr�e                                                     ****
		**** Entr�e: MATParam : CMatrice<MType>  => Matrice � traiter pour renvoyer sa commatrice    ****
		**** Entra�ne: L�ve une CMatriceException si la matrice pass�e en param�tre n'est pas carr�e ****
		**** Sortie: CMatrice<double> => Comatrice correspondante � la matrice pass� en param�tre    ****
		************************************************************************************************/
		CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam);
	private :

		/*************************************************************************************************
		**** Nom: int* CALTrouverMeilleurCibleDeterminant(CMatrice<MType> MATParam, MType             ****
		****    mValeurRechercheCalculDeterminant)                                                    ****
		**************************************************************************************************
		**** Recherche dans la matrice pass� en param�tre la ligne, ou colonne qui contient le plus   ****
		****    d'occurence de la 2nd valeur pass� en param�tre                                       ****
		**************************************************************************************************
		**** Pr�condition: Si MType est une classe d'Objet alors elle doit surcharger l'op�rateur "=" ****
		**** Entr�e: CMatrice<MType> : MATParam => Matrice � tratier                                  ****
		****    MType : mValeurRechercheCalculDeterminant => Valeur a rechercher                      ****
		**** Entra�ne:                                                                                ****
		**** Sortie: int* => tableau contenant l'index de la meilleure ligne ou colonne.              ****
		****    {indexLigne, indexColonne} si c'est une colonne qui a le plus d'occurence alors       ****
		****    indexLigne sera �gale � -1 et vice versa                                              ****
		****                                                                                          ****
		*************************************************************************************************/
		int* CALTrouverMeilleurCibleDeterminant(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant);
		
		/**************************************************************************************************
		**** Nom: double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int         ****
		****    iColonneCible, MType mValeurRechercheCalculDeterminant)                                ****
		***************************************************************************************************
		**** Fonction r�cursive permettant de calculer le determinant d'une matrice en utilisation la  ****
		****    version optimis�                                                                       ****
		***************************************************************************************************
		**** Pr�condition: Si MType est une classe d'Objet alors elle doit surcharger l'op�rateur "*"  ****
		****    pour retrouner une nombre et "=="                                                      ****
		**** Entr�e: CMatrice<MType> : MATParam => Matrice � traiter                                   ****
		****    int : iLigneCible => index de la ligne cible                                           ****
		****    int iColonneCible => index de la colonne cible                                         ****
		****    MType : mValeurRechercheCalculDeterminant => Valeur a rechercher                       ****
		****                                                                                           ****
		**** Entra�ne: Peut lever une CMatriceException si aucune ligne ou colonne n'est indiqu�e      ****
		****    comme cible ou alors que l'index est sup�rieur � la taille de la matrice               ****
		**** Sortie: double => determinant de la matrice pass� en param�tre                            ****
		**************************************************************************************************/
		double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible, MType mValeurRechercheCalculDeterminant);

		/*************************************************************************************************
		**** Nom: double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int        ****
		****    iColonneCible);                                                                       ****
		**************************************************************************************************
		**** Fonction r�cursive permettant de calculer le determinant d'une matrice                   ****
		**************************************************************************************************
		**** Pr�condition: Si MType est une classe d'Objet alors elle doit surcharger l'op�rateur "*" ****
		****    pour retrouner une nombre et "=="                                                     ****
		**** Entr�e: CMatrice<MType> : MATParam => Matrice � traiter                                  ****
		****    int : iLigneCible => index de la ligne cible                                          ****
		****    int iColonneCible => index de la colonne cible                                        ****
		**** Entra�ne: Peut lever une CMatriceException si aucune ligne ou colonne n'est indiqu�e     ****
		****    comme cible ou alors que l'index est sup�rieur � la taille de la matrice              ****
		**** Sortie: double => determinant de la matrice pass� en param�tre                           ****
		*************************************************************************************************/
		double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible);

		/**************************************************************************************************
		**** Nom: CMatrice<MType> CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int        ****
		****    uiLigne, unsigned int uiColonne);                                                      ****
		***************************************************************************************************
		**** Permet d'extraire la sous matrice d'une matrice pass� en param�tre en excluent les lignes ****
		****    et colonnes pass�es en param�tres                                                      ****
		***************************************************************************************************
		**** Pr�condition:                                                                             ****
		**** Entr�e: CMatrice<MType> : MATParam => Matrice � traiter                                   ****
		****    int : iLigneCible => index de la ligne a supprimer                                     ****
		****    int iColonneCible => index de la colonne a supprimer                                   ****
		**** Entra�ne: Peut lever une CMatriceException si la matrice n'est pas carr�e                 ****
		**** Sortie: CMatrice<MType> => Sous matrice de la matrice pass� en param�tre                  ****
		**************************************************************************************************/
		CMatrice<MType> CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int uiLigne, unsigned int uiColonne);

		/**************************************************************************************************
		**** Nom: int* CALComparerCible(unsigned int* piNbLigne, unsigned int* piNbColonne, unsigned   ****
		****    int uiTaille)                                                                          ****
		***************************************************************************************************
		**** Permet de comparer le nombre de ligne et de colonne afin de choisir quel index de colonne ****
		****    ou cible doit �tre utiliser pour la version am�lior�e du calcule de d�terminant        ****
		***************************************************************************************************
		**** Pr�condition:                                                                             ****
		**** Entr�e: unsigned int* : piNbLigne => Tableau contenant le nombre d'occurence de valeur    ****
		****    recherch�e sur chaque ligne                                                            ****
		****    unsigned int* : piNbColonne => Tableau contenant le nombre d'occurence de valeur       ****
		****    recherch�e sur chaque colonne                                                          ****
		****    unsigned int : uiTaille => Taille de la matrice                                        ****
		**** Entra�ne:                                                                                 ****
		**** Sortie: int* => Tableau contenant l'index de la ligne ou de la matrice contenant le plus  ****
		****    d'occurence (par d�faut la 1�re ligne)                                                 ****
		**************************************************************************************************/
		int* CALComparerCible(unsigned int* piNbLigne, unsigned int* piNbColonne, unsigned int uiTaille);
};


#include "CCalculMatriciel.cpp"
#endif // CCalculMatriciel_H
