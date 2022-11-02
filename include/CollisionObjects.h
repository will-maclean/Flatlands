#pragma once

#include "olcPixelGameEngine.h"
#include <memory>


class Rectangle {
public:
    Rectangle(olc::vf2d anchorLocation, float width, float height){
        this->anchorLocation = anchorLocation;
        this->width = width;
        this->height = height;
    }

    //TODO: can we make this nicer? Probably

    bool collision(Rectangle* otherRect) {
        return ((otherRect->anchorLocation.x < anchorLocation.x + width) 
                && (anchorLocation.x < otherRect->anchorLocation.x + otherRect->width))
                && ((otherRect->anchorLocation.y < anchorLocation.y +  height) 
                && (anchorLocation.y < otherRect->anchorLocation.y + otherRect->height));
    }

    bool collision(std::unique_ptr<Rectangle> otherRect){
        return ((otherRect->anchorLocation.x < anchorLocation.x + width) 
                && (anchorLocation.x < otherRect->anchorLocation.x + otherRect->width))
                && ((otherRect->anchorLocation.y < anchorLocation.y +  height) 
                && (anchorLocation.y < otherRect->anchorLocation.y + otherRect->height));
    }

    bool collision(std::shared_ptr<Rectangle> otherRect){
        return ((otherRect->anchorLocation.x < anchorLocation.x + width) 
                && (anchorLocation.x < otherRect->anchorLocation.x + otherRect->width))
                && ((otherRect->anchorLocation.y < anchorLocation.y +  height) 
                && (anchorLocation.y < otherRect->anchorLocation.y + otherRect->height));
    }

    olc::vf2d getAnchorLocation() const {
        return anchorLocation;
    }

    float getWidth() const {
        return width;
    }

    float getHeight() const {
        return height;
    }

private:
    olc::vf2d anchorLocation;
    float width;
    float height;
};