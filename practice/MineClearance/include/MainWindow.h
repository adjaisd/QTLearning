#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CustomGameDialog.h"
#include "HeroDialog.h"
#include "MineScene.h"
#include "common.h"
#include <QAction>
#include <QActionGroup>
#include <QGraphicsView>
#include <QInputDialog>
#include <QLCDNumber>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPalette>
#include <QPushButton>
#include <QSettings>
#include <QSoundEffect>
#include <QTime>
#include <QTimer>

class MineScene;

/*
 * Class:       MainWindow
 * Description: 游戏主窗口类
 * Author:      TheOne1221
 * Version:     1.0.0
 * Date:        2023.9.20
 */
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  /*
   * Function:    MainWindow
   * Description: 游戏主窗口类构造函数
   * Param:       parent
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  explicit MainWindow(QWidget *parent = nullptr);
  /*
   * Function:    create_action
   * Description: 创建行为
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void create_action();
  /*
   * Function:    create_menu
   * Description: 创建菜单
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void create_menu();
  /*
   * Function:    readSettings
   * Description: 读当前游戏设置
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void readSettings();
  /*
   * Function:    writeSettings
   * Description: 写当前游戏设置
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void writeSettings();

public slots:
  /*
   * Function:    slot_newGame
   * Description: 开始新游戏槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_newGame();
  /*
   * Function:    slot_newGameByLevel
   * Description: 点击游戏级别行为开始新游戏槽
   * Param:       action(菜单点击单独事件指针)
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_newGameByLevel(QAction *action);
  /*
   * Function:    slot_acceptCustomVal
   * Description: 接收自定义游戏设置槽
   * Param:       row(行数)、col(列数)、mineNum(雷数)
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_acceptCustomVal(int row, int col, int mineNum);
  /*
   * Function:    slot_colorChanged
   * Description: 设置颜色的槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_colorChanged();
  /*
   * Function:    slot_soundChanged
   * Description: 设置声音的槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_soundChanged();
  /*
   * Function:    slot_heroChecked
   * Description: 显示英雄榜的槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_heroChecked();
  /*
   * Function:    slot_about
   * Description: 显示about扫雷的槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_about();
  /*
   * Function:    slot_updateHero
   * Description: 更新英雄榜的槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_updateHero();
  /*
   * Function:    slot_displayMineNum
   * Description: 显示雷数的槽
   * Param:       mineNum(已标旗雷数)
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_displayMineNum(int mineNum);
  /*
   * Function:    slot_displayTime
   * Description: 显示时间的槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_displayTime();

public:
  static int count;
  // 采用临时变量在执行到play()后自动销毁，导致播放异常
  static QSoundEffect *timeSound;
  static QSoundEffect *winSound;
  static QSoundEffect *bongSound;
  /*
   * Function:    initMusic
   * Description: 初始化音乐
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  static void initMusic();

private:
  QAction *newAction{};
  QAction *lowLeveAction{};
  QAction *middleLeveAction{};
  QAction *highLeveAction{};
  QAction *customAction{};
  QAction *colorAction{};
  QAction *soundAction{};
  QAction *heroAction{}; // 英雄榜行为
  QAction *exitAction{};
  QAction *aboutAction{};

  // 主程序界面 mainWindow->setCentralWidget(centralWidget);
  QWidget *centralWidget{};
  QGraphicsView *mineView{};  // 主程序视图
  MineScene *mineScene{};     // 主程序场景
  QLCDNumber *mineNumLcd{};   // 雷数 LCD
  QLCDNumber *timeLcd{};      // 时间 LCD
  QPushButton *smileButton{}; // 笑脸按钮
  QTimer *m_timer{};          // 定时器
  int m_time{};               // 当前用时数
};

#endif // MAINWINDOW_H