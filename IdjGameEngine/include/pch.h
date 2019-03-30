#ifndef PCH_H
#define PCH_H

// SDL
#ifdef _WIN32
    #include "SDL.h"
    #include "SDL_image.h"
    #include "SDL_mixer.h"
    #include "SDL_ttf.h"
#else
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
#endif

// C++ Standard Library
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <ctime>
#include <memory>
#include <cmath>

#endif //PCH_H
