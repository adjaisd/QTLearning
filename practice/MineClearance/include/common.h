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

#include <QSoundEffect>
#include <QString>

void playMusic(const QString &path);

#endif // COMMON_H
