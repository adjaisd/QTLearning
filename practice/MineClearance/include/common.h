// 公共数据
#ifndef COMMON_H
#define COMMON_H

// 1. 游戏级别定义
enum gameLeve { LOWLEVEL = 0, MIDDLELEVEL = 1, HIGHLEVEL = 2, CUSTOMLEVEL = 3 };
// 2. 初级行、列、雷数设置
enum lowset { LOWROWANDCOL = 9, LOWMINENUM = 10 };
// 3. 中级行、列、雷数设置
enum middleset { MIDDLEROWANDCOL = 16, MIDDLEMINENUM = 40 };
// 4. 高级级行、列、雷数设置
enum heightset { HIGHROW = 16, HIGHCOL = 30, HIGHMINENUM = 99 };
// 5. 图片大小设置
enum mapset { MAPWIDTH = 25, MAPHEIGHT = 25 };

// 声音路径
const char timeSoundPath[] = ":/sounds/time.wav"; // 计时
const char winSoundPath[] = ":/sounds/win.wav";   // 胜利
const char bongSoundPath[] = ":/sounds/bong.wav"; // 失败
// 图片路径
const char flagImagePath[] = ":/images/flag1.png";       // 旗子
const char quesImagePath[] = ":/images/ques.png";        // 问号
const char bongImagePath[] = ":/images/bong/0.png";      // 炸弹
const char mineItemImagePath[] = ":/images/mine0_0.png"; // 打开的MineItem
const char initMineItemImagePath[] = ":/images/mine1_0.png"; // 初始化的MineItem
const char winImagePath[] = ":/images/cenWin0.png";          // 胜利
const char failImagePath[] = ":/images/cenLost0.png";        // 失败

#endif // COMMON_H
