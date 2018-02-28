#include "main.h"

int panel_default(SDL_Event * evt)
{
	switch (evt->type)
	{
	case SDL_QUIT:
		return 0;
	}
	return 1;
}

int view_default(SDL_Window * wind)
{
	SDL_Surface             *s = SDL_GetWindowSurface(wind);
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 0x88, 0xff, 0x88));
	return 1;
}
