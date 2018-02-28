#include "main.h"

int                      (*gl_panel_current) (SDL_Event * evt);
int                      (*gl_view_current) (SDL_Window * wind);
SDL_Surface             *gl_tuile[15] = { NULL };

int main(int argc, char **argv)
{
	SDL_Event                evt;
	int                      run;
	SDL_Window              *wind;
	gl_panel_current = panel_1;
	gl_view_current = view_1;
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n",
						SDL_GetError()), exit(EXIT_FAILURE);
	/* Création de la fenêtre */
	wind = NULL;
	wind = SDL_CreateWindow("Démineur", SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (wind)
	{
		do
		{
			gl_view_current(wind);
			SDL_UpdateWindowSurface(wind);
			if (!SDL_WaitEvent(&evt))
				fprintf(stdout,
								"la SDL n'a pas pu obtenir une evenemnt de la file (%s)\n",
								SDL_GetError());
			run = gl_panel_current(&evt);
		}
		while (run);
		SDL_DestroyWindow(wind);
	}
	else
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n",
						SDL_GetError());
	SDL_Quit();

	return 0;
}
