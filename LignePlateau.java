
public class LignePlateau {
	private int taille;
	private int numLigne;
	private CasePlateau ligne[];
	public LignePlateau(int taille,int numLigne){
		this.taille=taille;
		this.numLigne=numLigne;
		ligne=new CasePlateau[this.taille];
		for(int i=0;i<this.taille;i++)
			ligne[i]=new CasePlateau(i);
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
	
	int getNumLigne(){
		return this.numLigne;
	}
}
