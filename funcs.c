#include <gtk/gtk.h>
#include <stdlib.h>

//this functions executes Musket Doom
void 
run_game (GtkApplication* app,
      	  gpointer		  user_data)
{
	g_print ("Running game...\n");
	system("./prboom");
}