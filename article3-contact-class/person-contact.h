/* person-contact.h
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
#ifndef PERSONCONTACT_H
#define PERSONCONTACT_H

#include <glib-object.h>

G_BEGIN_DECLS

#define PERSON_TYPE_CONTACT (person_contact_get_type())
G_DECLARE_FINAL_TYPE(PersonContact, person_contact, PERSON, CONTACT, GObject)


const gchar* person_contact_get_name(PersonContact *self);
void person_contact_set_name(PersonContact *self, const gchar* name);

const gchar* person_contact_get_email(PersonContact *self);
void person_contact_set_email(PersonContact *self, const gchar* email);

const gchar* person_contact_get_phone(PersonContact *self);
void person_contact_set_phone(PersonContact *self, const gchar* phone_str);

G_END_DECLS

#endif
