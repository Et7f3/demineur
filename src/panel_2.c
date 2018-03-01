#include "main.h"

int panel_2(SDL_Event * evt)
{
	switch (evt->type)
	{
	case SDL_MOUSEBUTTONUP:
		break;
	default:
		break;
	}
	return panel_default(evt);
}

int view_2(SDL_Window * wind)
{
	view_default(wind);
	return 1;
}
