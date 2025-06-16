#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <ctime>

class Game {
public:
    Game();
    void Run();

private:
    void Input();
    void Update();
    void Render();
    void Spawn();
    void Check();
    void HUD();

    Player p;
    std::vector<Enemy> e;
    int sc;
    int t;
    bool over;
};