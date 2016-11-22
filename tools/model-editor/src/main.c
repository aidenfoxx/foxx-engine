#include <stdint.h>
#include <gtk/gtk.h>
#include <archive.h>
#include <archive_entry.h>

#include "obj.h"

int modelLength;
uint8_t *model;

int diffuseLength;
uint8_t *diffuse;

int normalLength;
uint8_t *normal;

int specularLength;
uint8_t *specular;

GtkBuilder *builder;
GtkWidget *window;

int loadFile(const char *path, uint8_t **buffer)
{
	FILE *file = fopen(path, "rb");

	if (!file)
	{
		return 0;
	}

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	*buffer = malloc(length * sizeof(uint8_t));

	if (length != fread(*buffer, sizeof(uint8_t), length, file)) 
	{ 
		free(buffer);
		return 0;
	}

	fclose(file);

	return length;
}

void showError(const char *message)
{
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, message);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

int parseParameters(const char *names, const char *values, const char *buffer)
{
	return 1;
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "assets/ui/model-editor.ui", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	gtk_builder_connect_signals(builder, NULL);

	gtk_widget_show(window);
	gtk_main();

	exit(EXIT_SUCCESS);
}

G_MODULE_EXPORT void destroyWindow()
{
	gtk_main_quit();
}

G_MODULE_EXPORT void clearModel()
{
	GtkFileChooser *button = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "filechooserbutton_model"));
	gtk_file_chooser_set_filename(button, NULL);
	free(model);
	model = NULL;
}

G_MODULE_EXPORT void clearDiffuse()
{
	GtkFileChooser *button = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "filechooserbutton_diffuse"));
	gtk_file_chooser_set_filename(button, NULL);
	free(diffuse);
	diffuse = NULL;
}

G_MODULE_EXPORT void clearNormal()
{
	GtkFileChooser *button = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "filechooserbutton_normal"));
	gtk_file_chooser_set_filename(button, NULL);
	free(normal);
	normal = NULL;
}

G_MODULE_EXPORT void clearSpecular()
{
	GtkFileChooser *button = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "filechooserbutton_specular"));
	gtk_file_chooser_set_filename(button, NULL);
	free(specular);
	specular = NULL;
}

G_MODULE_EXPORT void setModel(GtkFileChooserButton *button)
{
	char *file = gtk_file_chooser_get_filename((GtkFileChooser*)button);
	uint8_t *obj;

	if (loadFile(file, &obj) == 0)
	{
		clearModel();
		showError("There was a problem loading the mesh.");
	}

	if ((modelLength = objToFem(obj, &model)) == 0)
	{
		clearModel();
		showError("There was a problem processing the mesh.");
	}

	// debugModel();

	free(obj);
}

G_MODULE_EXPORT void setDiffuse(GtkFileChooserButton *button)
{
	char *file = gtk_file_chooser_get_filename((GtkFileChooser*)button);

	if ((diffuseLength = loadFile(file, &diffuse)) == 0)
	{
		clearDiffuse();
		showError("There was a problem loading the diffuse texture.");
	}
}

G_MODULE_EXPORT void setNormal(GtkFileChooserButton *button)
{
	char *file = gtk_file_chooser_get_filename((GtkFileChooser*)button);

	if ((normalLength = loadFile(file, &normal)) == 0)
	{
		clearNormal();
		showError("There was a problem loading the normal texture.");
	}
}

G_MODULE_EXPORT void setSpecular(GtkFileChooserButton *button)
{
	char *file = gtk_file_chooser_get_filename((GtkFileChooser*)button);

	if ((specularLength = loadFile(file, &specular)) == 0)
	{
		clearSpecular();
		showError("There was a problem loading the normal texture.");
	}
}

G_MODULE_EXPORT void openFile()
{
	GtkFileFilter *filter = GTK_FILE_FILTER(gtk_builder_get_object(builder, "filefilter_fem"));
	GtkWidget *fileChooser = gtk_file_chooser_dialog_new("Select a File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "_Open", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_CANCEL, NULL);

	gtk_window_set_transient_for(GTK_WINDOW(fileChooser), GTK_WINDOW(window));
	gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(fileChooser), filter);

	if (gtk_dialog_run(GTK_DIALOG(fileChooser)) == GTK_RESPONSE_ACCEPT)
	{
		char *file;
		file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileChooser));

		clearModel();
		clearDiffuse();
		clearNormal();
		clearSpecular();

		struct archive *archive = archive_read_new();
		struct archive_entry *entry;

		archive_read_support_format_tar(archive);
		archive_read_support_filter_compress(archive);
		archive_read_open_filename(archive, file, 10240);

		while (archive_read_next_header(archive, &entry) == ARCHIVE_OK)
		{
			int64_t length = archive_entry_size(entry);
			const char *filename = archive_entry_pathname(entry);

			if (!strcmp(filename, "model"))
			{
				modelLength += (int)length;
				model = malloc(modelLength);

				if (archive_read_data(archive, model, length) == 0)
				{
					showError("There was a problem loading the mode.");
				}
			}

			if (!strcmp(filename, "diffuse"))
			{
				diffuseLength += (int)length;
				diffuse = malloc(diffuseLength);

				if (archive_read_data(archive, diffuse, length) == 0)
				{
					showError("There was a problem loading the mode.");
				}
			}

			if (!strcmp(filename, "normal"))
			{
				normalLength += (int)length;
				normal = malloc(normalLength);

				if (archive_read_data(archive, normal, length) == 0)
				{
					showError("There was a problem loading the mode.");
				}
			}

			if (!strcmp(filename, "specular"))
			{
				specularLength += (int)length;
				specular = malloc(specularLength);

				if (archive_read_data(archive, specular, length) == 0)
				{
					showError("There was a problem loading the mode.");
				}
			}
		}

		archive_read_close(archive);
		archive_read_free(archive);
	}

	gtk_widget_destroy(fileChooser);
}

G_MODULE_EXPORT void exportFile(GtkButton *button)
{
	char *file = NULL;

	GtkWidget *fileChooser = gtk_file_chooser_dialog_new("Export File", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, "_Save", GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_CANCEL, NULL);

	gtk_window_set_transient_for(GTK_WINDOW(fileChooser), GTK_WINDOW(window));
	gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(fileChooser), "untitled.fem");

	if (gtk_dialog_run(GTK_DIALOG(fileChooser)) == GTK_RESPONSE_ACCEPT)
	{
		file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileChooser));
	}

	gtk_widget_destroy(fileChooser);

	if (file != NULL)
	{
		/**
		 * Create archive for the content.
		 */
		struct archive *archive = archive_write_new();
		struct archive_entry *entry;

		archive_write_add_filter_compress(archive);
		archive_write_set_format_pax_restricted(archive);
		archive_write_open_filename(archive, file);

		if (model)
		{
			entry = archive_entry_new();

			archive_entry_set_pathname(entry, "model");
			archive_entry_set_size(entry, modelLength);
			archive_entry_set_filetype(entry, AE_IFREG);
			archive_entry_set_perm(entry, 0644);
			archive_write_header(archive, entry);
			archive_write_data(archive, model, modelLength);
			archive_entry_free(entry);
		}

		if (diffuse)
		{
			entry = archive_entry_new();

			archive_entry_set_pathname(entry, "diffuse");
			archive_entry_set_size(entry, diffuseLength);
			archive_entry_set_filetype(entry, AE_IFREG);
			archive_entry_set_perm(entry, 0644);
			archive_write_header(archive, entry);
			archive_write_data(archive, diffuse, diffuseLength);
			archive_entry_free(entry);
		}

		if (normal)
		{
			entry = archive_entry_new();

			archive_entry_set_pathname(entry, "normal");
			archive_entry_set_size(entry, normalLength);
			archive_entry_set_filetype(entry, AE_IFREG);
			archive_entry_set_perm(entry, 0644);
			archive_write_header(archive, entry);
			archive_write_data(archive, normal, normalLength);
			archive_entry_free(entry);
		}

		if (specular)
		{
			entry = archive_entry_new();

			archive_entry_set_pathname(entry, "specular");
			archive_entry_set_size(entry, specularLength);
			archive_entry_set_filetype(entry, AE_IFREG);
			archive_entry_set_perm(entry, 0644);
			archive_write_header(archive, entry);
			archive_write_data(archive, specular, specularLength);
			archive_entry_free(entry);
		}

		archive_write_close(archive);
		archive_write_free(archive);

		showError("File exported successfully.");
	}
}