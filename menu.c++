#include <iostream>
#include <vector>
#include <ncurses.h>

#include "Headers/menu.hpp"
#include "Headers/utils.hpp"
#include "Headers/colors.hpp"

menu::menu(coord size, coord position, std::string title) {
    this->size = size;
    this->position = position;
    this->title = title;
}

option::option(int id, std::string text) {
    this->id = id;
    this->text = text;
}

void menu::setup() {
    WINDOW * window = subwin(
        stdscr, 
        this->size.y, 
        this->size.x, 
        this->position.y, 
        this->position.x
    );

    nodelay(window, TRUE);

    this->window = window;
}

option menu::get_selected_option() {
    return this->options[this->selected_option];
}

void menu::update() {
    for (int option_index = 0; option_index < this->options.size(); option_index++) {
        option * option = &this->options[option_index];

        if (option_index == this->selected_option) {
            attron(COLOR_PAIR(colors::codes::SELECTION));
        }
        else {
            attron(COLOR_PAIR(colors::codes::ERROR));
        }

        coord option_position(
            this->size.x / 2 - option->text.length() / 2,
            option_index * 2 + 2
        );
        option->position = option_position;
        utils::window_print_at(this->window, option_position, option->text);
    }

    option selected_option = this->get_selected_option();
    coord selected_option_position = selected_option.position;
    selected_option_position.x -= 2;
    utils::window_print_at(this->window, selected_option_position, "> ");

    box(this->window, 0, 0);

    utils::window_print_at(
        this->window,
        coord(
            this->size.x / 2 - this->title.length() / 2,
            0
        ),
        this->title
    );

    char input = wgetch(this->window);

    if (input == 'w') {
        this->selected_option = (this->selected_option - 1) % this->options.size(); 
    }
    else if (input == 's') {
        this->selected_option = (this->selected_option + 1) % this->options.size(); 
    }

    wrefresh(this->window);
}

void menu::add_option(int id, std::string text) {
    this->options.push_back(option(
        id,
        text
    ));
}

void menu::remove_option(int id) {
    int option_index = 0;
    
    for (option_index; option_index < this->options.size(); option_index++) {
        if (this->options[option_index].id == id) {
            break;
        }
    }

    this->options.erase(this->options.begin() + option_index);
}