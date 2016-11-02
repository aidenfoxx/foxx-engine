#include <stdint.h>
#include <gtk/gtk.h>

typedef struct {
	uint8_t *vertices;
	uint8_t *uvs;
	uint8_t *normals;
	uint8_t *indices;
	uint8_t *diffuseTexture;
	uint8_t *normalTexture;
	uint8_t *specularTexture; 
} Model;

Model mainModel;

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	GtkBuilder *builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "assets/ui/model-editor.ui", NULL);

	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	gtk_builder_connect_signals(builder, NULL);

	g_object_unref(builder);

	gtk_widget_show(window);
	gtk_main();

	return 0;
}

G_MODULE_EXPORT void destroyWindow()
{
	gtk_main_quit();
}