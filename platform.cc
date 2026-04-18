#include "platform.hh"
#include "assert.hh"
using namespace std;

using pro2::Color;

const int b = 0xc84d0b;
const int _ = 0;

// clang-format off
const vector<vector<int>> Platform::platform_texture_ = {
    {b, b, b, b, b, b, _}, 
	{b, b, b, b, b, b, _}, 
	{b, b, b, b, b, b, _}, 
	{_, _, _, _, _, _, _},
    {b, b, b, _, b, b, b}, 
	{b, b, b, _, b, b, b}, 
	{b, b, b, _, b, b, b}, 
	{_, _, _, _, _, _, _},
};
// clang-format on

void Platform::paint(pro2::Window& window) const {
    assert(!platform_texture_.empty() && !platform_texture_[0].empty(),
           "La textura de la plataforma no pot ser buida.");
    const int xsz = platform_texture_.size();
    const int ysz = platform_texture_[0].size();
    for (int i = top_ + 1; i <= bottom_; i++) {
        for (int j = left_; j <= right_; j++) {
            window.set_pixel({j, i}, platform_texture_[(i - top_ - 1) % xsz][(j - left_) % ysz]);
        }
    }
}

/* 
判断物体是否（从上往下）穿过或落在了平台顶面：
1. 上一次和当前的 x 坐标都在平台的左右宽度范围内；
2. 上一次在平台顶部上方（y较小），且当前已到达平台顶部下方（y较大）。
帧1: [角色在地面]  →  y > top_（平台下方）
帧2: [起跳上升]    →  y 减小，向 top_ 靠近
帧3: [最高点]      →  y 最小，可能 < top_
帧4: [开始下落]    →  y 增大，从 top_ 上方往下方运动 ← 这里触发检测！
帧5: [落在平台]    →  y >= top_，x 在 [left_, right_] 内
*/
bool Platform::has_crossed_floor_downwards(pro2::Pt plast, pro2::Pt pcurr) const {
    return (left_ <= plast.x && plast.x <= right_) && (left_ <= pcurr.x && pcurr.x <= right_) &&
           (plast.y <= top_ && pcurr.y >= top_);
}

bool Platform::is_pt_inside(pro2::Pt pt) const {
	return left_ <= pt.x && pt.x <= right_ && top_ <= pt.y && pt.y <= bottom_;
}