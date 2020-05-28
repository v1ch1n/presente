#include "entity.h"

#include <math.h>

int entity_physics(const level *lvl, entity *ent){
    // Update position
    ent->x += ent->vx;
    ent->y += ent->vy;

    // Check if the center is inside a solid cell
    int tile_x = (int) floor(ent->x/TILE_SIZE);
    int tile_y = (int) floor(ent->y/TILE_SIZE);
    char cell = level_get(lvl,tile_x,tile_y);

    if(cell=='#') return 1;

    if(ent->powerup == 1){
    	// Delete the power-up from the level and replace it with a free cell
    	lvl->cells[tile_y][tile_x] = '.';
    	// Return different values depending of the power-up
    	if(cell == 'D'){
    		return 2;
    	}
    	else if(cell == 'S'){
    		return 3;
    	}
    	else if(cell == 'H'){
    		return 4;
    	}
    }
    return 0;
}

int entity_collision(const entity *ent1, const entity *ent2){
    // If one of the enitities is dead, there is no collision
    if(ent1->dead || ent2->dead) return 0;

    // Compute the distance between the two centers
    float delta_x = ent1->x - ent2->x;
    float delta_y = ent1->y - ent2->y;
    float delta_mag = sqrt(delta_x*delta_x+delta_y*delta_y);

    // Return 1 if the distance is smaller than the sum of both radious
    return (delta_mag < ent1->rad + ent2->rad);
}
