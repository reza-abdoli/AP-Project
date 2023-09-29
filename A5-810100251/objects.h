#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "rsdl.hpp"

#ifndef OBJECTS_H
#define OBJECTS_H 

using namespace std;

struct Power
{
    int x_loc;
    int y_loc;
    int time_of_hit;
    bool the_power_is_shield;
};

class Shot
{
public:
    Shot(int x, int y, int movement);
    int update_shot_loc(int shot_movement);
    void draw_line(Window *window);
    int get_y_dst() { return y_dst; }
    int get_x_dst() { return x_dst; }
    int get_y_src() { return y_src; }

private:
    int x_src;
    int y_src;
    int x_dst;
    int y_dst;
};

class Ships
{
public:
    Ships(){};
    Ships(int src_loc_x, int src_loc_y, vector<string> the_map);
    void process_events(Window *window, bool &run_game);
    void update_objects(Window *window);
    void draw_screen(Window *window);
    void draw(Window *window, string the_ship_image_address);
    void handle_key_press(char key, Window *window);
    void handle_key_release(char key);
    void clear_map() { theMap.clear(); }
    void add_shot(Shot shoot);
    void update_objects_for_enemy(Window *window, int shot_by_time);
    bool if_hit_bullet(Ships &ship, Window *window);
    void is_movement_enemy();
    void check_movement_point_in_window();
    bool if_hit_bullet_to_main_ship(Ships the_main_ship);
    Power get_point_of_power(int the_power_is_shield);
    void if_ship_get_power(vector<Power> shield);
    bool check_has_shield() { return get_shield; }
    void check_ship_powers_time();

private:
    int x_location_ship;
    int y_location_ship;
    int x_movement = 0;
    int y_movement = 0;
    bool moving_enemy;
    vector<string> theMap;
    vector<Shot> shot;
    bool get_shield = false;
    int time_of_power;
    bool get_speed = false;
};

#endif