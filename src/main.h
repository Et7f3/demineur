#ifndef MAIN_H_
#  define MAIN_H_

#  include "SDL2/SDL.h"
#  include "stdlib.h"
#  include "stdio.h"

#  include "panel_default.h"
#  include "panel_1.h"

extern int               (*gl_panel_current) (SDL_Event * evt);
extern int               (*gl_view_current) (SDL_Window * wind);
extern SDL_Window       *wind;
#endif
