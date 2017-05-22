package main;


import java.util.InputMismatchException;
import java.util.Scanner;

import main.gestionJeu.GestionJeu;

public class JeuHex {
	private IAffichage i;
	char courant;
	public JeuHex(){
	}
	public void Partie(){
		boolean Abandon=false;
		i=new Interface();
		this.courant=i.getPremier();
		do{
			System.out.println("Au joueur "+courant+"de jouer ");
			if(i.SaisieTour(this.courant)){
				Abandon=this.AfficherMenu(this.courant);
				if(Abandon && this.courant=='x') {
					System.out.println("Le joueur jouant les Noirs à abandonner !");
					System.out.println("Le joueur jouant les Blancs à gagner !");
				}
				else if(Abandon && this.courant=='o'){
					System.out.println("Le joueur jouant les Blancs à abandonner !");
					System.out.println("Le joueur jouant les Noirs à gagner !");
				}
			}
			i.MajPlateau();
			i.AfficherPlateau();
			this.ProchainJoueur();
		}while(!GestionJeu.gagnant('o') && !GestionJeu.gagnant('x') && !Abandon);
		if(GestionJeu.gagnant('x')) System.out.println("Le joueur jouant les Noir à gagner !");
		else if(GestionJeu.gagnant('o')) System.out.println("Le joueur jouant les Blancs à gagner !");
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
			case 'A':
				if (GestionJeu.annuleCoup()) System.out.println("Dernier tour annuler");
				else {
					System.out.println("Impossible d'annuler le dernier tour car il n'y en à pas !");
					System.out.println("Retour au jeu");
					this.ProchainJoueur();
				}
				break;
			case 'N':
				i=new Interface();
				this.courant=i.getPremier();
				this.ProchainJoueur();
				break;
			case 'F':
				return true;
			case 'S':
				break;
			case 'C':
				break;
			default:
				System.out.println("Retour au jeu");
				this.ProchainJoueur();
		}
		return false;
	}
	public void ProchainJoueur(){
		if(courant=='x') courant='o';
		else courant='x';
	}
	
	public boolean accederMenu(){
	boolean isEntier;
	int y=0;
	do{
		isEntier = true;
		System.out.println("Entrez -1 pour accéder au menu sinon entrer n'importe quel autre chiffre");
	  	Scanner s = new Scanner(System.in);
	  	try{
	  		y = s.nextInt();
	  	} catch (InputMismatchException e) 
	  	{
	  		System.out.println("La valeur saisie n'est pas un entier");
	  		isEntier = false;
	  	}
	} while (isEntier != true);
	if(y==-1) return true;
	else return false;
	}
}
