#include "game.hh"
#include "assert.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}),
      mario2_({(width / 2) - 30, 150}),    // mario2_初始构造位置
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      finished_(false), paused_(false) {    // 加了paused_成员bool变量，记得这里要初始构造！(到这里是初始化列表) 
    assert(width > 0 && height > 0, "L'amplada i l'alcada del joc han de ser positives.");
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
}

/**
 * @brief is_key_down是windows里的函数，识别按下的键。这个函数：如果按下特定键，暂停或结束
 */
void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if(window.was_key_pressed('P')) {
        if(paused_ == true) {
            paused_ = false;
        } else {
            paused_ = true;
        }
        return;
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);
    mario2_.update(window, platforms_);     // 更新mario2_的移动，动作
}

/**
 * @brief 
 */
void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    // 这段代码在屏幕正中央画了一个看不见的矩形框。
    // 它的宽度是屏幕宽度的一半（左右各 1/4），高度是屏幕高度的一半（上下各 1/4）。
    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0; // dx和dy代表摄像机需要移动的距离，初始为0（不移动）
    // 检查是否出了矩形框，出了就更新dx, dy, 最终移动相机位置
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }

    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    if(!is_paused()) {
        update_objects(window);
        update_camera(window);
    }
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    mario_.paint(window);
    mario2_.paint(window);  // 打印第二个(mario2_)
}