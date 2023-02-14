#include "mot.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include <string.h>
#include <math.h>
#define TAILLE_MAX 35
char colorizedInterm[255];
int bluePos[2];
void blue(char *tmp,char c){
    char buffer[2];
    buffer[0]=c;
    buffer[1]='\0';
    strcpy(tmp,"");
    strcat(tmp, "<span foreground=\"#0000FF\">");
    strcat(tmp,buffer);
    strcat(tmp, "</span>");
}
void green(char *tmp, char c)
{
    char buffer[2];
    buffer[0] = c;
    buffer[1] = '\0';
    strcpy(tmp, "");
    strcat(tmp, "<span foreground=\"#00FFFF\">");
    strcat(tmp, buffer);
    strcat(tmp, "</span>");
}
void nouveau_mot(char mot_sec[])
{
    int graine = time(NULL);
    srand(graine);
    int nb_alea, j = 0, c;
    FILE *fichier = NULL;
    fichier = fopen("liste.txt", "r");

    if (fichier != NULL)
    {
        nb_alea = rand() % 78855;
        rewind(fichier);

        while ((c = fgetc(fichier)) != EOF)
        {
            if (c == '\n')
            {
                j++;
                if (j == nb_alea)
                {
                    fgets(mot_sec, TAILLE_MAX, fichier);
                }
            }
        }
        mot_sec[strlen(mot_sec) - 1] = 0;
    }

    else
        printf("Erreur d'ouverture de fichier\n");
}
void init_mot_devine(char mot[], int taille)
{
    int i = 0;
    for (i = 0; i < (taille); i++)
    {
        mot[i] = '_';
    }
    mot[taille] = '\0';
}

void existIn(char *motSoumis, char *motCached, char *motCherche, char *colorized, int tailleMot)
{
    int i=0;
    strcpy(colorized,"");
    char tmp[255];
    char tmpInterm[255];
    char tmpBlue[255];
    for(i=0;i<tailleMot;i++){
        char buffer[2];
        buffer[0]=motSoumis[i];
        buffer[1]='\0';
        if(motCached[i]!='_'){
            blue(tmpBlue,motCached[i]);
            strcat(colorized,tmpBlue);
            strcpy(tmpBlue,"");
        }
        if(i!=bluePos[0] && i!=bluePos[1]){
            if(motSoumis[i]==motCherche[i]){
                // motCached[i]=motCherche[i];
                green(tmp,motSoumis[i]);
                strcat(colorized,tmp);
                strcpy(tmp,"");
            }else{
                strcat(colorized,"_");
            }
        }
    }
    printf("%s",colorized);
}
void addAt(char* mot, int nombreEssai,int position){
    char buffer[2];
    sprintf(buffer,"%d",nombreEssai);
    mot[position]=buffer[0];
}

void reveal(char* motCache,char* motCherche,char* colorized){
    int graine = time(NULL);
    srand(graine);
    char tmp[255];
    int pos1 = (rand())%strlen(motCache);
    int pos2 = (rand()) % strlen(motCache);
    while(pos1==pos2){
        pos2 = (rand()) % strlen(motCache);
    }
    bluePos[0]=pos1;
    bluePos[1]=pos2;
    motCache[pos1]=motCherche[pos1];
    motCache[pos2] = motCherche[pos2];
    strcpy(colorized,"");
    for(int i=0;i<strlen(motCache);i++){
    char curr[2];
    curr[0]=motCache[i];
    curr[1]='\0';
        if(i==bluePos[0] || i==bluePos[1]){
            blue(tmp, motCache[i]);
                strcat(colorized,tmp);
        }else{
            strcat(colorized,curr);
        }
    }
    // int tab[]={pos1,pos2};
    // colorizeBlue(motCache, colorized, colorizedInterm, tab, 2);
}
void spacing(char* motCash,int taille){
    char tmp[taille];
    strcpy(tmp,motCash);
    for(int i=0;i<((taille*2)-1);i=i+2){
        motCash[i]=tmp[i];
        motCash[i+1]=' ';
    }
}