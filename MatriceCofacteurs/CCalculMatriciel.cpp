#ifndef ERROR_MAX_SIZE 
#define ERROR_MAX_SIZE 256
#endif

/************************************************
**** Nom: CALTranspose                       ****
*************************************************
**** Calcul et retourne la transposé le la   ****
****    matrice passé en paramètre           ****
*************************************************
**** Précondition:                           ****
**** Entrée: pMATParam : CMatrice, matrice à ****
****    transposer                           ****
**** Entraîne:                               ****
**** Sortie: CMatrice, matrice contenant la  ****
****    transposé                            ****
************************************************/
template <class MType>
CMatrice<MType> CCalculMatriciel<MType>::CALTranspose(CMatrice<MType> MATParam) {
	CMatrice<MType> MATTranspose(MATParam.MATLireNbColonne(), MATParam.MATLireNbLigne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) { //Pour chaque ligne 
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) { //et chaque colonne 
			MATTranspose.MATModifierElement(uiColonne, uiLigne, MATParam.MATLireElement(uiLigne, uiColonne)); //on inverser les éléments
		}
	}
	return MATTranspose;
}


/**************************************************************************************************
**** Nom: CALDeterminantMatrice(CMatrice<MType> MATParam)                                      ****
***************************************************************************************************
**** Permet de calculer le déterminant d'une matrice carrée passée en paramètre                ****
***************************************************************************************************
**** Précondition: Si MType est une classe d'Objet alors elle doit surcharger l'opérateur "*"  ****
****    La matrice doit être carrée                                                            ****
**** Entrée: CMatrice<MType> : MATParam => Matrice sujet au calcul du déterminant              ****
**** Entraîne: Lève une CMatriceException si la matrice passé en paramètre n'est pas carrée    ****
**** Sortie: double : déterminant de la matrice passé en paramètre                             ****
**************************************************************************************************/
#define MATRICE_ERROR_NON_CARREE 8
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam) {
	if (MATParam.MATLireNbColonne() != MATParam.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur la matrice n'est pas carrée => nombre de ligne : %d, nombre de colonne : %d\0", MATRICE_ERROR_NON_CARREE, MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_NON_CARREE, message);
	}

	int* puiLigneEtColonneCible = CALTrouverMeilleurCibleDeterminant(MATParam, 0); //On va chercher la meilleur cible (amélioration de Laplace)
	return CALCalculerDeterminant(MATParam, puiLigneEtColonneCible[0], puiLigneEtColonneCible[1]);
}

template <class MType>
CMatrice<double> CCalculMatriciel<MType>::CALCalculerComatrice(CMatrice<MType> MATParam) {
	CMatrice<double> dMATComatrice(MATParam.MATLireNbColonne());

	unsigned int uiLigne;
	unsigned int uiColonne;

	for (uiLigne=0; uiLigne<MATParam.MATLireNbLigne(); uiLigne++) {
		for (uiColonne=0; uiColonne<MATParam.MATLireNbColonne(); uiColonne++) {
			double dValeur = std::pow(-1, uiLigne + uiColonne) * (CALCalculerDeterminant(CALCalculerSousMatrice(MATParam, uiLigne, uiColonne)));
			dMATComatrice.MATModifierElement(uiLigne, uiColonne,dValeur); // (-1)^(i+j) * determinant des sous matrices
		}
	}
	return dMATComatrice;
}

template <class MType>
CMatrice<MType> CCalculMatriciel<MType>::CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int uiLigneCible, unsigned int uiColonneCible) {
	if (MATParam.MATLireNbColonne() != MATParam.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur la matrice n'est pas carrée => nombre de ligne : %d, nombre de colonne : %d\0", MATRICE_ERROR_NON_CARREE, MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());
		throw CMatriceException(ERROR_MAX_SIZE, message);
	}

	CMatrice<MType> MATSousMatrice(MATParam.MATLireNbColonne() - 1);

	unsigned int uiSousMatriceLigne = -1;
	unsigned int uiSousMatriceColonne = 0;
	
	unsigned int uiLigne;
	unsigned int uiColonne;

	for (uiLigne=0; uiLigne<MATParam.MATLireNbLigne(); uiLigne++) { //ligne
		uiSousMatriceLigne++;
		if (uiLigne == uiLigneCible) { //si la ligne est celle passé en paramètre on l'ignore
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
				piNbLigne[uiLigne] += 1; //incrementation quand trouvé
				piNbColonne[uiColonne] += 1;
			}
		}
	}

	return CALComparerCible(piNbLigne, piNbColonne, MATParam.MATLireNbLigne());
}

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

template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible) {
	double value = 0;
	unsigned int uiColonne = 0;
	unsigned int uiLigne = 0;

    if (MATParam.MATLireNbColonne() < 3)
		return (MATParam.MATLireElement(0,0)*MATParam.MATLireElement(1,1) - MATParam.MATLireElement(1,0)*MATParam.MATLireElement(0,1));

    if(iLigneCible>=0 && iColonneCible<0) {
        for (uiColonne = 0; uiColonne< MATParam.MATLireNbColonne(); uiColonne++) {
            CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, iLigneCible, uiColonne);
            value += (int) std::pow(-1, iLigneCible + uiColonne) * (MATParam.MATLireElement(iLigneCible, uiColonne) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible));
        }
    }
    else if(iColonneCible>=0 && iLigneCible<0){
        for (uiLigne = 0; uiLigne < MATParam.MATLireNbColonne(); uiLigne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, uiLigne, iColonneCible);
			value += (int)std::pow(-1, iColonneCible + uiLigne) * (MATParam.MATLireElement(uiLigne, iColonneCible) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible));
        }
    }
    return value;
}