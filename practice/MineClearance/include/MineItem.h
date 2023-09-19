// 游戏方块类
#ifndef MINEITEM_H
#define MINEITEM_H

#include "MineScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>
#include <QMessageBox>
#include <QObject>
#include <QWidget>

class MineItem : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
public:
  explicit MineItem(int t_x, int t_y, const QPixmap &itemPixmap,
                    QGraphicsItem *parent = nullptr);
  // 鼠标点击事件
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
