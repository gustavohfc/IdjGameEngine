#pragma once
#include "GameObject.h"


class Alien : public Component {
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) override;

    void NotifyCollision(GameObject& other) override;

private:

    class Action {
    public:
        enum ActionType { MOVE, SHOOT };
        Action(ActionType type, Vec2 pos);
        ActionType type;
        Vec2 pos;
    };

    Vec2 speed = {0, 0};
    int hp;

    int nMinions;
    std::queue<Action> taskQueue;
    std::vector<std::shared_ptr<GameObject>> minionArray;
};
