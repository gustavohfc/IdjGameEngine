#include "pch.h"
#include "State.h"
#include "Vec2.h"
#include "Face.h"
#include "Sound.h"


State::State():
    music("assets/audio/stageState.ogg") {

    auto background = new GameObject();
    background->AddComponent(new Sprite(*background, "assets/img/ocean.jpg"));
    objectArray.emplace_back(background);

    music.Play();
}


State::~State() {
    objectArray.clear();
}


bool State::QuitRequested() const {
    return quitRequested;
}


void State::LoadAssets() {}


void State::Update(float dt) {
    Input();

    for (auto& obj : objectArray) {
        if (!obj->IsDead()) {
            obj->Update(dt);
        }
    }

    // Remove dead objects
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(),
                       [](const std::unique_ptr<GameObject>& obj) { return obj->ReadyToBeDeleted(); }),
        objectArray.end()
    );
}


void State::Render() {
    for (auto& obj : objectArray) {
        if (!obj->IsDead()) {
            obj->Render();
        }
    }
}


void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {

        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN) {

            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for (int i = objectArray.size() - 1; i >= 0; --i) {
                // Obtem o ponteiro e casta pra Face.
                GameObject* go = (GameObject*)objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if (go->box.Contains({float(mouseX), float(mouseY)})) {
                    Face* face = static_cast<Face*>(go->GetFace());
                    if (nullptr != face) {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN) {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quitRequested = true;
            }
                // Se não, crie um objeto
            else {
                Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI * (rand() % 1001) / 500.0) +
                    Vec2(mouseX, mouseY);
                AddObject(int(objPos.x), int(objPos.y));
            }
        }
    }
}


void State::AddObject(int mouseX, int mouseY) {
    auto gameObject = new GameObject();

    gameObject->AddComponent(new Sprite(*gameObject, "assets/img/penguinface.png"));
    gameObject->AddComponent(new Sound(*gameObject, "assets/audio/boom.wav"));
    gameObject->AddComponent(new Face(*gameObject));

    gameObject->box.SetCenter(mouseX, mouseY);

    objectArray.emplace_back(gameObject);
}
