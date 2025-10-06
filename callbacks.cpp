#include "callbacks.h"
#include "helpers.h"

extern Fl_Text_Buffer *app_text_buffer;

extern bool text_changed;
extern char app_filename[FL_PATH_MAX];

void menu_quit_callback(Fl_Widget *, void *)
{
	if (text_changed)
	{
		int c = fl_choice("Changes in your text have not been saved.\n"
				  "Do you want to quit the editor anyway?",
				  "Cancel", "Save", "Discard");
		if (c == 0)
			return;
		else if (c == 1)
		{
			menu_save_callback(NULL, NULL);
			return;
		}
	}
	Fl::hide_all_windows();
}

void text_changed_callback(int, int n_inserted, int n_deleted, int, const char*, void*)
{
	if (n_inserted || n_deleted)
		set_changed(true);
}

void menu_new_callback(Fl_Widget*, void*)
{
	app_text_buffer->text("");
	set_changed(false);
}

void menu_saveas_callback(Fl_Widget*, void*)
{
	Fl_Native_File_Chooser file_chooser;
	file_chooser.title("Save File As...");
	file_chooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);

	if (app_filename[0])
	{
		char temp_filename[FL_PATH_MAX];
		fl_strlcpy(temp_filename, app_filename, FL_PATH_MAX);
		const char *name = fl_filename_name(temp_filename);

		if (name)
		{
			file_chooser.preset_file(name);
			temp_filename[name - temp_filename] = 0;
			file_chooser.directory(temp_filename);
		}
	}

	if (file_chooser.show() == 0)
	{
		app_text_buffer->savefile(file_chooser.filename());
		set_filename(file_chooser.filename());
		set_changed(false);
	}
}

void menu_save_callback(Fl_Widget*, void*)
{
	if (!app_filename[0])
	{
		menu_saveas_callback(NULL, NULL);
	}
	else
	{
		app_text_buffer->savefile(app_filename);
		set_changed(false);
	}
}

void menu_open_callback(Fl_Widget*, void*)
{
	if (text_changed)
	{
		int r = fl_choice("Changes in your text have not been saved.\n"
				  "Would you like to save it now?",
				  "Cancel", "Save", "Discard");
		
		if (r == 2)
			return;
		if (r == 1)
			menu_save_callback(NULL, NULL);
	}

	Fl_Native_File_Chooser file_chooser;
	file_chooser.title("Open file...");
	file_chooser.type(Fl_Native_File_Chooser::BROWSE_FILE);

	if (app_filename[0])
	{
		char temp_filename[FL_PATH_MAX];
		fl_strlcpy(temp_filename, app_filename, FL_PATH_MAX);
		const char *name = fl_filename_name(temp_filename);

		if (name)
		{
			file_chooser.preset_file(name);
			temp_filename[name - temp_filename] = 0;
			file_chooser.directory(temp_filename);
		}
	}

	if (file_chooser.show() == 0)
		load(file_chooser.filename());
}