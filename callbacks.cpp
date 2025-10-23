#include "callbacks.h"

void text_changed_callback(int, int n_inserted, int n_deleted, int, const char*, void*)
{
	if (n_inserted || n_deleted)
		set_changed(true);
}

///////////////////////// MENU FILE CALLBACKS /////////////////////////

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


///////////////////////// MENU EDIT CALLBACKS /////////////////////////

void menu_cut_callback(Fl_Widget*, void *v)
{
	Fl_Text_Editor::kf_cut(0, app_editor);
}

void menu_copy_callback(Fl_Widget*, void *v)
{
	Fl_Text_Editor::kf_copy(0, app_editor);
}
void menu_paste_callback(Fl_Widget*, void *v)
{
	Fl_Text_Editor::kf_paste(0, app_editor);
}

void menu_delete_callback(Fl_Widget*, void *v)
{
	Fl_Text_Editor::kf_delete(0, app_editor);
}

void menu_undo_callback(Fl_Widget*, void *v)
{
	Fl_Text_Editor::kf_undo(0, app_editor);
}

void menu_redo_callback(Fl_Widget*, void *v)
{
	Fl_Text_Editor::kf_redo(0, app_editor);
}

void menu_bg_color_callback(Fl_Widget *, void *v)
{
	double r, g, b;
	int state;

	state = fl_color_chooser("Background Color Chooser", r, g, b);
	if (state == 1) // confirm
	{
		Fl_Color bg_color = fl_color_cube(r, g, b);
		app_editor->color(bg_color);
	}
}

void menu_text_color_callback(Fl_Widget*, void *v)
{
	double r, g, b;
	int state;

	state = fl_color_chooser("Text Color Chooser", r, g, b);
	if (state == 1) // confirm
	{
		Fl_Color text_color = fl_color_cube(r, g, b);
		app_editor->textcolor(text_color);
	}
}

///////////////////////// MENU FIND CALLBACKS /////////////////////////

void menu_find_callback(Fl_Widget*, void *v)
{
	const char *find_text = fl_input("Find in text:", last_find_text);
	if (find_text)
	{
		fl_strlcpy(last_find_text, find_text, sizeof(last_find_text));
		find_next(find_text);
	}
}

void menu_find_next_callback(Fl_Widget*, void *v)
{
	if (last_find_text[0])
	{
		find_next(last_find_text);
	}
	else
	{
		menu_find_callback(NULL, NULL);
	}
}

///////////////////////// MENU REPLACE CALLBACKS /////////////////////////

void menu_replace_callback(Fl_Widget*, void *v)
{
	if (!replace_dialog)
		replace_dialog = new Replace_Dialog("Find and Replace");
	replace_dialog->show();
}

void menu_replace_next_callback(Fl_Widget*, void *v)
{
	if (!last_find_text[0])
	{
		menu_replace_callback(NULL, NULL);
	}
	else
	{
		replace_selection(last_replace_text);
		find_next(last_find_text);
	}
}