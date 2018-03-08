#include "main.h"

unsigned char     gl_tab[CASE_PAR_LIGNE][CASE_PAR_COLONNE];

int                      gl_perdu;

int panel_2(SDL_Event * evt)
{
	int                      x;
	int                      y;
	switch (evt->type)
	{
	case SDL_MOUSEBUTTONUP:
		if (50 <= evt->button.x && evt->button.x <= 395 && 100 <= evt->button.y
				&& evt->button.y <= 445 && !gl_perdu)
		{
			x = (evt->button.x - 50) / 35;
			y = (evt->button.y - 100) / 35;
			if (evt->button.button == SDL_BUTTON_LEFT)
				clic_tuile(x, y);
			else if (evt->button.button == SDL_BUTTON_RIGHT)
				deposer_tuile(x, y);
		}
		if (472 <= evt->button.y && evt->button.y <= 517 && 155 <= evt->button.x
				&& evt->button.x <= 290)
		{
			if (gl_perdu)
				view_2_init();
			else
				return 0;
		}
		break;
	default:
		break;
	}
	return panel_default(evt);
}

int view_2_init(void)
{
	int                      x;
	int                      y;
	int                      cnt;
	gl_perdu = 0;
	memset(gl_tab, 0, 100);
	for (cnt = 0; cnt < 12;)
	{
		x = rand() % 10;
		y = rand() % 10;
		if (!(cell(x, y) & TUILE_BOMBE))
			cnt++, cell_flag(x, y, TUILE_BOMBE);
	}
	cell_flag(0, 0, TUILE_BOMBE | TUILE_DRAPEAU);

	return 1;
}

int view_2(SDL_Window * wind)
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

	SDL_BlitSurface(gl_tuile[((gl_perdu) ? 17 : 1)], NULL,
									SDL_GetWindowSurface(wind), &dstrect);

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
				gl_perdu = 1;
				fin = 0;
			}
		}
	if (fin)
		SDL_BlitSurface(gl_tuile[15], NULL, SDL_GetWindowSurface(wind), &dstrect);

	return 1;
}
