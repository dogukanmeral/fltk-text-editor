#ifndef HELPERS_H
#define HELPERS_H

#include <FL/fl_ask.H>
#include <FL/filename.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_string_functions.h>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>

#include <errno.h>

void update_title();
void set_changed(bool v);
void set_filename(const char *new_filename);
void load(char const *filename);
void find_next(const char *needle);

#endif /* HELPERS_H */