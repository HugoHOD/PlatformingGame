/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"

static void logic(void);
static void draw(void);
static void drawHud(void);
static void drawStart(void);
static void drawEnd(void);
static void drawDeath(void);

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	app.delegate.drawStart = drawStart;
	app.delegate.drawEnd = drawEnd;
	app.delegate.drawDeath = drawDeath;

	memset(&stage, 0, sizeof(Stage));

	stage.entityTail = &stage.entityHead;

	initEntities();

	initPlayer();

	initMap();
}

static void logic(void)
{
	doPlayer();

	doEntities();

	doCamera();
}

static void draw(void)
{
	SDL_SetRenderDrawColor(app.renderer, 128, 0, 255, 255);
	SDL_RenderFillRect(app.renderer, NULL);

	drawMap();

	drawEntities();

	drawHud();
}

static void drawStart(void) {
	SDL_Rect r;
	
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_WIDTH;
	
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(app.renderer, &r);


	drawText(650, 200, 255, 255, 255, TEXT_RIGHT, "WELCOME TO");
	drawText(630, 300, 255, 0, 0, TEXT_RIGHT, "INSANITY");
	drawText(777, 375, 255, 255, 255, TEXT_RIGHT, "CLICK SPACE TO BEGIN.");
	drawText(666, 450, 255, 0, 1, TEXT_RIGHT, "(IF YOU DARE)");
	drawText(777, 600, 255, 0, 255, TEXT_RIGHT, "THE DEFINITION OF INSANITY IS DOING");
	drawText(1450, 650, 255, 0, 255, TEXT_RIGHT, "THE SAME THING OVER AND OVER AND OVER AND OVER AND OVER AND OVER AND OVER");


}

static void drawEnd(void) {
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_WIDTH;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(app.renderer, &r);

	drawText(650, 200, 255, 255, 255, TEXT_RIGHT, "YOU WON!");
	drawText(800, 300, 255, 255, 255, TEXT_RIGHT, "YOU BROKE THE CYCLE OF");
	drawText(650, 360, 255, 0, 0, TEXT_RIGHT, "INSANITY");
	drawText(700, 450, 255, 255, 255, TEXT_RIGHT, "YOUR SCORE: %d", getScore());
	drawText(780, 530, 255, 255, 255, TEXT_RIGHT, "YOUR TIME: %d SECONDS", finalTime);
}

static void drawDeath(void) {
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_WIDTH;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(app.renderer, &r);

	drawText(650, 200, 255, 255, 255, TEXT_RIGHT, "YOU DIED!");
	drawText(750, 300, 255, 255, 255, TEXT_RIGHT, "INSANITY TOOK YOU.");
	drawText(700, 450, 255, 255, 255, TEXT_RIGHT, "YOUR SCORE: %d", getScore());
	drawText(780, 530, 255, 255, 255, TEXT_RIGHT, "YOUR TIME: %d SECONDS", finalTime);
}

static void drawHud(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	
		drawText(1290, 5, 255, 255, 255, TEXT_LEFTER, "LIVES %d/%d", getLives(), 15);
		drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_RIGHT, "CHEESE %d/%d", stage.pizzaFound, stage.pizzaTotal);
		drawText(SCREEN_WIDTH - 5, 5, 255, 0, 0, TEXT_CENTER, "STAGE %d", getLevelNo());
		drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_LEFT, "SCORE %d", getScore());
		drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_CENTERRIGHT, "JARS %d/%d", stage.pbJars, stage.pbTotal);
	
	
}
