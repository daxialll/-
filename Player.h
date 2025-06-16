#pragma once
#include "Bullet.h"
#include <vector>
#include <string>

class Player {
public:
    Player(int a, int b);
    void Update();
    void Draw() const;
    void Move(int dx, int dy);
    void Shoot();
    void TakeDamage();
    bool IsAlive() const;
    int X() const;
    int Y() const;
    int W() const;
    int H() const;
    const std::vector<Bullet>& GetBullets() const;
    void RemoveBullet(int i);

private:
    int x, y;
    int h;
    std::vector<std::string> s;
    std::vector<Bullet> b;
};