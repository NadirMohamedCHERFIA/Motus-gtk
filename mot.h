#ifndef __MOT_H__
#define __MOT_H

void nouveau_mot(char mot_sec[]);
void init_mot_devine(char mot[], int taille);
void existIn(char *motSoumis, char *motCached, char *motCherche,char* colorized, int tailleMot);
void addAt(char *mot, int nombreEssai, int position);
void reveal(char *motCache, char *motCherche,char* colorized);
void spacing(char*motCash,int taille);
// void colorizeGreen(char *motCash, char *colorized, char *colorizedInterm, int *positions, int taille);
void colorizeBlue(char *motCash, char *colorized,char *colorizedInterm, int *positions,int taille);
void blue(char* tmp,char c);
void green(char *tmp, char c);

#endif