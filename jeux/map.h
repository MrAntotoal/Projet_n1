#include "collisions.h"

typedef struct{
  polygone p;
  int type;
}obstacle;

typedef obstacle *Obstacle;

typedef struct {
  polygone p_zone;
  liste l_obstacle;
}zone;

typedef zone *Zone;

Obstacle cree_obstacle(int type,polygone p);
Zone cree_zone(polygone zone,liste l_obstacle);
void afficher_obstacle(Obstacle o);
void afficher_zone(liste l_obs);
void afficher_map(liste all_zone);


