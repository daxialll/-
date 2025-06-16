#include "Enemy.h"
#include <Windows.h>
#include <iostream>

Enemy::Enemy(int a, int b) : x(a), y(b), h(1) {}

int Enemy::W() const { return 2; }
int Enemy::H() const { return 2; }

void Enemy::Update() {
    y++;
}

void Enemy::Draw() const {
    COORD p1 = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p1);
    std::cout << s[0];

    COORD p2 = { static_cast<SHORT>(x), static_cast<SHORT>(y + 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p2);
    std::cout << s[1];
}

int Enemy::X() const { return x; }
int Enemy::Y() const { return y; }
bool Enemy::Alive() const { return h > 0; }
void Enemy::Hit() { h--; }