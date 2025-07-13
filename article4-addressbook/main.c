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

static void callbk_new_contact(GtkButton *button, gpointer user_data);
static void callbk_add_new_contact(GtkButton *button, gpointer user_data);

static void callbk_delete_contact(GtkButton *button, gpointer user_data);

void save_contacts(GListStore *store);
GListStore *open_contacts();

int file_exists(const char *file_name);


static void callbk_setup(GtkSignalListItemFactory *factory,GObject  *listitem)
{
GtkWidget *label =gtk_label_new(NULL);
gtk_list_item_set_child(GTK_LIST_ITEM(listitem),label);
}


static void callbk_bind_name(GtkSignalListItemFactory *factory, GtkListItem *listitem)
{
GtkWidget *label = gtk_list_item_get_child(listitem);
GObject *item = gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
const char *string = person_contact_get_name(PERSON_CONTACT(item));  
gtk_label_set_text(GTK_LABEL (label), string);
}

static void callbk_bind_email(GtkSignalListItemFactory *factory, GtkListItem *listitem)
{
GtkWidget *label = gtk_list_item_get_child(listitem);
GObject *item = gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
const char *string = person_contact_get_email(PERSON_CONTACT(item));
gtk_label_set_text(GTK_LABEL (label), string);
}

static void callbk_bind_telephone(GtkSignalListItemFactory *factory, GtkListItem *listitem)
{
GtkWidget *label = gtk_list_item_get_child(listitem);
GObject *item = gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
const char *string = person_contact_get_phone(PERSON_CONTACT(item));
gtk_label_set_text(GTK_LABEL (label), string);
}

static void callbk_add_new_contact(GtkButton *button, gpointer user_data)
{
		
	GListStore *store =user_data;	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	
	GtkEntryBuffer *buffer_name;
	GtkWidget *entry_name = g_object_get_data(G_OBJECT(button), "entry-name-key");
	
	GtkEntryBuffer *buffer_email;
	GtkWidget *entry_email = g_object_get_data(G_OBJECT(button), "entry-email-key");
	
	GtkEntryBuffer *buffer_phone;
	GtkWidget *entry_phone = g_object_get_data(G_OBJECT(button), "entry-phone-key");
	
	buffer_name = gtk_entry_get_buffer (GTK_ENTRY(entry_name));
	const char* name= gtk_entry_buffer_get_text (buffer_name);
	buffer_email = gtk_entry_get_buffer (GTK_ENTRY(entry_email));
	const char* email= gtk_entry_buffer_get_text (buffer_email);
	
	buffer_phone = gtk_entry_get_buffer (GTK_ENTRY(entry_phone));
	const char* phone_str= gtk_entry_buffer_get_text (buffer_phone);
		
	PersonContact *contact_new= g_object_new(PERSON_TYPE_CONTACT,0);	
	g_object_set (contact_new, "name", name, NULL);
	g_object_set (contact_new, "email", email, NULL);
	g_object_set (contact_new, "phone", phone_str, NULL);
	
	g_list_store_append(store,contact_new);     
	
	save_contacts(store); //save new state here
	gtk_window_destroy(GTK_WINDOW(dialog)); 
}
//======================================================================
static void callbk_new_contact(GtkButton *button, gpointer user_data)
{		
	GListStore *store =user_data;	
	GtkWidget *dialog;
	
	GtkWidget *button_add;	
	GtkWidget *label_name;
	GtkWidget *entry_name;	
	GtkWidget *label_email;
	GtkWidget *entry_email;
	GtkWidget *label_phone;
	GtkWidget *entry_phone;
	GtkWidget *box;
	 
	dialog = gtk_window_new(); 
	gtk_window_set_title(GTK_WINDOW(dialog), "New Contact");
    gtk_window_set_default_size(GTK_WINDOW(dialog),350,100);

    box =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    gtk_window_set_child (GTK_WINDOW (dialog), box);

    button_add = gtk_button_new_with_label ("Add Contact");
    g_signal_connect (button_add, "clicked", G_CALLBACK (callbk_add_new_contact), store);

   label_name =gtk_label_new("Contact Name");
   entry_name =gtk_entry_new();
   gtk_entry_set_max_length(GTK_ENTRY(entry_name),100);

   label_email =gtk_label_new("Email");
   entry_email =gtk_entry_new();
   gtk_entry_set_max_length(GTK_ENTRY(entry_email),100);
   
   label_phone =gtk_label_new("Phone");
   entry_phone =gtk_entry_new();
   gtk_entry_set_max_length(GTK_ENTRY(entry_phone),50);
   
  g_object_set_data(G_OBJECT(button_add), "dialog-key",dialog);  
  g_object_set_data(G_OBJECT(button_add), "entry-name-key",entry_name);
  g_object_set_data(G_OBJECT(button_add), "entry-email-key",entry_email);
  g_object_set_data(G_OBJECT(button_add), "entry-phone-key",entry_phone);
   
  gtk_box_append(GTK_BOX(box), label_name);
  gtk_box_append(GTK_BOX(box), entry_name);  
  gtk_box_append(GTK_BOX(box), label_email);
  gtk_box_append(GTK_BOX(box), entry_email);
   gtk_box_append(GTK_BOX(box),label_phone);
  gtk_box_append(GTK_BOX(box), entry_phone);
  gtk_box_append(GTK_BOX(box), button_add);
  gtk_window_present (GTK_WINDOW (dialog));	
}

//======================================================================
static void callbk_delete_contact(GtkButton *button, gpointer user_data)
{	
	GtkSingleSelection *selection=user_data;	
	guint p = gtk_single_selection_get_selected((GtkSingleSelection*) selection);	
		
	GListModel *model = gtk_single_selection_get_model(selection);
    GListStore *store = G_LIST_STORE(model);
	
	PersonContact* selecteditem = gtk_single_selection_get_selected_item (selection);
	 
	 gchar *name_str = "";
	 gchar *email_str = "";	
	 gchar *phone_str = "";	
	 
	 g_object_get(selecteditem, "name", &name_str, NULL);
	 g_object_get(selecteditem, "email", &email_str, NULL);
	 g_object_get(selecteditem, "phone", &phone_str, NULL);
	
     g_list_store_remove(store,p);   
     save_contacts(store);   
}

//=====================================================================

int file_exists(const char *file_name)
{
    FILE *file;
    file = fopen(file_name, "r");
    if (file){       
        fclose(file);
        return 1; //file exists return 1
    }
    return 0; //file does not exist
}
//======================================================================

GListStore *open_contacts()
{		
	GListStore *store=NULL;
	
	int line_counter = 0; //counter	
    
	GFile *file;
    GFileInputStream *file_stream=NULL;   
	GDataInputStream *input = NULL;
    
    file = g_file_new_for_path("contacts.csv");

	file_stream = g_file_read(file, NULL, NULL);	
	if(!file_stream) {
		g_print("error: unable to open contacts.csv\n");
		return NULL;
	}
	
	store = g_list_store_new(G_TYPE_OBJECT);
	input = g_data_input_stream_new (G_INPUT_STREAM (file_stream));
		
	
	char *name_str = "";
	char *email_str = "";
	char* phone_str = "";
	
	while (TRUE) {
		
		char *line;
		line = g_data_input_stream_read_line(input, NULL, NULL, NULL);		
		if (line == NULL) break;
				
		 
		name_str = strtok(line,","); //first field
		email_str = strtok(NULL,","); //second field
		phone_str = strtok(NULL,","); //third field
		
		PersonContact *contact= g_object_new(PERSON_TYPE_CONTACT,0);
			
		g_object_set (contact, "name", name_str, NULL);
		g_object_set (contact, "email", email_str, NULL);
		g_object_set (contact, "phone", phone_str, NULL);
		
		g_list_store_append(store,contact);
		
		line_counter++;
	}//while
	
	return store;	
	
	g_object_unref (file_stream);	
	g_object_unref (file);
	
		
}

//======================================================================

void save_contacts(GListStore *store)
{
GFile *file;
gchar *file_name ="contacts.csv";	
guint n_items;

GFileOutputStream *file_stream;
GDataOutputStream *data_stream;
file = g_file_new_for_path(file_name);
file_stream = g_file_replace(file, NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL);

if (file_stream == NULL) {
g_object_unref (file);
g_print("error: unable to save contacts.csv file\n");
return;
}

data_stream = g_data_output_stream_new (G_OUTPUT_STREAM (file_stream));

GListModel *model = G_LIST_MODEL(store);
n_items = g_list_model_get_n_items(G_LIST_MODEL (model));
char *line = "";

for (int i=0; i<n_items; i++)
{
line="";
gchar *name_str = "";
gchar *email_str = "";
gchar *phone_str = "";

PersonContact  *contact = g_list_model_get_item(model, i);
g_object_get(contact, "name", &name_str, NULL);
g_object_get(contact, "email", &email_str, NULL);
g_object_get(contact, "phone", &phone_str, NULL);

line =g_strconcat(line,	    
name_str,",",
email_str,",",
phone_str,",",
"\n", NULL);

g_data_output_stream_put_string (data_stream, line, NULL, NULL);  
} //for

g_object_unref (data_stream);
g_object_unref (file_stream);
g_object_unref (file);	

}
//======================================================================
static void activate (GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *header;
	GtkWidget *scrolled_window;
	GtkListItemFactory *factory;	
	GtkSingleSelection *selection;
	GtkColumnViewColumn *column;
	GtkWidget *column_view; 
	GtkWidget *button_new_contact;
	GtkWidget *button_delete_contact;
	
	GListStore *store=NULL;
	
	window = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW(window), "Addressbook");
	gtk_window_set_default_size (GTK_WINDOW(window), 650, 250);
	
	header = gtk_header_bar_new();
	gtk_window_set_titlebar(GTK_WINDOW(window), header);
	
	scrolled_window = gtk_scrolled_window_new();
	gtk_widget_set_hexpand (GTK_WIDGET (scrolled_window), true);
	gtk_widget_set_vexpand (GTK_WIDGET (scrolled_window), true);	
	gtk_window_set_child (GTK_WINDOW(window), scrolled_window);
		
	store = g_list_store_new(G_TYPE_OBJECT);
	
	if(file_exists("contacts.csv"))
	{	  
	store =open_contacts();
	}
	else
	{
	g_print("contacts.csv does not exist\n");
	}
	
	selection = gtk_single_selection_new(G_LIST_MODEL(store));
	gtk_single_selection_set_autoselect(selection,TRUE);
	
	column_view = gtk_column_view_new(GTK_SELECTION_MODEL (selection));
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),column_view);
	gtk_column_view_set_show_column_separators (GTK_COLUMN_VIEW (column_view),FALSE);
	gtk_column_view_set_show_row_separators(GTK_COLUMN_VIEW (column_view),FALSE); 
	
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
		
	button_new_contact = gtk_button_new_with_label("New Contact");		
	g_signal_connect(button_new_contact, "clicked", G_CALLBACK(callbk_new_contact), store);	
	g_object_set_data(G_OBJECT(button_new_contact), "button-new-window-key",window);
	
	button_delete_contact = gtk_button_new_with_label("Delete Contact");	
	g_signal_connect(button_delete_contact, "clicked", G_CALLBACK(callbk_delete_contact), selection);
	
	// packing
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_new_contact);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_delete_contact);

	gtk_window_present(GTK_WINDOW (window));		
}
//======================================================================
int main (int argc, char **argv)
{
	GtkApplication *app;
	int status;
	app = gtk_application_new ("org.gtk.addressbook", G_APPLICATION_DEFAULT_FLAGS);	
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return status;
}
