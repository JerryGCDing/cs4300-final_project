#ifndef SDLGRAPHICSPROGRAM_H
#define SDLGRAPHICSPROGRAM_H

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

// The glad library helps setup OpenGL extensions.
#include <glad/glad.h>

class SDLGraphicsProgram {
	// Window size
	unsigned int m_screenWidth;
	unsigned int m_screenHeight;
	// Target rendering window
	SDL_Window* m_window;
	// OpenGL context
	SDL_GLContext m_openGLContext;

public:
	// Constructor
	SDLGraphicsProgram(int w, int h);
	// Destructor
	~SDLGraphicsProgram();
	// Initialize OpenGL
	bool InitGL();
	// Frame update
	void Update();
	// Render buffer to the screen
	void Render();
	// Run program forever
	void Loop();
	// Get window pointer
	SDL_Window* GetSDLWindow();
	// OpenGL information helper function
	void GetOpenGLVersionInfo();
};

#endif
