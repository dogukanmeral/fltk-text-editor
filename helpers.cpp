#include "helpers.h"
#include <FL/fl_ask.H>

extern Fl_Text_Buffer *app_text_buffer;
extern Fl_Double_Window *app_window;
extern Fl_Text_Editor *app_editor;

extern char last_replace_text[1024];
extern bool text_changed;
extern char app_filename[FL_PATH_MAX];


void update_title()
{
	const char *fname = NULL;
	if (app_filename[0])
		fname = fl_filename_name(app_filename);
	if (fname)
	{
		char buf[FL_PATH_MAX + 3];
		buf[FL_PATH_MAX + 2] = '\0';
		if (text_changed)
		{
			snprintf(buf, FL_PATH_MAX+2, "%s *", fname);
		}
		else
		{
			snprintf(buf, FL_PATH_MAX+2, "%s", fname);
		}
		app_window->copy_label(buf);
	}
	else
	{
		app_window->label("Text Editor");
	}
}

void set_changed(bool v)
{
	if (v != text_changed)
	{
		text_changed = v;
		update_title();
	}
}

void set_filename(const char *new_filename)
{
	if (new_filename)
	{
		fl_strlcpy(app_filename, new_filename, FL_PATH_MAX);
	}
	else
	{
		app_filename[0] = 0;
	}
	update_title();
}

void load(char const *filename)
{
	if (app_text_buffer->loadfile(filename) == 0)
	{
		set_filename(filename);
		set_changed(false);
	}
	else
	{
		fl_alert("Failed to load file: \'%s\'\n%s", filename, strerror(errno));
	}
}

void find_next(const char *needle)
{
	int pos = app_editor->insert_position();
	int found = app_text_buffer->search_forward(pos, needle, &pos);
	
	if (found)
	{
		app_text_buffer->select(pos	, pos + (int)strlen(needle));
		app_editor->insert_position(pos + (int)strlen(needle));
		app_editor->show_insert_position();
	}
	else
	{
		fl_alert("No further occurences of '%s' found!", needle);
	}
}

void replace_selection(const char *new_text)
{
	int start, end;
	if (app_text_buffer->selection_position(&start, &end))
	{
		app_text_buffer->remove_selection();
		app_text_buffer->insert(start, new_text);
		app_text_buffer->select(start, start + (int)strlen(new_text));
		app_editor->insert_position(start + (int)strlen(new_text));
		app_editor->show_insert_position();
	}
}