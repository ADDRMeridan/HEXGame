package main;



public class GestionJeu{
	static{
		System.loadLibrary("JavaGestionJeu");
	}
	public static native void nouvellePartie(char couleur, int taille); 
	public static native char couleurCase(int x, int y);
	public static native boolean coupValide(int x, int y, char couleur);
	public static native boolean gagnant(char couleur);
	public static native void supprPartie();
	public static native boolean annuleCoup();
	public static native int nbTourPartie();
	public static native boolean ContreOrdinateur();
	public static native char ProchainJoueur();
}