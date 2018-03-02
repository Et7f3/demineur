#include "main.h"
int                      (*gl_panel_current) (SDL_Event * evt);
int                      (*gl_view_current) (SDL_Window * wind);
SDL_Surface             *gl_tuile[NOMBRE_SPRITE] = { NULL };

int main(int argc, char **argv)
{
	SDL_Event                evt;
	int                      run;
	SDL_Window              *wind;
	srand(time(NULL));
	gl_panel_current = panel_1;
	gl_view_current = view_1;
	int                      clean_id;
	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n",
						SDL_GetError()), exit(EXIT_FAILURE);
	/* Création de la fenêtre */
	wind = NULL;
	wind = SDL_CreateWindow("Démineur", SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED, 445, 545, SDL_WINDOW_SHOWN);
	if (wind && load_sprite(wind))
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
		for (clean_id = 0; clean_id <= 14; clean_id++)
			SDL_FreeSurface(gl_tuile[clean_id]);
		SDL_DestroyWindow(wind);
	}
	else
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n",
						SDL_GetError());
	SDL_Quit();

	return 0;
}

int load_sprite(SDL_Window * wind)
{
	int                      i;
	int                      j;
	char                     nom_image[14] = "img\\vide0.bmp";
	i = 0;
	if (!(gl_tuile[i++] = SDL_LoadBMP("img\\jouer.bmp")))
		fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
						SDL_GetError());
	SDL_SetColorKey(gl_tuile[0], SDL_TRUE,
									SDL_MapRGB(SDL_GetWindowSurface(wind)->format, 0xff, 0xff,
														 0xff));

	if (!(gl_tuile[i++] = SDL_LoadBMP("img\\quitter.bmp")))
		fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
						SDL_GetError());
	SDL_SetColorKey(gl_tuile[1], SDL_TRUE,
									SDL_MapRGB(SDL_GetWindowSurface(wind)->format, 0xff, 0xff,
														 0xff));

	if (!(gl_tuile[i++] = SDL_LoadBMP("img\\bombe.bmp")))
		fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
						SDL_GetError());

	if (!(gl_tuile[i++] = SDL_LoadBMP("img\\tuile.bmp")))
		fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
						SDL_GetError());

	for (j = 0; j <= 9; j++)
	{
		nom_image[8] = j + '0';
		if (!(gl_tuile[i++] = SDL_LoadBMP(nom_image)))
			fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
							SDL_GetError());
	}

	if (!(gl_tuile[i++] = SDL_LoadBMP("img\\drapeau.bmp")))
		fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
						SDL_GetError());

	if (!(gl_tuile[i++] = SDL_LoadBMP("img\\bravo.bmp")))
		fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
						SDL_GetError());
	SDL_SetColorKey(gl_tuile[15], SDL_TRUE,
									SDL_MapRGB(SDL_GetWindowSurface(wind)->format, 0xff, 0xff,
														 0xff));

	if (!(gl_tuile[i++] = SDL_LoadBMP("img\\perdu.bmp")))
		fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
						SDL_GetError());
	SDL_SetColorKey(gl_tuile[16], SDL_TRUE,
									SDL_MapRGB(SDL_GetWindowSurface(wind)->format, 0xff, 0xff,
														 0xff));

	if (!(gl_tuile[i++] = SDL_LoadBMP("img\\recommencer.bmp")))
		fprintf(stderr, "la SDL n'a pas pu charger l'image (%s)\n",
						SDL_GetError());
	SDL_SetColorKey(gl_tuile[17], SDL_TRUE,
									SDL_MapRGB(SDL_GetWindowSurface(wind)->format, 0xff, 0xff,
														 0xff));
	return 1;
}
