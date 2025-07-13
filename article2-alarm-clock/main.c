/* main.c
 *
 * Copyright 2025 Alan Crispin <crispinalan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gtk/gtk.h>

static gboolean continue_timer = TRUE;
static int m_alarm_hour=0;
static int m_alarm_min=0;

static gboolean label_update(gpointer data)
{
GtkLabel *label = (GtkLabel*)data;

GDateTime *date_time;  
date_time = g_date_time_new_now_local(); // get local time   
gint hour =g_date_time_get_hour(date_time);
gint min =g_date_time_get_minute (date_time);
gint sec = g_date_time_get_second (date_time);

char *dt_format = g_date_time_format(date_time, "%H:%M:%S");   // 24hr time format
gtk_label_set_text(GTK_LABEL(label), dt_format);   // update label
g_free (dt_format);    

if(hour==m_alarm_hour && min==m_alarm_min && sec==0)
{
char * command_str ="aplay alarm.wav";       
system(command_str); 			
}	

g_date_time_unref(date_time);
return continue_timer;
}

//======================================================================
static void callbk_spin_alarm_hour(GtkSpinButton *button, gpointer user_data)
{	
m_alarm_hour = gtk_spin_button_get_value_as_int (button);	
}
//======================================================================
static void callbk_spin_alarm_min(GtkSpinButton *button, gpointer user_data)
{	
m_alarm_min = gtk_spin_button_get_value_as_int (button);
}
//======================================================================

static void callbk_button_minimise(GtkButton *button, gpointer user_data)
{
GtkWidget *window = user_data;	
gtk_window_minimize(GTK_WINDOW(window));
}
//======================================================================
static void activate (GtkApplication* app, gpointer user_data)
{
GtkWidget *window;
GtkWidget *grid;	
GtkWidget* label_time;
GtkWidget *label_alarm_hour;
GtkWidget *label_alarm_min;	
GtkWidget *label_spacer1;
GtkWidget *label_spacer2; 
GtkWidget *spin_button_alarm_hour;	
GtkWidget *spin_button_alarm_min;
GtkWidget *button_minimise;

window = gtk_application_window_new (app);
gtk_window_set_title (GTK_WINDOW (window), "Alarm Clock");
gtk_window_set_default_size (GTK_WINDOW (window),400, 150);

grid = gtk_grid_new();	
gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

label_spacer1 = gtk_label_new("");
label_spacer2 = gtk_label_new("");

label_time=gtk_label_new("");	
gtk_label_set_xalign(GTK_LABEL(label_time),0.5);

GtkAdjustment *adjustment_alarm_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
GtkAdjustment *adjustment_alarm_min= gtk_adjustment_new(1.00, 0.0, 59.00, 1.0, 1.0, 0.0);

label_alarm_hour =gtk_label_new("Hour: ");
spin_button_alarm_hour = gtk_spin_button_new(adjustment_alarm_hour, 1.0, 0);	
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_alarm_hour), 12);
g_signal_connect(GTK_SPIN_BUTTON(spin_button_alarm_hour), "value_changed", G_CALLBACK(callbk_spin_alarm_hour), NULL);	

label_alarm_min =gtk_label_new("Min: ");	
spin_button_alarm_min = gtk_spin_button_new(adjustment_alarm_min, 1.0, 0);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_alarm_min), 0);		
g_signal_connect(GTK_SPIN_BUTTON(spin_button_alarm_min), "value_changed", G_CALLBACK(callbk_spin_alarm_min), NULL);

button_minimise = gtk_button_new_with_label ("Minimise");	
g_signal_connect (GTK_BUTTON (button_minimise),"clicked", G_CALLBACK (callbk_button_minimise), window);

g_timeout_add_seconds(1, label_update, label_time);

gtk_grid_attach(GTK_GRID(grid), label_time, 			  1, 1, 4, 1);    
gtk_grid_attach(GTK_GRID(grid), label_spacer1,  		  1, 2, 4, 1); 
gtk_grid_attach(GTK_GRID(grid), label_alarm_hour,         1, 3, 1, 1);
gtk_grid_attach(GTK_GRID(grid), spin_button_alarm_hour,   2, 3, 1, 1);
gtk_grid_attach(GTK_GRID(grid), label_alarm_min,          3, 3, 1, 1);
gtk_grid_attach(GTK_GRID(grid), spin_button_alarm_min,    4, 3, 1, 1);    
gtk_grid_attach(GTK_GRID(grid), label_spacer2,  		  1, 4, 4, 1);	
gtk_grid_attach(GTK_GRID(grid), button_minimise,  		  1, 5, 4, 1);	
gtk_window_set_child (GTK_WINDOW (window), grid);	
gtk_window_present(GTK_WINDOW (window));
}

//======================================================================
int main (int argc, char **argv)
{
GtkApplication *app;
int status;

app = gtk_application_new ("org.gtk.alarmclock", G_APPLICATION_DEFAULT_FLAGS);
g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
status = g_application_run (G_APPLICATION (app), argc, argv);
g_object_unref (app);

return status;
}
