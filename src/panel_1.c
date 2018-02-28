#include "main.h"

int panel_1(SDL_Event * evt)
{
	switch (evt->type)
	{
	}
	return panel_default(evt);
}

int view_1(SDL_Window * wind)
{
	view_default(wind);

	return 1;
}
