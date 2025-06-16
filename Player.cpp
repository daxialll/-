#define NOMINMAX
#include "Player.h"
#include <Windows.h>
#include <algorithm>
#include <iostream>

Player::Player(int a, int b) : x(a), y(b), h(3) {
    s = { "  /=\\  ", " <<*>> ", "  * *  " };
}

int Player::W() const { return s.empty() ? 0 : static_cast<int>(s[0].size()); }
int Player::H() const { return static_cast<int>(s.size()); }

void Player::Update() {
    for (auto& bl : b) bl.Update();
    b.erase(std::remove_if(b.begin(), b.end(),
        [](const Bullet& bl) { return bl.Y() <= 0; }), b.end());
}

void Player::Draw() const {
    for (int i = 0; i < s.size(); ++i) {
        COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y + i) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        std::cout << s[i];
    }
    for (auto& bl : b) bl.Draw();
}

void Player::Move(int dx, int dy) {
    x = std::max(0, std::min(79 - W(), x + dx));
    y = std::max(0, std::min(24 - H(), y + dy));
}

void Player::Shoot() {
    b.emplace_back(x + W() / 2, y - 1, true);
}

void Player::TakeDamage() {
    if (h > 0) h--;
}

bool Player::IsAlive() const {
    return h > 0;
}

int Player::X() const { return x; }
int Player::Y() const { return y; }
const std::vector<Bullet>& Player::GetBullets() const { return b; }

void Player::RemoveBullet(int i) {
    if (i >= 0 && i < b.size()) b.erase(b.begin() + i);
}