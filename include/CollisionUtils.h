#pragma once

#include <vector>
#include "olcPixelGameEngine.h"

class Entity;
class Tile;

olc::vf2d getNewLocation(std::vector<Tile*> tiles, Entity* entity, float touchThreshold, olc::vf2d newLocation, olc::vf2d oldLocation);
