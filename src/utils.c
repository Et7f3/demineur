#include "main.h"

int combien_de_bombe(int x, int y)
{
	int                      c = 0;
	if (x > 0)
	{
		if (y > 0)
			c += ! !(TUILE_BOMBE & cell(x - 1, y - 1));

		c += ! !(TUILE_BOMBE & cell(x - 1, y));

		if (y < CASE_PAR_COLONNE - 1)
			c += ! !(TUILE_BOMBE & cell(x - 1, y + 1));
	}

	if (x < CASE_PAR_LIGNE - 1)
	{
		if (y > 0)
			c += ! !(TUILE_BOMBE & cell(x + 1, y - 1));

		c += ! !(TUILE_BOMBE & cell(x + 1, y));

		if (y < CASE_PAR_COLONNE - 1)
			c += ! !(TUILE_BOMBE & cell(x + 1, y + 1));
	}

	if (y > 0)
		c += ! !(TUILE_BOMBE & cell(x, y - 1));

	if (y < CASE_PAR_COLONNE - 1)
		c += ! !(TUILE_BOMBE & cell(x, y + 1));

	return c;
}

int clic_tuile(int x, int y)
{
	int                      c;
	c = 0;
	if (x < 0 || x > CASE_PAR_LIGNE - 1 || y < 0 || y > CASE_PAR_COLONNE - 1)
		return (-1);

	if (cell(x, y) & TUILE_DOUTE)
		return (c);
	else if (cell(x, y) & TUILE_DRAPEAU)
		return (c);
	else if (!(cell(x, y) & TUILE_VISIBLE))
	{
		cell_flag(x, y, TUILE_VISIBLE);
		if (!(cell(x, y) & TUILE_BOMBE) && !combien_de_bombe(x, y))
			c +=
				clic_tuile(x - 1, y - 1) + clic_tuile(x - 1, y) + clic_tuile(x - 1,
																																		 y + 1) +
				clic_tuile(x, y - 1) + clic_tuile(x, y + 1) + clic_tuile(x + 1,
																																 y - 1) +
				clic_tuile(x + 1, y) + clic_tuile(x + 1, y + 1);
	}

	return (c);
}

int deposer_tuile(int x, int y)
{
	if (x < 0 || x > CASE_PAR_LIGNE - 1 || y < 0 || y > CASE_PAR_COLONNE - 1)
		return (-1);

	if (!(cell(x, y) & TUILE_VISIBLE)
			&& !(cell(x, y) & (TUILE_DRAPEAU | TUILE_DOUTE)))
		cell_flag(x, y, TUILE_DRAPEAU);
	else if (!(cell(x, y) & TUILE_VISIBLE) && (cell(x, y) & TUILE_DRAPEAU))
		cell_flag(x, y, TUILE_DOUTE | TUILE_DRAPEAU);
	else if (!(cell(x, y) & TUILE_VISIBLE) && (cell(x, y) & TUILE_DOUTE))
		cell_flag(x, y, TUILE_DOUTE);
	return 1;
}
