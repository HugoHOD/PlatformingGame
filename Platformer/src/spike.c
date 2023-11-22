/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "common.h"

static void tick(void);
static void touch(Entity other);

void initSpike(char *line)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;

	e->texture = loadTexture("gfx/Spikes.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = touch;
}

static void tick () {

}

static void touch(Entity* other) {
	if (other == player) {
		player->x = player->y = 0;
		app.keyboard[SDL_SCANCODE_SPACE] = 0;
		decLives();
	}
}