#pragma once

#ifndef MENU
#define MENU

#include <vector>
#include <ncurses.h>
#include <string>
#include <vector>

#include "coord.hpp"

struct option {
    int id;
    std::string text;
    coord position;

    option(int, std::string);
};

class menu {
    public:
        WINDOW * window;
        std::string title;
        coord size, position;
        std::vector<option> options;
        int selected_option = 0;

        menu(coord, coord, std::string);
        void setup();
        void update();
        void add_option(int, std::string);
        void remove_option(int); // Returns 0 if succeeded
        option get_selected_option();
};

#endif