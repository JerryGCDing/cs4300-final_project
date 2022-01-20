#include "SDLGraphicsProgram.h"
#include "Camera.h"
#include "VFXManager.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

SDLGraphicsProgram::SDLGraphicsProgram(int w, int h) : m_screenWidth(w), m_screenHeight(h) {
	// Initialization flag
	bool success = true;
	// String to log error message
	std::stringstream errorStream;
	// Target rendering window
	m_window = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Create window
		m_window = SDL_CreateWindow("Particle simulation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			m_screenWidth,
			m_screenHeight,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		// Check if Window did not create.
		if (m_window == NULL) {
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create an OpenGL Graphics Context
		m_openGLContext = SDL_GL_CreateContext(m_window);
		if (m_openGLContext == NULL) {
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize GLAD Library
		if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if (!InitGL()) {
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
	}

	// Log initialization error
	if (!success) {
		errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
		std::string errors = errorStream.str();
		SDL_Log("%s\n", errors.c_str());
	}
	else {
		SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL errors detected during initialization\n\n");
	}

	GetOpenGLVersionInfo();

	// Setup Visual Effect instance (Developing)
}

// Properly shutdown SDL
SDLGraphicsProgram::~SDLGraphicsProgram() {
	// Destroy window
	SDL_DestroyWindow(m_window);
	// Remove window pointer
	m_window = nullptr;
	// Quit SDL subsystem
	SDL_Quit();
}

bool SDLGraphicsProgram::InitGL() {
	// Shader setup moved to VFX initialization
	bool success = true;

	return success;
}

// Update animation effect (VFX Manager)
void SDLGraphicsProgram::Update() {
	// Developing
	VFXManager::Instance().Update(m_screenWidth, m_screenHeight);
}

// Render to frame buffer
void SDLGraphicsProgram::Render() {
	// Blending particle effect by distance to camera
	glEnable(GL_DEPTH_TEST);
	// Load in sky and water background texture
	glEnable(GL_TEXTURE_2D);

	// Initialize background color (Used in galatic and gloomy)
	glViewport(0, 0, m_screenWidth, m_screenHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear both buffer each frame
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// VFX render (Developing)
	VFXManager::Instance().Render();
}

// Main loop
void SDLGraphicsProgram::Loop() {
	// Quit event handler
	bool quit = false;
	// Input event handler
	SDL_Event e;
	// Enable text input
	SDL_StartTextInput();
	// Wireframe mode flag
	char wireFrame = '-';
	// VFX mode flag
	char VFXMode = PLAIN;

	while (!quit) {
		// Event queue
		while (SDL_PollEvent(&e) != 0) {
			// Click on 'x' on the corner of the window
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			else if (e.type == SDL_MOUSEWHEEL) {
				if (e.wheel.y > 0) {
					Camera::Instance().Zoom(0.1, '+');
				}
				else if (e.wheel.y < 0) {
					Camera::Instance().Zoom(0.1, '-');
				}
			}

			// Handle keyboard event
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					// Toggle mesh wireframe
					if (wireFrame = '-') {
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						wireFrame = '+';
					}
					else {
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
						wireFrame = '-';
					}
					break;
				// Switch between different VFX mode (Developing)
				case SDLK_1:
					if (VFXMode != PLAIN) {
						VFXManager::Instance().SetMode(PLAIN);
						VFXMode = PLAIN;
					}
					break;
				case SDLK_2:
					if (VFXMode != GALATIC) {
						VFXManager::Instance().SetMode(GALATIC);
						VFXMode = GALATIC;
					}
					break;
				case SDLK_3:
					if (VFXMode != GLOOM) {
						VFXManager::Instance().SetMode(GLOOM);
						VFXMode = GLOOM;
					}
					break;
				case SDLK_4:
					if (VFXMode != FLUID) {
						VFXManager::Instance().SetMode(FLUID);
						VFXMode = FLUID;
					}
					break;
				case SDLK_q:
				case SDLK_ESCAPE:
					quit = true;
				}
			}
		}

		// Update frame
		Update();
		// Render to frame buffer
		Render();

		// Delay effect by millisecond (~60 fps)
		SDL_Delay(20);
		// Update to window
		SDL_GL_SwapWindow(GetSDLWindow());
	}
	// Disable text input
	SDL_StopTextInput();
}

// Get window pointer
SDL_Window* SDLGraphicsProgram::GetSDLWindow() {
	return m_window;
}

void SDLGraphicsProgram::GetOpenGLVersionInfo() {
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s", (const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s", (const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s", (const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
