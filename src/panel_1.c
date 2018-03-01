#include "main.h"

int panel_1(SDL_Event * evt)
{
	switch (evt->type)
	{
	}
	return panel_default(evt);
}

int view_1(SDL_Window * wind)
{
	SDL_Rect                 dstrect;
	dstrect.x = 155;
	dstrect.y = 205;
	view_default(wind);
	/*jour = 2,quitter=3 */
	SDL_BlitSurface(gl_tuile[2], NULL, SDL_GetWindowSurface(wind), &dstrect);

	dstrect.y = 275;
	SDL_BlitSurface(gl_tuile[3], NULL, SDL_GetWindowSurface(wind), &dstrect);
	return 1;
}
