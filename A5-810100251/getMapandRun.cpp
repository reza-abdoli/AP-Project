#include "rsdl.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

#include "rsdl.hpp"
#include "defines.h"
#include "game.h"


using namespace std;

Game::Game(string file_name)
{
    ifstream input_file(file_name);
    string map;
    int row, column, round;
    getline(input_file, map);
    column = stoi(map.substr(0, map.find(" ")));
    row = stoi(map.substr(map.find(" ")));
    Window *window = new Window(row * normal_scale * row, column * column * normal_scale, GAME_WINDOW);
    getline(input_file, map);
    round = stoi(map);
    for (int j = 0; j < round; j++)
    {
        for (int i = 0; i < column + 1; i++)
        {
            getline(input_file, map);
            the_map.push_back(map);
        }
        getline(input_file, map);
        run(window);
        the_map.clear();
        cout << WIN << endl;
    }
    cout << WIN_THE_GAME << endl;
}

int Game::find_random_digit(int width_of_map)
{
    int random;
    while (true)
    {
        srand(time(0));
        random = rand() % width_of_map;
        if (random > circle_radius && random < width_of_map)
            return random;
    }
    return 0;
}

void Game::check_if_ship_pose_outside_window(int &x_pose_of_ship, int &y_pose_of_ship, int width, int length)
{
    y_pose_of_ship = (width + 1) * (width + 1) * normal_scale;
    x_pose_of_ship = (length + 1) * (length + 1) * normal_scale;
    if (x_pose_of_ship >= (the_map[0].size()) * (the_map[0].size()) * normal_scale)
        x_pose_of_ship = ((the_map[0].size()) * (the_map[0].size())) * normal_scale - circle_radius;
    if (y_pose_of_ship >= (the_map.size()) * (the_map.size()) * normal_scale)
        y_pose_of_ship = (the_map.size()) * (the_map.size()) * normal_scale - circle_radius;
}

void Game::new_fixed_enemy(int x_pose_of_ship, int y_pose_of_ship)
{
    Ships ship(x_pose_of_ship, y_pose_of_ship, the_map);
    Shot shot(x_pose_of_ship, y_pose_of_ship, circle_radius);
    ship.add_shot(shot);
    ships.push_back(ship);
}

void Game::new_movement_enemy(int x_pose_of_ship, int y_pose_of_ship)
{
    Ships ship(x_pose_of_ship, y_pose_of_ship, the_map);
    Shot shot(x_pose_of_ship, y_pose_of_ship, circle_radius);
    ship.is_movement_enemy();
    ship.add_shot(shot);
    ships.push_back(ship);
}

void Game::find_enemys_ship()
{
    for (int width = 0; width < (the_map.size() - 1); width++)
    {
        for (int length = 0; length < the_map[width].size(); length++)
        {
            int y_pose_of_ship;
            int x_pose_of_ship;
            check_if_ship_pose_outside_window(x_pose_of_ship, y_pose_of_ship, width, length);
            if (the_map[width][length] == FIXED_ENEMY)
            {
                new_fixed_enemy(x_pose_of_ship, y_pose_of_ship);
            }
            if (the_map[width][length] == MOVING_ENEMY)
            {
                new_movement_enemy(x_pose_of_ship, y_pose_of_ship);
            }
            if (the_map[width][length] == MAIN_SHIP)
            {
                Ships ship(x_pose_of_ship, y_pose_of_ship, the_map);
                the_main_ship = ship;
            }
        }
    }
}

bool Game::running_game_process(Window *window)
{
    ships[our_own_ship].process_events(window, run_game);
    if (!run_game)
        return true;
    ships[our_own_ship].update_objects(window);
    for (int i = 1; i < ships.size(); i++)
        ships[i].check_movement_point_in_window();
    window->draw_img(BACKGROUND_IMAGE);
    possibility_of_power(window);
    window->update_screen();
    window->clear();
    window->draw_img(BACKGROUND_IMAGE);
    draw_powers_image(window);
    ships[our_own_ship].if_ship_get_power(power);
    ships[our_own_ship].check_ship_powers_time();
    update_enemys_object(window);
    draw_ships_in_window(window);
    window->update_screen();
    check_ship_lost(window);
    if (check_ship_hit_bullets(window))
        return true;
    delay(game_speed);
    window->update_screen();
    return false;
}

void Game::run(Window *window)
{
    int length_scale = the_map[width_size_exp].size() * normal_scale;
    int width_scale = (the_map.size() - 1) * normal_scale;
    run_game = true;
    Ships main_ship(find_random_digit(the_map[width_size_exp].size() * length_scale - circle_radius), (the_map.size() - 1) * width_scale, the_map);
    ships.push_back(main_ship);
    find_enemys_ship();
    while (run_game)
    {
        if (running_game_process(window))
            break;
    }
    window->clear();
    ships.clear();
    for (auto clear_ship_maps_temp : ships)
        clear_ship_maps_temp.clear_map();
    power.clear();
}
