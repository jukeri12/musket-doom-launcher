
/*
|		MUSKET DOOM LAUNCHER
|
|	A launcher program for Musket Doom.
|
|		Made with GTK+3.0.
|
|
|	Copyright 2015 jukeri12, johuotar
|
|
|	   Licensed under GPL v2.0
|						*/

#include <stdio.h>
#include <gtk/gtk.h>
#include "funcs.h"

/*activate is a signal within GTK+ that is responsible for opening the first window
* in GTK+. In essence, this should be where most of our interface programming is done.
* There are other signals to work with, like startup and open, but we probably don't
* need them. Refer to GTK+ docs for info on this one. 				*/
static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  //version number
  const version = "V0001";

  //create our GtkWidgets
  GtkWidget *window; //window
  //layout grid
  GtkWidget *grid;
  //buttons
  GtkWidget *exitbtn; //exit game
  GtkWidget *joinbtn;  //join game
  GtkWidget *createbtn; //create game
  //textboxes
  GtkEntry *ipaddr_field; //ip address field
  GtkEntry *numplrs_field; //# of players field
  GtkEntry *mapno_field; //# of map to be played
  //labels
  GtkWidget *ipaddr_label;
  GtkWidget *numplrs_label;
  GtkWidget *mapno_label;
  //switches, radio buttons
  GtkWidget *deathmatch_radio;
  GtkWidget *gamemode2_radio;
  GtkWidget *gamemode3_radio;
  
  //create the window
  window = gtk_application_window_new (app);
  //set window title
  gtk_window_set_title (GTK_WINDOW (window), "Launcher");

  //create the grid
  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);

  //create buttons
  //join
  joinbtn = gtk_button_new_with_label ("Join Game");
  g_signal_connect(joinbtn, "clicked", G_CALLBACK (run_game), NULL);
  gtk_grid_attach(GTK_GRID (grid), joinbtn, 2, 0, 1, 1);

  //create
  createbtn = gtk_button_new_with_label ("Create Game");
  gtk_grid_attach(GTK_GRID (grid), createbtn, 2, 2, 1, 1);
	
  //exit
  exitbtn = gtk_button_new_with_label ("Exit");
  g_signal_connect_swapped(exitbtn, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach(GTK_GRID (grid), exitbtn, 2, 5, 1, 1);

  //create entry fields
  //ip-address
  ipaddr_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID (grid), ipaddr_field, 2, 1, 1, 1);
  ipaddr_label = gtk_label_new("IP Address ");
  gtk_grid_attach(GTK_GRID (grid), ipaddr_label, 0, 1, 1, 1);

  //map number
  mapno_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID (grid), mapno_field, 2, 3, 1, 1);
  mapno_label = gtk_label_new("Map # (1-3) ");
  gtk_grid_attach(GTK_GRID (grid), mapno_label, 0, 3, 1, 1);
  gtk_entry_set_text(mapno_field, "1");

  //number of players
  numplrs_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID (grid), numplrs_field, 2, 4, 1, 1);
  numplrs_label = gtk_label_new("# of players ");
  gtk_grid_attach(GTK_GRID (grid), numplrs_label, 0, 4, 1, 1);
	

  //show all widgets within this app
  gtk_widget_show_all (window);  
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("com.github.jukeri12.md-launcher", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}