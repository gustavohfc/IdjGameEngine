#include "pch.h"
#include "Game.h"
#include "StageState.h"


int main(int argc, char** argv) {

#ifdef VS_LEAK_CHECK
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    auto& game = Game::GetInstance();
    game.Push(new StageState());
    game.Run();

    return 0;
}
