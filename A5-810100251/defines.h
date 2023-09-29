#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

const string GAME_WINDOW = "star-wars";
const char MOVING_ENEMY = 'M';
const char FIXED_ENEMY = 'E';
const char MAIN_SHIP = 'S';

#define SHIELD_IMAGE "Shield.png"
#define SHOT_POWER_IMAGE "Speed.png"
#define BACKGROUND_IMAGE "game-background.jpeg"
#define ENEMYS_SHIP_IMAGE "enemys-ship.png"
#define OWN_SHIP_IMAGE "own-ship.png"
#define MAIN_SHIP_IMAGE "main-ship.png"
#define SHOT_IMAGE "Shooot.png"


const string WIN = "LEVEL UP";
const string WIN_THE_GAME = "YOU WIN!!!!!!!!!!";
const string GAME_OVER = "GAME OVER!!!!!!!!!!!!";
const string NICE_SHOT = "NICE SHOT!!!!!";

//Setting------------------------------------------------------------------------------//
const int game_speed = 20;
const int circle_radius = 40;
const int normal_scale = 50;
const int speed_of_movement_enemy_per_frame = 7;
const int per_frame_ships_movement_speed = 7;
const int per_frame_shot_movement_speed = 7;
const int the_bullets_width = 20;
const int the_bullets_length = 55;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>//
const int width_size_exp = 0;
const int our_own_ship = 0;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>//
const int certain_time_disappear_powers = 4;
//--------------------------------------------------------------------------------------//
const int random_mult_shot_place = 200;
const int random_rem_shot_place = 211;
const int random_scl_shot_place = 4;
//--------------------------------------------------------------------------------------//
