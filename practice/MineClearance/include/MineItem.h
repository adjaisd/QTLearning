#ifndef MINEITEM_H
#define MINEITEM_H

#include "MineScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>
#include <QMessageBox>
#include <QObject>
#include <QWidget>

/*
 * Class:       MineItem
 * Description: 游戏场景中的方格类
 * Author:      TheOne1221
 * Version:     1.0.0
 * Date:        2023.9.20
 */
class MineItem : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
public:
  /*
   * Function:    MineScene
   * Description: 游戏场景中的方格类构造函数
   * Param:       t_x(横坐标)、t_y(纵坐标)、itemPixmap(初始化图片)、parent
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  explicit MineItem(int t_x, int t_y, const QPixmap &itemPixmap,
                    QGraphicsItem *parent = nullptr);
  /*
   * Function:    MineScene
   * Description: 鼠标点击事件
   * Param:       event(鼠标事件)
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
  void sig_restartGame();                     // 重新开始游戏信号
  void sig_resetMineNum(int t_signedMineNum); // 重设雷数信号

public:
  int m_X{};             // 在容器中的行数
  int m_Y{};             // 在容器中的列数
  int m_aroundMineNum{}; // 周围雷数
  int m_rMouseKeyNum{};  // 右键点击的次数
  bool m_isMine{};       // 是否为雷
  bool m_isOpened{};     // 是否打开
  bool m_isRightMouse{}; // 是否右键
};

#endif // MINEITEM_H
