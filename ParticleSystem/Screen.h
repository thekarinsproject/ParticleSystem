#pragma once

#include<SDL.h>

/*Members of a class are prefixed with m_*/

namespace tkp {

	class Screen
	{
	public:
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;
	public:
		Screen();
		bool init();
		void close();
		bool processEvent();
		void update();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void boxBlur();
		~Screen();
	private:
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
		Uint32 *m_buffer;
		Uint32* m_blurBuffer;
	};
}

