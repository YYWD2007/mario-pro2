#ifndef COIN_HH
#define COIN_HH

#include "window.hh"
#include <vector>

class Coin{
private:
    pro2::Pt pos_;    
    bool collected_;
    int turn_;
    bool increasing_;

    static const std::vector<std::vector<int>> coin_sprite_normal_;
    static const std::vector<std::vector<int>> coin_sprite_turn1_;
    static const std::vector<std::vector<int>> coin_sprite_turn2_;
    static const std::vector<std::vector<int>> coin_sprite_turn3_;
    static const std::vector<std::vector<int>> coin_sprite_turn4_;

public:
    Coin(pro2::Pt pos): pos_(pos), collected_(false), turn_(0) {}

    void paint(pro2::Window& window) const;

    bool collected(pro2::Pt pos);

    pro2::Pt pos() const{
        return pos_;
    }

    void increase_turn_() {
        if(turn_ == 4) {
            increasing_ = false;
        } else if(turn_ == 0) {
            increasing_ = true;
        }
        if(increasing_) {
            turn_ ++;
        } else {
            turn_ --;
        }
    }
};

#endif