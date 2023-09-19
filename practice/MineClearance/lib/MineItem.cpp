#include "MineItem.h"

/*
初始化图片，在容器中行，在容器中列数，及其它成员数据
 */
MineItem::MineItem(int t_x, int t_y, const QPixmap &itemPixmap,
                   QGraphicsItem *parent)
    : m_X(t_x), m_Y(t_y), QGraphicsPixmapItem(parent) {
  qDebug() << "MineItem";
  m_isMine = false;
  m_isOpened = false;
  m_isRightMouse = false;
  m_aroundMineNum = 0;
  m_rMouseKeyNum = 0;
  setPixmap(itemPixmap);
}

/*
函数功能：鼠标点击事件，主要根据右键点击次数修改方块上的图片及相应设置
函数流程：
1) 获取所在场景，
2) 如果游戏已经结束或方块已经打开则返回
3) 如果是左键则设置图片
4) 如果是右键
5) 右键点击次数加 1
6) 如果右键点击次数为 1
7) 右键标记雷数加 1，设置图片为已标记，并发送重设雷数信号
8) 如果被标识方块是雷，则标记正确雷数加 1
9) 如果右键点击次数为 2
10) 右键标记雷数减 1，设置图片为问号标记，并发送重设雷数信号
11) 如果被标识方块是雷，则标记正确雷数减 1
12) 如果右键点击次数为 3
13) 设置方块图片为初始图片，将右键点击次数设为 0
 */
void MineItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  qDebug() << "mousePressEvent";
  QGraphicsItem::mousePressEvent(event);
  // 1.获取所在场景，
  auto mineScene = (MineScene *)this->scene();
  // 2.如果游戏已经结束或方块已经打开则返回
  if (mineScene->m_isGameOver || m_isOpened)
    return;
  if (event->button() == Qt::RightButton) { // 4.如果是右键
    // 5.右键点击次数加 1
    m_rMouseKeyNum++;
    // 7.右键标记雷数加 设置图片为已标记，
    m_isRightMouse = true;
    if (m_rMouseKeyNum == 1) { // 6.如果右键点击次数为 1
      mineScene->m_signedMineNum++;
      setPixmap(QPixmap(":/images/flag1.png"));
      emit sig_resetMineNum(mineScene->m_signedMineNum); // 发送重设雷数信号
      // 8.如果被标识方块是雷
      if (m_isMine)
        mineScene->m_rightMineNum++;  // 则标记正确雷数加 1
    } else if (m_rMouseKeyNum == 2) { // 9.如果右键点击次数为2
      // 10.右键标记雷数减1，
      mineScene->m_signedMineNum--;
      setPixmap(QPixmap(":/images/ques.png")); // 设置图片为问号标记
      // 并发送重设雷数信号
      emit sig_resetMineNum(mineScene->m_signedMineNum);
      // 11.如果被标识方块是雷，则标记正确雷数减1
      if (m_isMine)
        mineScene->m_rightMineNum--;
    } else if (m_rMouseKeyNum == 3) { // 12.如果右键点击次数为 3
      // 13.设置方块图片为初始图片，将右键点击次数设为 0
      m_isRightMouse = false;
      setPixmap(QPixmap(":/images/mine1_0.png"));
      m_rMouseKeyNum = 0;
    }
  } else if (event->button() == Qt::LeftButton) { // 如果是左键
    // 如果此方块已经被右键点击 1 次，则返回
    if (m_isRightMouse)
      return;
    // 设置此方块已打开
    m_isOpened = true;
    // 如果是雷
    if (m_isMine) {
      //setPixmap(QPixmap(":/images/bong/0.png"));
      setPixmap(QPixmap(":/images/icon.png")); // 设置为雷的图片
      if (mineScene->m_soundOpen) { // 如果声音打开，则播放声音
        auto sound = QSoundEffect();
        sound.setSource(QUrl::fromLocalFile(":/sounds/bong.wav"));
        sound.play();
        sound.
      }
      // 打开所有方块，并设置游戏结束
      mineScene->m_isGameOver = true;
      mineScene->openAllItems();
      // 弹出扫雷失败消息
      QMessageBox::information((QWidget *)(scene()->parent()), tr("扫雷失败"),
                               tr("扫雷失败"));
      // 发送重新游戏信号，并返回
      emit sig_restartGame();
      return;
    } else { // 如果不是雷
      // 如果周围雷数为0,则设置图片，并扩散
      if (m_aroundMineNum == 0) {
        setPixmap(QPixmap(":/images/mine0_0.png"));
        mineScene->expandWater(this);
      } else { // 如果周围雷数不为0
        // 则设置方块图片为方块中周围雷数所对应图片
        auto picPath =
            ":/images/mine1_" + QString::number(m_aroundMineNum) + ".png";
        setPixmap(QPixmap(picPath));
      }
    }
    // 将场景中非雷数减1
    mineScene->m_remainNoMines--;
    if (mineScene->m_remainNoMines == 0) { // 如果场景中非雷数为0
      // 设置游戏结束，如果声音打开，则播放声音
      mineScene->m_isGameOver = true;
      if (mineScene->m_soundOpen) {
        auto sound = QSoundEffect();
        sound.setSource(QUrl::fromLocalFile(":/sounds/win.wav"));
        sound.play();
      }
      // 打开所有方块，发送场景的成功过关信号
      mineScene->openAllItems();
      emit mineScene->sig_successPassGame();
    }
  }
}