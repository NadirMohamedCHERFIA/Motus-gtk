#include <gtk/gtk.h>
#ifndef __CONTAINER_H__
#define __CONTAINER_H__
struct _MainWindow
{
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pEntry;
    GtkWidget *pButton[10];
    GtkWidget *pLabel[10];
    GtkWidget *pLabelDev[7];
    GtkWidget *dialog;
};
typedef struct _MainWindow MainWindow;
#endif