#pragma once
#include <vector>
#include <string>

class Enemy {
public:
    Enemy(int a, int b);
    void Update();
    void Draw() const;
    int X() const;
    int Y() const;
    int W() const;
    int H() const;
    bool Alive() const;
    void Hit();

private:
    int x, y;
    int h;
    std::vector<std::string> s = { "\\+/", " |" };
};