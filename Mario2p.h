#include "MainFile.h"

int play2pMario(void); //Plays a 2p mario "turn" returns 0 if terminating, 1 if not, 2 if p1 wins, 3 if p2 wins

void mario2pReset(void); //Resets 2p mario, resetting the internal variables to their defaults

void setLevel(int x); //Sets the internal variable representing the level to the desired level to load (0-3)
