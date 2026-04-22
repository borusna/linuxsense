#include <gtk/gtk.h>
#include <ini.h>
#include <cstdio>
#include "config.h"

static void print_hello(GtkWidget * /*widget*/, gpointer /*data*/) {
    g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    Config *cfg = static_cast<Config *>(user_data);

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "LinuxSense");
    gtk_window_set_default_size(GTK_WINDOW(window), 960, 720);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget *slider1 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    gtk_range_set_value(GTK_RANGE(slider1), static_cast<double>(cfg->r));
    gtk_box_append(GTK_BOX(box), slider1);

    GtkWidget *slider2 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    gtk_range_set_value(GTK_RANGE(slider2), static_cast<double>(cfg->g));
    gtk_box_append(GTK_BOX(box), slider2);

    GtkWidget *slider3 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    gtk_range_set_value(GTK_RANGE(slider3), static_cast<double>(cfg->b));
    gtk_box_append(GTK_BOX(box), slider3);

    /*
    GtkWidget *button = gtk_button_new_with_label("Hello World");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), nullptr);
    gtk_window_set_child(GTK_WINDOW(window), button);
    */

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    Config cfg;
    load_config("config.ini", cfg);

    std::printf("KeyboardRGB: %d, %d, %d\n", cfg.r, cfg.g, cfg.b);

    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), &cfg);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
