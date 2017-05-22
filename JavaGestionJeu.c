#include "GestionJeu.h"
#include "JavaGestionJeu.h"

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    nouvellePartie
 * Signature: (CI)V
 */
JNIEXPORT void JNICALL 
Java_gestionJeu_GestionJeu_nouvellePartie(JNIEnv *env, jclass cl, jchar couleur, jint taille){
  initPlateau(couleur,taille);
  g_initialisation(taille);
}
/*
 * Class:     gestionJeu_GestionJeu
 * Method:    couleurCase
 * Signature: (II)C
 */
JNIEXPORT jchar JNICALL 
Java_gestionJeu_GestionJeu_couleurCase(JNIEnv *env, jclass cl, jint x, jint y){
  return couleurCellule(x,y);
}
/*
 * Class:     gestionJeu_GestionJeu
 * Method:    coupValide
 * Signature: (IIC)Z
 */
JNIEXPORT jboolean JNICALL 
Java_gestionJeu_GestionJeu_coupValide(JNIEnv *env, jclass cl, jint x, jint y, jchar couleur){
  if(couleurCellule(x,y)!='.') return false;
  else{
    int c;
    if(couleur=='x') c=0;
    else c=1;
    ajoutCoup(couleur,x,y);
    g_ajout_hexagone(x-1,y-1,c);
    return true;
  }
}
/*
 * Class:     gestionJeu_GestionJeu
 * Method:    gagnant
 * Signature: (C)Z
 */
JNIEXPORT jboolean JNICALL 
Java_gestionJeu_GestionJeu_gagnant(JNIEnv *env, jclass cl, jchar couleur){
  int c;
  if(couleur=='x') c=0;
  else c=1;
  return g_chaine_gagnante(c);
}
/*
 * Class:     gestionJeu_GestionJeu
 * Method:    supprPartie
 * Signature: ()V
 */
JNIEXPORT void JNICALL 
Java_gestionJeu_GestionJeu_supprPartie(JNIEnv *env, jclass cl){
  supprPlateau();
  g_suppression();
}
/*
 * Class:     gestionJeu_GestionJeu
 * Method:    annuleCoup
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL 
Java_gestionJeu_GestionJeu_annuleCoup(JNIEnv *env, jclass cl){
  int x;
  int y;
  bool possible=dernierCoup(&x,&y);
  if(!possible) return false;
  annulerDernierCoup();
  g_supprime_hexagone(x-1,y-1);
  return true;
}
/*
 * Class:     gestionJeu_GestionJeu
 * Method:    nbTourPartie
 * Signature: ()I
 */
JNIEXPORT jint JNICALL 
Java_gestionJeu_GestionJeu_nbTourPartie(JNIEnv *env, jclass cl){
  return nbTour();
}
/*
 * Class:     gestionJeu_GestionJeu
 * Method:    ContreOrdinateur
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL 
Java_gestionJeu_GestionJeu_ContreOrdinateur(JNIEnv *env, jclass cl){
  return contreOrdinateur();
}

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    SauvegarderPartie
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL 
Java_gestionJeu_GestionJeu_SauvegarderPartie(JNIEnv *env, jclass cl, jstring js){
      
    /* */
    const char *nom = (*env) -> GetStringUTFChars(env, js, 0);
    
    SauvegarderPartie((char*)nom);
   
}

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    ChargerPartie
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL 
Java_gestionJeu_GestionJeu_ChargerPartie(JNIEnv *env, jclass cl, jstring js){
    
    /**/
    const char *nom = (*env) -> GetStringUTFChars(env, js, 0);
    
    if(!chargerPartie((char*)nom)) return false;
	int nbcoup=nbCoup();
	int x;
	int y;
	int couleur;
	if(!g_vide()) g_suppression();
	g_initialisation(getDim());
	for(int i=0; i<nbcoup;i++){
		getCoup(i,&x,&y,&couleur);
		g_ajout_hexagone(x-1,y-1,couleur);
	}
	return true;
}



/*
 * Class:     gestionJeu_GestionJeu
 * Method:    ProchainJoueur
 * Signature: ()C
 */
JNIEXPORT jchar JNICALL 
Java_gestionJeu_GestionJeu_ProchainJoueur(JNIEnv *env, jclass cl){
  int x;
  int y;
  int couleur;
  getCoup(nbCoup()-1,&x,&y,&couleur);
  if(couleur) return 'x';
  else return 'o';
}
