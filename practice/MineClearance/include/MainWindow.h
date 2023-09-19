// 主程序窗口类
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
#include <QTextEdit>
#include <QTextStream>
#include <QTime>
#include <QTimer>

class MineScene;
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

  void create_action(); // 创建行为
  void create_menu();   // 创建菜单
  void readSettings();  // 读当前游戏设置
  void writeSettings(); // 写当前游戏设置

public slots:
  void slot_newGame(); // 开始新游戏槽
  // 点击游戏级别行为开始新游戏槽
  void slot_newGameByLevel(QAction *);
  // 接收自定义游戏设置槽
  void slot_acceptCustomVal(int row, int col, int mineNum);
  void slot_colorChanged();      // 设置颜色的槽
  void slot_soundChanged();      // 设置声音的槽
  void slot_heroChecked();       // 显示英雄榜的槽
  void slot_about();             // 显示 about 扫雷的槽
  void slot_updateHero();        // 更新英雄榜的槽
  void slot_displayMineNum(int); // 显示雷数的槽
  void slot_displayTime();       // 显示时间的槽

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