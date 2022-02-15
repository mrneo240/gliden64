/* SPDX-FileCopyrightText: 2022 Hayden Kowalchuk 819028+mrneo240@users.noreply.github.com */
/* SPDX-License-Identifier: BSD-3-Clause */
/* Note: The above applies to parts of this file modified by Hayden Kowalchuk only and not existing code */

#include "osal_keys.h"

#include <SDL.h>
#include <SDL_events.h>

#ifdef __cplusplus
extern "C" {
#endif

static unsigned char keyboard_state[256] = {0};
static int last_key = 0;

EXPORT void CALL osal_keys_init()
{
}

EXPORT void CALL osal_keys_quit()
{
}

EXPORT void CALL osal_keys_update_state()
{
	SDL_Event event;
	memset(keyboard_state, 0, sizeof(keyboard_state));
	SDL_PumpEvents();
	if(SDL_PeepEvents(&event, 1, SDL_PEEKEVENT,SDL_KEYDOWN, SDL_KEYUP) > 0)
	{
			switch(event.type)
			{
			case SDL_KEYDOWN:
					//last_key = event.key.keysym.sym;
					//if(last_key > 256)
					//	last_key ^= SDLK_SCANCODE_MASK;
					//keyboard_state[last_key%256] = 0;
					break;
			case SDL_KEYUP:
					last_key = event.key.keysym.sym;
					if(last_key > 256)
						last_key ^= SDLK_SCANCODE_MASK;
					keyboard_state[last_key%256] = 1;
					break;
			}
	}
}

EXPORT unsigned int CALL osal_is_key_pressed(unsigned int _key, unsigned int _mask)
{
	return keyboard_state[_key%256];
}


#ifdef __cplusplus
}
#endif
