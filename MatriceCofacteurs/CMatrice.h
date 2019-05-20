#pragma once
#ifndef CMatrice_H
#define CMatrice_H

#include <iostream>
#include <stdio.h>
#include "CMatriceException.h"

template <class MType = int>
class CMatrice { //int comme type par defaut
public:
	/**************************************************************************
	**** Nom: CMatrice<MType>();                                           ****
	***************************************************************************
	**** Constructeur par default de CMatrice, cr�er une matrice carr�e 2x2****
	***************************************************************************
	**** Pr�condition:                                                     ****
	**** Entr�e:                                                           ****
	**** Entra�ne:                                                         ****
	**** Sortie:                                                           ****
	**************************************************************************/
	CMatrice<MType>(); //par defaut une 2x2

	/*********************************************************************************************
	**** Nom: CMatrice<MType>(unsigned int uiTaille);                                         ****
	**********************************************************************************************
	**** Constructeur de confort de CMatrice, cr�er une matrice carr�e avec la taille pass� en****
	****    param�tre                                                                         ****
	**********************************************************************************************
	**** Pr�condition:                                                                        ****
	**** Entr�e: uiTaille : unsigned int => taille de la matrice                              ****
	**** Entra�ne:                                                                            ****
	**** Sortie:                                                                              ****
	*********************************************************************************************/
	CMatrice<MType>(const unsigned int uiTaille);

	/*************************************************************************************************
	**** Nom: CMatrice<MType>(unsigned int uiLigne, unsigned int uiColonne)                       ****
	**************************************************************************************************
	**** Constructeur de confort de CMatrice, cr�er une matrice avec la taille pass� en param�tre ****
	**************************************************************************************************
	**** Pr�condition:                                                                            ****
	**** Entr�e: uiLigne : unsigned int => nombre de ligne de la matrice                          ****
	****    uiColonne : unsigned int => nombre de ligne de la matrice                             ****
	**** Entra�ne:                                                                                ****
	**** Sortie:                                                                                  ****
	*************************************************************************************************/
	CMatrice<MType>(const unsigned int uiLigne, const unsigned int uiColonne);

	/****************************************************************************************
	**** Nom: CMatrice<MType>(const CMatrice<MType> &pMATParam)                          ****
	*****************************************************************************************
	**** Constructeur de recopie de CMatrice                                             ****
	*****************************************************************************************
	**** Pr�condition:                                                                   ****
	**** Entr�e: pMATParam : const CMatrice<MType> & => r�f�rence de la matrice � copier ****
	**** Entra�ne:                                                                       ****
	**** Sortie:                                                                         ****
	****************************************************************************************/
	CMatrice<MType>(const CMatrice<MType> &pMATParam);


	/**************************************************************************************************
	**** Nom: ~CMatrice()                                                                          ****
	***************************************************************************************************
	**** Destructeur de la classe CMatrice, permet de desallouer toutes les valeurs de la matrices ****
	***************************************************************************************************
	**** Pr�condition:                                                                             ****
	**** Entr�e:                                                                                   ****
	**** Entra�ne:                                                                                 ****
	**** Sortie:                                                                                   ****
	**************************************************************************************************/
	~CMatrice();
	/********************************************************************************************
	**** Nom: void MATAfficherMatrice()                                                      ****
	*********************************************************************************************
	**** Permet d'afficher la matrice dans la console                                        ****
	*********************************************************************************************
	**** Pr�condition: Si vous utiliser une matrice d'objet, vous devez vous assurez d'avoir ****
	****    surcharg� l'op�rateur "<<" de cette classe                                       ****
	**** Entr�e:                                                                             ****
	**** Entra�ne:                                                                           ****
	**** Sortie:                                                                             ****
	********************************************************************************************/
	void MATAfficherMatrice();

	/**************************************************************************************************
	**** Nom: void MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, MType          ****
	****    MTValeur);                                                                             ****
	***************************************************************************************************
	**** Permet de modifier un �l�ment du tableau                                                  ****
	***************************************************************************************************
	**** Pr�condition:                                                                             ****
	**** Entr�e:                                                                                   ****
	****	uiLigne : unsigned int => ligne de l'�l�ment � modifier                                ****
	****    uiColonne : unsigned int => colonne de l'�l�ment � modifier                            ****
	****    MTValeur : MType => valeur � sauvegarder                                               ****
	**** Entra�ne: Peut lever une MatriceException                                                 ****
	****    si uiLigne ou uiColonne sont sup�rieurs au nombre de ligne de la matrice  ou au nombre ****
	****    de la colonne de la matrice                                                            ****
	**** Sortie:                                                                                   ****
	**************************************************************************************************/
	void MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, MType MTValeur);

	/*************************************************************************************************
	**** Nom: MType& MATLireElement(unsigned int uiLigne, unsigned int uiColonne)                 ****
	**************************************************************************************************
	**** Renvoie une r�f�rence de l'element stocker dans la matrice                               ****
	**************************************************************************************************
	**** Pr�condition:                                                                            ****
	**** Entr�e: uiLigne : unsigned int => ligne de l'�l�ment � r�cup�rer                         ****
	****    uiColonne : unsigned int => colonne de l'�l�ment � r�cup�rer                          ****
	**** Entra�ne: Peut lever une MatriceException                                                ****
	****    si uiLigne ou uiColonne sont sup�rieurs au nombre de ligne de la matrice ou au nombre ****
	****    de la colonne de la matrice                                                           ****
	**** Sortie: MType& => R�ference vers l'�lement                                               ****
	**************************************************************************************************/
	MType& MATLireElement(unsigned int uiLigne, unsigned int uiColonne);

	/**************************************************************************************************
	**** Nom: MType& operator()(unsigned int uiLigne, unsigned int uiColonne)                      ****
	***************************************************************************************************
	**** Surcharge de l'operateur () permettant de renvoyer une r�f�rence d'un �l�ment stock� dans ****
	****    la matrice                                                                             ****
	***************************************************************************************************
	**** Pr�condition:                                                                             ****
	**** Entr�e: uiLigne : unsigned int => ligne de l'�l�ment � r�cup�rer                          ****
	****    uiColonne : unsigned int => ligne de l'�l�ment � r�cup�er                              ****
	**** Entra�ne: Peut lever une MatriceException                                                 ****
	****    si uiLigne ou uiColonne sont sup�rieurs au nombre de ligne de la matrice ou au nombre  ****
	****    de la colonne de la matrice                                                            ****
	**** Sortie: MType& => R�ference vers l'�lement                                                ****
	**************************************************************************************************/
	MType& operator()(unsigned int uiLigne, unsigned int uiColonne) { return MATLireElement(uiLigne, uiColonne); };

	/******************************************************************************************
	**** Nom: CMatrice<MType> operator+(CMatrice<> MATParam)                               ****
	*******************************************************************************************
	**** Permet de calculer pour deux matrices A+B et de renvoyer la matrice resultante    ****
	*******************************************************************************************
	**** Pr�condition: Si MType est un objet avec vous devez surcharger son op�rateur "+"  ****
	**** pour retourner un nombre                                                          ****
	**** Entr�e:   MATParam: CMatrice<> => matrice � additionner (B)                       ****
	**** Entra�ne:                                                                         ****
	**** Sortie: CMatrice<MType> => renvoie une matrice de MType r�sultat de l'op�ration   ****
	******************************************************************************************/
	CMatrice<MType> operator+(CMatrice<MType> MATParam);

	/******************************************************************************************
	**** Nom: CMatrice<MType> operator-(CMatrice<MType> MATParam)                          ****
	*******************************************************************************************
	**** Permet de calculer pour deux matrices A-B et de renvoyer la matrice resultante    ****
	*******************************************************************************************
	**** Pr�condition: Si MType est un objet alors vous devez surcharger son op�rateur "-" ****
	**** pour retourner un MType                                                           ****
	**** Entr�e:  MATParam: CMatrice<MType> => matrice � soustraire (B)                    ****
	**** Entra�ne:                                                                         ****
	**** Sortie: CMatrice<MType> => renvoie une matrice de MType r�sultat de l'op�ration   ****
	******************************************************************************************/
	CMatrice<MType> operator-(CMatrice<MType> MATParam);

	/******************************************************************************************
	**** Nom: CMatrice<MType> operator*(CMatrice<MType> MATParam)                          ****
	*******************************************************************************************
	**** Permet de calculer pour deux matrices A*B et de renvoyer la matrice resultante    ****
	*******************************************************************************************
	**** Pr�condition: Si MType est un objet alors vous devez surcharger son op�rateur "*" ****
	**** pour retourner un MType                                                           ****
	**** Entr�e:  MATParam: CMatrice<MType> => matrice � soustraire (B)                    ****
	**** Entra�ne:                                                                         ****
	**** Sortie: CMatrice<MType> => renvoie une matrice de MType r�sultat de l'op�ration   ****
	******************************************************************************************/
	CMatrice<MType> operator*(CMatrice<MType> MATParam); //warning new

	/*******************************************************************************************
	**** Nom: CMatrice<double> operator/(double dDiviseur)                                  ****
	********************************************************************************************
	**** Permet de calculer pour une matrice et une constante M/c et de renvoyer la matrice ****
	****    r�sultante                                                                      ****
	********************************************************************************************
	**** Pr�condition: Si MType est un objet, vous devez surcharger son op�rateur "/" pour  ****
	****    retourner un double                                                             ****
	**** Entr�e: dDiviseur : double => diviseur de la matrice (c)                           ****
	**** Entra�ne: Peut lever une CMatriceException dDiviseur = 0                           ****
	**** Sortie: CMatrice<Double> => renvoie une matrice de double r�sultat de l'op�ration  ****
	*******************************************************************************************/
	CMatrice<double> operator/(double dDiviseur); //warning new

	/**************************************************************************************************
	**** Nom: unsigned int MATLireNbLigne()                                                        ****
	***************************************************************************************************
	**** Acc�sseur en lecture de l'attribut uiMATnbLigne, renvoie le nombre de ligne de la matrice ****
	***************************************************************************************************
	**** Pr�condition: Si MType est un objet avec vous devez surcharger son op�rateur+             ****
	**** pour retourner un nombre                                                                  ****
	**** Entr�e:                                                                                   ****
	**** Entra�ne:                                                                                 ****
	**** Sortie: unsigned int => renvoie le nombre de ligne de la matrice                          ****
	**************************************************************************************************/
	unsigned int MATLireNbLigne() { return uiMATNbLigne; }

	/**********************************************************************************************
	**** Nom: unsigned int MATLireNbColonne()                                                  ****
	***********************************************************************************************
	**** Acc�sseur en lecture de l'attribut uiMATnbColonne, renvoie le nombre de colonne de la ****
	****    matrice                                                                            ****
	***********************************************************************************************
	**** Pr�condition:                                                                         ****
	**** Entr�e:                                                                               ****
	**** Entra�ne:                                                                             ****
	**** Sortie: unsigned int => renvoie le nombre de colonne de la matrice                    ****
	**********************************************************************************************/
	unsigned int MATLireNbColonne() { return uiMATNbColonne; }


	/*****************************************************************************************
	**** Nom: void MATAllouer(unsigned int uiNbLigne, unsigned int uiNbColonne)           ****
	******************************************************************************************
	**** Permet d'allouer en m�moire le tableau de pointeur pMATvaleurs pour recevoir les ****
	****    diff�rents �l�ments                                                           ****
	******************************************************************************************
	**** Pr�condition:                                                                    ****
	**** Entr�e: unsigned int uiNbLigne => nombre de ligne � allouer                      ****
	****    unsigned int uiNbColonne => nombre de colonne � allouer                       ****
	**** Entra�ne:                                                                        ****
	**** Sortie:                                                                          ****
	*****************************************************************************************/
	void MATAllouer(unsigned int uiNbLigne, unsigned int uiNbColonne);
private:
	unsigned int uiMATNbLigne;
	unsigned int uiMATNbColonne;

	MType **pMATvaleurs; //tableau 2D;
};

#include "CMatrice.cpp"

#endif