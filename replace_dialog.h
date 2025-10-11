#ifndef REPLACE_DIALOG_H
#define REPLACE_DIALOG_H

#include "helpers.h"

#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl.H>
#include <FL/Fl_Flex.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_string_functions.h>

extern char last_find_text[1024];
extern char last_replace_text[1024];

class Replace_Dialog : public Fl_Double_Window
{
    Fl_Input *find_text_input;
    Fl_Input *replace_text_input;
    Fl_Button *find_next_button;
    Fl_Button *replace_and_find_button;
    Fl_Button *close_button;

    public:
        Replace_Dialog(const char *label);
        void show() FL_OVERRIDE;

    private:
        static void find_next_callback(Fl_Widget*, void*);
        static void replace_and_find_callback(Fl_Widget*, void*);
        static void close_callback(Fl_Widget*, void*);
};

#endif /* REPLACE_DIALOG_H*/