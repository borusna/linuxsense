#include <gtk/gtk.h>
#include <ini.h>
#include <cstdio>
#include "config.h"

static GtkCssProvider *provider = gtk_css_provider_new();


void drawColor(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data) {
    Config *cfg = static_cast<Config*>(data);

    cairo_set_source_rgb(
        cr,
        cfg->r / 255.0,
        cfg->g / 255.0,
        cfg->b / 255.0
    );

    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);
}

void onSliderChanged(GtkRange *range, gpointer data) {
    SliderData *sd = static_cast<SliderData*>(data);
    int value = static_cast<int>(gtk_range_get_value(range));

    if (sd->channel == 0)
        sd->cfg->r = value;
    else if (sd->channel == 1)
        sd->cfg->g = value;
    else if (sd->channel == 2)
        sd->cfg->b = value;

    gtk_widget_queue_draw(sd->panel);
}

static void activate(GtkApplication *app, gpointer user_data) {
    Config *cfg = static_cast<Config *>(user_data);

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "LinuxSense");
    gtk_window_set_default_size(GTK_WINDOW(window), 960, 720);

    gtk_css_provider_load_from_path(provider, "Rslider.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget *labelR = gtk_label_new("Red");
    gtk_widget_set_halign(labelR, GTK_ALIGN_START);
    gtk_widget_set_margin_start(labelR, 10);

    GtkWidget *slider1 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    gtk_range_set_value(GTK_RANGE(slider1), static_cast<double>(cfg->r));
    gtk_widget_add_css_class(slider1, "red-slider");

    gtk_box_append(GTK_BOX(box), labelR);
    gtk_box_append(GTK_BOX(box), slider1);

    GtkWidget *labelG = gtk_label_new("Green");
    gtk_widget_set_halign(labelG, GTK_ALIGN_START);
    gtk_widget_set_margin_start(labelG, 10);

    GtkWidget *slider2 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    gtk_range_set_value(GTK_RANGE(slider2), static_cast<double>(cfg->g));
    gtk_widget_add_css_class(slider2, "green-slider");

    gtk_box_append(GTK_BOX(box), labelG);
    gtk_box_append(GTK_BOX(box), slider2);

    GtkWidget *labelB = gtk_label_new("Blue");
    gtk_widget_set_halign(labelB, GTK_ALIGN_START);
    gtk_widget_set_margin_start(labelB, 10);

    GtkWidget *slider3 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 255, 1);
    gtk_range_set_value(GTK_RANGE(slider3), static_cast<double>(cfg->b));
    gtk_widget_add_css_class(slider3, "blue-slider");

    gtk_box_append(GTK_BOX(box), labelB);
    gtk_box_append(GTK_BOX(box), slider3);

    GtkWidget *ColorPanel = gtk_drawing_area_new();
    gtk_widget_set_size_request(ColorPanel, 200, 100);
    gtk_box_append(GTK_BOX(box), ColorPanel);

    gtk_drawing_area_set_draw_func(
        GTK_DRAWING_AREA(ColorPanel),
        drawColor,
        cfg,
        NULL
    );

    SliderData *dataR = new SliderData{cfg, ColorPanel, 0};
    SliderData *dataG = new SliderData{cfg, ColorPanel, 1};
    SliderData *dataB = new SliderData{cfg, ColorPanel, 2};

    g_signal_connect(slider1, "value-changed", G_CALLBACK(onSliderChanged), dataR);
    g_signal_connect(slider2, "value-changed", G_CALLBACK(onSliderChanged), dataG);
    g_signal_connect(slider3, "value-changed", G_CALLBACK(onSliderChanged), dataB);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    Config cfg;
    load_config("config.ini", cfg);

    std::printf("KeyboardRGB: %d, %d, %d\n", cfg.r, cfg.g, cfg.b);

    GtkApplication *app = gtk_application_new(
        "org.gtk.example",
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(app, "activate", G_CALLBACK(activate), &cfg);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(provider);
    g_object_unref(app);

    return status;
}