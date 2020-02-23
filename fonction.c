#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include"fonction.h"
#include"constante.h"

int acceuil(SDL_Window* window,SDL_Renderer* renderer ){
	//charger l'image qui servira comme page d'acceuil	
	SDL_Surface* surface = IMG_Load("images/acceuil.jpg");	
	if (!surface)
    	{
        	 	printf("error creating surface\n");
        	 	SDL_DestroyRenderer(renderer);
        	 	SDL_DestroyWindow(window);
        	 	SDL_Quit();
		return 1;
    	}
         SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
         SDL_FreeSurface(surface);
         if (!texture)
         {
           printf("error creating texture: %s\n", SDL_GetError());
           SDL_DestroyRenderer(renderer);
           SDL_DestroyWindow(window);
           SDL_Quit();
           return 1;
         }
	SDL_Rect dest;
         SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
         dest.x = (WINDOW_WIDTH - dest.w) / 2;
         dest.y = WINDOW_HEIGHT;
	//permet d animer l'image en la faisant defiler en haut
         while (dest.y >= -dest.h)
         {
           SDL_RenderClear(renderer);
           dest.y -= 6;
           SDL_RenderCopy(renderer, texture, NULL, &dest);
           SDL_RenderPresent(renderer);
           SDL_Delay(1000/60);
         }
  
}

void verifierEstCercle(SDL_Rect* destRobot,SDL_Rect* destC1,SDL_Rect* destC2,SDL_Rect* destC3,int space){
		//si le robot est dans la meme postion qu'un cercle dans la premiere rangee le robot deplace le cercle vers la 			//deuxieme rangee		
		if((destRobot->x<=destC1->x+15 && destC1->x-15<=destRobot->x)&&(destRobot->y==destC1->y)&& space){
			destRobot->y=WINDOW_HEIGHT-destRobot->h;
		         destC1->y+=WINDOW_HEIGHT-destC1->h;
                  }
		if((destRobot->x<=destC2->x+15 && destC2->x-15<=destRobot->x)&&(destRobot->y==destC2->y)&& space){
			destRobot->y+=WINDOW_HEIGHT-destRobot->h;
		         destC2->y+=WINDOW_HEIGHT-destC2->h;
                  }
		if((destRobot->x<=destC3->x+15 && destC3->x-15<=destRobot->x)&&(destRobot->y==destC3->y)&& space){
			destRobot->y+=WINDOW_HEIGHT-destRobot->h;
		         destC3->y+=WINDOW_HEIGHT-destC3->h;
                  }
}

void detecterCollision(SDL_Rect* destRobot,SDL_Rect* destC1,SDL_Rect* destC2,SDL_Rect* destC3){
		//si le robot depace les bornes de la fenetre en initialise sa position pour qu'il soit toujours visible
		if (destRobot->x <= 0) destRobot->x = 0;
        		if (destRobot->y <= 0) destRobot->y = 0;
        		if (destRobot->x >= WINDOW_WIDTH - destRobot->w) destRobot->x = WINDOW_WIDTH - destRobot->w;
        		if (destRobot->y >= WINDOW_HEIGHT - destRobot->h) destRobot->y= WINDOW_HEIGHT - destRobot->h;
        		if (destC1->y >= WINDOW_HEIGHT - destC1->h) destC1->y= WINDOW_HEIGHT - destC1->h;
        		if (destC2->y >= WINDOW_HEIGHT - destC2->h) destC2->y= WINDOW_HEIGHT - destC2->h;
        		if (destC3->y >= WINDOW_HEIGHT - destC3->h) destC3->y= WINDOW_HEIGHT - destC3->h;


}
void rejouer(SDL_Rect* destRobot,SDL_Renderer* renderer){
	//on met le robot dans la position initiale
	destRobot->x=14*((WINDOW_WIDTH - destRobot->w)/14);
	destRobot->y=(WINDOW_HEIGHT - destRobot->h) / 2;
	//on importe une image qui demande au joueur s'il veut rejouer en la faisant clinioté
	SDL_Surface* Rejouer=IMG_Load("images/rejouer.png");
	SDL_Texture* REJOUER = SDL_CreateTextureFromSurface(renderer, Rejouer);
	SDL_Rect destRejouer;
	SDL_QueryTexture(REJOUER, NULL, NULL, &destRejouer.w, &destRejouer.h);
	destRejouer.x=10;
	destRejouer.y=(WINDOW_HEIGHT - destRejouer.h) / 2;
        	SDL_RenderCopy(renderer, REJOUER , NULL, &destRejouer);
         SDL_RenderPresent(renderer);
	SDL_Delay(100);

}
