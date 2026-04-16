# requirements
sudo apt-get install libx11-dev libxkbfile-dev  # 用来编译图形界面程序的开发库

# run
make clean
make MODE=release
./mario_pro_2

# other commands
make tgz

# explanation
![链路图](images/image-1.png)
![算逻辑 ➔ 画图 ➔ 画面瞬间上屏让玩家看到 ➔ 剩下的时间强制等待](images/image-2.png)
![画面更新全图](images/image-3.png)
