#include "Screen.h"
#include <iostream>
namespace tkp {

	Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_blurBuffer(NULL) {
	}

	Screen::~Screen() {
	}

	bool Screen::init() {

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			return false;
		}

		//initialize a window
		m_window = SDL_CreateWindow("Particle System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// check if the window couldnt be created
		if (m_window == NULL) {
			SDL_Quit();
			return false;
		}

		// Creating a renderer

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_HEIGHT, SCREEN_HEIGHT);
		if (m_renderer == NULL) {
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		if (m_texture == NULL) {
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		// Create a buffer to store the RGBA information of each pixel which occupies 1 byte
		m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		m_blurBuffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];


		memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); // Sets the buffer memory block to x value, printing everything white
		memset(m_blurBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); // Sets the buffer memory block to x value, printing everything white

		//m_buffer[30000] = 0xFFFFFFFF;  0xRRGGBBAA R = red, G = green, B = blue, A = alpha

		// Fills the screen with a color
		/*
		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
			m_buffer[i] = 0xFF0000FF; // Set the current pixel to a color
		}
		*/
		return true;
	}
	void Screen::close() {
		// Freeing memory
		delete[] m_buffer;
		delete[] m_blurBuffer;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);

		SDL_Quit(); // deinitilises SDL
	}
	bool Screen::processEvent() {
		SDL_Event event;
		// fetch the next event in event queue
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}

	void Screen::update() {
		SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32)); //copies the pixels to the buffer
		SDL_RenderClear(m_renderer); // clears the render
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); // Passes the texture info to the render
		SDL_RenderPresent(m_renderer); // presents the render information
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
			return;
		}

		Uint32 color = 0;

		//shifts the stored value by 1 byte
		color += red; //0000012
		color <<= 8; //00001200
		color += green; //00001234
		color <<= 8; //00123400
		color += blue; //00123456
		color <<= 8; //12345600
		color += 0xFF; //123456FF

		m_buffer[(y * SCREEN_WIDTH) + x] = color;
	}

	// This process is a too heavy CPU process
	void Screen::boxBlur() {
		Uint32 * tempBuffer = m_buffer;
		// Swap the buffers, so pixel info is in blurBuffer and then draws to the main buffer
		m_buffer = m_blurBuffer;
		m_blurBuffer = tempBuffer;

		for(int y = 0; y < SCREEN_HEIGHT; y++)
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				
				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++) {
					for (int col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
							Uint32 color = m_blurBuffer[currentY * SCREEN_WIDTH + currentX];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;

						}

					}
				}
				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);

			}

	}
}