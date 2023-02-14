#include <stdlib.h>
#include <gtk/gtk.h>

#define FROM_UTF8(string) (g_locale_from_utf8(string, -1, NULL, NULL, NULL))

static void soumission(GtkWidget *wid, gpointer data) // wid est le widget qui déclenche le callback et data des données fournies via le callback
{
    GtkWidget *dialog = NULL;
    GtkWidget *win;

    win = (char *)data; // cast pour récupérer les données
    dialog = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "je suis dans le  callback du bouton1");
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[])
{
    GtkWidget *win;
    GtkWidget *label;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *vbox;
    GtkWidge *vboxquit;

    /* Initialize GTK+ */
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc)gtk_false, NULL);
    gtk_init(&argc, &argv);
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    /* Create the main window */
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(win), 10);
    gtk_window_set_title(GTK_WINDOW(win), "Mot");
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(win), 200, 200);
    gtk_widget_realize(win);
    g_signal_connect(win, "destroy", gtk_main_quit, NULL);

    /* Create a vertical box with buttons */
    vbox = gtk_vbox_new(FALSE, 20); // widgets de différentes tailles et espacées de 20
    gtk_container_add(GTK_CONTAINER(win), vbox);
    vboxquit = gtk_vbox_new(FALSE, 20); // widgets de différentes tailles et espacées de 20
    gtk_container_add(GTK_CONTAINER(win), vboxquit);

    /* Rajout de Labels */

    label1 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label1), "Devinez le mot contenant les lettres suivantes :");
    gtk_box_pack_start(GTK_BOX(vbox), label1, TRUE, FALSE, 0);
    /* Rajout de boutons */
    
    button1 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_INFO);
    gtk_button_set_label(GTK_BUTTON(button1), "Commencer nouvelle partie");
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(soumission), (gpointer)win); // assigner le callback au button1
    gtk_box_pack_start(GTK_BOX(vbox), button1, TRUE, FALSE, 0);

    // button2 = gtk_button_new_from_stock(GTK_STOCK_DIALOG_INFO);
    // gtk_button_set_label(GTK_BUTTON(button2), "Quitter le jeu");
    // // g_signal_connect(G_OBJECT(button1), "destroy", gtk_main_quit, NULL); // assigner le callback au button1
    // gtk_box_pack_start(GTK_BOX(vboxquit), button2, TRUE, FALSE, 0);

    /* Enter the main loop */
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}