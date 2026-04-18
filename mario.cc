#include "mario.hh"
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
const vector<vector<int>> Mario::mario_sprite_normal_ = {
    {_, _, _, r, r, r, r, r, _, _, _, _},
    {_, _, r, r, r, r, r, r, r, r, r, _},
    {_, _, h, h, h, s, s, h, s, _, _, _},
    {_, h, s, h, s, s, s, h, s, s, s, _},
    {_, h, s, h, h, s, s, s, h, s, s, s},
    {_, h, h, s, s, s, s, h, h, h, h, _},
    {_, _, _, s, s, s, s, s, s, s, _, _},
    {_, _, r, r, b, r, r, r, _, _, _, _},
    {_, r, r, r, b, r, r, b, r, r, r, _},
    {r, r, r, r, b, b, b, b, r, r, r, r},
    {g, g, r, b, y, b, b, y, b, r, g, g},
    {g, g, g, b, b, b, b, b, b, g, g, g},
    {g, g, b, b, b, b, b, b, b, b, g, g},
    {_, _, b, b, b, _, _, b, b, b, _, _},
    {_, w, w, w, _, _, _, _, w, w, w, _},
    {w, w, w, w, _, _, _, _, w, w, w, w},
};
// clang-format on

void Mario::paint(pro2::Window& window) const {
    // pos_是Mario中下点（这个坐标是在game.cc里构造Mario的时候传入的），这里需要传入Mario左上角坐标开始渲染（print_sprite的orig参数）
    const Pt top_left = {pos_.x - 6, pos_.y - 15};  
    paint_sprite(window, top_left, mario_sprite_normal_, looking_left_);
}

void Mario::apply_physics_() {
    if (grounded_) {
        speed_.y = 0;
        accel_.y = 0;
    }

    // Always falling to check if we aren't grounded
    // If we are, we will return to the same spot

    const int gravity = 1;  // gravity = 1 pixel / frame_time^2
    speed_.y += gravity;

    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }

    pos_.x += speed_.x;
    pos_.y += speed_.y;
}

void Mario::jump() {
    if (grounded_) {
        accel_.y = -6;
        grounded_ = false;
        accel_time_ = 2;
    }
}

/**
 * @brief 更新mario人物，例如：跳，左右移动，等等，这个函数是更新数值，然后再apply。最后在game.cc里面调用paint
 */
void Mario::update(pro2::Window& window, const vector<Platform>& platforms) {
    // 先预留位置，再更新，这样就有了更新后的位置和之前的位置，用于
    last_pos_ = pos_;
    if (window.is_key_down(jump_key_)) {    // 把原来硬编码的Keys::Space改成成员变量
        jump();
    }

    // Velocitat horitzontal
    speed_.x = 0; 
    if (window.is_key_down(left_key_)) {   // 把原来硬编码的Keys::Left改成成员变量
        speed_.x = -4;
    } else if (window.is_key_down(right_key_)) {   // 把原来硬编码的Keys::Right改成成员变量
        speed_.x = 4;
    }
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }

    // Apply acceleration and speed
    apply_physics_();

    // Check position
    set_grounded(false);

    // 遍历游戏里所有平台
    for (const Platform& platform : platforms) {
        // 如果穿越了平台，Mario y 轴就 = platform.top(), grounded_ = true
        if (platform.has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform.top());
        }
    }
}