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
#include <time.h>

static void capFrameRate(long* then, float* remainder);

char* global_dir = "C:\\Users\\di918039\\source\\repos\\cs1pr-portfolio\\project-visual-studio\\SpringProject";


time_t startTime, endTime;
int levelno = 1;
int lives = 15;
int score = 0;

void runGame() {
	if (getLevelNo() == 1) { 
		setTime();
	}
	long then;
	float remainder;

	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	initSDL();

	atexit(cleanup);

	initGame();

	initStage();

	then = SDL_GetTicks();

	remainder = 0;
	start = 1;
	end = 1;
	
	if (getLevelNo() == 1) {
		while (start)
		{

			prepareScene();

			doInput();

			app.delegate.logic();

			app.delegate.drawStart();

			presentScene();

			capFrameRate(&then, &remainder);
		}
	}

	while (1)
	{
		if (getLives() == 0) {
			death = 1;
			break;
		}
		else if (getLevelNo() == 5) {
			break;
		}
		prepareScene();

		doInput();

		app.delegate.logic();

		app.delegate.draw();

		presentScene();

		capFrameRate(&then, &remainder);
	}

	if (!death) {
		finalTime = getCurrentTime();
		while (end) {

			prepareScene();

			doInput();

			app.delegate.logic();

			app.delegate.drawEnd();

			presentScene();

			capFrameRate(&then, &remainder);
		}
		exit(1);
	}
	if (death) {
		finalTime = getCurrentTime();
		while (end) {

			prepareScene();

			doInput();

			app.delegate.logic();

			app.delegate.drawDeath();

			presentScene();

			capFrameRate(&then, &remainder);
		}
	}
	return 0;
}



void setTime() {
	startTime = time(0);
}

int getCurrentTime() {
	endTime = time(0);
	int diff = difftime(endTime, startTime);
	return diff;
}

int WinMain() {
	runGame();
	return 0;
}



int getScore() {
	return score;
}

void setScore(int s) {
	score = score + s;
}


int getLives() {
	return lives;
}

void decLives() {
	lives--;
}

void incLives() {
	if (lives < 15) {
		lives++;
	}
}

int getLevelNo() {
	return levelno;
}

int incrementLevelNo() {
	levelno++;
	return 0;
}

static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)* remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
