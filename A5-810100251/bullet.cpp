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


Shot::Shot(int x, int y, int movement)
{
    x_src = x;
    y_src = y + movement;
    x_dst = x;
    y_dst = y + 2 * movement;
}

bool Ships::if_hit_bullet(Ships &ship, Window *window)
{
    for (int i = 0; i < shot.size(); i++)
    {
        if( ((shot[i].get_y_dst() >= ship.y_location_ship - circle_radius && shot[i].get_y_dst() <= ship.y_location_ship + circle_radius) 
        && (shot[i].get_x_dst() >= ship.x_location_ship - circle_radius && shot[i].get_x_dst() <= ship.x_location_ship + circle_radius))
        ||  sqrt(pow(ship.x_location_ship-x_location_ship,2) + pow(ship.y_location_ship-y_location_ship,2)) < circle_radius)
        {
            if (ship.check_has_shield() == true)
                return false;
            return true;
        }
    }
    return false;
}

bool Ships::if_hit_bullet_to_main_ship(Ships the_main_ship)
{
    if(sqrt(pow(the_main_ship.x_location_ship-x_location_ship,2) + pow(the_main_ship.y_location_ship-y_location_ship,2)) < circle_radius) 
        return true;
    for (int i = 0; i < shot.size(); i++)
    {
        if( ((shot[i].get_y_src() >= the_main_ship.y_location_ship - circle_radius && shot[i].get_y_src() <= the_main_ship.y_location_ship + circle_radius) 
        && (shot[i].get_x_dst() >= the_main_ship.x_location_ship - circle_radius && shot[i].get_x_dst() <= the_main_ship.x_location_ship + circle_radius))) 
        {
            return true;
        }
    }
    return false;
}

void Ships::add_shot(Shot shoot)
{
    shot.push_back(shoot);
}

int Shot::update_shot_loc(int shot_movement)
{
    y_src = y_src + shot_movement;
    y_dst = y_dst + shot_movement;
    return y_dst;
}
