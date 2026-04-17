# 新功能
1. Ex0.1. 按下P暂停，再次按下P继续。55daf6d
2. Ex0.2. 增加一个mario2_（在mario_左侧）, 和mario_同时移动，同样动作。50c7a95
3. Ex0.3. mario2_用WAD控制，mario_用LeftRightSpace控制，摄像机跟着mario_。fb0647e
4. Ex0.4. 镜头一直保持mario_在中心，持续跟随移动。e052c2d
5. Ex0.5-0.8. 根据相机位置，画出游戏界面边界框。在util.cc增加了paint_rect, 作用是画出长方形。
   在game.hh增加成员变量，使得长方形可以闪烁。