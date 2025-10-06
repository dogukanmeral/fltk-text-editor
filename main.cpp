#include <FL/platform.H>
#include <FL/Fl.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Double_Window.H>
#include "helpers.h"
#include "callbacks.h"

Fl_Text_Editor *app_editor = NULL;
Fl_Text_Buffer *app_text_buffer = NULL;
Fl_Double_Window *app_window = NULL;
Fl_Menu_Bar *app_menu_bar = NULL;

bool text_changed = false;
char app_filename[FL_PATH_MAX] = "";

void build_app_menu_bar()
{
	app_window->begin();
	app_menu_bar = new Fl_Menu_Bar(0, 0, app_window->w(), 25);
    app_menu_bar->add("File/New", FL_COMMAND+'n', menu_new_callback);
	app_menu_bar->add("File/Open", FL_COMMAND+'o', menu_open_callback, NULL, FL_MENU_DIVIDER);
	app_menu_bar->add("File/Save", FL_COMMAND+'s', menu_save_callback);
	app_menu_bar->add("File/Save as...", FL_COMMAND+'S', menu_saveas_callback, NULL, FL_MENU_DIVIDER);
    app_menu_bar->add("File/Quit Editor", FL_COMMAND+'q', menu_quit_callback);
    //app_window->callback(menu_quit_callback);
    app_window->end();

    //int ix = app_menu_bar->find_index(menu_quit_callback);
	//app_menu_bar->insert(ix, "Open", FL_COMMAND+'o', menu_open_callback, NULL, FL_MENU_DIVIDER);
	//app_menu_bar->insert(ix+1, "Save", FL_COMMAND+'s', menu_save_callback);
	//app_menu_bar->insert(ix+2, "Save as...", FL_COMMAND+'S', menu_saveas_callback, NULL, FL_MENU_DIVIDER);
}

void build_main_editor()
{
	app_window->begin();
	app_text_buffer = new Fl_Text_Buffer();
	app_text_buffer->add_modify_callback(text_changed_callback, NULL);
	app_editor = new Fl_Text_Editor(0, app_menu_bar->h(), app_window->w(), app_window->h() - app_menu_bar->h());
	app_editor->buffer(app_text_buffer);
	app_editor->textfont(FL_COURIER);
	app_window->resizable(app_editor);
	app_window->end();

	//int ix = app_menu_bar->find_index(menu_quit_callback);
	//app_menu_bar->insert(ix, "New", FL_COMMAND+'n', menu_new_callback);
}

int args_handler(int argc, char **argv, int &i)
{
	if (argv && argv[i] && argv[i][0] != '-')
	{
		load(argv[i]);
		i++;
		return 1;
	}
	return 0;
}

int handle_args_and_run(int argc, char **argv)
{
	int i = 0;
	Fl::args_to_utf8(argc, argv);
	Fl::args(argc, argv, i, args_handler);
	fl_open_callback(load);
	app_window->show(argc, argv);
	return Fl::run();
}

int main(int argc, char **argv)
{
	app_window = new Fl_Double_Window(640, 480, "Text Editor");
	build_app_menu_bar();
	build_main_editor();
	// app_window->show(argc, argv);
	// return Fl::run();
	return handle_args_and_run(argc, argv);
}