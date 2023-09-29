#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <math.h>

#include "rsdl.hpp"
#include "objects.h"
#include "defines.h"

using namespace std;

void Ships::is_movement_enemy()
{
     moving_enemy = 1;
    x_movement = speed_of_movement_enemy_per_frame;
 }

void Ships::check_movement_point_in_window()
{
    if (moving_enemy == 1)
    {
        x_location_ship = x_location_ship + x_movement;
        if (x_location_ship + circle_radius > (theMap[width_size_exp].size()) * theMap[width_size_exp].size() * normal_scale)
        {
            x_location_ship = ((theMap[width_size_exp].size()) * theMap[width_size_exp].size() * normal_scale) - circle_radius;
            x_movement = -x_movement;
        }
        if (x_location_ship - circle_radius < 0)
        {
            x_location_ship = circle_radius;
            x_movement = -x_movement;
        }
    }
}

Ships::Ships(int src_loc_x, int src_loc_y, vector<string> the_map)
{
    x_location_ship = src_loc_x;
    y_location_ship = src_loc_y;
    theMap = the_map;
}

void Ships::handle_key_press(char key, Window *window)
{
    switch (key)
    {
    case 'd':
        x_movement = +per_frame_ships_movement_speed;
        break;
    case 'a':
        x_movement = -per_frame_ships_movement_speed;
        break;
    case 'w':
        y_movement = -per_frame_ships_movement_speed;
        break;
    case 's':
        y_movement = +per_frame_ships_movement_speed;
        break;
    case ' ':
        Shot the_new_shot(x_location_ship, y_location_ship, -circle_radius);
        shot.push_back(the_new_shot);
        break;
    }
}

void Ships::handle_key_release(char key)
{
    switch (key)
    {
    case 'd':
        if (x_movement > 0)
            x_movement = 0;
        break;
    case 'a':
        if (x_movement < 0)
            x_movement = 0;
        break;
    case 's':
        if (y_movement > 0)
            y_movement = 0;
        break;
    case 'w':
        if (y_movement < 0)
            y_movement = 0;
        break;
    }
}

void Ships::process_events(Window *window, bool &run_game)
{
    while (window->has_pending_event())
    {
        Event event = window->poll_for_event();
        switch (event.get_type())
        {
        case Event::QUIT:
            run_game = false;
            break;
        case Event::KEY_PRESS:
            handle_key_press(event.get_pressed_key(), window);
            break;
        case Event::KEY_RELEASE:
            handle_key_release(event.get_pressed_key());
            break;
        }
    }
}

void Shot::draw_line(Window *window)
{
    window->draw_img(SHOT_IMAGE, Rectangle(x_src, y_src, the_bullets_width, the_bullets_length));
}

void Ships::update_objects_for_enemy(Window *window, int shot_by_time)
{
    int last_pos_of_shot;
    for (int i = 0; i < shot.size(); i++)
    {
        last_pos_of_shot = shot[i].update_shot_loc(per_frame_shot_movement_speed);
    }
    if (shot[shot.size() - 1].get_y_dst() > (shot_by_time % random_rem_shot_place) * random_scl_shot_place)
    {
        Shot shoot(x_location_ship, y_location_ship, circle_radius);
        this->add_shot(shoot);
    }
}

void Ships::update_objects(Window *window)
{
    int bullets_speed = 1;
    for (int i = 0; i < shot.size(); i++)
    {
        if (get_speed)
            bullets_speed = 2;
        shot[i].update_shot_loc(-(per_frame_shot_movement_speed * bullets_speed));
    }
    x_location_ship = x_location_ship + x_movement;
    y_location_ship = y_location_ship + y_movement;
    if (x_location_ship + circle_radius > (theMap[width_size_exp].size()) * theMap[width_size_exp].size() * normal_scale)
        x_location_ship = ((theMap[width_size_exp].size()) * theMap[width_size_exp].size() * normal_scale) - circle_radius;
    if (x_location_ship - circle_radius < 0)
        x_location_ship = circle_radius;

    if (y_location_ship + circle_radius > (theMap.size() - 1) * normal_scale * (theMap.size() - 1))
        y_location_ship = (theMap.size() - 1) * normal_scale * (theMap.size() - 1) - circle_radius;
    if (y_location_ship - circle_radius < 0)
        y_location_ship = circle_radius;
}

void Ships::draw(Window *window, string the_ship_image_address)
{
    window->draw_img(the_ship_image_address, Rectangle(x_location_ship - circle_radius, y_location_ship - circle_radius, circle_radius * 2, circle_radius * 2));
}

void Ships::draw_screen(Window *window)
{
    for (int i = 0; i < shot.size(); i++)
    {
        shot[i].draw_line(window);
    }
}