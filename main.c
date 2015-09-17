
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

  //creates a GtkWidget called window
  GtkWidget *window;
  GtkWidget *exitbtn;
  GtkWidget *exitbtn_box;
  GtkWidget *joinbtn;
  GtkWidget *createbtn;

  //defines it as a GTK window
  window = gtk_application_window_new (app);
  //set window title
  gtk_window_set_title (GTK_WINDOW (window), "Launcher");
  //set window size
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 300);

  //create buttons
  //exit
  exitbtn_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), exitbtn_box);

  exitbtn = gtk_button_new_with_label ("Exit");
  g_signal_connect_swapped(exitbtn, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (exitbtn_box), exitbtn);

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