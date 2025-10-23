#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "helpers.h"
#include "replace_dialog.h"

#include <FL/Fl_Widget.H>
#include <FL/fl_ask.H>
#include <FL/fl_string_functions.h>
#include <FL/filename.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Color_Chooser.H> 


extern Fl_Text_Buffer *app_text_buffer;
extern Fl_Text_Editor *app_editor;

extern Replace_Dialog *replace_dialog;

extern char last_replace_text[1024];
extern char last_find_text[1024];
extern bool text_changed;
extern char app_filename[FL_PATH_MAX];


void text_changed_callback(int, int n_inserted, int n_deleted, int, const char*, void*);

/* MENU FILE CALLBACKS*/
void menu_save_callback(Fl_Widget*, void*);
void menu_quit_callback(Fl_Widget *, void *);
void menu_new_callback(Fl_Widget*, void*);
void menu_saveas_callback(Fl_Widget*, void*);
void menu_save_callback(Fl_Widget*, void*);
void menu_open_callback(Fl_Widget*, void*);

/* MENU EDIT CALLBACKS */
void menu_cut_callback(Fl_Widget*, void *v);
void menu_copy_callback(Fl_Widget*, void *v);
void menu_paste_callback(Fl_Widget*, void *v);
void menu_delete_callback(Fl_Widget*, void *v);
void menu_undo_callback(Fl_Widget*, void *v);
void menu_redo_callback(Fl_Widget*, void *v);
void menu_bg_color_callback(Fl_Widget*, void *v);
void menu_text_color_callback(Fl_Widget*, void *v);


/* MENU FIND CALLBACKS */

void menu_find_callback(Fl_Widget*, void *v);
void menu_find_next_callback(Fl_Widget*, void *v);

/* MENU REPLACE CALLBACKS */
void menu_replace_callback(Fl_Widget*, void *v);
void menu_replace_next_callback(Fl_Widget*, void *v);

#endif /* CALLBACKS_H */