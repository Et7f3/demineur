#ifndef PANEL_2_H
#  define PANEL_2_H

#  include "main.h"

extern int               panel_2(SDL_Event * evt);
extern int               view_2_init(void);
extern int               view_2(SDL_Window * wind);


#  define cell(x, y) (gl_tab[y][x])
#  define cell_value(x, y, v) (gl_tab[y][x] = v)
#  define cell_flag(x, y, f) (gl_tab[y][x] ^= f)
#  define TUILE_VISIBLE 1
#  define TUILE_BOMBE 2
#  define TUILE_DRAPEAU 4
#  define TUILE_DOUTE 8

#  define CASE_PAR_LIGNE 10
#  define CASE_PAR_COLONNE 10
extern unsigned char     gl_tab[CASE_PAR_LIGNE][CASE_PAR_COLONNE];
#endif
