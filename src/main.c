#include "main.h"

int main(int argc, char **argv)
{
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n",
						SDL_GetError()), exit(EXIT_FAILURE);
	/* Création de la fenêtre */
	SDL_Window              *pWindow = NULL;
	pWindow =
		SDL_CreateWindow("Démineur", SDL_WINDOWPOS_UNDEFINED,
										 SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (pWindow)
	{
		/* Attendre trois secondes, que l'utilisateur voit la fenêtre */
		SDL_Delay(3000);
		SDL_DestroyWindow(pWindow);
	}
	else
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n",
						SDL_GetError());
	SDL_Quit();

	return 0;
}
