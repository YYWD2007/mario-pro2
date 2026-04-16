#include <vector>
#include "game.hh"
#include "window.hh"

using namespace std;

const int WIDTH = 480, HEIGHT = 320;
const int ZOOM = 2;
const int FPS = 48;

int main() {
    pro2::Window window("Mario Pro 2", WIDTH, HEIGHT, ZOOM);
    window.set_fps(FPS);

    Game game(WIDTH, HEIGHT);

    // 每一次 while 循环就是生成一帧画面
    // 为了保证游戏节奏平稳，程序会强制让每一次循环的总耗时卡在刚好 16ms 左右
    // 算一次逻辑 ➔ 画一次画面 ➔ 强制挂机等到 16ms 结束 ➔ 才能开始下一次。
    while (window.next_frame() && !game.is_finished()) {
        game.update(window);
        game.paint(window);
    }
}