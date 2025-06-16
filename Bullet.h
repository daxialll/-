#pragma once

class Bullet {
public:
    Bullet(int a, int b, bool p);
    void Update();
    void Draw() const;
    int X() const;
    int Y() const;
    bool IsPlayer() const;

private:
    int x, y;
    bool p;
    char s;
};