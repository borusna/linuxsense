#include "config.h"
#include <ini.h>
#include <cstring>
#include <cstdlib>

static int handler(void *user, const char *section, const char *name, const char *value) {
    Config *cfg = static_cast<Config *>(user);

    if (std::strcmp(section, "keyboardcolor") == 0) {
        if (std::strcmp(name, "r") == 0) cfg->r = std::atoi(value);
        if (std::strcmp(name, "g") == 0) cfg->g = std::atoi(value);
        if (std::strcmp(name, "b") == 0) cfg->b = std::atoi(value);
    }
    return 1;
}

int load_config(const char *filename, Config &cfg) {
    return ini_parse(filename, handler, &cfg);
}
