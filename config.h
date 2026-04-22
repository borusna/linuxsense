#ifndef CONFIG_H
#define CONFIG_H

struct Config {
    int r = 0;
    int g = 0;
    int b = 0;
};

int load_config(const char *filename, Config &cfg);

#endif
