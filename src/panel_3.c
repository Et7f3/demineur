#include "main.h"

int panel_3(SDL_Event * evt)
{
	switch (evt->type)
	{
	case SDL_MOUSEBUTTONUP:
		if (472 <= evt->button.y && evt->button.y <= 517 && 155 <= evt->button.x
				&& evt->button.x <= 290)
		{
			gl_panel_current = panel_2;
			gl_view_current = view_2;
			view_2_init();
		}
		break;
	default:
		break;
	}
	return panel_default(evt);
}

int view_3(SDL_Window * wind)
{
	SDL_Rect                 dstrect;
	int                      x;
	int                      y;
	char                     fin = 1;
	view_default(wind);
	for (x = 0; x < 10; x++)
		for (y = 0; y < 10; y++)
		{
			dstrect.x = 50 + x * 35;
			dstrect.y = 100 + y * 35;
			if (cell(x, y) & TUILE_VISIBLE)
				if (cell(x, y) & TUILE_BOMBE)
					SDL_BlitSurface(gl_tuile[2], NULL, SDL_GetWindowSurface(wind),
													&dstrect);
				else
					SDL_BlitSurface(gl_tuile[4 + combien_de_bombe(x, y)], NULL,
													SDL_GetWindowSurface(wind), &dstrect);
			else
				SDL_BlitSurface(gl_tuile[3], NULL, SDL_GetWindowSurface(wind),
												&dstrect);
			if (cell(x, y) & TUILE_DRAPEAU)
				SDL_BlitSurface(gl_tuile[14], NULL, SDL_GetWindowSurface(wind),
												&dstrect);
			if (cell(x, y) & TUILE_DOUTE)
				SDL_BlitSurface(gl_tuile[18], NULL, SDL_GetWindowSurface(wind),
												&dstrect);
		}

	dstrect.x = 155;
	dstrect.y = 472;

	SDL_BlitSurface(gl_tuile[17], NULL, SDL_GetWindowSurface(wind), &dstrect);

	dstrect.x = 155;
	dstrect.y = 30;

	for (x = 0; x < 10; x++)
		for (y = 0; y < 10; y++)
		{
			if (!(cell(x, y) & (TUILE_VISIBLE | TUILE_BOMBE)))
				fin = 0;
			if ((cell(x, y) & TUILE_BOMBE) && (cell(x, y) & TUILE_VISIBLE))
			{
				SDL_BlitSurface(gl_tuile[16], NULL, SDL_GetWindowSurface(wind),
												&dstrect);
				fin = 0;
			}
		}
	if (fin)
		SDL_BlitSurface(gl_tuile[15], NULL, SDL_GetWindowSurface(wind), &dstrect);

	return 1;
}
