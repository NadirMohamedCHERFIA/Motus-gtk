#include <stdlib.h>
#include <string.h>
#include "mot.h"
#include "container.h"
// #include <gtk/gtk.h>


// #define TO_UTF8 g_locale_to_utf8
#define TAILLE_MOT_DEVINE 255
char motdev[TAILLE_MOT_DEVINE];
char motcash[TAILLE_MOT_DEVINE];
char colorized[TAILLE_MOT_DEVINE];

int nombreEssai=7;
int pos=0;
void OnClick(GtkWidget *pEntry, gpointer data);
void handleNewGame(GtkWidget *pEntry);
char afficher[]="il vous reste : ";
int main(int argc, char **argv)
{
    MainWindow *pApp;
    gtk_init(&argc, &argv);
    nouveau_mot(motdev);
    init_mot_devine(motcash,strlen(motdev));
    strcpy(colorized,motcash);
    reveal(motcash,motdev,colorized);
    // init_mot_devine(motdev,5)
    char BUFFER[2];
    sprintf(BUFFER,"%d",nombreEssai);
    strcat(afficher,BUFFER);
    strcat(afficher," Essais");
    pApp = g_malloc(sizeof(MainWindow));
    pApp -> pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pApp -> pWindow), "Motus");
    gtk_window_set_default_size(GTK_WINDOW(pApp -> pWindow), 600, 600);
    g_signal_connect(G_OBJECT(pApp -> pWindow), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    pApp -> pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pApp -> pWindow), pApp -> pVBox);
    // Label creation
    pApp->pLabel[1]=gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(pApp->pLabel[1]),afficher);
    gtk_box_pack_start(GTK_BOX(pApp->pVBox),pApp->pLabel[1],TRUE,FALSE,0);
    pApp->pLabel[0]=gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(pApp->pLabel[0]),motdev);
    gtk_box_pack_start(GTK_BOX(pApp->pVBox),pApp->pLabel[0],TRUE,FALSE,0);
    for (int i=0;i<7;i++){
        pApp->pLabelDev[i] = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(pApp->pLabelDev[i]),colorized);
        gtk_box_pack_start(GTK_BOX(pApp->pVBox), pApp->pLabelDev[i], TRUE, FALSE, 0);
    }
    // gtk_box_pack_start(GTK_BOX(pApp->pVBox), pApp->pLabelDev, TRUE, FALSE, 0);
    /* Creation du GtkEntry */
    pApp -> pEntry = gtk_entry_new();
    /* Insertion du GtkEntry dans la GtkVBox */
    gtk_box_pack_start(GTK_BOX(pApp -> pVBox), pApp -> pEntry, TRUE, FALSE, 0);
    pApp -> pButton [0]= gtk_button_new_with_label("Commencer nouvelle partie");
    gtk_box_pack_start(GTK_BOX(pApp -> pVBox), pApp -> pButton[0], TRUE, FALSE, 0);
    // ******************************************
    gtk_box_pack_start(GTK_BOX(pApp->pVBox), pApp->pEntry, TRUE, FALSE, 0);
    pApp->pButton[1] = gtk_button_new_with_label("Quitter le jeu");
    gtk_box_pack_start(GTK_BOX(pApp->pVBox), pApp->pLabel[0], TRUE, FALSE, 0);
    pApp->pButton[2] = gtk_button_new_with_label("Soummetre ma proposition");
    gtk_box_pack_start(GTK_BOX(pApp->pVBox),pApp->pButton[2],TRUE,FALSE,0);
    
    gtk_box_pack_start(GTK_BOX(pApp->pVBox), pApp->pButton[1], TRUE, FALSE, 0);
    // pApp -> pLabel = gtk_label_new(NULL);
    /* Connexion du signal "activate" du GtkEntry */
    g_signal_connect(G_OBJECT(pApp -> pEntry), "activate", G_CALLBACK(OnClick),(gpointer)pApp);
    /*Connexion du signal "clicked" du GtkButton * /
    /* La donnee supplementaire est la GtkVBox pVBox */
    g_signal_connect(G_OBJECT(pApp->pButton[0]), "clicked", G_CALLBACK(handleNewGame), (gpointer)pApp);
    g_signal_connect(G_OBJECT(pApp -> pButton[2]), "clicked", G_CALLBACK(OnClick),(gpointer)pApp);
    g_signal_connect(G_OBJECT(pApp->pButton[1]), "clicked", gtk_main_quit, (gpointer)pApp);
    gtk_widget_show_all(pApp -> pWindow);
    gtk_main();
    g_free(pApp);
    return 0;
}
/* Fonction callback execute lors du signal "activate" */
void OnClick(GtkWidget *pEntry, gpointer data)
{
    char *sText;
    MainWindow *pApp;
    pApp = (MainWindow *)data;
    pApp->dialog=NULL;
    sText = gtk_entry_get_text(GTK_ENTRY(pApp -> pEntry));
    // pApp->dialog = gtk_message_dialog_new(GTK_WINDOW(pApp->pWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, sText);
    // gtk_window_set_position(GTK_WINDOW(pApp->dialog), GTK_WIN_POS_CENTER);
    // gtk_window_set_position(GTK_WINDOW(pApp->dialog), GTK_WIN_POS_CENTER);
    // gtk_dialog_run(GTK_DIALOG(pApp->dialog));
    // gtk_widget_destroy(pApp->dialog);
    existIn(sText, motcash, motdev,colorized,strlen(motdev));
    // strcpy(pApp->pLabelDev[pos],motcash);
    gtk_label_set_markup(GTK_LABEL(pApp->pLabelDev[pos]),colorized);
    pos++;
    addAt(afficher,nombreEssai-pos,16);
    gtk_label_set_markup(GTK_LABEL(pApp->pLabel[1]), afficher);
}
void handleNewGame(GtkWidget *pApplica){
    MainWindow *pApp;
    nouveau_mot(motdev);
    init_mot_devine(motcash, strlen(motdev));
    for (int i = 0; i < 7; i++)
    {
        pApp->pLabelDev[i] = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(pApp->pLabelDev[i]), motcash);
        gtk_box_pack_start(GTK_BOX(pApp->pVBox), pApp->pLabelDev[i], TRUE, FALSE, 0);
    }
}