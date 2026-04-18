#include "game.hh"
#include "assert.hh"
using namespace pro2;

// 新: 调用utils里面的函数打印
#include "utils.hh"

// main.cc里面进行game对象构造
Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Space, Keys::Left, Keys::Right),
      mario2_({(width / 2) - 30, 150}, 'W', 'A', 'D'),    // mario2_初始构造位置和移动键
      // 初始构造3个平台
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      // 新：构造金币
      coins_{
        Coin({110, 150}),
        Coin({120, 195}),
        Coin({130, 195}),
      },
      finished_(false), paused_(false), render(false), sparkle(0) {    // 加变量后，记得这里要初始构造！(到这里是初始化列表) 
    assert(width > 0 && height > 0, "L'amplada i l'alcada del joc han de ser positives.");
    // 这里又添加了19个平台！！！
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
        coins_.push_back(Coin({130 + i * 100, 150}));
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

// void Game::update_camera(pro2::Window& window) {
//     const Pt pos = mario_.pos();
//     const Pt cam = window.camera_center();

//     // 这段代码在屏幕正中央画了一个看不见的矩形框。
//     // 它的宽度是屏幕宽度的一半（左右各 1/4），高度是屏幕高度的一半（上下各 1/4）。
//     const int left = cam.x - window.width() / 4;
//     const int right = cam.x + window.width() / 4;
//     const int top = cam.y - window.height() / 4;
//     const int bottom = cam.y + window.height() / 4;

//     int dx = 0, dy = 0; // dx和dy代表摄像机需要移动的距离，初始为0（不移动）
//     // 检查是否出了矩形框，出了就更新dx, dy, 最终移动相机位置
//     if (pos.x > right) {
//         dx = pos.x - right;
//     } else if (pos.x < left) {
//         dx = pos.x - left;
//     }
//     if (pos.y < top) {
//         dy = pos.y - top;
//     } else if (pos.y > bottom) {
//         dy = pos.y - bottom;
//     }

//     window.move_camera({dx, dy});
// }

/**
 * @brief 新增：永远保持Mario在中心位置，和上面注释的镜头移动函数的逻辑不同。
 */
void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    int dx = 0, dy = 0; // dx和dy代表摄像机需要移动的距离，初始为0（不移动）
    if (pos.x != cam.x) {
        dx = pos.x - cam.x;
    }
    if (pos.y != cam.y) {
        dy = pos.y - cam.y;
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
    // 后打印的会覆盖前面打印的，位置不是无所谓
    window.clear(sky_blue);
    Rect r = window.camera_rect();  // 此函数作用见docs/window.md

    Rect r1 = {r.left+10, r.top+10, r.right-10, r.bottom-10};
    if(sparkle==10) {
        render = !render;
        sparkle = 0;
    }
    if(render) paint_rect(window, r1, yellow);  // 新: 渲染长方形
    // sparkle ++;  // 开启后会闪烁

    for (const Platform& p : platforms_) {
        p.paint(window);
    }

    // 新：如果mario_还没和金币重合就打印金币
    for(Coin& c : coins_) {
        if(!c.collected(mario_.pos())) {
            c.paint(window);
            c.increase_turn_();
        }
    }

    mario_.paint(window);
    mario2_.paint(window);  // 打印第二个(mario2_)
    
    // nou: imprimir requadre al marc de la pantalla, -1?
    paint_hline(window, r.left, r.right-1, r.top);
    paint_hline(window, r.left, r.right-1, r.bottom-1);
    paint_vline(window, r.left, r.top, r.bottom-1);
    paint_vline(window, r.right-1, r.top, r.bottom-1);

    // paint_rect(window, r1, yellow);  // 如果放在最后就会覆盖!
}