#include "replace_dialog.h"

Replace_Dialog::Replace_Dialog(const char *label) : Fl_Double_Window(430, 110, label)
{
    find_text_input = new Fl_Input(100, 10, 320, 25, "Find:");
    replace_text_input = new Fl_Input(100, 40, 320, 25, "Replace:");

    Fl_Flex *button_field = new Fl_Flex(100, 70, w()-100, 40);
    button_field->type(Fl_Flex::HORIZONTAL);
    button_field->margin(0, 5, 10, 10);
    button_field->gap(10);

    find_next_button = new Fl_Button(0, 0, 0, 0, "Next");
    find_next_button->callback(find_next_callback, this);
    
    replace_and_find_button = new Fl_Button(0, 0, 0, 0, "Replace");
    replace_and_find_button->callback(replace_and_find_callback, this);

    close_button = new Fl_Button(0, 0, 0, 0, "Close");
    close_button->callback(close_callback, this);

    button_field->end();
    set_non_modal();
}

void Replace_Dialog::show()
{
    find_text_input->value(last_find_text);
    replace_text_input->value(last_replace_text);
    Fl_Double_Window::show();
}

void Replace_Dialog::close_callback(Fl_Widget*, void *my_dialog)
{
    Replace_Dialog *dlg = static_cast<Replace_Dialog*>(my_dialog);
    dlg->hide();
}

void Replace_Dialog::find_next_callback(Fl_Widget*, void *my_dialog)
{
    Replace_Dialog *dlg = static_cast<Replace_Dialog*>(my_dialog);
    fl_strlcpy(last_find_text, dlg->find_text_input->value(), sizeof(last_find_text));
    fl_strlcpy(last_replace_text, dlg->replace_text_input->value(), sizeof(last_replace_text));

    if (last_find_text[0])
        find_next(last_find_text);
}

void Replace_Dialog::replace_and_find_callback(Fl_Widget*, void *my_dialog)
{
    Replace_Dialog *dlg = static_cast<Replace_Dialog*>(my_dialog);
    replace_selection(dlg->replace_text_input->value());
    find_next_callback(NULL , my_dialog);
}