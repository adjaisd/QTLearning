#include "MineScene.h"

QPoint t_around[8] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1},
};

/*
函数流程：
1) 设置游戏未结束
2) 右键标记雷数
3) 右键标记正确雷数为 0
4) 默认声音打开
 */
MineScene::MineScene(QWidget *parent) : QGraphicsScene(parent) {
  qDebug() << "MineScene";
  m_isGameOver = false;
  m_signedMineNum = 0;
  m_rightMineNum = 0;
  m_soundOpen = true;
}

/*
函数功能：初始化游戏场景，主要创建方块和随机布雷及连接信号
函数流程：
1) 初始化非雷数＝方块总数 - 总雷数
2) 根据当前行，列循环创建方块并加入行 vector 和场景中，并将行 vector 加入到总
vector中
3) 根据雷数循环随机布雷
4) 随机产生一个坐标
5) 如果该方块不是雷，则设置其为雷，并将周围八个方块上的周围雷数加 1
6) 将所有方块的重新开始游戏信号连接到场景的重新开始游戏信号
7) 将所有方块的重新设置雷数信号连接到场景的重新显示雷数信号
 */
void MineScene::initScene() {
  qDebug() << "initScene";
  // 1.初始化非雷数＝方块总数 - 总雷数
  m_remainNoMines = m_sceneRow * m_sceneCol - m_mineNum;
  for (int i = 0; i < m_sceneRow; ++i) {
    // 2.根据当前行，列循环创建方块并加入行 vector 和场景中，并将行 vector
    // 加入到总 vector中
    QVector<MineItem *> itemVec;
    for (int j = 0; j < m_sceneCol; ++j) {
      auto item =
          new MineItem(i, j,
                       QPixmap(initMineItemImagePath)
                           .scaled(MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio));
      item->setPos(j * MAPWIDTH, i * MAPHEIGHT);
      addItem(item);
      itemVec.push_back(item);
    }
    m_itemVec.push_back(itemVec);
  }
  // 3.根据雷数循环随机布雷
  srand(time(nullptr));
  for (int i = 0; i < m_mineNum; ++i) {
    // 4.随机产生一个坐标
    int tx = rand() % m_sceneRow;
    int ty = rand() % m_sceneCol;
    auto item = m_itemVec[tx][ty];
    // 5.如果该方块不是雷，则设置其为雷，并将周围八个方块上的周围雷数加 1
    if (!item->m_isMine) {
      item->m_isMine = true;
      // qDebug() << "m_sceneRow = " << m_sceneRow << "\tm_sceneCol=" <<
      // m_sceneCol;
      countAroundMines(item);
    } else {
      i--;
    }
  }
  for (int i = 0; i < m_sceneRow; ++i) {
    for (int j = 0; j < m_sceneCol; ++j) {
      auto item = m_itemVec[i][j];
      // 6.将所有方块的重新开始游戏信号连接到场景的重新开始游戏信号
      // connect(item, SIGNAL(sig_restartGame()), this, SLOT(slot_newGame()));
      connect(item, QOverload<>::of(&MineItem::sig_restartGame), this,
              [&]() { emit sig_sceneNewGame(); });
      // 7.将所有方块的重新设置雷数信号连接到场景的重新显示雷数信号
      connect(item, QOverload<int>::of(&MineItem::sig_resetMineNum), this,
              [&](int newSignedMineNum) {
                m_signedMineNum = newSignedMineNum;
                emit sig_sceneDisplayMineNum(m_signedMineNum);
              });
    }
  }
}

/*
函数功能：统计该方块周围的雷数，如果当前为雷，则将其周围 8
个方位的方块的周围雷数加 1
函数流程：
1) 如果为空或者不是雷，则返回
2) 循环查找 8 个方位
3) 计算所找方块在容器中的行，列
4) 如果越界,则重新下一次循环
5) 如果所找方块是雷，则重新下一次循环
6) 所找方块的周围雷数加 1
 */
void MineScene::countAroundMines(MineItem *t_item) {
  // qDebug() << "countAroundMines";
  //  1.如果为空或者不是雷，则返回
  if (t_item == nullptr || !t_item->m_isMine) {
    return;
  }
  // 2.循环查找 8 个方位
  for (int i = 0; i < 8; ++i) {
    // 3.计算所找方块在容器中的行，列
    int tx = t_item->m_X + t_around[i].x();
    int ty = t_item->m_Y + t_around[i].y();

    // 4.如果越界,则重新下一次循环
    // qDebug() << "tx = " << tx << "\tty=" << ty;
    if (tx < 0 || tx >= m_sceneRow || ty < 0 || ty >= m_sceneCol)
      continue;
    // 5.如果所找方块是雷，则重新下一次循环
    if (m_itemVec[tx][ty]->m_isMine)
      continue;
    // 6.所找方块的周围雷数加 1
    m_itemVec[tx][ty]->m_aroundMineNum++;
  }
}

/*
函数功能：打开所有的方块
函数流程：
1) 循环遍历所有方块
2) 将方块设置为打开
3) 如果是雷则将方块图片设置为雷图片
4) 如果不是雷则将方块图片设置为方块周围雷数所对应图片
 */
void MineScene::openAllItems() {
  qDebug() << "openAllItems";
  // 1.循环遍历所有方块
  if (m_isGameOver)
    return;
  // 2.将方块设置为打开
  for (int i = 0; i < m_sceneRow; ++i) {
    for (int j = 0; j < m_sceneCol; ++j) {
      auto item = m_itemVec[i][j];
      item->m_isOpened = true;
      if (item->m_isMine) { // 3.如果是雷则将方块图片设置为雷图片
        item->setPixmap(QPixmap(bongImagePath)
                            .scaled(MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio));
      } else {
        // 4.如果不是雷则将方块图片设置为方块周围雷数所对应图片
        QString picPath;
        picPath = (item->m_aroundMineNum == 0)
                      ? mineItemImagePath
                      : ":/images/mine1_" +
                            QString::number(item->m_aroundMineNum) + ".png";
        item->setPixmap(
            QPixmap(picPath).scaled(MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio));
      }
    }
  }
}

/*
函数功能：扩散函数，查找周围 8 个方位方块的周围雷数是否为
0,如果是则递归，如果不是 则设置方块图片为方块周围雷数对应图片
函数流程：
1) 如果为空，如果是雷则返回
2) 循环查找8个方位
3) 计算所找方块在容器中的行，列
4) 如果越界,则重新下一次循环
5) 如果所找方块是雷或者已打开，则重新下一次循环
6) 如果所找方块的已经右键点击
7) 设置所找方块已打开，当前剩余非雷数减 1
8) 如果所找方块周围雷数为0，则设置相应图片，并递归查找
9) 如果所找方块周围雷数不为0,则设置所找方块的图片为所找方块的周围雷数对应图片
10) 如果当前剩余非雷数为 0
11) 设置当前游戏结束，如果声音打开，则播放声音
12) 打开所有雷
13) 发送成功过关的信号
 */
//void MineScene::expandWater(MineItem *t_item) {
//  qDebug() << "expandWater";
//  // 1.如果为空，如果是雷则返回
//  if (t_item == nullptr || t_item->m_isMine)
//    return;
//  // 2.循环查找 8 个方位
//  for (int i = 0; i < 8; ++i) {
//    // 3.计算所找方块在容器中的行，列
//    int tx = t_item->m_X + t_around[i].x();
//    int ty = t_item->m_Y + t_around[i].y();
//    // 4.如果越界,则重新下一次循环
//    if (tx < 0 || tx >= m_sceneRow || ty < 0 || ty >= m_sceneCol)
//      continue;
//    // 5.如果所找方块是雷或者已打开，则重新下一次循环
//    auto nxtItem = m_itemVec[tx][ty];
//    if (nxtItem->m_isMine || nxtItem->m_isOpened)
//      continue;
//    // 6.如果所找方块的已经右键点击
//    if (nxtItem->m_rMouseKeyNum > 0)
//      continue;
//    // 7.设置所找方块已打开，当前剩余非雷数减 1
//    nxtItem->m_isOpened = true;
//    m_remainNoMines--;
//    // 8.如果所找方块周围雷数为 0，则设置相应图片，并递归查找
//    if (nxtItem->m_aroundMineNum == 0) {
//      nxtItem->setPixmap(QPixmap(mineItemImagePath)
//                             .scaled(MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio));
//      // nxtItem->setPixmap(QPixmap(mineItemImagePath));
//      expandWater(nxtItem);
//    } else {
//      // 9.如果所找方块周围雷数不为0,则设置所找方块的图片为所找方块的周围雷数对应图片
//      auto picPath = ":/images/mine1_" +
//                     QString::number(nxtItem->m_aroundMineNum) + ".png";
//      nxtItem->setPixmap(
//          QPixmap(picPath).scaled(MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio));
//    }
//  }
//  // 10.如果当前剩余非雷数为 0
//  if (m_remainNoMines == 0) {
//    // 打开所有雷，设置当前游戏结束，
//    openAllItems();
//    m_isGameOver = true;
//    // 如果声音打开，则播放声音
//    if (m_soundOpen) {
//      qDebug() << "play win.wav"
//               << "\tstatus : " << MainWindow::winSound->status();
//      MainWindow::winSound->play();
//    }
//    // 13.发送成功过关的信号
//    emit sig_successPassGame();
//  }
//}

// 采用dfs实现扩散
void MineScene::expandWater(MineItem *t_item) {
  qDebug() << "expandWater";
  // 1.如果为空，如果是雷则返回
  if (t_item == nullptr || t_item->m_isMine)
    return;
  QQueue<MineItem *> queue;
  queue.append(t_item);
  while (!queue.isEmpty()) {
    auto curItem = queue.front();
    queue.pop_front();
    for (int i = 0; i < 8; ++i) {
      // 3.计算所找方块在容器中的行，列
      int tx = curItem->m_X + t_around[i].x();
      int ty = curItem->m_Y + t_around[i].y();
      // 4.如果越界,则重新下一次循环
      if (tx < 0 || tx >= m_sceneRow || ty < 0 || ty >= m_sceneCol)
        continue;
      // 5.如果所找方块是雷或者已打开，则重新下一次循环
      auto nxtItem = m_itemVec[tx][ty];
      if (nxtItem->m_isMine || nxtItem->m_isOpened)
        continue;
      // 6.如果所找方块的已经右键点击
      if (nxtItem->m_rMouseKeyNum > 0)
        continue;
      // 7.设置所找方块已打开，当前剩余非雷数减 1
      nxtItem->m_isOpened = true;
      m_remainNoMines--;
      // 8.如果所找方块周围雷数为 0，则设置相应图片，并递归查找
      if (nxtItem->m_aroundMineNum == 0) {
        nxtItem->setPixmap(
            QPixmap(mineItemImagePath)
                .scaled(MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio));
        queue.append(nxtItem);
        // expandWater(nxtItem);
      } else {
        // 9.如果所找方块周围雷数不为0,则设置所找方块的图片为所找方块的周围雷数对应图片
        auto picPath = ":/images/mine1_" +
                       QString::number(nxtItem->m_aroundMineNum) + ".png";
        nxtItem->setPixmap(
            QPixmap(picPath).scaled(MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio));
      }
    }
  }
  // 10.如果当前剩余非雷数为 0
  if (m_remainNoMines == 0) {
    // 打开所有雷，设置当前游戏结束，
    openAllItems();
    m_isGameOver = true;
    // 如果声音打开，则播放声音
    if (m_soundOpen) {
      qDebug() << "play win.wav"
               << "\tstatus : " << MainWindow::winSound->status();
      MainWindow::winSound->play();
    }
    // 13.发送成功过关的信号
    emit sig_successPassGame();
  }
}