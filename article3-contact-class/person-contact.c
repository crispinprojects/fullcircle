/* person-contact.c
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
#include "person-contact.h"

struct _PersonContact
{
GObject parent_instance; //parent
gchar* name; 
gchar* email;  
gchar* phone;   
};

G_DEFINE_TYPE (PersonContact, person_contact, G_TYPE_OBJECT);

enum {
PROP_0,  
PROP_NAME,
PROP_EMAIL,
PROP_PHONE,
LAST_PROP
};

static GParamSpec *properties[LAST_PROP];

static void person_contact_get_property(GObject *object,
guint   prop_id,
GValue  *value,
GParamSpec *pspec)
{
PersonContact *self =(PersonContact *)object;
switch (prop_id)
{
case PROP_NAME:
g_value_set_string(value, person_contact_get_name(self)); //boxing
break;
case PROP_EMAIL:
g_value_set_string(value, person_contact_get_email(self)); //boxing
break; 
case PROP_PHONE:
g_value_set_string(value, person_contact_get_phone(self));
break;        
}
}

static void person_contact_set_property(GObject *object,
guint   prop_id,
const GValue  *value,
GParamSpec *pspec)
{
PersonContact *self =(PersonContact *)object;
switch (prop_id)
{        
case PROP_NAME:
person_contact_set_name(self, g_value_get_string(value));
break;
case PROP_EMAIL:
person_contact_set_email(self, g_value_get_string(value));
break; 
case PROP_PHONE:
person_contact_set_phone(self, g_value_get_string(value));
break;         
}
}

static void person_contact_class_init (PersonContactClass *klass)
{
GObjectClass *object_class =G_OBJECT_CLASS(klass);
object_class->get_property = person_contact_get_property;
object_class->set_property = person_contact_set_property;

properties[PROP_NAME] =
g_param_spec_string("name",
"Name",
"The contact name",
NULL,
(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

properties[PROP_EMAIL] =
g_param_spec_string("email",
"Email",
"The contact email",
NULL,
(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

properties[PROP_PHONE] =
g_param_spec_string("phone",
"Phone",
"The phone number string",
NULL,
(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

g_object_class_install_properties(object_class, LAST_PROP, properties);
}

static void person_contact_init (PersonContact *self)
{  
}

//static void person_contact_dispose(GObject *object)
//{
	////destructor not used	
//}
const gchar* person_contact_get_phone(PersonContact *self){
return self->phone;
}

void person_contact_set_phone(PersonContact *self, const gchar* phone_str)
{
	if(g_strcmp0(phone_str, self->phone)) 
	{
	g_free(self->phone);
	self->phone =g_strdup(phone_str);
	}
}

const gchar* person_contact_get_name(PersonContact *self){
return self->name;
}
void person_contact_set_name(PersonContact *self, const gchar* name){
	if(g_strcmp0(name, self->name)) 
	{
	g_free(self->name);
	self->name =g_strdup(name);
	}
}
const gchar* person_contact_get_email(PersonContact *self){
return self->email;
}
void person_contact_set_email(PersonContact *self, const gchar* email){

if(g_strcmp0(email, self->email)) {  
g_free(self->email);
self->email =g_strdup(email);
}

}
