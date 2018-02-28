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
