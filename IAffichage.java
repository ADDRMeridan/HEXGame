
/*----------------------------------------------
 *Interface Java
 *Auteur : LENOIR Matthieu
 *Date de modification : 19/05/2017
 *---------------------------------------------*/
public interface IAffichage {
	//permet d'afficher le menu
	public void AfficherMenu(char joueur,int tour);
	//permet de faire la saisie d'un coup et potentiellement l'affichage du menu et du plateau
	public void SaisieTour(char joueur,int tour);
	//permet d'afficher le plateau
	public void AfficherPlateau();
	//permet de mettre à jour le plateau après un coup pae exemple
	public void MajPlateau();
}
