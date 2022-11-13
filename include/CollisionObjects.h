#pragma once

#include "olcPixelGameEngine.h"
#include <memory>


class Rectangle {
public:
    Rectangle(olc::vf2d anchorLocation, float width, float height){
        this->mAnchorLocation = anchorLocation;
        this->mWidth = width;
        this->mHeight = height;
    }

    //TODO: can we make this nicer? Probably

    bool collision(Rectangle* otherRect) {
        return ((otherRect->mAnchorLocation.x < mAnchorLocation.x + mWidth)
                && (mAnchorLocation.x < otherRect->mAnchorLocation.x + otherRect->mWidth))
                && ((otherRect->mAnchorLocation.y < mAnchorLocation.y + mHeight)
                && (mAnchorLocation.y < otherRect->mAnchorLocation.y + otherRect->mHeight));
    }

    bool collision(std::unique_ptr<Rectangle> otherRect){
        return ((otherRect->mAnchorLocation.x < mAnchorLocation.x + mWidth)
                && (mAnchorLocation.x < otherRect->mAnchorLocation.x + otherRect->mWidth))
                && ((otherRect->mAnchorLocation.y < mAnchorLocation.y + mHeight)
                && (mAnchorLocation.y < otherRect->mAnchorLocation.y + otherRect->mHeight));
    }

    bool collision(std::shared_ptr<Rectangle> otherRect){
        return ((otherRect->mAnchorLocation.x < mAnchorLocation.x + mWidth)
                && (mAnchorLocation.x < otherRect->mAnchorLocation.x + otherRect->mWidth))
                && ((otherRect->mAnchorLocation.y < mAnchorLocation.y + mHeight)
                && (mAnchorLocation.y < otherRect->mAnchorLocation.y + otherRect->mHeight));
    }

    olc::vf2d getAnchorLocation() const {
        return mAnchorLocation;
    }

    float getWidth() const {
        return mWidth;
    }

    float getHeight() const {
        return mHeight;
    }

private:
    olc::vf2d mAnchorLocation;
    float mWidth;
    float mHeight;
};