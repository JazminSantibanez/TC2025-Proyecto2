#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/server_functions.h"

char *get_html() {
  return "<div style=\"display: flex; align-items: center; justify-content: center; width: 100%; height: 100%; flex-direction: column; background-color: #131516;\"> \
    <p style=\"color: #3391ff; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;\"> \
        EZ Clap \
    </p> \
    <img src=\"https://cdn.betterttv.net/emote/60b4349bf8b3f62601c35e7e/3x.gif\"> \
    </div>\")";
}
