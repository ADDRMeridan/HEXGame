/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class gestionJeu_GestionJeu */

#ifndef _Included_gestionJeu_GestionJeu
#define _Included_gestionJeu_GestionJeu
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     gestionJeu_GestionJeu
 * Method:    nouvellePartie
 * Signature: (CI)V
 */
JNIEXPORT void JNICALL Java_gestionJeu_GestionJeu_nouvellePartie
  (JNIEnv *, jclass, jchar, jint);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    couleurCase
 * Signature: (II)C
 */
JNIEXPORT jchar JNICALL Java_gestionJeu_GestionJeu_couleurCase
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    coupValide
 * Signature: (IIC)Z
 */
JNIEXPORT jboolean JNICALL Java_gestionJeu_GestionJeu_coupValide
  (JNIEnv *, jclass, jint, jint, jchar);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    gagnant
 * Signature: (C)Z
 */
JNIEXPORT jboolean JNICALL Java_gestionJeu_GestionJeu_gagnant
  (JNIEnv *, jclass, jchar);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    supprPartie
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_gestionJeu_GestionJeu_supprPartie
  (JNIEnv *, jclass);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    annuleCoup
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_gestionJeu_GestionJeu_annuleCoup
  (JNIEnv *, jclass);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    nbTourPartie
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_gestionJeu_GestionJeu_nbTourPartie
  (JNIEnv *, jclass);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    ContreOrdinateur
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_gestionJeu_GestionJeu_ContreOrdinateur
  (JNIEnv *, jclass);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    SauvegarderPartie
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gestionJeu_GestionJeu_SauvegarderPartie
  (JNIEnv *, jclass, jstring);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    ChargerPartie
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_gestionJeu_GestionJeu_ChargerPartie
  (JNIEnv *, jclass, jstring);

/*
 * Class:     gestionJeu_GestionJeu
 * Method:    ProchainJoueur
 * Signature: ()C
 */
JNIEXPORT jchar JNICALL Java_gestionJeu_GestionJeu_ProchainJoueur
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
