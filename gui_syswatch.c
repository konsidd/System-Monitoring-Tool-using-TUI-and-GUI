#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

GtkWidget *cpu_bar;
GtkWidget *mem_bar;

gboolean update_stats(gpointer data) {
    gdouble cpu = rand() % 100;
    gdouble mem = rand() % 100;

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(cpu_bar), cpu / 100.0);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(cpu_bar), g_strdup_printf("CPU: %.2f%%", cpu));

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(mem_bar), mem / 100.0);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(mem_bar), g_strdup_printf("Memory: %.2f%%", mem));

    return TRUE; // keep running
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    srand(time(NULL));

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SysWatch - GUI Mode");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 15);

    cpu_bar = gtk_progress_bar_new();
    mem_bar = gtk_progress_bar_new();

    gtk_box_pack_start(GTK_BOX(vbox), cpu_bar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), mem_bar, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    g_timeout_add(1000, update_stats, NULL);
    gtk_main();

    return 0;
}
