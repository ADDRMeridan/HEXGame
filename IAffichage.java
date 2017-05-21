
/*----------------------------------------------
 *Interface Java
 *Auteur : LENOIR Matthieu
 *Date de modification : 19/05/2017
 *---------------------------------------------*/
public interface IAffichage {
	//permet de faire la saisie d'un coup et potentiellement l'affichage du menu et du plateau
	public void SaisieTour(char joueur);
	//permet d'afficher le plateau
	public void AfficherPlateau();
	//permet de mettre à jour le plateau après un coup pae exemple
	public void MajPlateau();
	//permet de connaitre qui est le premier joueur à devoir jouer
	public char getPremier();
}
