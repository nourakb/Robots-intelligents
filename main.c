#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 
#include"fonction.h"
#include"constante.h"
int main()
{   //initialiser la SDL
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		printf("erreur lors de l'initialisation de SDL:%s\n", SDL_GetError());
		return 1;
	}

	//creer la fenetre
	SDL_Window* window = SDL_CreateWindow("Robot Intelligent", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,0);
	if (!window)
	{
		printf("erreur lors de la création de la fenêtre:%s\n", SDL_GetError());
		SDL_Quit();
	}
	//creer le renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		printf("erreur lors de la création du renderer:%s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	// fonction qui affiche la page d'acceuil du jeu
	acceuil(window,renderer);
	//fenetre blanche
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//charger les images
	SDL_Surface* robot=IMG_Load("images/robot.png");
	SDL_Surface* Cercle=IMG_Load("images/cercle.png");
	SDL_Surface* Rectangle=IMG_Load("images/rectangle.png");
	SDL_Surface* Triangle=IMG_Load("images/triangle.png");
	if (!robot || !Cercle || !Rectangle || !Triangle) 
	{
		printf("erreur lors de l'importation de l'image\n");
                  SDL_DestroyRenderer(renderer);
	         SDL_DestroyWindow(window);
        		SDL_Quit();
        		return 1;
         }
	//creer les textures
	SDL_Texture* ROBOT = SDL_CreateTextureFromSurface(renderer, robot);
	SDL_Texture* CERCLE = SDL_CreateTextureFromSurface(renderer, Cercle);
	SDL_Texture* RECTANGLE = SDL_CreateTextureFromSurface(renderer, Rectangle);
	SDL_Texture* TRIANGLE = SDL_CreateTextureFromSurface(renderer, Triangle);
	SDL_FreeSurface(robot);
	SDL_FreeSurface(Cercle);
	SDL_FreeSurface(Rectangle);
	SDL_FreeSurface(Triangle);

	 if (!ROBOT || !CERCLE || !RECTANGLE || !TRIANGLE)
          {
		printf("erreur lors de la création des textures: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
        		return 1;
          }
	SDL_Rect destRobot,destC1,destC2,destC3,destT1,destT2,destR1,destR2;
	//coordonnees du robot	
	SDL_QueryTexture(ROBOT, NULL, NULL, &destRobot.w, &destRobot.h);
	destRobot.w/=9;
	destRobot.h/=9;
	destRobot.x=14*((WINDOW_WIDTH - destRobot.w)/14);
	destRobot.y=(WINDOW_HEIGHT - destRobot.h) / 2;
	//coordonnees du cercle1	
    SDL_QueryTexture(CERCLE, NULL, NULL, &destC1.w, &destC1.h);
	destC1.w/=19;
	destC1.h/=19;
	destC1.x=0*((WINDOW_WIDTH - destRobot.w)/14);
	destC1.y=0;
	//coordonnees du  cercle2	
    SDL_QueryTexture(CERCLE, NULL, NULL, &destC2.w, &destC2.h);
	destC2.w/=19;
	destC2.h/=19;
	destC2.x=6*((WINDOW_WIDTH - destRobot.w)/14);
	destC2.y=0;
	//coordonnees du cercle3	
    SDL_QueryTexture(CERCLE, NULL, NULL, &destC3.w, &destC3.h);
	destC3.w/=19;
	destC3.h/=19;
	destC3.x=12*((WINDOW_WIDTH - destRobot.w)/14);
	destC3.y=0;
	//coordonnees du rectangle1
    SDL_QueryTexture(RECTANGLE, NULL, NULL, &destR1.w, &destR1.h);
	destR1.w/=7;
	destR1.h/=7;
	destR1.x=2*((WINDOW_WIDTH - destRobot.w)/14);
	//coordonnees du rectangle2	
    SDL_QueryTexture(RECTANGLE, NULL, NULL, &destR2.w, &destR2.h);
	destR2.w/=7;
	destR2.h/=7;
	destR2.x=10*((WINDOW_WIDTH - destRobot.w)/14);
	//coordonnees du triangle1	
	SDL_QueryTexture(TRIANGLE, NULL, NULL, &destT1.w, &destT1.h);
	destT1.w/=11;
	destT1.h/=11;
	destT1.x=4*((WINDOW_WIDTH - destRobot.w)/14);
	destT1.y=0;
	//coordonnees du triangle2	
    SDL_QueryTexture(TRIANGLE, NULL, NULL, &destT2.w, &destT2.h);
	destT2.w/=11;
	destT2.h/=11;
	destT2.x=8*((WINDOW_WIDTH - destRobot.w)/14);
	destT2.y=0;

    //corespondent aux entreex 
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
	int space=0;
	int close_requested = 0;
	while (!close_requested)
	{
		SDL_Event event;
        		while (SDL_PollEvent(&event))
        		{
            	    switch (event.type)
                      {
            	     case SDL_QUIT:  //lorsequ'on appuie sur le bouton x pour fermer la fenetre
                		close_requested = 1;
                		break;
            	     case SDL_KEYDOWN:
                		switch (event.key.keysym.scancode)
                           {
                             case SDL_SCANCODE_UP: //lorsequ'on appuie sur la touche 'up' du clavier
                                   up = 1;
                                   break;

                             case SDL_SCANCODE_LEFT: //lorsequ'on appuie sur la touche 'left' du clavier
                                 left = 1;
                                 break;

                              case SDL_SCANCODE_DOWN: //lorsequ'on appuie sur la touche 'down' du clavier
                                  down = 1;
                                  break;

                             case SDL_SCANCODE_RIGHT: //lorsequ'on appuie sur la touche 'right' du clavier
                                  right = 1;
                                  break;
			                 case SDL_SCANCODE_SPACE: //lorsequ'on appuie sur la barre d'espace du clavier
			                       space = 1;
                                   break;	
			                 case SDL_SCANCODE_R: //lorsequ'on appuie sur la touche de la lettre R  du clavier
			                       destC1.y=0;
			                       destC2.y=0;
	    	 	                   destC3.y=0;
			                       break;
			                 default:
                                    break;
                           }
                           break;
                     case SDL_KEYUP:
                           switch (event.key.keysym.scancode)
                           {
                               case SDL_SCANCODE_UP: //losequ'on relache la touche 'up' du clavier
                                  up = 0;
                                  break;

                               case SDL_SCANCODE_LEFT: //losequ'on relache la touche 'left' du clavier
                                  left = 0;
                                  break;

                               case SDL_SCANCODE_DOWN: //losequ'on relache la touche 'down' du clavier
                                  down = 0;
                                  break;

                                case SDL_SCANCODE_RIGHT: //losequ'on relache la touche 'right' du clavier
                                   right = 0;
                                   break;	
			      			    case SDL_SCANCODE_SPACE: //losequ'on relache la barre d'espace du clavier
			       					space = 0;
                                   break;
			                    default:
                                   break;
                           }
                           break;
		             default:
                           break;
                     }        
                  }

		//on deplace le robot dans la direction de la touche entree au clavier
        if (up && !down) destRobot.y-=5;
       	if (down && !up) destRobot.y += 5;
        if (left && !right) destRobot.x-= 5;
        if (right && !left) destRobot.x += 5;

        //fonction qui evite au robot et aux cercles  de sortir de la fenetre et rester dans le champs visuel de l'utilisateur
        detecterCollision(&destRobot , &destC1,&destC2,&destC3);
		//au cas ou tout les cercles sont dans la deuxieme rangee on propose a l'utilisateur de rejouer
		if ((destC1.y==WINDOW_HEIGHT-destC1.h) && (destC2.y==WINDOW_HEIGHT-destC1.h) && (destC3.y==WINDOW_HEIGHT-destC1.h)){
		
		rejouer(&destRobot,renderer);
		}
		//fonction qui verifie si une forme est un cercle ou pas et permet au robot de le deplacer si c'est le cas
		verifierEstCercle(&destRobot,&destC1,&destC2,&destC3, space);
	 	SDL_RenderClear(renderer);
       		//affichage des figures a l'ecran
        		SDL_RenderCopy(renderer, ROBOT , NULL, &destRobot);
        		SDL_RenderCopy(renderer, CERCLE, NULL, &destC1);
        		SDL_RenderCopy(renderer, CERCLE, NULL, &destC2);
        		SDL_RenderCopy(renderer, CERCLE, NULL, &destC3);
        		SDL_RenderCopy(renderer, TRIANGLE, NULL, &destT1);
        		SDL_RenderCopy(renderer, TRIANGLE, NULL, &destT2);
        		SDL_RenderCopy(renderer, RECTANGLE, NULL, &destR1);
        		SDL_RenderCopy(renderer, RECTANGLE, NULL, &destR2);
        		SDL_RenderPresent(renderer);
        		// attendre 1/60 s avant de rafraichir la fenetre
 	         SDL_Delay(1000/60);
    	}
    	// nettoyer les ressources avant de quitter

         SDL_DestroyRenderer(renderer);
         SDL_DestroyWindow(window);
         SDL_Quit();

}



