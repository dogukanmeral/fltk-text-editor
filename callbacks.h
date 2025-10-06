#ifndef CALLBACKS_H
#define CALLBACKS_H


#include <FL/Fl_Widget.H>
#include <FL/filename.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Native_File_Chooser.H>


void menu_save_callback(Fl_Widget*, void*);
void menu_quit_callback(Fl_Widget *, void *);
void text_changed_callback(int, int n_inserted, int n_deleted, int, const char*, void*);
void menu_new_callback(Fl_Widget*, void*);
void menu_saveas_callback(Fl_Widget*, void*);
void menu_save_callback(Fl_Widget*, void*);
void menu_open_callback(Fl_Widget*, void*);

#endif /* CALLBACKS_H */