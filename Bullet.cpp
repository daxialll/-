#include "Bullet.h"
#include <Windows.h>
#include <iostream>

Bullet::Bullet(int a, int b, bool p) : x(a), y(b), p(p), s(p ? '^' : 'v') {}

void Bullet::Update() {
    p ? y-- : y++;
}

void Bullet::Draw() const {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << s;
}

int Bullet::X() const { return x; }
int Bullet::Y() const { return y; }
bool Bullet::IsPlayer() const { return p; }