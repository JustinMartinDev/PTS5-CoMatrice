//#ifndef ERROR_MAX_SIZE 
#define ERROR_MAX_SIZE 256
//#endif

/**************************************************************************
**** Nom: CMatrice<MType>();                                           ****
***************************************************************************
**** Constructeur par default de CMatrice, cr�er une matrice carr� 2x2 ****
***************************************************************************
**** Pr�condition:                                                     ****
**** Entr�e:                                                           ****
**** Entra�ne:                                                         ****
**** Sortie:                                                           ****
**************************************************************************/
template <class MType>
CMatrice<MType>::CMatrice() {	
	uiMATNbLigne = 2;
	uiMATNbColonne = 2;

	MATAllouer(2, 2);
};

/*********************************************************************************************
**** Nom: CMatrice<MType>(unsigned int uiTaille);                                         ****
**********************************************************************************************
**** Constructeur de confort de CMatrice, cr�er une matrice carr� avec la taille pass� en ****
****    param�tre                                                                         ****
**********************************************************************************************
**** Pr�condition:                                                                        ****
**** Entr�e: uiTaille : unsigned int => taille de la matrice                              ****
**** Entra�ne:                                                                            ****
**** Sortie:                                                                              ****
*********************************************************************************************/
template <class MType>
CMatrice<MType>::CMatrice(const unsigned int uiTaille) {
	uiMATNbColonne = uiTaille;
	uiMATNbLigne = uiTaille;

	MATAllouer(uiMATNbLigne, uiMATNbColonne);
}

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
template <class MType>
CMatrice<MType>::CMatrice(const unsigned int uiLigne, const unsigned int uiColonne) {
	uiMATNbLigne = uiLigne;
	uiMATNbColonne = uiColonne;

	MATAllouer(uiMATNbLigne, uiMATNbColonne);
};

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
template <class MType>
CMatrice<MType>::CMatrice(const CMatrice<MType> &pMATParam) {
	uiMATNbColonne = pMATParam.uiMATNbColonne;
	uiMATNbLigne = pMATParam.uiMATNbLigne;

	MATAllouer(uiMATNbLigne, uiMATNbColonne);
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < uiMATNbColonne; uiColonne++) { //on recopie chaque �l�ment de la matrice via sa r�f�rence
			pMATvaleurs[uiLigne][uiColonne] = pMATParam.pMATvaleurs[uiLigne][uiColonne];
		}
	}
};

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
template <class MType>
CMatrice<MType>::~CMatrice() {
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) { //on d�saloue toutes les lignes de notre matrice
		delete pMATvaleurs[uiLigne];
	}
}

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
template <class MType>
void CMatrice<MType>::MATAfficherMatrice() {
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < uiMATNbColonne; uiColonne++) {
			std::cout << MATLireElement(uiLigne, uiColonne) << " "; //Pour chaque �l�ment d'une ligne on l'affiche suivit d'un espace et en fin de ligne on fait un retour � la ligne
		}
		std::cout << std::endl;
	}
}

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
#define MATRICE_ERROR_SIZE_ACCESS 1
template <class MType>
void CMatrice<MType>::MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, MType MTValeur) {
	if (uiLigne > MATLireNbLigne()) { //On leve une exception si on tente de modifier un �l�ment � une ligne qui n'existe pas
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)", MATRICE_ERROR_SIZE_ACCESS, uiLigne, MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_SIZE_ACCESS, message);
	}
	else if (uiColonne > MATLireNbColonne()) { //On leve une exception si on tente de modifier un �l�ment � une colonnne qui n'existe pas
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_SIZE_ACCESS, uiColonne, MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_SIZE_ACCESS, message);
	}
	pMATvaleurs[uiLigne][uiColonne] = MTValeur;
}

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
template <class MType>
void CMatrice<MType>::MATAllouer(unsigned int uiNbLigne, unsigned int uiNbColonne) {
	pMATvaleurs = new MType*[uiNbLigne];

	for (unsigned int uiLigne = 0; uiLigne < uiNbLigne; uiLigne++) { //Allocation de chaque �l�ment
		pMATvaleurs[uiLigne] = new MType[uiNbColonne];
	}
}

/*************************************************************************************************
**** Nom: MType& MATLireElement(unsigned int uiLigne, unsigned int uiColonne)                 ****
**************************************************************************************************
**** Renvoie une r�f�rence de l'element stocker dans la matrice                               ****
**************************************************************************************************
**** Pr�condition:                                                                            ****
**** Entr�e: uiLigne : unsigned int => ligne de l'�l�ment � r�cup�rer                         ****
****    uiColonne : unsigned int => colonne de l'�l�ment � r�cup�rer                          ****
**** Entra�ne: Peut lever une CMatriceException                                               ****
****    si uiLigne ou uiColonne sont sup�rieurs au nombre de ligne de la matrice ou au nombre ****
****    de la colonne de la matrice                                                           ****
**** Sortie: MType& => R�ference vers l'�lement                                               ****
**************************************************************************************************/
template <class MType>
MType& CMatrice<MType>::MATLireElement(unsigned int uiLigne, unsigned int uiColonne) {
	if (uiLigne > MATLireNbLigne()) { //On leve une exception si on tente d'acc�der � une ligne qui n'existe pas
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_SIZE_ACCESS, uiLigne, MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_SIZE_ACCESS, message);
	}
	else if (uiColonne > MATLireNbColonne()) { //On leve une exception si on tente d'acc�der � une colonnne qui n'existe pas
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_SIZE_ACCESS, uiColonne, MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_SIZE_ACCESS, message);
	}

	return pMATvaleurs[uiLigne][uiColonne];
}

/******************************************************************************************
**** Nom: CMatrice<double> operator+(CMatrice<> pMATParam)                             ****
*******************************************************************************************
**** Permet de calculer pour deux matrices A+B et de renvoyer la matrice resultante    ****
*******************************************************************************************
**** Pr�condition: Si MType est un objet avec vous devez surcharger son op�rateur "+"  ****
**** pour retourner un nombre                                                          ****
**** Entr�e:  pMATParam: CMatrice<> => matrice � additionner (B)                       ****
**** Entra�ne:                                                                         ****
**** Sortie: CMatrice<double> => renvoie une matrice de double r�sultat de l'op�ration ****
******************************************************************************************/
#define MATRICE_ERROR_OPERATION_SIZE 3
template <class MType>
CMatrice<MType> CMatrice<MType>::operator+(CMatrice<MType> MATParam) {
	if (MATLireNbLigne() != MATParam.MATLireNbLigne()) { //On leve une exception si on tente d'additionner des matrices de taille diff�rentes
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de ligne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATLireNbLigne(), MATParam.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	else if (MATLireNbColonne() != MATParam.MATLireNbColonne()) {
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de colonne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATLireNbColonne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	CMatrice<MType> dMmatrice(uiMATNbLigne, uiMATNbColonne);

	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) { //chaque �l�ment de la matrice A est additionn� � l'�l�ment correspondant dans la matrice B
		for (unsigned int uiColonne = 0; uiColonne < uiMATNbColonne; uiColonne++) {
			MType newValue = MATLireElement(uiLigne, uiColonne) + MATParam.MATLireElement(uiLigne, uiColonne); 
			dMmatrice.MATModifierElement(uiLigne, uiColonne, newValue); //Le r�sultat est stock� dans la nouvelle matrice
		}
	}
	return dMmatrice;
}

/******************************************************************************************
**** Nom: CMatrice<double> operator-(CMatrice<> pMATParam)                             ****
*******************************************************************************************
**** Permet de calculer pour deux matrices A-B et de renvoyer la matrice resultante    ****
*******************************************************************************************
**** Pr�condition: Si MType est un objet avec vous devez surcharger son op�rateur "-"  ****
**** pour retourner un nombre                                                          ****
**** Entr�e:  pMATParam: CMatrice<> => matrice � soustraire (B)                        ****
**** Entra�ne:                                                                         ****
**** Sortie: CMatrice<double> => renvoie une matrice de double r�sultat de l'op�ration ****
******************************************************************************************/
template <class MType>
CMatrice<MType> CMatrice<MType>::operator-(CMatrice<MType> MATParam) { 
	if (MATLireNbLigne() != MATParam.MATLireNbLigne()) {  //On leve une exception si on tente de soustraire des matrices de taille diff�rentes
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de ligne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATLireNbLigne(), MATParam.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	else if (MATLireNbColonne() != MATParam.MATLireNbColonne()) {
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de colonne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATLireNbColonne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	CMatrice<MType> dMmatrice(uiMATNbLigne, uiMATNbColonne);

	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) { //chaque �l�ment de la matrice A est soustrait � l'�l�ment correspondant dans la matrice B
		for (unsigned int uiColonne = 0; uiColonne < uiMATNbColonne; uiColonne++) {
			MType newValue = MATLireElement(uiLigne, uiColonne) - MATParam.MATLireElement(uiLigne, uiColonne);
			dMmatrice.MATModifierElement(uiLigne, uiColonne, newValue); //Le r�sultat est stock� dans la nouvelle matrice
		}
	}
	return dMmatrice;
}

/******************************************************************************************
**** Nom: CMatrice<double> operator*(CMatrice<> pMATParam)                             ****
*******************************************************************************************
**** Permet de calculer pour deux matrices A*B et de renvoyer la matrice resultante    ****
*******************************************************************************************
**** Pr�condition: Si MType est un objet avec vous devez surcharger son op�rateur "*"  ****
**** pour retourner un object MType                                                    ****
**** Entr�e:  pMATParam: CMatrice<> => matrice � multiplier (B)                        ****
**** Entra�ne: Peut lever une CMatriceException                                        ****
****    si le nombre de colonne de A est diff�rent du nombre de ligne de B (code 2)    ****
**** Sortie: CMatrice<double> => renvoie une matrice de double r�sultat de l'op�ration ****
******************************************************************************************/
#define MATRICE_ERROR_MULTIPLICATION_SIZE 2
template <class MType>
CMatrice<MType> CMatrice<MType>::operator*(CMatrice<MType> MATParam) {
	if (MATLireNbColonne() != MATParam.MATLireNbLigne()) { //On leve une exception si on tente de multiplier des matrices dont le nombre de ligne de A n'est pas �gale au nombre de colonne de B
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_MULTIPLICATION_SIZE, MATLireNbColonne(), MATParam.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_MULTIPLICATION_SIZE, message);
	}
	CMatrice<MType> MATResultat(MATLireNbLigne(), MATParam.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			MType MTSomme = 0;
			for (unsigned int uiCalcIncrement = 0; uiCalcIncrement < MATLireNbColonne(); uiCalcIncrement++) {
				MTSomme += MATLireElement(uiLigne, uiCalcIncrement) * MATParam.MATLireElement(uiCalcIncrement, uiColonne);
			}
			MATResultat.MATModifierElement(uiLigne, uiColonne, MTSomme);
		}
	}
	return MATResultat;
}


/*******************************************************************************************
**** Nom: CMatrice<double> operator/(double dDiviseur)                                  ****
********************************************************************************************
**** Permet de calculer pour une matrice et une constante M/c et de renvoyer la matrice ****
****    r�sultante                                                                      ****
********************************************************************************************
**** Pr�condition: Si MType est un objet, vous devez surcharger son op�rateur "/" pour  ****
****    retourner un double                                                             ****
**** Entr�e: dDiviseur : double => diviseur de la matrice (c)                           ****
**** Entra�ne: Peut lever une CMatriceException si dDiviseur est �gale � 0 (code 4)     ****
**** Sortie: CMatrice<Double> => renvoie une matrice de double r�sultat de l'op�ration  ****
*******************************************************************************************/
#define MATRICE_ERROR_DIVISEUR_0 4
template <class MType>
CMatrice<double> CMatrice<MType>::operator/(double dDiviseur) {
	if (dDiviseur == 0) {
		throw CMatriceException(MATRICE_ERROR_DIVISEUR_0);
	}

	CMatrice<double> dMATResult(MATLireNbLigne(), MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATLireNbColonne(); uiColonne++) {
			double dCalcValeur = MATLireElement(uiLigne, uiColonne)/dDiviseur;
			dMATResult.MATModifierElement(uiLigne, uiColonne, dCalcValeur);
		}
	}
	return dMATResult;
}

/*** FUNCTION EN DEHORS DE LA CLASSE ***/
/************************************************************************************************
**** Nom: CMatrice<double> operator*(const double dMultiplicateur, CMatrice<MType> MATParam) ****
*************************************************************************************************
**** Permet de mulplier une constante num�rique par une matrice et de renvoyer la matrice    ****
****    resultante                                                                           ****
*************************************************************************************************
**** Pr�condition: Si MType est un objet avec vous devez surcharger son op�rateur "*" pour   ****
****    retourner un nombre                                                                  ****
**** Entr�e: dMultiplicateur : const double => constante multiplciateur                      ****
****    MATParam : CMatrice => matrice � multiplier                                          ****
**** Entra�ne:                                                                               ****
**** Sortie: CMatrice<double> => matrice resultat dMultiplicateur*MATParam                   ****
************************************************************************************************/
template<class MType>
CMatrice<double> operator*(const double dMultiplicateur, CMatrice<MType> MATParam) {
	CMatrice<double> dMATResult(MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			double dCalcValeur = MATParam.MATLireElement(uiLigne, uiColonne) * dMultiplicateur;
			dMATResult.MATModifierElement(uiLigne, uiColonne, dCalcValeur);
		}
	}
	return dMATResult;
}


/************************************************************************************************
**** Nom: CMatrice<double> operator*(const double dMultiplicateur, CMatrice<MType> MATParam) ****
*************************************************************************************************
**** Permet de mulplier une matrice par une constante num�rique et de renvoyer la matrice    ****
****    resultante                                                                           ****
*************************************************************************************************
**** Pr�condition: Si MType est un objet avec vous devez surcharger son op�rateur "*" pour   ****
****    retourner un nombre                                                                  ****
**** Entr�e: MATParam : CMatrice => matrice � multiplier                                     ****
****    dMultiplicateur : const double => constante multiplciateur                           ****
**** Entra�ne:                                                                               ****
**** Sortie: CMatrice<double> => matrice resultat MATParam*dMultiplicateur                   ****
************************************************************************************************/
template<class MType>
CMatrice<double> operator*(CMatrice<MType> MATParam, const double dMultiplicateur) {
	CMatrice<double> dMATResult(MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			double dCalcValeur = MATParam.MATLireElement(uiLigne, uiColonne) * dMultiplicateur;
			dMATResult.MATModifierElement(uiLigne, uiColonne, dCalcValeur);
		}
	}
	return dMATResult;
}

/******************************************************************************************
**** Nom: CMatrice<double> operator*(CMatrice<MType> MATParamGauche, CMatrice<MType2>  ****
****    MATParamDroite) CMatrice<MType> MATParam)                                      ****
*******************************************************************************************
**** Permet de mulplier 2 matrices et de renvoyer la matrice resultante                ****
*******************************************************************************************
**** Pr�condition: Si MType et MType2 sont des objets alors vous devez surcharger leur ****
****    op�rateur "*" pour retourner un nombre                                         ****
**** Entr�e: MATParamGauche : CMatrice => matrice � multiplier � gauche                ****
****    MATParamDroite : CMatrice => matrice � multiplier � droite                     ****
**** Entra�ne: Peut lever une CMatriceException                                        ****
****    si le nombre de colonne de A est diff�rent du nombre de ligne de B (code 2)    ****
**** Sortie: CMatrice<double> => matrice resultat MATParamGauche*MATParamDroite        ****
******************************************************************************************/
template <class MType, class MType2>
CMatrice<double> operator*(CMatrice<MType> MATParamGauche, CMatrice<MType2> MATParamDroite) {
	if (MATParamGauche.MATLireNbColonne() != MATParamDroite.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_MULTIPLICATION_SIZE, MATParamGauche.MATLireNbColonne(), MATParamDroite.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_MULTIPLICATION_SIZE, message);
	}
	CMatrice<double> dMATResult(MATParamGauche.MATLireNbLigne(), MATParamDroite.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParamGauche.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParamDroite.MATLireNbColonne(); uiColonne++) {
			double dSomme = 0;
			for (unsigned int uiCalcIncrement = 0; uiCalcIncrement < MATParamGauche.MATLireNbColonne(); uiCalcIncrement++) {
				dSomme += MATParamGauche.MATLireElement(uiLigne, uiCalcIncrement) * MATParamDroite.MATLireElement(uiCalcIncrement, uiColonne);
			}
			dMATResult.MATModifierElement(uiLigne, uiColonne, dSomme);
		}
	}
	return dMATResult;
}

/******************************************************************************************
**** Nom: CMatrice<double> operator+(CMatrice<MType> MATParamGauche, CMatrice<MType2>  ****
****    MATParamDroite)                                                                ****
*******************************************************************************************
**** Permet d'aditionner  2 matrices et de renvoyer la matrice resultante              ****
*******************************************************************************************
**** Pr�condition: Si MType et MType2 sont des objets alors vous devez surcharger leur ****
****    op�rateur "+" pour retourner un nombre                                         ****
**** Entr�e: MATParamGauche : CMatrice => matrice � additionner (gauche du +)          ****
****    MATParamDroite : CMatrice => matrice � additionner (droite du +)               ****
**** Entra�ne: Peut lever une CMatriceException                                        ****
****    si le nombre de colonne de A est diff�rent du nombre de colonne de B ou        ****
****    si le nombre de ligne de A est diff�rent du nombre de ligne de B (code 3)      ****
**** Sortie: CMatrice<double> => matrice resultat MATParamGauche+MATParamDroite        ****
******************************************************************************************/
template <class MType, class MType2>
CMatrice<double> operator+(CMatrice<MType> MATParamGauche, CMatrice<MType2> MATParamDroite) {
	if (MATParamGauche.MATLireNbLigne() != MATParamDroite.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de ligne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATParamGauche.MATLireNbLigne(), MATParamDroite.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	else if (MATParamGauche.MATLireNbColonne() != MATParamDroite.MATLireNbColonne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de colonne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATParamGauche.MATLireNbColonne(), MATParamDroite.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	CMatrice<double> dMATResult(MATParamGauche.MATLireNbLigne(), MATParamGauche.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParamGauche.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParamDroite.MATLireNbColonne(); uiColonne++) {
			double newValue = MATParamGauche.MATLireElement(uiLigne, uiColonne) + MATParamDroite.MATLireElement(uiLigne, uiColonne);
			dMATResult.MATModifierElement(uiLigne, uiColonne, newValue);
		}
	}
	return dMATResult;
}
/******************************************************************************************
**** Nom: CMatrice<double> operator-(CMatrice<MType> MATParamGauche, CMatrice<MType2>  ****
****    MATParamDroite)                                                                ****
*******************************************************************************************
**** Permet de soustraire 2 matrices et de renvoyer la matrice resultante              ****
*******************************************************************************************
**** Pr�condition: Si MType et MType2 sont des objets alors vous devez surcharger leur ****
****    op�rateur "-" pour retourner un nombre                                         ****
**** Entr�e: MATParamGauche : CMatrice => matrice � soustraire (gauche du -)           ****
****    MATParamDroite : CMatrice => matrice � soustraire (droite du -)                ****
**** Entra�ne: Peut lever une CMatriceException                                        ****
****    si le nombre de colonne de A est diff�rent du nombre de colonne de B ou        ****
****    si le nombre de ligne de A est diff�rent du nombre de ligne de B (code 3)      ****
**** Sortie: CMatrice<double> => matrice resultat MATParamGauche-MATParamDroite        ****
******************************************************************************************/
template <class MType, class MType2>
CMatrice<double> operator-(CMatrice<MType> MATParamGauche, CMatrice<MType2> MATParamDroite) {
	if (MATParamGauche.MATLireNbLigne() != MATParamDroite.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de ligne de la 1ere matrice (%d) est diff�rent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATParamGauche.MATLireNbLigne(), MATParamDroite.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	else if (MATParamGauche.MATLireNbColonne() != MATParamDroite.MATLireNbColonne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est diff�rent du nombre de colonne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATParamGauche.MATLireNbColonne(), MATParamDroite.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	CMatrice<double> dMATResult(MATParamGauche.MATLireNbLigne(), MATParamGauche.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParamGauche.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParamDroite.MATLireNbColonne(); uiColonne++) {
			double newValue = MATParamGauche.MATLireElement(uiLigne, uiColonne) - MATParamDroite.MATLireElement(uiLigne, uiColonne);
			dMATResult.MATModifierElement(uiLigne, uiColonne, newValue);
		}
	}
	return dMATResult;
}