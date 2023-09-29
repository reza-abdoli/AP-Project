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

Power Ships::get_point_of_power(int the_power_is_shield)
{
    Power this_enemy_power;
    this_enemy_power.y_loc = y_location_ship;
    this_enemy_power.x_loc = x_location_ship;
    this_enemy_power.time_of_hit = time(NULL);
    if (the_power_is_shield)
        this_enemy_power.the_power_is_shield = true;
    else
        this_enemy_power.the_power_is_shield = false;
    return this_enemy_power;
}

void Ships::if_ship_get_power(vector<Power> power)
{
    for (auto the_shield : power)
    {
        if ((the_shield.y_loc >= y_location_ship - circle_radius && the_shield.y_loc <= y_location_ship + circle_radius) 
        && (the_shield.x_loc >= x_location_ship - circle_radius && the_shield.x_loc <= x_location_ship + circle_radius))
        {
            if (the_shield.the_power_is_shield)
            {
                get_shield = true;
                time_of_power = time(NULL);
            }
            if (!the_shield.the_power_is_shield)
            {
                get_speed = true;
                time_of_power = time(NULL);
            }
            break;
        }
    }
}

void Ships::check_ship_powers_time()
{
    if (get_shield == true)
    {
        if (time_of_power + certain_time_disappear_powers <= time(NULL))
            this->get_shield = false;
    }
    if (get_speed == true)
    {
        if (time_of_power + certain_time_disappear_powers <= time(NULL))
            this->get_speed = false;
    }
}
