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

#include "person-contact.h"

//======================================================================
GListModel *create_contact_model(void)
{
PersonContact *contact1= g_object_new(PERSON_TYPE_CONTACT,0);
PersonContact *contact2= g_object_new(PERSON_TYPE_CONTACT,0);

g_object_set (contact1, "name", "Mr Jellyfish", NULL);
g_object_set (contact1, "email", "jellyfish@ubuntu.com", NULL);
g_object_set (contact1, "phone", "+2022 062027", NULL);

g_object_set (contact2, "name", "Mr Puffin", NULL);
g_object_set (contact2, "email", "puffin@ubuntu.com", NULL);
g_object_set (contact2, "phone", "+2025 012026", NULL);

GListStore *store = g_list_store_new(G_TYPE_OBJECT);
g_list_store_append(store,contact1);
g_list_store_append(store,contact2);   
return G_LIST_MODEL(store);
}
//=====================================================================
static void callbk_setup(GtkSignalListItemFactory *factory,GObject  *listitem)
{
GtkWidget *label =gtk_label_new(NULL);
gtk_list_item_set_child(GTK_LIST_ITEM(listitem),label);
}
//======================================================================
static void callbk_bind_name(GtkSignalListItemFactory *factory, GtkListItem *listitem)
{
GtkWidget *label = gtk_list_item_get_child(listitem);
GObject *item = gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
const char *string = person_contact_get_name(PERSON_CONTACT(item));  
gtk_label_set_text(GTK_LABEL (label), string);
}
//======================================================================
static void callbk_bind_email(GtkSignalListItemFactory *factory, GtkListItem *listitem)
{
GtkWidget *label = gtk_list_item_get_child(listitem);
GObject *item = gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
const char *string = person_contact_get_email(PERSON_CONTACT(item));
gtk_label_set_text(GTK_LABEL (label), string);
}
//======================================================================
static void callbk_bind_telephone(GtkSignalListItemFactory *factory, GtkListItem *listitem)
{
GtkWidget *label = gtk_list_item_get_child(listitem);
GObject *item = gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
const char *string = person_contact_get_phone(PERSON_CONTACT(item));
gtk_label_set_text(GTK_LABEL (label), string);
}
//======================================================================
static void activate (GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;	
	GtkWidget *scrolled_window;
	GtkListItemFactory *factory;
	GListModel *model;
	GtkSingleSelection *selection;
	GtkColumnViewColumn *column;
	GtkWidget *column_view;
		
	window = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW(window), "Contacts");
	gtk_window_set_default_size (GTK_WINDOW(window), 500, 200);
		
	scrolled_window = gtk_scrolled_window_new();
	gtk_widget_set_hexpand (GTK_WIDGET (scrolled_window), true);
	gtk_widget_set_vexpand (GTK_WIDGET (scrolled_window), true);	
	gtk_window_set_child (GTK_WINDOW(window), scrolled_window);
	
	model = create_contact_model();
	selection = gtk_single_selection_new(G_LIST_MODEL(model));
	gtk_single_selection_set_autoselect(selection,TRUE);
	
	column_view = gtk_column_view_new(GTK_SELECTION_MODEL (selection));
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),column_view);
	gtk_column_view_set_show_column_separators (GTK_COLUMN_VIEW (column_view),TRUE);
	
	// one factory for each column 
	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory, "setup", G_CALLBACK(callbk_setup),NULL);
	g_signal_connect(factory, "bind", G_CALLBACK(callbk_bind_name),NULL);
	column = gtk_column_view_column_new("Name", factory);	
	gtk_column_view_append_column (GTK_COLUMN_VIEW (column_view), column);
	g_object_unref (column);
	
	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory, "setup", G_CALLBACK(callbk_setup),NULL);
	g_signal_connect(factory, "bind", G_CALLBACK(callbk_bind_email),NULL);
	column = gtk_column_view_column_new("Email", factory);	
	gtk_column_view_append_column (GTK_COLUMN_VIEW (column_view), column);
	g_object_unref (column);
	
	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory, "setup", G_CALLBACK(callbk_setup),NULL);
	g_signal_connect(factory, "bind", G_CALLBACK(callbk_bind_telephone),NULL);
	column = gtk_column_view_column_new("Telephone", factory);	
	gtk_column_view_append_column (GTK_COLUMN_VIEW (column_view), column);
	g_object_unref (column);
		
	gtk_window_present(GTK_WINDOW (window));		
}
//======================================================================
int main (int argc, char **argv)
{
	GtkApplication *app;
	int status;
	app = gtk_application_new ("org.gtk.mycontacts", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return status;
}
