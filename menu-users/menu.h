/* 
En este modulo se incluye todo lo relacionado con la parte de los menu y los usuarios.
Todos los formuliarios que se utilizaran, los menus iterativos para cada usuario y mucho mas.
*/

#ifndef MENU 
#define MENU

#include "usr.h"
#include "../gc-functions/gc.h"

#include<iostream>
#include<libpq-fe.h>
#include<string>

void menu_admin(USR::User *, GC::DBgc *);
void menu_profesor(USR::Profesor *, GC::DBgc *);
void menu_student(USR::Student *, GC::DBgc *);

#endif // MENU