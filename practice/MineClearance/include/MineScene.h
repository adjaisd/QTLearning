// 游戏场景类
#ifndef MINESCENE_H
#define MINESCENE_H

#include "MainWindow.h"
#include "MineItem.h"
#include "common.h"
#include <QGraphicsScene>
#include <QWidget>

class MineItem;
class MainWindow;
class MineScene : public QGraphicsScene {
  Q_OBJECT
public:
  explicit MineScene(QWidget *parent = nullptr);

  void initScene();                        // 初始化游戏场景
  void countAroundMines(MineItem *t_item); // 统计方块周围的雷数
  void openAllItems();                     // 打开所有的方块
  void expandWater(MineItem *t_item);      // 扩散函数

signals:
  void sig_successPassGame();        // 游戏成功过关信号
  void sig_sceneNewGame();           // 重新开始游戏信号
  void sig_sceneDisplayMineNum(int); // 显示雷数信号

public:
  // 存储方块的容器
  QVector<QVector<MineItem *>> m_itemVec;
  int m_sceneRow{};      // 当前场景行数
  int m_sceneCol{};      // 当前场景列数
  int m_mineNum{};       // 当前场景雷数
  int m_currentLevel{};  // 当前场景难度级别
  int m_signedMineNum{}; // 右键标记的雷数
  int m_rightMineNum{};  // 右键标记正确的雷数
  bool m_isGameOver{};   // 游戏是否结束
  int m_remainNoMines{}; // 剩余非雷数
  bool m_soundOpen{};    // 声音开关: true: 打开声音 false: 关闭声音
};

#endif // MINESCENE_H
