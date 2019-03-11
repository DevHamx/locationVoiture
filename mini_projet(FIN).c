#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// @para c: switch variable 
char c;
short x, i = 0, bonStructure = 0;
FILE *p_fichier=NULL, *p_fichier2=NULL;
//-------------L'ouverture du fichier Bureau-------------------
void FichieBureauropen()
{
	p_fichier = fopen("Bureau.txt", "a+");
	if (!p_fichier)
		printf("Impossible d\'ovrire le fichier");
}
//-------------L'ouverture du fichier Client--------------------
void FichieClientopen()
{
	p_fichier = fopen("Client.txt", "a+");
	if (!p_fichier)
		printf("Impossible d\'ovrire le fichier");
}
//--------------L'ouverture du fichier Opération----------------
void FichieOperationopen()
{
	p_fichier = fopen("Operation.txt", "a+");
	if (!p_fichier)
		printf("Impossible d\'ovrire le fichier");
}
//--------------L'ouverture du fichier Vehicule-----------------
void FichieVehiculeopen()
{
	p_fichier = fopen("Vehicule.txt", "a+");
	if (!p_fichier)
		printf("Impossible d\'ovrire le fichier");
}
//---------------L'ouverture du fichier Locataire---------------
void FichieLocataireopen()
{
	p_fichier = fopen("Locataire.txt", "a+");
	if (!p_fichier)
		printf("Impossible d\'ovrire le fichier");
}
//---------------L'ouvreture d'un nouveau-----------------------
void nvFichier()
{
	p_fichier2 = fopen("nvFichier.txt", "w");
	if (!p_fichier2)
		printf("Impossible d\'ovrire le fichier");
}
/*structure de Bureau et sa liste simplement chainee et ses fonctions*/
typedef struct bureau
{
	unsigned short code_bureau;
	char nom_bureau[20];
	char ville[20];
	char adresse[30];
	char tele_bureau[20];
} bureau;
typedef struct bureauList
{
	bureau p;
	struct bureauList *suivant;
} bureauList;
// global variable
bureauList *B;
bureauList *InsertEnStructureBureau(bureauList *L)
{
	bureauList *nouveau;
	nouveau = (bureauList *)malloc(sizeof(bureauList));
	/*Lecture de la valeur et son assignation au nouvel element*/
	printf("entrer le code du bureau: ");
	scanf("%hu", &nouveau->p.code_bureau);
	printf("entrer le nom du bureau: ");
	scanf("%s", nouveau->p.nom_bureau);
	printf("entrer la ville du bureau: ");
	scanf("%s", nouveau->p.ville);
	printf("entrer l\'adresse du bureau: ");
	scanf("%s", nouveau->p.adresse);
	printf("entrer le tele du bureau: ");
	scanf("%s", &nouveau->p.tele_bureau);
	/*dernier donnee*/
	nouveau->suivant = NULL;
	if (L == NULL)
		return nouveau;
	else
	{
		bureauList *temp2=L;
		while(temp2!=NULL){
			if(temp2->p.code_bureau!=nouveau->p.code_bureau) 
				temp2 = temp2->suivant;
			else return L;	
		}
		//----------------rechercher le dernier element de la liste--------
		bureauList *temp;
		temp = L;
		while (temp->suivant != NULL)
		{

			temp = temp->suivant;
		}
		//----------relier le dernier element de la liste au  nouveau element------
		temp->suivant = nouveau;
		return L;
	}
}
bureauList *RechercherEnStructureBureau(bureauList *L)
{
	unsigned short code_rech;
	bureauList *temp = L;
	printf("entrer le code du bureau pour rechercher: ");
	scanf("%hu", &code_rech);
	//------parcourir toute la liste---------------------
	while (temp != NULL)

	{
		if (temp->p.code_bureau ==code_rech)
		{
			return temp;
		}
		temp = temp->suivant;
	}
	return NULL;
}
bureauList *SupprimerSeulDonneeEnStructureBureau(bureauList *L)
{
	bureauList *tmp = RechercherEnStructureBureau(L);
	if (L == NULL)
		return NULL;
	else if (L == tmp)
	{
		bureauList *SuppTete = L->suivant;
		free(L);
		return SuppTete;
	}
	if (tmp != NULL)
	{
		bureauList *tmpD = L;
		bureauList *tmpAD = L;
		while (tmpD != tmp)
		{
			tmpAD = tmpD;
			tmpD = tmpD->suivant;
		}
		tmpAD->suivant = tmpD->suivant;
		free(tmpD);
	}
	else printf("Ce code  n \' exixte pas !\n");
	return L;
}
void AfficheUneDonneeDeStructureBureau(bureauList *L)
{
	bureauList *tmp = RechercherEnStructureBureau(L);
	if (L == NULL)
		printf("Liste Vide\n");
	if (tmp == NULL)
		printf("ce code du bureau n\'existe pas\n");
	else
	{

		printf("code_bureau\t");
		printf("nom_bureau\t");
		printf("ville\t");
		printf("adresse\t\t");
		printf("tele_bureau\n");
		printf("%hu\t\t", tmp->p.code_bureau);
		printf("%s\t\t", tmp->p.nom_bureau);
		printf("%s\t", tmp->p.ville);
		printf("%s\t\t", tmp->p.adresse);
		printf("%s\n", tmp->p.tele_bureau);
	}
}
void AfficheTousLesDonnesDeStructureBureau(bureauList *L)
{
	bureauList *tmp = L;
	if (L == NULL)
		printf("Liste Vide\n");
	else
	{
			printf("code_bureau\t");
		printf("nom_bureau\t");
		printf("ville\t");
		printf("adresse\t\t");
		printf("tele_bureau\n");
		while (tmp != NULL)
		{

			printf("%hu\t\t", tmp->p.code_bureau);
			printf("%s\t\t", tmp->p.nom_bureau);
			printf("%s\t", tmp->p.ville);
			printf("%s\t\t", tmp->p.adresse);
			printf("%s\n", tmp->p.tele_bureau);
			tmp = tmp->suivant;
		}
	}
}
void AjouteAuFichierBureau(bureauList *L)
{
		FichieBureauropen();
	unsigned short code_bureau;
	char nom_bureau[20], ville[20], adresse[30], tele_bureau[20];
	while (L != NULL)
	{
		fseek(p_fichier, 0, SEEK_SET);
		while (!feof(p_fichier))
		{
			fscanf(p_fichier, "%s\t%s\t%s\t%s\t%hu\n", nom_bureau, ville, adresse, &tele_bureau, &code_bureau);
			if (code_bureau == L->p.code_bureau)
			{
				goto incrementer;
			}
		}
			fseek(p_fichier, 0, SEEK_END);
			fprintf(p_fichier, "%s\t%s\t%s\t%s\t%hu\n", L->p.nom_bureau, L->p.ville, L->p.adresse, L->p.tele_bureau, L->p.code_bureau);
		incrementer:
		L = L->suivant;
	}
	fclose(p_fichier);
}
void SupprimerDonnesduFichierBureau()
{
		FichieBureauropen();
	unsigned short code_bureau, code_bureauSupprimer;
	char nom_bureau[20], ville[20], adresse[30], tele_bureau[20];
	fseek(p_fichier, 0, SEEK_SET);
	nvFichier();
	printf("Entrer le code de bureau a supprimer: ");
	scanf("%hu", &code_bureauSupprimer);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%hu\n", nom_bureau, ville, adresse, &tele_bureau, &code_bureau);
		if (code_bureau != code_bureauSupprimer)
			fprintf(p_fichier2, "%s\t%s\t%s\t%s\t%hu\n", nom_bureau, ville, adresse, tele_bureau, code_bureau);
	}
	fclose(p_fichier);
	remove("Bureau.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Bureau.txt");
}
void ModifierDonnesduFichierBureau()
{
		FichieBureauropen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short code_bureau, code_bureauModifier, code_bureauNv;
	char nom_bureau[20], ville[20], adresse[30], tele_bureau[20];
	char nom_bureauNv[20], villeNv[20], adresseNv[30], tele_bureauNv[20]; 
	nvFichier();
	printf("Entrer le code de bureau a modifier: ");
	scanf("%hu", &code_bureauModifier);
	printf("entrer le nouveau code du bureau: ");
	scanf("%hu", &code_bureauNv);
	printf("entrer le nouveau nom du bureau: ");
	scanf("%s", nom_bureauNv);
	printf("entrer la nouvelle ville du bureau: ");
	scanf("%s", villeNv);
	printf("entrer la nouvelle adresse du bureau: ");
	scanf("%s", adresseNv);
	printf("entrer le nouveau tele du bureau: ");
	scanf("%s", &tele_bureauNv);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%hu\n", nom_bureau, ville, adresse, &tele_bureau, &code_bureau);
		if (code_bureau != code_bureauModifier)
			fprintf(p_fichier2, "%s\t%s\t%s\t%s\t%hu\n", nom_bureau, ville, adresse, tele_bureau, code_bureau);
		else
			fprintf(p_fichier2, "%s\t%s\t%s\t%s\t%hu\n", nom_bureauNv, villeNv, adresseNv, tele_bureauNv, code_bureauNv);
	} 
	fclose(p_fichier);
	remove("Bureau.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Bureau.txt");
}
void AfficherToutDonnesduFichierBureau()
{
	FichieBureauropen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short code_bureau;
	char nom_bureau[20], ville[20], adresse[30], tele_bureau[20];
	printf("code_bureau\t");
	printf("nom_bureau\t");
	printf("ville\t");
	printf("adresse\t\t");
	printf("tele_bureau\n");
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%hu\n", nom_bureau, ville, adresse, &tele_bureau, &code_bureau);
	printf("%hu\t\t", code_bureau);
		printf("%s\t\t", nom_bureau);
		printf("%s\t", ville);
		printf("%s\t\t", adresse);
		printf("%s\n", tele_bureau);
	}
	fclose(p_fichier);
}
void AfficherUneDonnesduFichierBureau()
{
	FichieBureauropen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short code_bureau,code_bureauRecherche;
	char nom_bureau[20], ville[20], adresse[30], tele_bureau[20];
	printf("Entrer le code de bureau a Afficher: ");
	scanf("%hu", &code_bureauRecherche);
	while (!feof(p_fichier)){
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%hu\n", nom_bureau, ville, adresse, &tele_bureau, &code_bureau);
			if (code_bureau == code_bureauRecherche){
				printf("code_bureau\t");
				printf("nom_bureau\t");
				printf("ville\t");
				printf("adresse\t\t");
				printf("tele_bureau\n");
				printf("%hu\t\t", code_bureau);
				printf("%s\t\t", nom_bureau);
				printf("%s\t", ville);
				printf("%s\t\t", adresse);
				printf("%s\n", tele_bureau); 
				fclose(p_fichier);
				return;
			}
	}
				printf("ce Bureau n\'existe pas\n");fclose(p_fichier);	
}
//--------------structure de vehicule et sa liste simplement chainee-------------
typedef struct vehicule
{
	unsigned short id_vehicule;
	unsigned short code_bureau;
	char Permi[3];
	char marque[20];
	char modele[20];
	unsigned short capacite_coffre;
} vehicule;
typedef struct vehiculeList
{
	vehicule p;
	struct vehiculeList *suivant;
} vehiculeList;
// global variable
vehiculeList *V;
vehiculeList *InsertEnStructurevehicule(vehiculeList *L)
{
	unsigned short code_bureau;
	char nom_bureau[20], ville[20], adresse[30], tele_bureau[20];
	short ajouter=0;
	vehiculeList *nouveau;
	nouveau = (vehiculeList *)malloc(sizeof(vehiculeList));
	//-----remplissage des champs de la structure vehicule----
	printf("entrer l\'ID de Vehicule: ");
	scanf("%hu", &nouveau->p.id_vehicule);
	printf("entrer le code du bureau: ");
	scanf("%hu", &nouveau->p.code_bureau);
	printf("entrer le Type de Permit: ");
	scanf("%s", nouveau->p.Permi);
	printf("entrer la marque de Vehicule: ");
	scanf("%s", &nouveau->p.marque);
	printf("entrer le modele de Vehicule: ");
	scanf("%s", nouveau->p.modele);
	printf("entrer la capacite du coffre: ");
	scanf("%hu", &nouveau->p.capacite_coffre);
	nouveau->suivant = NULL;
	if (p_fichier)	fclose(p_fichier);
	p_fichier = fopen("Bureau.txt", "r");
	while (!feof(p_fichier)){
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%hu\n", nom_bureau, ville, adresse, &tele_bureau, &code_bureau);
		if(code_bureau == nouveau->p.code_bureau){ajouter=1; goto terminer;} 
	}
	terminer:
	fclose(p_fichier);
	if(ajouter == 1){
	if (L == NULL)
		return nouveau;
		/*rechercher le dernier element de la liste */
	else{
		vehiculeList *temp2=L;
		while(temp2!=NULL){
			if(temp2->p.id_vehicule!=nouveau->p.id_vehicule) 
				temp2 = temp2->suivant;
			else return L;
			}
		vehiculeList *temp;
		temp = L;
		while (temp->suivant != NULL)
		{
			temp = temp->suivant;
		}
		/*relier le dernier element de la liste au nouveau element*/
		temp->suivant = nouveau;
		}
	}
	else printf("ce code Bureau n\'existe pas\n");
	return L;
}
vehiculeList *RechercherEnStructurevehicule(vehiculeList *L)
{
	unsigned short code_rech;
	vehiculeList *temp = L;
	printf("entrer le ID du Vehicule pour rechercher: ");
	scanf("%hu", &code_rech);
//------parcourir toute la liste---------------------
	while (temp != NULL)

	{
		if (temp->p.id_vehicule ==code_rech)
		{
			return temp;
		}
		temp = temp->suivant;
	}
	return NULL;
}
vehiculeList *SupprimerSeulDonneeEnStructurevehicule(vehiculeList *L)
{
	vehiculeList *tmp = RechercherEnStructurevehicule(L);
	if (L == NULL)
		return NULL;
	else if (L == tmp)
	{
		vehiculeList *SuppTete = L->suivant;
		free(L);
		return SuppTete;
	}
	if (tmp != NULL)
	{
		vehiculeList *tmpV = L;
		vehiculeList *tmpAV = L;
		while (tmpV != tmp)
		{
			tmpAV = tmpV;
			tmpV = tmpV->suivant;
		}
		tmpAV->suivant = tmpV->suivant;
		free(tmpV);
	}
	else printf("Ce Id N\' existe pas !\n");
	return L;
}
void AfficheUneDonneeDeStructurevehicule(vehiculeList *L)
{
	vehiculeList *tmp = RechercherEnStructurevehicule(L);
	if (L == NULL)
		printf("Liste Vide\n");
	if (tmp == NULL)
		printf("ce ID du Vehicule n\'existe pas\n");
	else
	{
			printf("id_vehicule\t");
		printf("code_bureau\t");
		printf("Permi\t");
		printf("marque\t");
		printf("modele\t");
		printf("capacite_coffre\n");
		printf("%hu\t\t", tmp->p.id_vehicule);
		printf("%hu\t\t", tmp->p.code_bureau);
		printf("%s\t", tmp->p.Permi);
		printf("%s\t\t", tmp->p.marque);
		printf("%s\t", tmp->p.modele);
		printf("%hu\n", tmp->p.capacite_coffre);
	}
}
void AfficheTousLesDonnesDeStructurevehicule(vehiculeList *L)
{
	vehiculeList *tmp = L;
	if (L == NULL)
		printf("Liste Vide\n");
	else
	{
	    printf("id_vehicule\t");
		printf("code_bureau\t");
		printf("Permi\t");
		printf("marque\t");
		printf("modele\t");
		printf("capacite_coffre\n");
		while (tmp != NULL)
		{
			printf("%hu\t\t", tmp->p.id_vehicule);
			printf("%hu\t\t", tmp->p.code_bureau);
			printf("%s\t", tmp->p.Permi);
			printf("%s\t", tmp->p.marque);
			printf("%s\t\t", tmp->p.modele);
			printf("%hu\n", tmp->p.capacite_coffre);
			tmp = tmp->suivant;
		}
		
		
	}
}
void AjouteAuFichiervehicule(vehiculeList *L)
{
		FichieVehiculeopen();
	unsigned short id_vehicule,code_bureau,capacite_coffre;
	char Permi[3], marque[20], modele[20];
	while (L != NULL)
	{
		fseek(p_fichier, 0, SEEK_SET);
		while (!feof(p_fichier))
		{
			fscanf(p_fichier, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",&capacite_coffre, modele, marque, Permi, &code_bureau, &id_vehicule);
			if (id_vehicule == L->p.id_vehicule)
			{
				goto ancrementer2;
			}
		}
			fseek(p_fichier, 0, SEEK_END);
			fprintf(p_fichier, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",L->p.capacite_coffre, L->p.modele, L->p.marque, L->p.Permi, L->p.code_bureau, L->p.id_vehicule);
		ancrementer2:
		L = L->suivant;
	}
	fclose(p_fichier);
}
void SupprimerDonnesduFichiervehicule()
{
		FichieVehiculeopen();
	unsigned short id_vehicule,code_bureau,capacite_coffre,id_vehiculeSupprime;
	char Permi[3], marque[20], modele[20];
	fseek(p_fichier, 0, SEEK_SET);
	nvFichier();
	printf("Entrer l\'ID de vehicule a supprimer: ");
	scanf("%hu", &id_vehiculeSupprime);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",&capacite_coffre, modele, marque, Permi, &code_bureau, &id_vehicule);
		if (id_vehicule != id_vehiculeSupprime)
			fprintf(p_fichier2, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",capacite_coffre, modele, marque, Permi, code_bureau, id_vehicule);
	}
	fclose(p_fichier);
	remove("Vehicule.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Vehicule.txt");
}
void ModifierDonnesduFichiervehicule()
{
		FichieVehiculeopen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short id_vehicule,code_bureau,capacite_coffre,id_vehiculeModifier;
	char Permi[3], marque[20], modele[20];
	unsigned short id_vehiculeNv,code_bureauNV,capacite_coffreNv;
	char PermiNv[3], marqueNv[20], modeleNv[20];
	nvFichier();
	printf("entrer l\'ID de Vehicule a modifier: ");
	scanf("%hu",&id_vehiculeModifier);
	printf("entrer le nouveau ID de Vehicule: ");
	scanf("%hu",&id_vehiculeNv);
	printf("entrer le nouveau code du bureau: ");
	scanf("%hu", &code_bureauNV);
	printf("entrer le nouveau Type de Permit: ");
	scanf("%s", PermiNv);
	printf("entrer la nouveau marque de Vehicule: ");
	scanf("%s", marqueNv);
	printf("entrer le nouveau modele de Vehicule: ");
	scanf("%s", modeleNv);
	printf("entrer la nouveau capacite du coffre: ");
	scanf("%hu", &capacite_coffreNv);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",&capacite_coffre, modele, marque, Permi, &code_bureau, &id_vehicule);
		if (id_vehicule != id_vehiculeModifier)
			fprintf(p_fichier2, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",capacite_coffre, modele, marque, Permi, code_bureau, id_vehicule);
		else
			fprintf(p_fichier2, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",capacite_coffreNv, modeleNv, marqueNv, PermiNv, code_bureauNV, id_vehiculeNv);
	}
	fclose(p_fichier);
	remove("Vehicule.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Vehicule.txt");
}
void AfficherDonnesduFichiervehicule()
{
	FichieVehiculeopen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short id_vehicule,code_bureau,capacite_coffre;
	char Permi[3], marque[20], modele[20];
	printf("id_vehicule\t");
	printf("code_bureau\t");
	printf("Permi\t");
	printf("marque\t");
	printf("modele\t");
	printf("capacite_coffre\n");
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",&capacite_coffre, modele, marque, Permi, &code_bureau, &id_vehicule);
		printf("%hu\t\t", id_vehicule);
		printf("%hu\t\t", code_bureau);
		printf("%s\t", Permi);
		printf("%s\t", marque);
		printf("%s\t\t", modele);
		printf("%hu\n", capacite_coffre);
	}
	fclose(p_fichier);
}
void AfficherUneDonnesduFichiervehicule()
{
	FichieVehiculeopen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short id_vehicule,code_bureau,capacite_coffre,id_vehiculeRecherche;
	char Permi[3], marque[20], modele[20];
	printf("Entrer ID de vehicule a Afficher: ");
	scanf("%hu", &id_vehiculeRecherche);
	while (!feof(p_fichier)){
		fscanf(p_fichier, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",&capacite_coffre, modele, marque, Permi, &code_bureau, &id_vehicule);
			if (id_vehicule == id_vehiculeRecherche){
			printf("id_vehicule\t");
				printf("code_bureau\t");
				printf("Permi\t");
				printf("marque\t");
				printf("modele\t");
				printf("capacite_coffre\n");
				printf("%hu\t\t", id_vehicule);
				printf("%hu\t\t", code_bureau);
				printf("%s\t", Permi);
				printf("%s\t", marque);
				printf("%s\t\t", modele);
				printf("%hu\n", capacite_coffre);
				fclose(p_fichier);
				return;
			}
	}
			 printf("cette vehicule n\'existe pas\n");fclose(p_fichier);		
}
/*structure de client et sa liste simplement chainee*/
typedef struct client
{
	char CIN[20];
	char nom[20];
	char adresse[30];
	char tele_Client[20];
	char Credit_Card[20];
} client;
typedef struct clientList
{
	client p;
	struct clientList *suivant;
} clientList;
// global variable
clientList *C;
clientList *InsertEnStructureclient(clientList *L)
{
	clientList *nouveau;
	nouveau = (clientList *)malloc(sizeof(clientList));
	/*Lecture de la valeur et son assignation au nouvel element*/
	printf("entrer le CIN de client: ");
	scanf("%s", nouveau->p.CIN);
	printf("entrer le Nom de client: ");
	scanf("%s", nouveau->p.nom);
	printf("entrer l\'adresse de client: ");
	scanf("%s", nouveau->p.adresse);
	printf("entrer le Tele de client: ");
	scanf("%s", nouveau->p.tele_Client);
	printf("entrer Credit Card de client: ");
	scanf("%s", nouveau->p.Credit_Card);
	nouveau->suivant = NULL;
	if (L == NULL)
		return nouveau;
	else
	{
		clientList *temp2=L;
		while(temp2!=NULL){
			if(strcmp(temp2->p.CIN,nouveau->p.CIN)!=0) 
				temp2 = temp2->suivant;
			else return L;
			}
		/*recherche le dernier element de la liste */
		clientList *temp;
		temp = L;
		while (temp->suivant != NULL)
		{

			temp = temp->suivant;
		}
		/*relier le dernier element de la liste au nouveau element */
		temp->suivant = nouveau;
		return L;
	}
}
clientList *RechercherEnStructureclient(clientList *L)
{
	char CIN_rech[20];
	clientList *temp = L;
	printf("entrer le CIN du client pour rechercher: ");
	scanf("%s",CIN_rech);
	/*repeter j'usqua la fin de la liste*/
	while (temp != NULL)

	{
		if (strcmp(temp->p.CIN, CIN_rech)==0)
		{
			return temp;
		}
		temp = temp->suivant;
	}
	return NULL;
}
clientList *SupprimerSeulDonneeEnStructureclient(clientList *L)
{
	clientList *tmp = RechercherEnStructureclient(L);
	if (L == NULL)
		return NULL;
	else if (L == tmp)
	{
		clientList *SuppTete = L->suivant;
		free(L);
		return SuppTete;
	}
	if (tmp != NULL)
	{
		clientList *tmpV = L;
		clientList *tmpAV = L;
		while (tmpV != tmp)
		{
			tmpAV = tmpV;
			tmpV = tmpV->suivant;
		}
		tmpAV->suivant = tmpV->suivant;
		free(tmpV);
	}
	else printf("Ce CIN  du client N\' existe pas !\n");
	return L;
}
void AfficheUneDonneeDeStructureclient(clientList *L)
{
	clientList *tmp = RechercherEnStructureclient(L);
	if (L == NULL)
		printf("Liste Vide\n");
	if (tmp == NULL)
		printf("ce CIN du Client n\'existe pas\n");
	else
	{
	printf("CIN\t");
		printf("Nom\t");
		printf("Adresse\t");
		printf("tele_Client\t");
		printf("Credit_Card\n");
		printf("%s\t", tmp->p.CIN);
		printf("%s\t", tmp->p.nom);
		printf("%s\t", tmp->p.adresse);
		printf("%s\t\t", tmp->p.tele_Client);
		printf("%s\n", tmp->p.Credit_Card);
	}
}
void AfficheTousLesDonnesDeStructureclient(clientList *L)
{
	clientList *tmp = L;
	if (L == NULL)
		printf("Liste Vide\n");
	else
	{
		
			printf("CIN\t");
			printf("Nom\t");
			printf("Adresse\t");
			printf("tele_Client\t");
			printf("Credit_Card\n");
		while (tmp != NULL)
		{
			printf("%s\t", tmp->p.CIN);
			printf("%s\t", tmp->p.nom);
			printf("%s\t", tmp->p.adresse);
			printf("%s\t\t", tmp->p.tele_Client);
			printf("%s\n", tmp->p.Credit_Card);
			tmp = tmp->suivant;
		}
	}
}
void AjouteAuFichierclient(clientList *L)
{
		FichieClientopen();
	char CIN[20], nom[20], adresse[30], tele_Client[30],Credit_Card[20];
	while (L != NULL)
	{
		fseek(p_fichier, 0, SEEK_SET);
		while (!feof(p_fichier))
		{
			fscanf(p_fichier, "%s\t%s\t%s\t%s\t%s\n", nom, &tele_Client, adresse, Credit_Card, CIN);
			if (strcmp(L->p.CIN,CIN)==0)
			{
				goto ancrementer3;
			}
		}
			fseek(p_fichier, 0, SEEK_END);
			fprintf(p_fichier, "%s\t%s\t%s\t%s\t%s\n",L->p.nom,L->p.tele_Client,L->p.adresse,L->p.Credit_Card,L->p.CIN);
		ancrementer3:
		L = L->suivant;
	}
	fclose(p_fichier);
}
void SupprimerDonnesduFichierclient()
{
		FichieClientopen();
	char CIN[20], nom[20], adresse[30], tele_Client[30],Credit_Card[20],CINaSupprime[20];
	fseek(p_fichier, 0, SEEK_SET);
	nvFichier();
	printf("Entrer le CIN de client a supprimer: ");
	scanf("%s", CINaSupprime);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%s\n", nom, &tele_Client, adresse, Credit_Card, CIN);
		if (strcmp(CINaSupprime,CIN)!=0)
			fprintf(p_fichier2, "%s\t%s\t%s\t%s\t%s\n",nom,tele_Client,adresse,Credit_Card,CIN);
	}
	fclose(p_fichier);
	remove("Client.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Client.txt");
}
void ModifierDonnesduFichierclient()
{
		FichieClientopen();

	fseek(p_fichier, 0, SEEK_SET);
	char CIN[20], nom[20], adresse[30], tele_Client[30],Credit_Card[20],CINaModifier[20];
	char CINnv[20], nomNv[20], adresseNv[30], tele_ClientNv[30],Credit_CardNv[20];
	nvFichier();
	printf("Entrer le CIN de client a modifier: ");
	scanf("%s", CINaModifier);
	printf("entrer le nouveau CIN du client: ");
	scanf("%s", CINnv);
	printf("entrer le nouveau nom du client: ");
	scanf("%s", nomNv);
	printf("entrer la nouveau adresse du client: ");
	scanf("%s", adresseNv);
	printf("entrer le nouveau tele du client: ");
	scanf("%s", tele_ClientNv);
	printf("entrer la nouveau Credit Card du client: ");
	scanf("%s", Credit_CardNv);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%s\n", nom, &tele_Client, adresse, Credit_Card, CIN);
		if (strcmp(CINaModifier,CIN)!=0)
			fprintf(p_fichier2, "%s\t%s\t%s\t%s\t%s\n", nom, tele_Client, adresse, Credit_Card, CIN);
		else
			fprintf(p_fichier2, "%s\t%s\t%s\t%s\t%s\n", nomNv, tele_ClientNv, adresseNv, Credit_CardNv, CINnv);
	}
	fclose(p_fichier);
	remove("Client.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Client.txt");
}
void AfficherDonnesduFichierclient()
{
	FichieClientopen();
	char CIN[20], nom[20], adresse[30], tele_Client[30],Credit_Card[20];
	fseek(p_fichier, 0, SEEK_SET);
	printf("CIN\t");
	printf("nom_cliet\t");
	printf("tele client\t");
	printf("adresse\t\t");
	printf("credit card\n");
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%s\n", nom, &tele_Client, adresse, Credit_Card, CIN);
	    printf("%s\t", CIN);
		printf("%s\t\t", nom);
		printf("%s\t\t", tele_Client);
		printf("%s\t\t", adresse);
		printf("%s\n", Credit_Card);
	}
	fclose(p_fichier);
}
void AfficherUneDonnesduFichierclient()
{
	FichieClientopen();
	char CIN[20], nom[20], adresse[30], tele_Client[30],Credit_Card[20],CINRecherche[20];
	fseek(p_fichier, 0, SEEK_SET);
	printf("Entrer CIN de Client a Afficher: ");
	scanf("%s", CINRecherche);
	while (!feof(p_fichier)){
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%s\n", nom, &tele_Client, adresse, Credit_Card, CIN);
			if (strcmp(CIN,CINRecherche)==0){
				printf("CIN\t");
				printf("nom_cliet\t");
				printf("tele client\t");
				printf("adresse\t\t");
				printf("credit card\n");
		     	printf("%s\t", CIN);
	        	printf("%s\t\t", nom);
	        	printf("%s\t\t", tele_Client);
	        	printf("%s\t\t", adresse);
	        	printf("%s\n", Credit_Card);
				fclose(p_fichier);
				return;
			}			
	}
	printf("ce Client n\'existe pas\n");fclose(p_fichier);
}
/*structure d'operation et sa liste simplement chainee*/
typedef struct operation
{
	unsigned short id_Operation;
	char duree[20];
	float prix;
} operation;
typedef struct operationList
{
	operation p;
	struct operationList *suivant;
} operationList;
operationList *O;
operationList *InsertEnStructureoperation(operationList *L)
{
	operationList *nouveau;
	nouveau = (operationList *)malloc(sizeof(operationList));
	/*Lecture de la valeur et son assignation au nouvel element*/
	printf("entrer l\'ID de l\'operation: ");
	scanf("%hu", &nouveau->p.id_Operation);
	printf("entrer la Duree de l\'operation: ");
	scanf("%s", nouveau->p.duree);
	printf("entrer le Prix de l\'operation: ");
	scanf("%f", &nouveau->p.prix);
	/*dernier donnee*/
	nouveau->suivant = NULL;
	if (L == NULL)
		return nouveau;
	else
	{
		operationList *temp2=L;
		while(temp2!=NULL){
			if(temp2->p.id_Operation!=nouveau->p.id_Operation) 
				temp2 = temp2->suivant;
			else return L;
			}
		/*recherche le dernier element de la liste */
		operationList *temp;
		temp = L;
		while (temp->suivant != NULL)
		{
			temp = temp->suivant;
		}
		/*relier le dernier element de la liste au nouveau element*/
		temp->suivant = nouveau;
		return L;
	}
}
operationList *RechercherEnStructureoperation(operationList *L)
{
	unsigned short id_rech;
	operationList *temp = L;
	printf("entrer l\'ID de l\'Operation pour rechercher: ");
	scanf("%hu", &id_rech);
	//-------parcourir toute la liste-----------------------
	while (temp != NULL)

	{
		if (temp->p.id_Operation ==id_rech)
		{
			return temp;
		}
		temp = temp->suivant;
	}
	return NULL;
}
operationList *SupprimerSeulDonneeEnStructureoperation(operationList *L)
{
	operationList *tmp = RechercherEnStructureoperation(L);
	if (L == NULL)
		return NULL;
	else if (L == tmp)
	{
		operationList *SuppTete = L->suivant;
		free(L);
		return SuppTete;
	}
	if (tmp != NULL)
	{
		operationList *tmpV = L;
		operationList *tmpAV = L;
		while (tmpV != tmp)
		{
			tmpAV = tmpV;
			tmpV = tmpV->suivant;
		}
		tmpAV->suivant = tmpV->suivant;
		free(tmpV);
	}
	else printf("ce ID d \'operation n\'existe pas! \n");
	return L;
}
void AfficheUneDonneeDeStructureoperation(operationList *L)
{
	operationList *tmp = RechercherEnStructureoperation(L);
	if (L == NULL)
		printf("Liste Vide\n");
	if (tmp == NULL)
		printf("ce ID d\'opeartion n\'existe pas\n");
	else
	{
		printf("Id_Operation\t");
		printf("Duree\t");
		printf("Prix\n");
		printf("%hu\t\t", tmp->p.id_Operation);
		printf("%s\t", tmp->p.duree);
		printf("%f\n", tmp->p.prix);
	}
}
void AfficheTousLesDonnesDeStructureoperation(operationList *L)
{
	operationList *tmp = L;
	if (L == NULL)
		printf("Liste Vide\n");
	else
	{
		printf("Id_Operation\t");
		printf("Duree\t");
		printf("Prix\n");
		while (tmp != NULL)
		{
			printf("%hu\t\t", tmp->p.id_Operation);
			printf("%s\t", tmp->p.duree);
			printf("%f\n", tmp->p.prix);
			tmp = tmp->suivant;
		}
	}
}
void AjouteAuFichieroperation(operationList *L)
{
		FichieOperationopen();
	unsigned short id_Operation;
	char duree[20];
	float prix;
	while (L != NULL)
	{
		fseek(p_fichier, 0, SEEK_SET);
		while (!feof(p_fichier))
		{
			fscanf(p_fichier, "%f\t%s\t%hu\n",&prix, duree, &id_Operation);
			if (L->p.id_Operation==id_Operation)
			{
				goto ancrementer4;
			}
		}
			fseek(p_fichier, 0, SEEK_END);
			fprintf(p_fichier, "%f\t%s\t%hu\n",L->p.prix,L->p.duree,L->p.id_Operation);
		ancrementer4:
		L = L->suivant;
	}
	fclose(p_fichier);
}
void SupprimerDonnesduFichieroperation()
{
		FichieOperationopen();
	unsigned short id_Operation,id_OperationSupprimer;
	char duree[20];
	float prix;
	fseek(p_fichier, 0, SEEK_SET);
	nvFichier();
	printf("Entrer le code d\'operation a supprimer: ");
	scanf("%hu", &id_OperationSupprimer);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%f\t%s\t%hu\n",&prix, duree, &id_Operation);
		if (id_Operation != id_OperationSupprimer)
			fprintf(p_fichier2,"%f\t%s\t%hu\n",prix,duree,id_Operation);
	}
	fclose(p_fichier);
	remove("Operation.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Operation.txt");
}
void ModifierDonnesduFichieroperation()
{
		FichieOperationopen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short id_Operation,id_OperationModifier,id_OperationNv;
	char duree[20],dureeNv[20];
	float prix,prixNv;
	nvFichier();
	printf("Entrer le code d\'operation a modifier: ");
	scanf("%hu", &id_OperationModifier);
	printf("entrer le nouveau code d\'operation: ");
	scanf("%hu", &id_OperationNv);
	printf("entrer la Duree de l\'operation: ");
	scanf("%s", dureeNv);
	printf("entrer le Prix de l\'operation: ");
	scanf("%f", &prixNv);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%f\t%s\t%hu\n",&prix, duree, &id_Operation);
		if (id_Operation != id_OperationModifier)
			fprintf(p_fichier2, "%f\t%s\t%hu\n",prix,duree,id_Operation);
		else
			fprintf(p_fichier2, "%f\t%s\t%hu\n",prixNv,dureeNv,id_OperationNv);
	}
	fclose(p_fichier);
	remove("Operation.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Operation.txt");
}
void AfficherDonnesduFichieroperation()
{
	FichieOperationopen();
	unsigned short id_Operation;
	char duree[20];
	float prix;
	fseek(p_fichier, 0, SEEK_SET);
	printf("ID operation\t");
	printf("Prix\t\t");
	printf("Duree\n");
	while (!feof(p_fichier))
	{
		fscanf(p_fichier, "%f\t%s\t%hu\n",&prix, duree, &id_Operation);
		printf("%hu\t\t", id_Operation);
		printf("%f\t", prix);
		printf("%s\n", duree);
	}
	fclose(p_fichier);
}
void AfficherUneDonnesduFichieroperation()
{
	FichieOperationopen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short id_Operation,id_OperationRecherche;
	char duree[20];
	float prix;
	printf("Entrer ID d\'operation a Afficher: ");
	scanf("%hu", &id_OperationRecherche);
	while (!feof(p_fichier)){
		fscanf(p_fichier, "%f\t%s\t%hu\n",&prix, duree, &id_Operation);
			if (id_Operation == id_OperationRecherche){
				printf("ID operation\t");
				printf("Prix\t\t");
				printf("Duree\n");
				printf("%hu\t\t", id_Operation);
				printf("%f\t", prix);
				printf("%s\n", duree);
				fclose(p_fichier);
				return;
			}			
	}
	printf("cette Operation n\'existe pas\n");fclose(p_fichier);
}
/*structure de locataire et sa liste simplement chainee*/
typedef struct locataire
{
	unsigned short id_vehicule;
	char CIN[20];
	unsigned short id_Operation;
} locataire;
typedef struct locataireList
{
	locataire p;
	struct locataireList *suivant;
} locataireList;
locataireList *Lo;
locataireList *InsertEnStructurelocataire(locataireList *L)
{
	short client=0,operation=0,vehicule=0;
	//donnees du vehicule
	unsigned short id_vehicule,code_bureau,capacite_coffre;
	char Permi[3], marque[20], modele[20];
	//donnees du client
	char CIN[20], nom[20], adresse[30], tele_Client[30],Credit_Card[20];
	//donnees du operation
	unsigned short id_Operation;
	char duree[20];
	float prix;
	locataireList *nouveau;
	nouveau = (locataireList *)malloc(sizeof(locataireList));
	//----------remplissage des champs de la structure Locataire---------
	printf("entrer l\'ID de l\'operation: ");
	scanf("%hu", &nouveau->p.id_Operation);
	printf("entrer le CIN de Client: ");
	scanf("%s", nouveau->p.CIN);
	printf("entrer l\'ID de Vehicule: ");
	scanf("%hu", &nouveau->p.id_vehicule);
	nouveau->suivant = NULL;
	p_fichier = fopen("Operation.txt", "a+");
	fseek(p_fichier, 0, SEEK_SET);
	while (!feof(p_fichier)){
		fscanf(p_fichier, "%f\t%s\t%hu\n",&prix, duree, &id_Operation);
		if(id_Operation == nouveau->p.id_Operation){operation=1; goto terminer1;} 
	}
	terminer1:
	fclose(p_fichier);
	p_fichier = fopen("Vehicule.txt", "a+");
	fseek(p_fichier, 0, SEEK_SET);
	while (!feof(p_fichier)){
		fscanf(p_fichier, "%hu\t%s\t%s\t%s\t%hu\t%hu\n",&capacite_coffre, modele, marque, Permi, &code_bureau, &id_vehicule);
		if(id_vehicule == nouveau->p.id_vehicule){vehicule=1; goto terminer2;} 
	}
	terminer2:
	fclose(p_fichier);
	p_fichier = fopen("Client.txt", "a+");
	fseek(p_fichier, 0, SEEK_SET);
	while (!feof(p_fichier)){
		fscanf(p_fichier, "%s\t%s\t%s\t%s\t%s\n", nom, &tele_Client, adresse, Credit_Card, CIN);
		if(strcmp(CIN,nouveau->p.CIN)==0){client=1; goto terminer3;} 
	}
	terminer3:
	fclose(p_fichier);
	if((operation==1)&&(vehicule==1)&&(client==1)){
	if (L == NULL)
		return nouveau;
		/*rechercher le dernier element de la liste */
	else{
		locataireList *temp2=L;
		while(temp2!=NULL){
			if(temp2->p.id_Operation!=nouveau->p.id_Operation) 
				temp2 = temp2->suivant;
			else return L;
			}
		locataireList *temp;
		temp = L;
		while (temp->suivant != NULL)
		{
			temp = temp->suivant;
		}
		/*relier le dernier element de la liste au nouveau element*/
		temp->suivant = nouveau;
		}
	}
	if(operation==0)printf("ce Id d\'operation n\'existe pas\n");
	if(vehicule==0)printf("ce Id de vehicule n\'existe pas\n");
	if(client==0)printf("ce CIN de client n\'existe pas\n");
	return L;
}
locataireList *RechercherEnStructurelocataire(locataireList *L)
{
	unsigned short id_rech;
	locataireList *temp = L;
	printf("entrer l\'ID de l\'Operation pour rechercher: ");
	scanf("%hu", &id_rech);
	//-----parcourir toute la liste----------
	while (temp != NULL)

	{
		if (temp->p.id_Operation ==id_rech)
		{
			return temp;
		}
		temp = temp->suivant;
	}
	return NULL;
}
locataireList *SupprimerSeulDonneeEnStructurelocataire(locataireList *L)
{
	locataireList *tmp = RechercherEnStructurelocataire(L);
	if (L == NULL)
		return NULL;
	else if (L == tmp)
	{
		locataireList *SuppTete = L->suivant;
		free(L);
		return SuppTete;
	}
	if (tmp != NULL)
	{
		locataireList *tmpV = L;
		locataireList *tmpAV = L;
		while (tmpV != tmp)
		{
			tmpAV = tmpV;
			tmpV = tmpV->suivant;
		}
		tmpAV->suivant = tmpV->suivant;
		free(tmpV);
	}
	else printf("ce ID du l\'operation n\'existe pas! \n");
	return L;
}
void AfficheUneDonneeDeStructurelocataire(locataireList *L)
{
	locataireList *tmp = RechercherEnStructurelocataire(L);
	if (L == NULL)
		printf("Liste Vide\n");
	if (tmp == NULL)
		printf("ce ID d\'opeartion n\'existe pas\n");
	else
	{
		printf("Id_Operation\t");
		printf("CIN\t");
		printf("Id_Vehicule\n");
		printf("%hu\t\t", tmp->p.id_Operation);
		printf("%s\t", tmp->p.CIN);
		printf("%hu\n", tmp->p.id_vehicule);
	}
}
void AfficheTousLesDonnesDeStructurelocataire(locataireList *L)
{
	locataireList *tmp = L;
	if (L == NULL)
		printf("Liste Vide\n");
	else
	{
		printf("Id_Operation\t");
		printf("CIN\t");
		printf("Id_Vehicule\n");
		while (tmp != NULL)
		{
			printf("%hu\t\t", tmp->p.id_Operation);
			printf("%s\t", tmp->p.CIN);
			printf("%hu\n", tmp->p.id_vehicule);
			tmp = tmp->suivant;
		}
	}
}
void AjouteAuFichierlocataire(locataireList *L)
{
		FichieLocataireopen();
	unsigned short id_Operation,id_vehicule;
	char CIN[20];
	while (L != NULL)
	{
		fseek(p_fichier, 0, SEEK_SET);
		while (!feof(p_fichier))
		{
			fscanf(p_fichier, "%hu\t%s\t%hu\n",&id_vehicule, CIN, &id_Operation);
			if (L->p.id_Operation==id_Operation)
			{
				goto ancrementer5;
			}
		}
			fseek(p_fichier, 0, SEEK_END);
			fprintf(p_fichier, "%hu\t%s\t%hu\n",L->p.id_vehicule, L->p.CIN, L->p.id_Operation);
		ancrementer5:
		L = L->suivant;
	}
	fclose(p_fichier);
}
void SupprimerDonnesduFichierlocataire()
{
		FichieLocataireopen();
	unsigned short id_vehicule,id_Operation,id_OperationSupprimer;
	char CIN[20];
	fseek(p_fichier, 0, SEEK_SET);
	nvFichier();
	printf("Entrer le code d\'operation a supprimer: ");
	scanf("%hu", &id_OperationSupprimer);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier,"%hu\t%s\t%hu\n",&id_vehicule, CIN, &id_Operation);
		if (id_Operation != id_OperationSupprimer)
			fprintf(p_fichier2,"%hu\t%s\t%hu\n",id_vehicule, CIN, id_Operation);
	}
	fclose(p_fichier);
	remove("Vehicule.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Vehicule.txt");
}
void ModifierDonnesduFichierlocataire()
{
		FichieLocataireopen();
	fseek(p_fichier, 0, SEEK_SET);
	unsigned short id_vehicule,id_vehiculeNv,id_Operation,id_OperationModifier,id_OperationNv;
	char CIN[20],CINnv[20];
	nvFichier();
	printf("Entrer le code d\'operation a modifier: ");
	scanf("%hu", &id_OperationModifier);
	printf("entrer le nouveau code d\'operation: ");
	scanf("%hu", &id_OperationNv);
	printf("entrer le nouveau CIN de client: ");
	scanf("%s", CINnv);
	printf("entrer le nouveau ID du vehicule: ");
	scanf("%hu", &id_vehiculeNv);
	while (!feof(p_fichier))
	{
		fscanf(p_fichier,"%hu\t%s\t%hu\n",&id_vehicule, CIN, &id_Operation);
		if (id_Operation != id_OperationModifier)
			fprintf(p_fichier2,"%hu\t%s\t%hu\n",id_vehicule, CIN, id_Operation);
		else
			fprintf(p_fichier2,"%hu\t%s\t%hu\n",id_vehiculeNv, CINnv, id_OperationNv);
	}
	fclose(p_fichier);
	remove("Vehicule.txt");
	fclose(p_fichier2);
	rename("nvFichier.txt", "Vehicule.txt");
}
void AfficherDonnesduFichierlocataire()
{
	FichieLocataireopen();
	unsigned short id_Operation,id_vehicule;
	char CIN[20];
	fseek(p_fichier, 0, SEEK_SET);
	printf("ID operation\t");
	printf("CIN\t");
	printf("ID vehicule\n");
	while (!feof(p_fichier))
	{
		fscanf(p_fichier,"%hu\t%s\t%hu\n",&id_vehicule, CIN, &id_Operation);
		printf("%hu\t\t", id_Operation);
		printf("%s\t", CIN);
		printf("%hu\n", id_vehicule);
	}
	fclose(p_fichier);
}
void AfficherUneDonnesduFichierlocataire()
{
	FichieLocataireopen();
	unsigned short id_Operation,id_OperationRecherche,id_vehicule;
	char CIN[20];
	fseek(p_fichier, 0, SEEK_SET);
	printf("Entrer ID d\'operation a Afficher: ");
	scanf("%hu", &id_OperationRecherche);
	while (!feof(p_fichier)){
		fscanf(p_fichier,"%hu\t%s\t%hu\n",&id_vehicule, CIN, &id_Operation);
			if (id_Operation == id_OperationRecherche){
				printf("ID operation\t");
				printf("CIN\t");
				printf("ID vehicule\n");
				printf("%hu\t\t", id_Operation);
				printf("%s\t", CIN);
				printf("%hu\n", id_vehicule);
				fclose(p_fichier);
				return;
			}
			}
			 printf("cette Operation n\'existe pas\n");fclose(p_fichier);			
	
}
//-------------Les fonctions pour la gestion du programme-----------------------
void terminerOuNon(bureauList *L,clientList *D,operationList *A,vehiculeList *H,locataireList *K)
{
	printf("1--->Pour terminer l\'edition du fichier\n");
	printf("2--->Pour reediter le fichier selectionne\n");
	printf("entrez votre choix: ");
	scanf("%s", &c);
	switch (c)
	{
	case '1':
		x = 1;
		/* test si la structure bureau est vide sortir sans ajoutement*/
		if (bonStructure == 1){
			if (L != NULL)
			AjouteAuFichierBureau(L);		
			else return;
			}
		/* test si la structure vehicule est vide sortir sans ajoutement*/
		else if (bonStructure == 2){
			if (H == NULL)
				return;
			/* si non copie les donnees d'une liste chainees vers le fichier correspondent*/	
			else AjouteAuFichiervehicule(H);	
			}
		/* test si la structure client est vide sortir sans ajoutement*/
		else if (bonStructure == 3){
			if (D == NULL)
				return;
			/* si non copie les donnees d'une liste chainees vers le fichier correspondent*/	
			else AjouteAuFichierclient(D);	
			}
		/* test si la structure operation est vide sortir sans ajoutement*/
		else if (bonStructure == 4){
			if (A == NULL)
				return;
			/* si non copie les donnees d'une liste chainees vers le fichier correspondent*/	
			else AjouteAuFichieroperation(A);	
			}
		/* test si la structure locataire est vide sortir sans ajoutement*/
		else {
			if (K == NULL)
				return;
			/* si non copie les donnees d'une liste chainees vers le fichier correspondent*/	
			else AjouteAuFichierlocataire(Lo);	
			}
		break;
	case '2':
		
		break;
	default:
		printf("error! choix faulse\n ");
		terminerOuNon(L,D,A,H,K);
	}
}
void openFile()
{
	printf("======================Menu======================\n");
	printf("\t 1--->pour travailler avec le fichier Bureau\n");
	printf("\t 2--->pour travailler avec le fichier Vehicule\n");
	printf("\t 3--->pour travailler avec le fichier Client\n");
	printf("\t 4--->pour travailler avec le fichier Operation\n");
	printf("\t 5--->pour travailler avec le fichier Locataire\n");
	printf("*************entrez votre choix:******** ");
	scanf("%s", &c);
	switch (c)
	{
	case '1':
		bonStructure = 1;
		break;
	case '2':
		bonStructure = 2;
		break;
	case '3':
		bonStructure = 3;
		break;
	case '4':
		bonStructure = 4;
		break;
	case '5':
		bonStructure = 5;
		break;
	default:
		printf("error! choix faulse \n");
		openFile();
	}
}
void editerAutreFichierOuNon()
{
	printf("1--->Pour sortir de programme\n");
	printf("2--->Pour selectionne un autre fichier\n");
	printf("entrez votre choix: ");
	scanf("%s", &c);
	switch (c)
	{
	case '1':
		i = 1;
		break;
	case '2':
		break;
	default:
		printf("error! choix faulse \n");
		editerAutreFichierOuNon();
	}
}
int main()
{
	B = (bureauList *)malloc(sizeof(bureauList));
	B = NULL;
	C = (clientList *)malloc(sizeof(clientList));
	C = NULL;
	O = (operationList *)malloc(sizeof(operationList));
	O = NULL;
	V = (vehiculeList *)malloc(sizeof(vehiculeList));
	V = NULL;
	Lo = (locataireList *)malloc(sizeof(locataireList));
	Lo = NULL;
	/*repeter le programme si l'utilisateur veut editer une autre structure */
	while (i == 0)
	{
		x = 0;
		/*ouvrir le fichier du structure choisi*/
		openFile();
		/*demander à l'utilisateur de terminer l'edition du fichier ou non
	  apres chaque edition ou affichage*/
		while (x == 0)
		{
		/*donne le choix a l'utilisateur pour gerer le fichier*/
		jump:
			printf("\t 1--------->Pour Ajouter des donnes au structure\n");
			printf("\t 2--------->Pour Supprimer une donnes du structure\n");
			printf("\t 3--------->Pour Afficher tous les donnes du struture\n");
			printf("\t 4--------->Pour Afficher une donnee  du structure\n");
			printf("\t 5--------->Pour Supprimer des donnes du fichier\n");
			printf("\t 6--------->Pour Modifier des donnes du fichier\n");
			printf("\t 7--------->Pour Afficher tous les donnes du fichier\n");
			printf("\t 8--------->Pour Afficher une donnee du fichier\n");
			printf("*************entrez votre choix:********** ");
			scanf("%s", &c);
			switch (c)
			{
			case '1':
				/* travail avec structure bureau */
				if (bonStructure == 1)
					B = InsertEnStructureBureau(B);
				/* travail avec structure vehicule */	
				else if (bonStructure == 2)
					V = InsertEnStructurevehicule(V);
				/* travail avec structure Client */	
				else if (bonStructure == 3)
					C = InsertEnStructureclient(C);
				/* travail avec structure operation */	
				else if (bonStructure == 4)
					O = InsertEnStructureoperation(O);
				/* travail avec structure locataire */
				else Lo = InsertEnStructurelocataire(Lo);	
				break;
			case '2':
				/* travail avec structure bureau */
				if (bonStructure == 1)
					 B = SupprimerSeulDonneeEnStructureBureau(B);
				/* travail avec structure vehicule */
				else if (bonStructure == 2)
					 V = SupprimerSeulDonneeEnStructurevehicule(V);
				/* travail avec structure Client */	
				else if (bonStructure == 3)
					 C = SupprimerSeulDonneeEnStructureclient(C);
				/* travail avec structure operation */	
				else if (bonStructure == 4)
					O = SupprimerSeulDonneeEnStructureoperation(O);
				/* travail avec structure locataire */
				else Lo = SupprimerSeulDonneeEnStructurelocataire(Lo);
				break;
			case '3':
				/* travail avec structure bureau */
				if (bonStructure == 1)
					AfficheTousLesDonnesDeStructureBureau(B);
				/* travail avec structure vehicule */
				else if (bonStructure == 2)
					AfficheTousLesDonnesDeStructurevehicule(V);
				/* travail avec structure client */
				else if (bonStructure == 3)
					AfficheTousLesDonnesDeStructureclient(C);
				/* travail avec structure operation */
				else if (bonStructure == 4)
					AfficheTousLesDonnesDeStructureoperation(O);
				/* travail avec structure locataire */
				else AfficheTousLesDonnesDeStructurelocataire(Lo);
				break;
			case '4':
				/* travail avec structure bureau */
				if (bonStructure == 1)
					AfficheUneDonneeDeStructureBureau(B);
				/* travail avec structure vehicule */
				else if (bonStructure == 2)
					AfficheUneDonneeDeStructurevehicule(V);
				/* travail avec structure client */
				else if (bonStructure == 3)
					AfficheUneDonneeDeStructureclient(C);
				/* travail avec structure operation */
				else if (bonStructure == 4)
					AfficheUneDonneeDeStructureoperation(O);
				/* travail avec structure locataire */
				else AfficheUneDonneeDeStructurelocataire(Lo);
				break;
			case '5':
				/* travail avec structure bureau */
				if (bonStructure == 1)
					SupprimerDonnesduFichierBureau();
				/* travail avec structure vehicule */
				else if (bonStructure == 2)
					SupprimerDonnesduFichiervehicule();
				/* travail avec structure client */
				else if (bonStructure == 3)
					SupprimerDonnesduFichierclient();
				/* travail avec structure operation */	
				else if (bonStructure == 4)
					SupprimerDonnesduFichieroperation();
				/* travail avec structure locataire */
				else SupprimerDonnesduFichierlocataire();
				break;
			case '6':
				/* travail avec structure bureau */
				if (bonStructure == 1)
					ModifierDonnesduFichierBureau();
				/* travail avec structure vehicule */
				else if (bonStructure == 2)
					ModifierDonnesduFichiervehicule();
				/* travail avec structure client */
				else if (bonStructure == 3)
					ModifierDonnesduFichierclient();
				/* travail avec structure operation */
				else if (bonStructure == 4)
					ModifierDonnesduFichieroperation();
				/* travail avec structure locataire */
				else ModifierDonnesduFichierlocataire();
				break;
			case '7':
				/* travail avec structure bureau */
				if (bonStructure == 1)
					AfficherToutDonnesduFichierBureau();
				/* travail avec structure vehicule */
				else if (bonStructure == 2)
					AfficherDonnesduFichiervehicule();
				/* travail avec structure client */
				else if (bonStructure == 3)
					AfficherDonnesduFichierclient();
				/* travail avec structure operation */
				else if (bonStructure == 4)
					AfficherDonnesduFichieroperation();
				/* travail avec structure locataire */
				else AfficherDonnesduFichierlocataire();
				break;
			case '8':
				/* travail avec structure bureau */
				if (bonStructure == 1)
					AfficherUneDonnesduFichierBureau();
				/* travail avec structure vehicule */
				else if (bonStructure == 2)
					AfficherUneDonnesduFichiervehicule();
				/* travail avec structure client */
				else if (bonStructure == 3)
					AfficherUneDonnesduFichierclient();
				/* travail avec structure operation */
				else if (bonStructure == 4)
					AfficherUneDonnesduFichieroperation();
				/* travail avec structure locataire */
				else AfficherUneDonnesduFichierlocataire();
				break;	
			default:
				printf("error! choix faulse \n");
				goto jump;
			}
			terminerOuNon(B,C,O,V,Lo);
		}

		/*fonction pour editer un autre fichier*/
		editerAutreFichierOuNon();
	}
}

