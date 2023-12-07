#include <SDL.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argb[]) {

	SDL_Window* window = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "SDL could not be initialized: " << SDL_GetError();
	else
		cout << "SDL video system is ready to go\n";

	window = SDL_CreateWindow("C++ SDL2 WINDOW", 20, 20, 640, 480, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* tile_map_surface = SDL_LoadBMP("D:/fisier joc sdl2/tiles.bmp");

	SDL_Texture* tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);

	SDL_FreeSurface(tile_map_surface);

	srand(time(NULL));
	int tilemap[40][15];

	/*for (int x = 0; x < 40; x++)
		for (int y = 0; y < 15; y++)
			tilemap[x][y] = rand() % 4 + 1;*/
	int heights[40];
	for (int x = 0; x < 40; ++x)
		heights[x] = rand() % 12 + 1;

	for (int x = 1; x < 40; ++x) {
		int roll = rand() % 2;
		if (0 == roll)
			heights[x] = heights[x - 1] + 1;
		else {
			heights[x] = heights[x - 1] - 1;
			if (heights[x] < 0)
				heights[x] = 0;
		}
	}
	for (int x = 0; x < 40 - 3; ++x)
		heights[x] = (heights[x] + heights[x + 1] + heights[x + 2]) / 3;

	for (int x = 0; x < 40; x++) {
		int stackHeight = heights[x];
		for (int y = 0; y < 15; y++) {
			if (y > stackHeight)
				tilemap[x][y] = 1;
			else if (y == stackHeight)
				tilemap[x][y] = 2;
			else
				tilemap[x][y] = 0;
		}
	}


	SDL_Rect tile[20][15];
	for (int x = 0; x < 20; x++)
		for (int y = 0; y < 15; y++) {
			tile[x][y].x = x * 32;
			tile[x][y].y = y * 32;
			tile[x][y].w = 32;
			tile[x][y].h = 32;
		}

	SDL_Rect select_tile_1;
	select_tile_1.x = 0;
	select_tile_1.y = 0;
	select_tile_1.w = 32;
	select_tile_1.h = 32;

	SDL_Rect select_tile_2;
	select_tile_2.x = 32;
	select_tile_2.y = 0;
	select_tile_2.w = 32;
	select_tile_2.h = 32;

	SDL_Rect select_tile_3;
	select_tile_3.x = 0;
	select_tile_3.y = 32;
	select_tile_3.w = 32;
	select_tile_3.h = 32;

	SDL_Rect select_tile_4;
	select_tile_4.x = 32;
	select_tile_4.y = 32;
	select_tile_4.w = 32;
	select_tile_4.h = 32;

	const Uint8* pKeys = SDL_GetKeyboardState(NULL);

	bool gameisrunning = true;

	while (gameisrunning) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				gameisrunning = false;
		}



		SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0xBB, 0xFF);
		SDL_RenderClear(renderer);

		SDL_Delay(20);

		if (pKeys[SDL_SCANCODE_ESCAPE])
			gameisrunning = false;
		static int offSetX = 0;
		if (pKeys[SDL_SCANCODE_RIGHT])
			offSetX++, SDL_Delay(20);
		if (pKeys[SDL_SCANCODE_LEFT])
			offSetX--, SDL_Delay(20);
		if (offSetX < 0)
			offSetX = 0;
		if (offSetX > 39)
			offSetX = 39;

		for (int x = 0; x < 20; x++)
			for (int y = 0; y < 15; y++)
				switch (tilemap[x + offSetX][y]) {
				case 1:
					SDL_RenderCopy(renderer, tile_texture, &select_tile_1, &tile[x][y]);
					break;
				case 2:
					SDL_RenderCopy(renderer, tile_texture, &select_tile_2, &tile[x][y]);
					break;
				case 3:
					SDL_RenderCopy(renderer, tile_texture, &select_tile_3, &tile[x][y]);
					break;
				case 4:
					SDL_RenderCopy(renderer, tile_texture, &select_tile_4, &tile[x][y]);
					break;
				}

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(tile_texture);
	return 0;
}