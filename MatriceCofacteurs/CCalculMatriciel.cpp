#ifndef ERROR_MAX_SIZE 
#define ERROR_MAX_SIZE 256
#endif

//PUBLIC

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
template <class MType>
CMatrice<MType> CCalculMatriciel<MType>::CALTranspose(CMatrice<MType> MATParam) {
	CMatrice<MType> MATTranspose(MATParam.MATLireNbColonne(), MATParam.MATLireNbLigne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) { //Pour chaque ligne 
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) { //et chaque colonne 
			MATTranspose.MATModifierElement(uiColonne, uiLigne, MATParam.MATLireElement(uiLigne, uiColonne)); //on inverser les �l�ments
		}
	}
	return MATTranspose;
}

	
#define MATRICE_ERROR_NON_CARREE 10
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant) {
	if (MATParam.MATLireNbColonne() != MATParam.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur la matrice n'est pas carr�e => nombre de ligne : %d, nombre de colonne : %d\0", MATRICE_ERROR_NON_CARREE, MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_NON_CARREE, message);
	}

	int* puiLigneEtColonneCible = CALTrouverMeilleurCibleDeterminant(MATParam, mValeurRechercheCalculDeterminant); //On va chercher la meilleur cible (am�lioration de Laplace)
	return CALCalculerDeterminant(MATParam, puiLigneEtColonneCible[0], puiLigneEtColonneCible[1]);
}

/**************************************************************************************************
**** Nom: CALDeterminantMatrice(CMatrice<MType> MATParam)                                      ****
***************************************************************************************************
**** Permet de calculer le d�terminant d'une matrice carr�e pass�e en param�tre                ****
***************************************************************************************************
**** Pr�condition: Si MType est une classe d'Objet alors elle doit surcharger l'op�rateur "*"  ****
****    La matrice doit �tre carr�e                                                            ****
**** Entr�e: CMatrice<MType> : MATParam => Matrice sujet au calcul du d�terminant              ****
**** Entra�ne: L�ve une CMatriceException si la matrice pass� en param�tre n'est pas carr�e    ****
**** Sortie: double : d�terminant de la matrice pass� en param�tre                             ****/
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam) {
	if (MATParam.MATLireNbColonne() != MATParam.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur la matrice n'est pas carr�e => nombre de ligne : %d, nombre de colonne : %d\0", MATRICE_ERROR_NON_CARREE, MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_NON_CARREE, message);
	}

	int puiLigneEtColonneCible[2] = {0, -1};
	return CALCalculerDeterminant(MATParam, puiLigneEtColonneCible[0], puiLigneEtColonneCible[1]);
}

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
**** Sortie: CMatrice<double> => Comatrice correspondante � la matrice pass� en param�tre    ****
************************************************************************************************/
template <class MType>
CMatrice<double> CCalculMatriciel<MType>::CALCalculerComatrice(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant) {
	CMatrice<double> dMATComatrice(MATParam.MATLireNbColonne());

	unsigned int uiLigne;
	unsigned int uiColonne;

	for (uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			double dValeur = std::pow(-1, uiLigne + uiColonne) * (CALCalculerDeterminant(CALCalculerSousMatrice(MATParam, uiLigne, uiColonne), mValeurRechercheCalculDeterminant));
			dMATComatrice.MATModifierElement(uiLigne, uiColonne, dValeur); // (-1)^(i+j) * determinant des sous matrices
		}
	}
	return dMATComatrice;
}

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
template <class MType>
CMatrice<double> CCalculMatriciel<MType>::CALCalculerComatrice(CMatrice<MType> MATParam) {
	CMatrice<double> dMATComatrice(MATParam.MATLireNbColonne());

	unsigned int uiLigne;
	unsigned int uiColonne;

	for (uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			double dValeur = std::pow(-1, uiLigne + uiColonne) * (CALCalculerDeterminant(CALCalculerSousMatrice(MATParam, uiLigne, uiColonne)));
			dMATComatrice.MATModifierElement(uiLigne, uiColonne, dValeur); // (-1)^(i+j) * determinant des sous matrices
		}
	}
	return dMATComatrice;
}
//PRIVATE

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
template <class MType>
int* CCalculMatriciel<MType>::CALTrouverMeilleurCibleDeterminant(CMatrice<MType> MATParam, MType valeurRecherchee) {
	unsigned int* piNbLigne = new unsigned int[MATParam.MATLireNbLigne()];
	unsigned int* piNbColonne = new unsigned int[MATParam.MATLireNbColonne()];

	unsigned int uiLigne = 0;
	unsigned int uiColonne = 0;

	for (uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		piNbLigne[uiLigne] = 0;
		piNbColonne[uiLigne] = 0;
	}

	for (uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			if (MATParam.MATLireElement(uiLigne, uiColonne) == valeurRecherchee) {
				piNbLigne[uiLigne] += 1; //incrementation quand trouv�
				piNbColonne[uiColonne] += 1;
			}
		}
	}

	return CALComparerCible(piNbLigne, piNbColonne, MATParam.MATLireNbLigne());
}

#ifndef MATRICE_DETERMINANT_INDEX_NOT_DEFINED
#define MATRICE_DETERMINANT_INDEX_NOT_DEFINED 9
#endif // ! MATRICE_DETERMINANT_INDEX_NOT_DEFINED 9

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
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible, MType mValeurRechercheCalculDeterminant) {
	double value = 0;
	unsigned int uiColonne = 0;
	unsigned int uiLigne = 0;

	if (MATParam.MATLireNbColonne() < 3)
		return (MATParam.MATLireElement(0, 0)*MATParam.MATLireElement(1, 1) - MATParam.MATLireElement(1, 0)*MATParam.MATLireElement(0, 1)); //Calcule simple du determinant, condition d'arret de la m�thode r�cursive

	if (iLigneCible >= 0 && iLigneCible <= MATParam.MATLireNbLigne() && iColonneCible < 0) { //Si le calcul doit �tre effectu� en fonction des lignes 
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, iLigneCible, uiColonne); //On calcul la sousMatrice
			value += std::pow(-1, iLigneCible + uiColonne) * (MATParam.MATLireElement(iLigneCible, uiColonne) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible, mValeurRechercheCalculDeterminant)); //Formule de Laplace en utilisant un appelle r�cursife 
		}
	}
	else if (iColonneCible >= 0 && iColonneCible <= MATParam.MATLireNbColonne() && iLigneCible < 0) {
		for (uiLigne = 0; uiLigne < MATParam.MATLireNbColonne(); uiLigne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, uiLigne, iColonneCible);
			value += std::pow(-1, iColonneCible + uiLigne) * (MATParam.MATLireElement(uiLigne, iColonneCible) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible, mValeurRechercheCalculDeterminant));
		}
	}
	else {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur vous devez indiquer soit une ligne cible ou une colonne cible pour le calcul du determinant ligne cible : %d, colonne cible : %d\0", MATRICE_DETERMINANT_INDEX_NOT_DEFINED, iLigneCible, iColonneCible);
		throw CMatriceException(ERROR_MAX_SIZE, message);
	}
	std::cout << value << std::endl;
	return value;
}

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
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible) {
	double value = 0;
	unsigned int uiColonne = 0;
	unsigned int uiLigne = 0;

	if (MATParam.MATLireNbColonne() < 3)
		return (MATParam.MATLireElement(0, 0)*MATParam.MATLireElement(1, 1) - MATParam.MATLireElement(1, 0)*MATParam.MATLireElement(0, 1)); //Calcule simple du determinant, condition d'arret de la m�thode r�cursive

	if (iLigneCible >= 0 && iLigneCible <= MATParam.MATLireNbLigne() && iColonneCible < 0) { //Si le calcul doit �tre effectu� en fonction des lignes 
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, iLigneCible, uiColonne); //On calcul la sousMatrice
			value += std::pow(-1, iLigneCible + uiColonne) * (MATParam.MATLireElement(iLigneCible, uiColonne) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible)); //Formule de Laplace en utilisant un appelle r�cursife 
		}
	}
	else if (iColonneCible >= 0 && iColonneCible <= MATParam.MATLireNbColonne() && iLigneCible < 0) {
		for (uiLigne = 0; uiLigne < MATParam.MATLireNbColonne(); uiLigne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, uiLigne, iColonneCible);
			value += std::pow(-1, iColonneCible + uiLigne) * (MATParam.MATLireElement(uiLigne, iColonneCible) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible));
		}
	}
	else {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur vous devez indiquer soit une ligne cible ou une colonne cible pour le calcul du determinant ligne cible : %d, colonne cible : %d\0", MATRICE_DETERMINANT_INDEX_NOT_DEFINED, iLigneCible, iColonneCible);
		throw CMatriceException(ERROR_MAX_SIZE, message);
	}
	std::cout << value << std::endl;
	return value;
}

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
template <class MType>
CMatrice<MType> CCalculMatriciel<MType>::CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int uiLigneCible, unsigned int uiColonneCible) {
	if (MATParam.MATLireNbColonne() != MATParam.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur la matrice n'est pas carr�e => nombre de ligne : %d, nombre de colonne : %d\0", MATRICE_ERROR_NON_CARREE, MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());
		throw CMatriceException(ERROR_MAX_SIZE, message);
	}

	CMatrice<MType> MATSousMatrice(MATParam.MATLireNbColonne() - 1);

	unsigned int uiSousMatriceLigne = -1;
	unsigned int uiSousMatriceColonne = 0;
	
	unsigned int uiLigne;
	unsigned int uiColonne;

	for (uiLigne=0; uiLigne<MATParam.MATLireNbLigne(); uiLigne++) { //ligne
		uiSousMatriceLigne++;
		if (uiLigne == uiLigneCible) { //si la ligne est celle pass� en param�tre on l'ignore
			uiSousMatriceLigne--;
			continue;
		}
		uiSousMatriceColonne = -1;
		for (uiColonne=0; uiColonne<MATParam.MATLireNbColonne(); uiColonne++) { //colonne
			uiSousMatriceColonne++;
			if (uiColonne == uiColonneCible) {
				uiSousMatriceColonne--;
				continue;
			}
			MATSousMatrice.MATModifierElement(uiSousMatriceLigne, uiSousMatriceColonne, MATParam.MATLireElement(uiLigne, uiColonne));
			//MATSousMatrice.MATAfficherMatrice();
		}
	}
	return MATSousMatrice;
}

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
template <class MType>
int* CCalculMatriciel<MType>::CALComparerCible(unsigned int* piNbLigne, unsigned int* piNbColonne, unsigned int uiTaille) {
	unsigned int uiMeilleurCibleLigne = 0;
	unsigned int uiMeilleurCibleColonne = 0;

	unsigned int uiLigne = 0;

	for (int uiBoucle = 0; uiBoucle < uiTaille; uiBoucle++) {
		if (piNbLigne[uiBoucle] > piNbLigne[uiMeilleurCibleLigne])
			uiMeilleurCibleLigne = uiBoucle;

		if (piNbColonne[uiBoucle] > piNbColonne[uiMeilleurCibleColonne])
			uiMeilleurCibleColonne = uiBoucle;
	}

	if (piNbColonne[uiMeilleurCibleColonne] >= piNbLigne[uiMeilleurCibleLigne])
		return new int[2] { static_cast<int>(uiMeilleurCibleColonne), -1};
	else
		return new int[2] {-1, static_cast<int>(uiMeilleurCibleColonne)};
}