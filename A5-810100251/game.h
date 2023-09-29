#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

#ifndef GAME_H
#define GAME_H 

#include "rsdl.hpp"
#include "objects.h"

using namespace std;


class Game
{
public:
    Game(string file_name);
    void run(Window *window);
    bool running_game_process(Window *window);
    int find_random_digit(int width_of_map);
    void find_enemys_ship();
    bool check_ship_lost(Window *window);
    bool check_ship_hit_bullets(Window *window);
    void check_if_ship_pose_outside_window(int &x_pose_of_ship, int &y_pose_of_ship, int width, int length);
    void new_fixed_enemy(int x_pose_of_ship, int y_pose_of_ship);
    void new_movement_enemy(int x_pose_of_ship, int y_pose_of_ship);
    void draw_ships_in_window(Window *window);
    void possibility_of_power(Window *window);
    void draw_powers_image(Window *window);
    void update_enemys_object(Window *window);

private:
    vector<string> the_map;
    bool run_game;
    vector<Ships> ships;
    Ships the_main_ship;
    vector<Power> power;
};

#endif
