#include "main.h"

int panel_1(SDL_Event * evt)
{
	switch (evt->type)
	{
	case SDL_MOUSEBUTTONUP:
		if (155 <= evt->button.x && evt->button.x <= 290)
		{
			if (205 <= evt->button.y && evt->button.y <= 240)
			{
				gl_panel_current = panel_2;
				gl_view_current = view_2;
				view_2_init();
			}
			if (275 <= evt->button.y && evt->button.y <= 320)
				return 0;
		}
		break;
	default:
		break;
	}
	return panel_default(evt);
}

int view_1(SDL_Window * wind)
{
	SDL_Rect                 dstrect;
	dstrect.x = 155;
	dstrect.y = 205;
	view_default(wind);
	SDL_BlitSurface(gl_tuile[0], NULL, SDL_GetWindowSurface(wind), &dstrect);

	dstrect.y = 275;
	SDL_BlitSurface(gl_tuile[1], NULL, SDL_GetWindowSurface(wind), &dstrect);
	return 1;
}
