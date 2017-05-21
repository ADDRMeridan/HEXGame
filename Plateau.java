package main;



public class Plateau {
	private int taille;
	private LignePlateau lignes[];
	
	public int getTaille(){
		return this.taille;
	}
	
	public Plateau (){
		this.taille=11;
		lignes=new LignePlateau[this.taille];
		for(int i=0;i<this.taille;i++)
			lignes[i]=new LignePlateau(this.taille,i);
	}
	
	public Plateau (int taille){
		this.taille=taille;
		lignes=new LignePlateau[this.taille];
		for(int i=0;i<this.taille;i++)
			lignes[i]=new LignePlateau(this.taille,i);
	}
	public void AfficherHautDuPlateau() {
		for(int i=0;i<this.taille;i++)
			System.out.print("W ");
		System.out.println("W/B");
	}
	
	public void AfficherBasDuPlateau(){
		for(int i=0;i<=this.taille;i++)
			System.out.print(" ");
		System.out.print("B/W");
		for(int i=0;i<this.taille;i++)
			System.out.print(" W");
		System.out.println("");
	}
	
	public void AfficherLignesPlateau(){
		String decalage=" ";
		for(int i=0;i<this.taille;i++){
			System.out.println(decalage+"B"+this.lignes[i].getLigne()+"B");
			decalage=decalage+" ";
		}
	}
	
	public void getPlateau(){
		this.AfficherHautDuPlateau();
		this.AfficherLignesPlateau();
		this.AfficherBasDuPlateau();
	}

	public LignePlateau getLignes(int i) {
		return lignes[i];
	}

	
}
