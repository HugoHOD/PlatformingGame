#include "common.h"

static void tick(void);
static void touch(Entity* other);

void initMTrap(char* line)
{
	Entity* e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f %f %f", &e->sx, &e->sy, &e->ex, &e->ey);

	e->health = 1;

	e->x = e->sx;
	e->y = e->sy;

	e->tick = tick;
	e->touch = touch;
	e->texture = loadTexture("gfx/MTrap3.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
}

static void tick(void)
{
	if (abs(self->x - self->sx) < PLATFORM_SPEED && abs(self->y - self->sy) < PLATFORM_SPEED)
	{
		calcSlope(self->ex, self->ey, self->x, self->y, &self->dx, &self->dy);

		self->dx *= PLATFORM_SPEED;
		self->dy *= PLATFORM_SPEED;
	}

	if (abs(self->x - self->ex) < PLATFORM_SPEED && abs(self->y - self->ey) < PLATFORM_SPEED)
	{
		calcSlope(self->sx, self->sy, self->x, self->y, &self->dx, &self->dy);

		self->dx *= PLATFORM_SPEED;
		self->dy *= PLATFORM_SPEED;
	}
}

static void touch(Entity* other) {
	if (other == player) {
		player->x = player->y = 0;
		app.keyboard[SDL_SCANCODE_SPACE] = 0;
		decLives();
	}
}