
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

//gchars for launcher values
gchar *map;
gchar *ip_addr;
gchar *numplrs;
gchar *maptime;
//arguments for running
char arguments[100];

//entry fields 
GtkEntry *mapno_field; //# of map to be played
GtkEntry *ipaddr_field; //ip address field
GtkEntry *numplrs_field; //# of players field
GtkEntry *maptime_field; //Time a map runs (minutes)

//Some essential functions
//this function launches Musket Doom Server
void 
create_game (GtkApplication* app,
      	     gpointer		 user_data)
{
	//clean the commandline argument string
	strcpy(arguments, "");
	g_print ("Running server...\n");
	//parses together a command line argument to run Musket-Doom as server with all the settings
	
	//choice of map
	strcat(arguments, "./prboom-game-server ");
	strcat(arguments, "-l ");
	//map is 1 except otherwise specified
	map = gtk_entry_get_text(mapno_field); //get value from map# entry
	strcat(arguments, map);
	
	//remember to add spaces between arguments
	//SPACE
	strcat(arguments, " ");
	//SPACE
	
	//determine no. of players (always at least 2, no technical maximum)
	strcat(arguments, "-N ");
	numplrs = gtk_entry_get_text(numplrs_field); //get value from plr# entry
	strcat(arguments, numplrs);
	
	//SPACE
	strcat(arguments, " ");
	//SPACE
	
	//time per map (0 for no time limit)
	strcat(arguments, "-timer ");
	maptime = gtk_entry_get_text(maptime_field); //get value from maptime entry
	strcat(arguments, maptime);
		
	//SPACE
	strcat(arguments, " ");
	//SPACE
	
	//mandatory arguments
	strcat(arguments, "-a "); //define the game as alt deathmatch
	strcat(arguments, "-n"); //define game as no-monsters (no doom monsters spawn)
	system(arguments);
}

//This function makes the game join a server as specified in IP Addr field
void
join_game (GtkApplication* app,
           gpointer		   user_data)
{
	//clean the commandline argument
	strcpy(arguments, "");
	//parse together a commandline string for joining a net-game
	g_print("Joining game...");
	strcat(arguments, "./prboom ");
	strcat(arguments, "-net ");
	ip_addr = gtk_entry_get_text(ipaddr_field);
	strcat(arguments, ip_addr);
	system(arguments);
}


/*activate is a signal within GTK+ that is responsible for opening the first window
* in GTK+. In essence, this should be where most of our interface programming is done.
* There are other signals to work with, like startup and open, but we probably don't
* need them. Refer to GTK+ docs for info on this one. 				*/
static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  //version number
  const char version = "V0002";

  //create our GtkWidgets
  GtkWidget *window; //window
  //layout grid
  GtkWidget *grid;
  //buttons
  GtkWidget *exitbtn; //exit game
  GtkWidget *joinbtn;  //join game
  GtkWidget *createbtn; //create game
  //labels
  GtkWidget *ipaddr_label;
  GtkWidget *numplrs_label;
  GtkWidget *mapno_label;
  GtkWidget *maptime_label;
  //switches, radio buttons (unused at this time)
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
  g_signal_connect(joinbtn, "clicked", G_CALLBACK (join_game), NULL);
  gtk_grid_attach(GTK_GRID (grid), joinbtn, 2, 0, 1, 1);

  //create
  createbtn = gtk_button_new_with_label ("Create Game");
  g_signal_connect(createbtn, "clicked", G_CALLBACK (create_game), NULL);
  gtk_grid_attach(GTK_GRID (grid), createbtn, 2, 2, 1, 1);
	
  //exit
  exitbtn = gtk_button_new_with_label ("Exit");
  g_signal_connect_swapped(exitbtn, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach(GTK_GRID (grid), exitbtn, 2, 6, 1, 1);

  //create entry fields
  //ip-address
  ipaddr_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID (grid), ipaddr_field, 2, 1, 1, 1);
  ipaddr_label = gtk_label_new("IP Address ");
  gtk_entry_set_text(ipaddr_field, "127.0.0.1"); //by default we connect to localhost
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
  gtk_entry_set_text(numplrs_field, "2"); //by default we have a minimum of 2 players
  numplrs_label = gtk_label_new("# of players ");
  gtk_grid_attach(GTK_GRID (grid), numplrs_label, 0, 4, 1, 1);

  //time per map
  maptime_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID (grid), maptime_field, 2, 5, 1, 1);
  maptime_label = gtk_label_new("Time / Map");
  gtk_grid_attach(GTK_GRID (grid), maptime_label, 0, 5, 1, 1);
	

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