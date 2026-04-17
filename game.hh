#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"

class Game {
    Mario                 mario_;
    Mario                 mario2_;  // 新增加一个人物，mario2_
    std::vector<Platform> platforms_;

    bool finished_, paused_;    // 新增paused_，识别游戏是否暂停

    int sparkle;  // 新: 控制闪烁间隔
    bool render;  // 新: 控制打印渲染

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }

    bool is_paused() const {
        return paused_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif