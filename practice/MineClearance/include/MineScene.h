#ifndef MINESCENE_H
#define MINESCENE_H

#include "MainWindow.h"
#include "MineItem.h"
#include "common.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QQueue>
#include <QWidget>

class MineItem;
class MainWindow;

/*
 * Class:       MineScene
 * Description: 游戏场景窗口类
 * Author:      TheOne1221
 * Version:     1.0.0
 * Date:        2023.9.20
 */
class MineScene : public QGraphicsScene {
  Q_OBJECT
public:
  /*
   * Function:    MineScene
   * Description: 游戏场景窗口类构造函数
   * Param:       parent
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  explicit MineScene(QWidget *parent = nullptr);
  /*
   * Function:    initScene
   * Description: 初始化游戏场景
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void initScene();
  /*
   * Function:    countAroundMines
   * Description: 统计方块周围的雷数
   * Param:       t_item(方格对象指针)
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void countAroundMines(MineItem *t_item);
  /*
   * Function:    openAllItems
   * Description: 打开所有的方块
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void openAllItems();
  /*
   * Function:    expandWater
   * Description: 扩散函数
   * Param:       t_item(方格对象指针)
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void expandWater(MineItem *t_item);
  /*
   * Function:    randomMine
   * Description: 消除一个并随机生成一个雷
   * Param:       oldMine(有雷的方格对象指针)
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void randomMine(MineItem *oldMine);

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
  int m_leftMouseNum{};  // 鼠标左击次数
};

#endif // MINESCENE_H
