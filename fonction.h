int acceuil(SDL_Window* window,SDL_Renderer* renderer );

void verifierEstCercle(SDL_Rect* destRobot,SDL_Rect* destC1,SDL_Rect* destC2,SDL_Rect* destC3,int space);

void detecterCollision(SDL_Rect* destRobot,SDL_Rect* destC1,SDL_Rect* destC2,SDL_Rect* destC3);

void rejouer(SDL_Rect* Robot,SDL_Renderer* renderer );
