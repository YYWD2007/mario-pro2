#include "coin.hh"
#include "utils.hh"

using namespace std;
using namespace pro2;

const int _ = -1;
const int r = pro2::red;
const int s = 0xecc49b;
const int b = 0x5e6ddc;
const int y = pro2::yellow;
const int h = pro2::black;
const int g = 0xaaaaaa;
const int w = 0x8d573c;

// clang-format off
const vector<vector<int>> Coin::coin_sprite_normal_ = {
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, y, y, y, y, y, y, y, _, _, _},
    {_, _, y, y, y, y, y, y, y, _, _, _},
    {_, _, y, y, y, y, y, y, y, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
};
// clang-format on

const vector<vector<int>> Coin::coin_sprite_turn1_ = {
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
};

const vector<vector<int>> Coin::coin_sprite_turn2_ = {
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, y, y, y, y, y, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
};

const vector<vector<int>> Coin::coin_sprite_turn3_ = {
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
    {_, _, _, _, y, y, y, _, _, _, _, _},
};

const vector<vector<int>> Coin::coin_sprite_turn4_ = {
    {_, _, _, _, _, y, _, _, _, _, _, _},
    {_, _, _, _, _, y, _, _, _, _, _, _},
    {_, _, _, _, _, y, _, _, _, _, _, _},
    {_, _, _, _, _, y, _, _, _, _, _, _},
    {_, _, _, _, _, y, _, _, _, _, _, _},
    {_, _, _, _, _, y, _, _, _, _, _, _},
    {_, _, _, _, _, y, _, _, _, _, _, _},
};

void Coin::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 6, pos_.y - 6};
    if(turn_ == 0) {
        paint_sprite(window, top_left, coin_sprite_normal_, false);
    } else if(turn_ == 1) {
        paint_sprite(window, top_left, coin_sprite_turn1_, false);
    } else if(turn_ == 2) {
        paint_sprite(window, top_left, coin_sprite_turn2_, false);
    } else if(turn_ == 3) {
        paint_sprite(window, top_left, coin_sprite_turn3_, false);
    } else if(turn_ == 4) {
        paint_sprite(window, top_left, coin_sprite_turn4_, false);
    }
}

bool Coin::collected(pro2::Pt pos) {
    if(abs(pos.x-pos_.x)<10 && abs(pos.y-pos_.y)<10) {
        collected_ = true;
    }
    return collected_;    
}