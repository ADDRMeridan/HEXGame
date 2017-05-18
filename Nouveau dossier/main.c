#include "GestionJeu.h"
int main (){
	nouvellePartie('o',2);
	printf("nbtour: %d\n",nbTourPartie());
	if(ContreOrdinateur()) printf("Contre ordi\n");
	else printf("Contre joueur\n");
	coupValide(1,1,'o');
	printf("nbtour: %d\n",nbTourPartie());
	coupValide(1,2,'o');
	printf("nbtour: %d\n",nbTourPartie());
	coupValide(1,2,'x');
	printf("nbtour: %d\n",nbTourPartie());
	if(gagnant('o')) printf(" o gagne !\n");
	annuleCoup();
	printf("nbtour: %d\n",nbTourPartie());
	if(gagnant('o')) printf(" o gagne !\n");
	SauvegarderPartie("abc");
	supprPartie();
	nouvellePartie('o',3);
	printf("nbtour: %d\n",nbTourPartie());
	if(ContreOrdinateur()) printf("Contre ordi\n");
	else printf("Contre joueur\n");
	coupValide(1,1,'o');
	printf("nbtour: %d\n",nbTourPartie());
	coupValide(1,2,'o');
	printf("nbtour: %d\n",nbTourPartie());
	coupValide(1,2,'x');
	printf("nbtour: %d\n",nbTourPartie());
	if(gagnant('o')) printf(" o gagne !\n");
	annuleCoup();
	printf("nbtour: %d\n",nbTourPartie());
	if(gagnant('o')) printf(" o gagne !\n");
	ChargerPartie("abc");
	coupValide(1,2,'o');
	printf("nbtour: %d\n",nbTourPartie());
	if(gagnant('o')) printf(" o gagne !\n");
	return 0;
}
