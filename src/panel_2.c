#include "main.h"

#define CASE_PAR_LIGNE 10
#define CASE_PAR_COLONNE 10
static unsigned char     tab[CASE_PAR_LIGNE][CASE_PAR_COLONNE];
#define cell(x, y) (tab[y][x])
#define cell_value(x, y, v) (tab[y][x] = v)
#define TUILE_BOMBE 1
#define TUILE_BOMBE_VISIBLE (2 | TUILE_BOMBE)
#define TUILE_SANS_RIEN 4
#define TUILE_VIDE 8
#define TUILE_DRAPEAU 16


int                      combien_de_bombe(int x, int y);
int                      clic_tuile(int x, int y);

int panel_2(SDL_Event * evt)
{
	int                      x;
	int                      y;
	switch (evt->type)
	{
	case SDL_MOUSEBUTTONUP:
		if (50 <= evt->button.x && evt->button.x <= 395 && 100 <= evt->button.y
				&& evt->button.y <= 445)
		{
			x = (evt->button.x - 50) / 35;
			y = (evt->button.y - 100) / 35;
			clic_tuile(x, y);
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
	memset(tab, TUILE_SANS_RIEN, 100);
	for (cnt = 0; cnt < 10;)
	{
		x = rand() % 10;
		y = rand() % 10;
		if (cell(x, y) != TUILE_BOMBE)
			cnt++, cell_value(x, y, TUILE_BOMBE);
	}
	cell_value(0, 0, TUILE_BOMBE);

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
			if (cell(x, y) == TUILE_SANS_RIEN || cell(x, y) == TUILE_BOMBE)
				SDL_BlitSurface(gl_tuile[3], NULL, SDL_GetWindowSurface(wind),
												&dstrect);
			else if (cell(x, y) == TUILE_BOMBE_VISIBLE)
				SDL_BlitSurface(gl_tuile[2], NULL, SDL_GetWindowSurface(wind),
												&dstrect);
			else if (cell(x, y) == TUILE_DRAPEAU)
				SDL_BlitSurface(gl_tuile[14], NULL, SDL_GetWindowSurface(wind),
												&dstrect);
			else
				SDL_BlitSurface(gl_tuile[4 + combien_de_bombe(x, y)], NULL,
												SDL_GetWindowSurface(wind), &dstrect);
		}

	for (x = 0; x < 10 && fin; x++)
		for (y = 0; y < 10 && fin; y++)
		{
			if (cell(x, y) == TUILE_SANS_RIEN || cell(x, y) == TUILE_BOMBE_VISIBLE)
				fin = 0;
		}
	dstrect.x = 155;
	dstrect.y = 30;
	if (fin)
		SDL_BlitSurface(gl_tuile[15], NULL, SDL_GetWindowSurface(wind), &dstrect);

	return 1;
}

int combien_de_bombe(int x, int y)
{
	int                      c = 0;
	if (x > 0)
	{
		if (y > 0)
			c += (TUILE_BOMBE & cell(x - 1, y - 1));

		c += (TUILE_BOMBE & cell(x - 1, y));

		if (y < CASE_PAR_COLONNE - 1)
			c += (TUILE_BOMBE & cell(x - 1, y + 1));
	}

	if (x < CASE_PAR_LIGNE - 1)
	{
		if (y > 0)
			c += (TUILE_BOMBE & cell(x + 1, y - 1));

		c += (TUILE_BOMBE & cell(x + 1, y));

		if (y < CASE_PAR_COLONNE - 1)
			c += (TUILE_BOMBE & cell(x + 1, y + 1));
	}

	if (y > 0)
		c += (TUILE_BOMBE & cell(x, y - 1));

	if (y < CASE_PAR_COLONNE - 1)
		c += (TUILE_BOMBE & cell(x, y + 1));

	return c;
}

int clic_tuile(int x, int y)
{
	int                      c;
	c = 0;
	if (x < 0 || x > CASE_PAR_LIGNE - 1 || y < 0 || y > CASE_PAR_COLONNE - 1)
		return c;
	switch (cell(x, y))
	{
	case TUILE_SANS_RIEN:
		cell_value(x, y, TUILE_VIDE);
		if (!combien_de_bombe(x, y))
		{
			c +=
				clic_tuile(x - 1, y - 1) + clic_tuile(x - 1, y) + clic_tuile(x - 1,
																																		 y + 1) +
				clic_tuile(x, y - 1) + clic_tuile(x, y + 1) + clic_tuile(x + 1,
																																 y - 1) +
				clic_tuile(x + 1, y) + clic_tuile(x + 1, y + 1);
		}
		break;
	case TUILE_BOMBE:
		cell_value(x, y, TUILE_BOMBE_VISIBLE);
		break;
	}
	return c;
}

#undef CASE_PAR_LIGNE
#undef cell
#undef cell_value
