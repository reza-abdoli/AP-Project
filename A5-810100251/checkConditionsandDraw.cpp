#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

#include "rsdl.hpp"
#include "defines.h"
#include "game.h"

using namespace std;

bool Game::check_ship_lost(Window *window)
{
    for (int i = 1; i < ships.size(); i++)
    {
        if (ships[i].if_hit_bullet(ships[our_own_ship], window))
        {
            cout << GAME_OVER << endl;
            exit(0);
        }
    }
    return false;
}

bool Game::check_ship_hit_bullets(Window *window)
{
    int checker_for_speed_power = 0;
    int checker_for_shield_power = 0;
    for (int i = 1; i < ships.size(); i++)
    {
        if (ships[our_own_ship].if_hit_bullet(ships[i], window))
        {
            srand(time(NULL));
            if (rand() % 2 == 1 && checker_for_shield_power == 0)
            {
                power.push_back(ships[i].get_point_of_power(true));
                checker_for_speed_power = 1;
            }
            if (rand() % 2 == 0 && checker_for_speed_power == 0)
            {
                checker_for_shield_power = 1;
                power.push_back(ships[i].get_point_of_power(false));
            }
            ships.erase(ships.begin() + i);
            checker_for_shield_power = 0;
            checker_for_speed_power = 0;
        }
    }
    if (ships[our_own_ship].if_hit_bullet_to_main_ship(the_main_ship))
    {
        cout<<"LOST"<<endl;
        exit(0);
    }
    if (ships.size() == 1)
        return true;
    return false;
}

void Game::possibility_of_power(Window *window)
{
    for (int i = 0; i < power.size(); i++)
    {
        if (power[i].the_power_is_shield)
        {
            if (power[i].time_of_hit + certain_time_disappear_powers >= time(NULL))
            {
                window->draw_img(SHIELD_IMAGE, Rectangle(power[i].x_loc - circle_radius, power[i].y_loc - circle_radius, circle_radius * 2, circle_radius * 2));
                continue;
            }
        }
        if (!power[i].the_power_is_shield)
        {
            if (power[i].time_of_hit + certain_time_disappear_powers >= time(NULL))
            {
                window->draw_img(SHOT_POWER_IMAGE, Rectangle(power[i].x_loc - circle_radius, power[i].y_loc - circle_radius, circle_radius * 2, circle_radius * 2));
                continue;
            }
        }
        power.erase(power.begin() + i);
    }
}

void Game::draw_ships_in_window(Window *window)
{
    for (int i = 1; i < ships.size(); i++)
        ships[i].draw(window, ENEMYS_SHIP_IMAGE);
    ships[our_own_ship].draw(window, OWN_SHIP_IMAGE);
    if (ships[our_own_ship].check_has_shield())
        ships[our_own_ship].draw(window, SHIELD_IMAGE);
    the_main_ship.draw(window, MAIN_SHIP_IMAGE);

    for (auto the_ships : ships)
        the_ships.draw_screen(window);
}

void Game::draw_powers_image(Window *window)
{
    for (int i = 0; i < power.size(); i++)
    {
        if (power[i].the_power_is_shield)
            window->draw_img(SHIELD_IMAGE, Rectangle(power[i].x_loc - circle_radius, power[i].y_loc - circle_radius, circle_radius * 2, circle_radius * 2));
        if (!power[i].the_power_is_shield)
            window->draw_img(SHOT_POWER_IMAGE, Rectangle(power[i].x_loc - circle_radius, power[i].y_loc - circle_radius, circle_radius * 2, circle_radius * 2));
    }
}

void Game::update_enemys_object(Window *window)
{
    for (int i = 1; i < ships.size(); i++)
        ships[i].update_objects_for_enemy(window, (i * random_mult_shot_place));
}