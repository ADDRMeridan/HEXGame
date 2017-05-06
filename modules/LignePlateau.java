
public class LignePlateau {
	private int taille;
	private CasePlateau ligne[];
	public LignePlateau(int taille){
		this.taille=taille;
		ligne=new CasePlateau[this.taille];
		for(int i=0;i<this.taille;i++)
			ligne[i]=new CasePlateau();
	}
	public String getLigne(){
		String ligne=" ";
		for(int i=0;i<this.taille;i++)
			ligne=ligne+this.ligne[i].getCouleur()+" ";
		return ligne;
	}
	
	public CasePlateau getLigne(int i){
		return ligne[i];
	}
}
