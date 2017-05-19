//Ceci importe la classe Scanner du package java.util
import java.util.Scanner; 
//Ceci importe toutes les classes du package java.util
import java.util.*;

public class Interface implements IAffichage{
	private Plateau plateau;
	private Menu menu;
	public Interface(){
		Scanner sc=new Scanner(System.in);
		System.out.println("Voulez-vous saisir la taille du Plateau ? (o/n)");
		String str=sc.nextLine();
		char carac=str.charAt(0);
		if(carac=='o' || carac=='O') {
			int str2=11;
			boolean isEntier = true;
		  	Scanner s = new Scanner(System.in);
			do {
				do {
					isEntier = true;
					System.out.print("Veuillez saisir la taille du plateau :");

				  	try{
				  		str2 = s.nextInt();
				  	} catch (InputMismatchException e) 
				  	{
				  		System.out.println("La valeur saisie n'est pas un entier");
				  		isEntier = false;
				  	}
				} while (isEntier != true);
			} while(str2<1 || str2>20);
			this.plateau=new Plateau(str2);
			System.out.println("La taille du plateau à été initialisé à "+str2);
		}
		else{
			this.plateau=new Plateau(11);
			System.out.println("La taille du plateau à été initialisé par défault à 11");
		}
		Scanner c=new Scanner(System.in);
		char j;
		do {
			System.out.println("Qui commence ? Entrez B pour les blancs et N pour les noirs");
			String joueur=c.nextLine();
			j=joueur.charAt(0);
		} while(j!='B'&&j!='b'&&j!='N'&&j!='n');
		this.menu=new Menu();
	}
	public void AfficherMenu(char joueur,int tour){
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
				menu.AnnulerDernierCoup();
				break;
			case 'N' | 'n':
				menu.NouvellePartie();
				break;
			case 'F' | 'f':
				menu.Abandon();
				break;
			case 'S' | 's':
				menu.Sauvegarder();
			case 'C' | 'c':
				menu.Charger();
			default:
				System.out.println("Retour au jeu");
				this.SaisieTour(joueur,tour);
		}
	}
	
	public void SaisieTour(char joueur,int tour){
		System.out.println("Tour "+tour);
		this.plateau.getPlateau();
		System.out.println("Entrez les coordonnées de la case sur laquelle vous voulez jouer: ");
		System.out.println("Ou entrez -1 pour accéder au menu");
		int x=0;
		int y=0;
		boolean isEntier = true;
		do{
			do {
				isEntier = true;
				System.out.print("Veuillez saisir la colonne: ");
			  	Scanner s = new Scanner(System.in);
			  	try{
			  		x = s.nextInt();
			  	} catch (InputMismatchException e) 
			  	{
			  		System.out.println("La valeur saisie n'est pas un entier");
			  		isEntier = false;
			  	}
			} while (isEntier != true);
		} while(x<1 || x>this.plateau.getTaille());
		if(x==-1) this.AfficherMenu(joueur,tour);
		else{
			do{
				do {
					isEntier = true;
					System.out.print("Veuillez saisir la ligne: ");
				  	Scanner s = new Scanner(System.in);
				  	try{
				  		y = s.nextInt();
				  	} catch (InputMismatchException e) 
				  	{
				  		System.out.println("La valeur saisie n'est pas un entier");
				  		isEntier = false;
				  	}
				} while (isEntier != true);
			} while(y<1 || y>this.plateau.getTaille());
			this.plateau.getLignes(y-1).getLigne(x-1).setCouleur(joueur);
		}
	}
	
	public Plateau getPlateau(){
		return this.plateau;
	}
	
	public void AfficherPlateau(){
		this.plateau.getPlateau();
	}
	
	public void MajPlateau(){
		for(int i=1;i<=plateau.getTaille();i++){
			for(int j=1;j<=plateau.getTaille();j++){
				this.plateau.getLignes(j-1).getLigne(i-1).setCouleur('.');
			}
		}
	}
}
