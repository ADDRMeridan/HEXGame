package main;

public class CasePlateau {
	private char couleur;
	private int numColonne;
	public CasePlateau(int numColonne){
		this.numColonne=numColonne;
		this.couleur='.';
	}
	public char getCouleur() {
		return couleur;
	}
	public void setCouleur(char couleur) {
		this.couleur = couleur;
	}
	
	int getNumColonne(){
		return this.numColonne;
	}
}
