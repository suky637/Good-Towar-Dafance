#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#undef main

SDL_Texture* getTextureFromIMG(SDL_Renderer* ren, std::string path)
{
	SDL_Surface* tex = IMG_Load(path.c_str());
	return SDL_CreateTextureFromSurface(ren, tex);
}

SDL_Rect* createRect(int x, int y, int w, int h)
{
	SDL_Rect r = { x,y,w,h };
	return &r;
}

int getXOffsetFont(char _c)
{
	if (_c == '1') return 0;
	if (_c == '2') return 128;
	if (_c == '3') return 256;
	if (_c == '4') return 384;
	if (_c == '5') return 512;
	if (_c == '6') return 640;
	if (_c == '7') return 768;
	if (_c == '8') return 896;
	if (_c == '9') return 1024;
	if (_c == '0') return 1152;
	return -1;
}

int RenderNumbersCentered(std::string num, int xOff, int y, int spacing, float scale, SDL_Texture* font, SDL_Renderer* ren)
{
	unsigned int textL = (num.length() * (128 - spacing)) * scale;
	unsigned int CenteredText = (unsigned int)(floor((1280 - textL) / 2)) + xOff;

	// Getting each number
	int _off = 0;
	int outRight = 0;
	for (char c : num)
	{
		int off = getXOffsetFont(c);
		if (off == -1) { continue; }

		SDL_RenderCopy(ren, font, createRect(off, 0, 128, 128), createRect(CenteredText + _off, y, 128 * scale, 128 * scale));
		_off += (128 - spacing) * scale;
	}
	outRight = CenteredText + _off;
	return outRight;
}

int RenderNumbersCentered(int num, int xOff, int y, int spacing, float scale, SDL_Texture* font, SDL_Renderer* ren)
{
	// Getting length of the number
	std::string n = std::to_string(num);
	return RenderNumbersCentered(n, xOff, y, spacing, scale, font, ren);
}

int main()
{
	std::string currScene = "mainmenu";

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* win = SDL_CreateWindow("Good Towar Dafance", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG);

	SDL_SetRenderDrawColor(ren, 177, 201, 178, 255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);

	SDL_Texture* logo = getTextureFromIMG(ren, "Res/title.png");
	SDL_Texture* play_btn = getTextureFromIMG(ren, "Res/play_btn.png");
	SDL_Texture* numberTex = getTextureFromIMG(ren, "Res/font_number.png");
	SDL_Texture* waveText = getTextureFromIMG(ren, "Res/wave_text.png");
	SDL_Texture* cashLogo = getTextureFromIMG(ren, "Res/cash.png");
	SDL_Texture* shopBtn = getTextureFromIMG(ren, "Res/shop_btn.png");
	SDL_Texture* shop_gui = getTextureFromIMG(ren, "Res/shop.png");

	int mousePosX = 0;
	int mousePosY = 0;
	bool leftReleased = false;

	int wave = 0;
	int money = 0;

	bool shouldClose = false;
	bool isFullScreen = false;
	bool isShopOpened = false;

	double lastTime = SDL_GetTicks();


	while (!shouldClose)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				shouldClose = true;
				break;
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				mousePosX = e.motion.x;
				mousePosY = e.motion.y;
			}
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (e.button.button == 1)
				{
					leftReleased = true;
				}
			}
			if (e.type == SDL_KEYDOWN)
			{
				std::cout << e.key.keysym.sym << std::endl;
			}
			if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_F11)
				{
					isFullScreen = !isFullScreen;
					if (isFullScreen)
						SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
					else
						SDL_SetWindowFullscreen(win, 0);
				}
			}
		}

		if (currScene == "mainmenu")
		{
			SDL_SetRenderDrawColor(ren, 177, 201, 178, 255);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, logo, NULL, createRect(338,100,603,100));
			SDL_RenderCopy(ren, play_btn, NULL, createRect(390, 240, 500, 120));

			if (mousePosX > 390 && mousePosX < 890 && mousePosY > 240 && mousePosY < 360)
			{
				if (leftReleased)
				{
					currScene = "game";
					wave = 0;
					money = 200;
					isShopOpened = false;
				}
			}
			double curTime = SDL_GetTicks();
			while (curTime - lastTime >= (double)1000 / 60)
			{
				lastTime += 1000 / 60;

				leftReleased = false;
			}
			
		}

		if (currScene == "game")
		{
			// RENDERING
			SDL_SetRenderDrawColor(ren, 177, 201, 178, 255);
			SDL_RenderClear(ren);

			SDL_RenderCopy(ren, waveText, NULL, createRect(576, 5, 128, 56));
			RenderNumbersCentered(wave, -10, 62, 60, 0.5f, numberTex, ren);

			int moneySp = RenderNumbersCentered(money, -10, 128, 60, 0.2f, numberTex, ren);
			SDL_RenderCopy(ren, cashLogo, NULL, createRect(moneySp + 16, 128, 24, 24));

			int yPos = 682;
			if (isShopOpened) {
				SDL_RenderCopy(ren, shop_gui, NULL, createRect(0, 400, 1280, 320));
				yPos = 362;
			}
			SDL_RenderCopy(ren, shopBtn, NULL, createRect(0, yPos, 180, 38));
			

			// UPDATE
			double curTime = SDL_GetTicks();
			while (curTime - lastTime >= (double)1000 / 60)
			{
				lastTime += 1000 / 60;

				// update code goes there
				if (mousePosX > 0 && mousePosX < 180 && mousePosY > yPos && mousePosY < yPos + 38)
				{
					if (leftReleased)
					{
						isShopOpened = !isShopOpened;
					}
				}

				leftReleased = false;
			}
		}
		SDL_RenderSetLogicalSize(ren, 1280, 720);
		SDL_RenderPresent(ren);
		
	}

	SDL_DestroyTexture(logo);
	SDL_DestroyTexture(play_btn);
	SDL_DestroyTexture(numberTex);
	SDL_DestroyTexture(waveText);
	SDL_DestroyTexture(cashLogo);
	SDL_DestroyTexture(shopBtn);

	SDL_Quit();
	return 0;
}