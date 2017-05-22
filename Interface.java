package main;


import main.gestionJeu.GestionJeu;

//Ceci importe la classe Scanner du package java.util
//Ceci importe toutes les classes du package java.util
import java.util.*;

public class Interface implements IAffichage{
	private Plateau plateau;
	private char Premier;
	public Interface(){
		Scanner sc=new Scanner(System.in);
		System.out.println("Voulez-vous saisir la taille du Plateau ? (o/n)");
		String str=sc.nextLine();
		char carac=str.charAt(0);
		int str2=11;
		if(carac=='o' || carac=='O') {
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
		if(j=='B' || j=='b'){
			j='o';
		}
		else
			j='x';
		GestionJeu.nouvellePartie(j,str2);
		Premier=j;
	}
	public char getPremier(){
		return this.Premier;
	}
	public char ProchainJoueur(){
		if(GestionJeu.nbTourPartie()<2) return this.getPremier();
		else return GestionJeu.ProchainJoueur();
	}

	
	public boolean SaisieTour(char joueur){
		System.out.println("Tour "+GestionJeu.nbTourPartie());
		System.out.println("Veuillez saisir la colonne: ");
		System.out.println("Ou entrez -1 pour accéder au menu");
		int x=0;
		int y=0;
		boolean isEntier = true;
		do {
			isEntier = true;
		  	Scanner s = new Scanner(System.in);
		  	try{
		  		x = s.nextInt();
		  	} catch (InputMismatchException e) 
		  	{
		  		System.out.println("La valeur saisie n'est pas un entier");
		  		isEntier = false;
		  	}
		} while (isEntier != true);
		if(x==-1){
			return true;
		}
		else{
				while(x<1 || x>this.plateau.getTaille()){
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
				}
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
			if(!GestionJeu.coupValide(x, y, joueur)){
				do{
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
				}while(!GestionJeu.coupValide(x, y, joueur));
			}
		}
		return false;
	}
	
	public Plateau getPlateau(){
		return this.plateau;
	}
	
	public void AfficherPlateau(){
		this.plateau.getPlateau();
	}
	
	public void MajPlateau(){
		char joueur;
		for(int i=1;i<=plateau.getTaille();i++){
			for(int j=1;j<=plateau.getTaille();j++){
				joueur=GestionJeu.couleurCase(i,j);
				this.plateau.getLignes(j-1).getLigne(i-1).setCouleur(joueur);
			}
		}
	}
}
