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
 
 static void button_clicked (GtkButton *button, gpointer   user_data)
 {
 GtkWidget *label =user_data;
 gtk_label_set_text(GTK_LABEL(label),"Button Clicked");
 }
 
 static void activate (GtkApplication* app, gpointer user_data)
 {
 GtkWidget *window;
 GtkWidget *button;
 GtkWidget *label;	
 GtkWidget *box; 
 window = gtk_application_window_new (app);
 gtk_window_set_title (GTK_WINDOW (window), "Hello Window");
 gtk_window_set_default_size (GTK_WINDOW (window),400, 100); 
 label =gtk_label_new("GTK4 Programming in C"); 
 box =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
 gtk_window_set_child (GTK_WINDOW (window), box); 
 button = gtk_button_new_with_label ("Click Me");	
 gtk_button_set_has_frame(GTK_BUTTON(button),FALSE);
 g_signal_connect (GTK_BUTTON (button),"clicked", G_CALLBACK (button_clicked),label); 
 gtk_box_append(GTK_BOX(box), label);
 gtk_box_append(GTK_BOX(box), button);	 
 gtk_window_present(GTK_WINDOW (window));		
 }
 
 int main (int argc, char **argv)
 {
 GtkApplication *app;
 int status; 
 app = gtk_application_new ("org.gtk.demo", G_APPLICATION_DEFAULT_FLAGS);
 g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
 status = g_application_run (G_APPLICATION (app), argc, argv);
 g_object_unref (app); 
 return status;
 }
