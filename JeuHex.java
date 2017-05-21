import java.util.Scanner;

public class JeuHex {
	private IAffichage i;
	public JeuHex(){
	}
	public void Partie(){
		boolean Abandon=false;
		i=new Interface();
		do{
			if(i.SaisieTour(this.ProchainJoueur())==1){
				char prochain=ProchainJoueur();
				Abandon=this.AfficherMenu(prochain);
				if(Abandon && prochain=='x') {
					System.out.println("Le joueur jouant les Noirs à abandonner !");
					System.out.println("Le joueur jouant les Blancs à gagner !");
				}
				else if(Abandon && prochain=='o'){
					System.out.println("Le joueur jouant les Blancs à abandonner !");
					System.out.println("Le joueur jouant les Noirs à gagner !");
				}
			}
		}while(!gestionJeu.GestionJeu.gagnant('o') && !gestionJeu.GestionJeu.gagnant('x') && !Abandon);
		if(gestionJeu.GestionJeu.gagnant('x')) System.out.println("Le joueur jouant les Noir à gagner !");
		else if(gestionJeu.GestionJeu.gagnant('o')) System.out.println("Le joueur jouant les Blancs à gagner !");
	}
	public boolean AfficherMenu(char joueur){
		Scanner sc=new Scanner(System.in);
		System.out.println("Tapez A pour annuler votre dernier coup");
		System.out.println("Tapez N pour lancer une nouvelle partie");
		System.out.println("Tapez F pour declarer votre forfait");
		System.out.println("Tapez S pour sauvegarder la partie");
		System.out.println("Tapez C pour charger la partie");
		System.out.println("Tapez R pour retourner au jeu");
		String str=sc.nextLine();
		char carac=str.charAt(0);
		switch (carac){
			case 'A' | 'a':
				if (gestionJeu.GestionJeu.annuleCoup()) System.out.println("Dernier tour annuler");
				else System.out.println("Impossible d'annuler le dernier tour car il n'y en à pas !");
				System.out.println("Retour au jeu");
				i.SaisieTour(this.ProchainJoueur());
				break;
			case 'N' | 'n':
				i=new Interface();
				break;
			case 'F' | 'f':
				return true;
			case 'S' | 's':
				break;
			case 'C' | 'c':
				break;
			default:
				System.out.println("Retour au jeu");
				i.SaisieTour(joueur);
		}
		return false;
	}
	public char ProchainJoueur(){
		if(gestionJeu.GestionJeu.nbTourPartie()<2) return i.getPremier();
		else return gestionJeu.GestionJeu.ProchainJoueur();
	}
}
