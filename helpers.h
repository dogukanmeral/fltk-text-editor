#ifndef HELPERS_H
#define HELPERS_H

#include <FL/fl_ask.H>
#include <FL/filename.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_string_functions.h>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>

#include <errno.h>

extern Fl_Text_Buffer *app_text_buffer;
extern Fl_Double_Window *app_window;
extern Fl_Text_Editor *app_editor;

extern char last_replace_text[1024];
extern bool text_changed;
extern char app_filename[FL_PATH_MAX];

void update_title();
void set_changed(bool v);
void set_filename(const char *new_filename);
void load(char const *filename);
void find_next(const char *needle);
void replace_selection(const char *new_text);

#endif /* HELPERS_H */