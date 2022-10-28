#include "CollisionUtils.h"
#include "Tile.h"
#include "Entity.h"

olc::vf2d getNewLocation(std::vector<Tile*> tiles, Entity* entity, float touchThreshold, olc::vf2d newLocation, olc::vf2d oldLocation){
    // tiles -> vector of tiles that are currently colliding with the entity
    // entity -> entity that we need to find a new locaiton for
    // touchThreshold -> the max distance between an entity and a tile for us to call them touching
    // oldLocation -> last location of the entity
    // newLocatoin -> new location of entity (with collision(s)
    
    olc::vf2d searchPath = oldLocation - newLocation; // invariant -> searchPath.mag() > 0

    int nTrials = searchPath.mag() / (2 * touchThreshold);

    for(int i = 1; i < nTrials; i++){
        // make a new location to test
        olc::vf2d addVec = i * searchPath.norm() / (2 * touchThreshold);
        olc::vf2d testLocation = newLocation + addVec;

        bool collisionOccured = false;
        for(auto tile : tiles){
            olc::vf2d tileAnchorLocation = tile->getAnchorLocation();
            bool noCollision = (tileAnchorLocation.x + tile->getTileWidth() < testLocation.x) 
                && (tileAnchorLocation.y + tile->getTileHeight() < testLocation.y) 
                && (testLocation.x + entity->getWidth() < tileAnchorLocation.x) 
                && (testLocation.y + entity->getHeight() < tileAnchorLocation.y);
            
            bool collision = !noCollision;  // easier to do this then to try and write the test the other way around

            collisionOccured = collisionOccured || collision;
        }

        if (!collisionOccured){
            return testLocation;
        }
    }

    // if can't find a suitable location, just resturn the old position. Should be fine right?
    return oldLocation;

}
