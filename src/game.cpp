#include <cassert>
#include <cstdio>
#include <SDL2/SDL_image.h>
#include "exception.hpp"
#include "timer.hpp"
#include "game.hpp"


Game::Game() 
: mTitle(""),
  mWidth(1240),
  mHeight(720),
  mWinFlags(SDL_WINDOW_SHOWN),  // Default window options.
  mRenFlags(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),  // Default renderer options.
  mWin(nullptr),
  mRen(nullptr),
  mRunning(false) {

    initSDL();

}


Game::~Game() {

    SDL_DestroyRenderer(mRen);
    SDL_DestroyWindow(mWin);
    exitSDL();

}


void Game::run() {

    // Create window and render.
    createWin();
    createRen();
    Timer timer;
    timer.start();

    printf("running...\n");

    mRunning = true;
    while (mRunning) {

        // Handle queued events.
        handleEvents();

        // Get time past since last update and restart timer.
        float deltaTime = timer.getTime();
        timer.start();

        // Update game world with time passed since last update.
        update(deltaTime);

        // Draw the game world.
        render();

    }

    // Destroy window and renderer.
    SDL_DestroyRenderer(mRen);
    SDL_DestroyWindow(mWin);

}


void Game::initSDL() const {

    printf("initialising...\n");

    if ((SDL_Init(SDL_INIT_VIDEO) < 0) ||
        (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))) {

        throw SDLException();

    }

}


void Game::exitSDL() const {

    printf("exiting...\n");

    IMG_Quit();
    SDL_Quit();

    printf("finished\n");

}


// TODO: add window settings customisation.
void Game::createWin() {

    if (mWin != nullptr) {

        SDL_DestroyWindow(mWin);

    }

    // TODO: add title customisation.
    mWin = SDL_CreateWindow(mTitle.c_str(),
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            mWidth,
                            mHeight,
                            mWinFlags);

    if (mWin == nullptr) {

        throw SDLException();

    }

}


// TODO: add renderer settings customisation.
void Game::createRen() {

    if (mRen != nullptr) {

        SDL_DestroyRenderer(mRen);

    }

    mRen = SDL_CreateRenderer(mWin, -1, mRenFlags);

    if (mRen == nullptr) {

        throw SDLException();

    }
}


void Game::handleEvents() {

    SDL_Event event;
    while (mRunning && SDL_PollEvent(&event)) {

        mRunning = event.type != SDL_QUIT;

    }

}


void Game::update(float /*deltaTime*/) {

    // TODO: implement.

}


void Game::render() {

    // TODO: implement.

}


void Game::setTitle(const std::string& title) {

    mTitle = title;

}


void Game::setWinSize(int x, int y) {

    mWidth = x;
    mHeight = y;

}


void Game::setFullScreen(bool full) {

    if (full) {

        mWinFlags |= SDL_WINDOW_FULLSCREEN;
        assert(mWinFlags & SDL_WINDOW_FULLSCREEN);

    } else {

        mWinFlags &= ~SDL_WINDOW_FULLSCREEN;
        assert(!(mWinFlags & SDL_WINDOW_FULLSCREEN));

    }

}


void Game::setVSync(bool vsync) {

    if (vsync) {

        mRenFlags |= SDL_RENDERER_PRESENTVSYNC;
        assert(mRenFlags & SDL_RENDERER_PRESENTVSYNC);

    } else {

        mRenFlags &= ~SDL_RENDERER_PRESENTVSYNC;
        assert(!(mRenFlags & SDL_RENDERER_PRESENTVSYNC));

    }

}
