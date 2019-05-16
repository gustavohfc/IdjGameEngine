#include "pch.h"
#include "Game.h"
#include "StateStage.h"


int main(int argc, char** argv) {

#ifdef VS_LEAK_CHECK
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    auto& game = Game::GetInstance();
    game.Push(new StateStage());
    game.Run();

    return 0;
}
