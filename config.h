#ifndef CONFIG_H
#define CONFIG_H
#include <gtk/gtk.h>

struct Config {
    int r = 0;
    int g = 0;
    int b = 0;
    int hid_fd = -1;
};

// Another struct for the slider data to tell which slider is which R = 0 G = 1 B = 2
    struct SliderData {
        Config *cfg;
        GtkWidget *panel;
        int channel;
    };

int load_config(const char *filename, Config &cfg);

#endif
