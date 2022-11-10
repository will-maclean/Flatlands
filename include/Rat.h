//
// Created by will on 10/11/22.
//

#pragma once

#include <string>
#include "olcPixelGameEngine.h"
#include "Entity.h"

class Rat : public Entity{
public:
    Rat(olc::vf2d location);

    bool tick(Game* game, float fElapsedTime) override;

};
