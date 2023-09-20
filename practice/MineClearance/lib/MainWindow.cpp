#include "MainWindow.h"

/*
函数功能：
函数流程：
1) 设置窗口标题，图片，只关闭按钮有效
2) 初始化列表中初始化主界面内的所有对象
3) 创建行为
4) 创建菜单
5) 开始新游戏 slot_newGame()
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  // 1.设置窗口标题，图片，只关闭按钮有效
  setWindowTitle(tr("扫雷"));
  setWindowIcon(QIcon(":/images/icon.png"));

  // 3.创建行为
  create_action();
  // 4.创建菜单
  create_menu();
  // 5.开始新游戏 slot_newGame()
  slot_newGame();
}

/*
函数功能：开始新游戏槽
函数流程：
1) 清理旧对象 deleteLater();
2) 创建主界面对象
3) 创建调色板，雷数 LCD，时间 LCD，并设置 LCD 上的颜色
4) 创建笑脸按钮，并设置图片，并将信号连接到开始新游戏槽
5) 创建水平布局，将雷数 LCD，笑脸按钮，时间 LCD，加入到水平布局
6) 创建主视图，主场景，将场景加入到视图，并读取游戏当前设置
7)
将场景的开始新游戏信号连接到开始新游戏槽，将场景的显示雷数信号连接到显示雷数的槽，将场
景成功过关信号连接到更新英雄榜的槽
8) 创建垂直布局，并将水平布局和主视图加入到垂直布局，将主界面设置应用程序主界面
9) 根据图片大小和行，列数据设置场景，主视图，主窗口大小
10) 根据当前场景的游戏级别设置相应的级别行为被选中
11) LCD 显示雷数和时间（初始为 0）
12) 创建定时器，将超时信号连接到显示时间槽
13) 初始化场景,启动定时器
 */
void MainWindow::slot_newGame() {
  // 1.清理旧对象
  centralWidget->deleteLater();
  mineView->deleteLater();
  mineScene->deleteLater();
  mineNumLcd->deleteLater();
  smileButton->deleteLater();
  timeLcd->deleteLater();
  m_timer->deleteLater();
  // 2.主界面
  centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  // 3.创建调色板，雷数 LCD，时间 LCD，并设置 LCD 上的颜色
  QPalette textPalette;
  textPalette.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
  mineNumLcd = new QLCDNumber(centralWidget);
  mineNumLcd->setPalette(textPalette);
  mineNumLcd->setDigitCount(3);
  timeLcd = new QLCDNumber(centralWidget);
  timeLcd->setPalette(textPalette);
  timeLcd->setDigitCount(3);

  // 4.创建笑脸按钮，并设置图片，并将信号连接到开始新游戏槽
  smileButton = new QPushButton(centralWidget);
  smileButton->setIcon(QPixmap(":/images/cenNormal0.png"));
  connect(smileButton, SIGNAL(clicked(bool)), this, SLOT(slot_newGame()));
  // 5.创建水平布局，将雷数 LCD，笑脸按钮，时间 LCD，加入到水平布局
  auto hLayout = new QHBoxLayout;
  hLayout->addWidget(mineNumLcd);
  hLayout->addStretch();
  hLayout->addWidget(smileButton);
  hLayout->addStretch();
  hLayout->addWidget(timeLcd);
  // 6.创建主视图，主场景，将场景加入到视图，并读取游戏当前设置
  mineView = new QGraphicsView(centralWidget);
  mineScene = new MineScene(mineView);
  mineView->setScene(mineScene);
  readSettings();
  // 7.将场景的开始新游戏信号连接到开始新游戏槽，将场景的显示雷数信号连接到显示雷数的槽，将场景成功过关信号连接到更新英雄榜的槽
  connect(mineScene, SIGNAL(sig_sceneNewGame()), this, SLOT(slot_newGame()));
  connect(mineScene, SIGNAL(sig_sceneDisplayMineNum(int)), this,
          SLOT(slot_displayMineNum(int)));
  connect(mineScene, SIGNAL(sig_successPassGame()), this,
          SLOT(slot_updateHero()));
  // 8.创建垂直布局，并将水平布局和主视图加入到垂直布局，将主界面设置应用程序主界面
  auto vLayout = new QVBoxLayout(centralWidget);
  vLayout->addLayout(hLayout);
  vLayout->addWidget(mineView);
  setCentralWidget(centralWidget);

  // 9.根据图片大小和行，列数据设置场景，主视图，主窗口大小
  mineScene->setSceneRect(0, 0, mineScene->m_sceneCol * MAPWIDTH,
                          mineScene->m_sceneRow * MAPHEIGHT);
  mineView->setFixedSize(mineScene->m_sceneCol * MAPWIDTH + 5,
                         mineScene->m_sceneRow * MAPHEIGHT + 5);
  setFixedSize(mineScene->m_sceneCol * MAPWIDTH + 25,
               mineScene->m_sceneRow * MAPHEIGHT + 70);
  // setContentsMargins(0, 0, 0, 5);
  //  10.根据当前场景的游戏级别设置相应的级别行为被选中
  if (mineScene->m_currentLevel == LOWLEVEL)
    lowLeveAction->setChecked(true);
  else if (mineScene->m_currentLevel == MIDDLELEVEL)
    middleLeveAction->setChecked(true);
  else if (mineScene->m_currentLevel == HIGHLEVEL)
    highLeveAction->setChecked(true);
  else if (mineScene->m_currentLevel == CUSTOMLEVEL)
    customAction->setChecked(true);
  // 11.LCD 显示雷数和时间（初始为 0）
  m_time = 0;
  mineNumLcd->display(mineScene->m_mineNum);
  timeLcd->display(m_time);
  // 12.创建定时器，将超时信号连接到显示时间槽
  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_displayTime()));
  m_timer->start(1000);
  // 13.初始化场景,启动定时器
  mineScene->initScene();
  if (MainWindow::count == 0)
    slot_soundChanged();
  MainWindow::count++;
}

/*
函数功能：创建行为，并连接到相应槽
函数流程：
1) 创建开局行为，并将其连接到开始新游戏槽
2) 创建初级行为，并设置为可选择 setCheckable，已选中 setChecked()
3) 创建中级行为，并设置为可选择
4) 创建高级行为，并设置为可选择
5) 创建算定义行为，并设置为可选择
6)
创建行为组，并将初级，中级，高级，自定义行为加入到行为组，并将行为级信号连接到点击游戏
级别行为创建游戏的槽
7) 创建颜色行为，并设置可选和选中，并连接到颜色设置槽
8) 创建声音行为，并设置可选和选中，并连接到声音设置槽
9) 创建英雄榜行为，并连接到显示英雄榜的槽
10) 创建退出和关于扫雷槽，并连接到相应槽
 */
void MainWindow::create_action() {
  newAction = new QAction("新游戏");
  connect(newAction, SIGNAL(triggered(bool)), this, SLOT(slot_newGame()));

  // 行为组
  auto levelActionGroup = new QActionGroup(this);
  lowLeveAction = new QAction("低难度");
  middleLeveAction = new QAction("中难度");
  highLeveAction = new QAction("高难度");
  customAction = new QAction("自定义难度");
  levelActionGroup->addAction(lowLeveAction);
  levelActionGroup->addAction(middleLeveAction);
  levelActionGroup->addAction(highLeveAction);
  levelActionGroup->addAction(customAction);
  lowLeveAction->setCheckable(true);
  middleLeveAction->setCheckable(true);
  highLeveAction->setCheckable(true);
  customAction->setCheckable(true);

  lowLeveAction->setChecked(true);

  connect(levelActionGroup, SIGNAL(triggered(QAction *)), this,
          SLOT(slot_newGameByLevel(QAction *)));

  colorAction = new QAction("颜色");
  colorAction->setCheckable(true);
  connect(colorAction, SIGNAL(triggered(bool)), this,
          SLOT(slot_colorChanged()));
  soundAction = new QAction("声音");
  if (MainWindow::count == 0)
    soundAction->setCheckable(false);
  connect(soundAction, SIGNAL(triggered(bool)), this,
          SLOT(slot_soundChanged()));

  heroAction = new QAction("英雄榜");
  connect(heroAction, SIGNAL(triggered(bool)), this, SLOT(slot_heroChecked()));

  exitAction = new QAction("退出");
  connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

  aboutAction = new QAction("关于");
  connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(slot_about()));
}

/*
函数功能：读当前游戏设置，并设置到场景的行，列，雷数，级别
 */
void MainWindow::readSettings() {
  auto settings = new QSettings("MineOrg", "MineClearance", this);

  // 1.获取数据: 行、列、雷数量
  settings->beginGroup("level"); // 难度
  auto row = settings->value("row", LOWROWANDCOL).toInt();
  auto col = settings->value("col", LOWROWANDCOL).toInt();
  auto mineNum = settings->value("mineNum", LOWMINENUM).toInt();
  auto level = settings->value("level", LOWLEVEL).toInt();
  settings->endGroup();

  // 2.更新数据
  mineScene->m_sceneRow = row;
  mineScene->m_sceneCol = col;
  mineScene->m_mineNum = mineNum;
  mineScene->m_currentLevel = level;
}

/*
函数功能：创建菜单
函数流程：
创建菜单栏及菜单
将相应行为加入菜单
 */
void MainWindow::create_menu() {
  auto menuBar = this->menuBar();
  auto gameMenu = menuBar->addMenu("游戏");
  gameMenu->addAction(newAction);
  gameMenu->addSeparator();
  gameMenu->addAction(lowLeveAction);
  gameMenu->addAction(middleLeveAction);
  gameMenu->addAction(highLeveAction);
  gameMenu->addAction(customAction);
  gameMenu->addSeparator();

  gameMenu->addAction(colorAction);
  gameMenu->addAction(soundAction);
  gameMenu->addSeparator();

  gameMenu->addAction(heroAction);
  gameMenu->addAction(exitAction);

  auto helpMenu = menuBar->addMenu("帮助");
  helpMenu->addAction(aboutAction);
}

/*
函数功能：写当前游戏设置，将当前场景的行，列，雷数，级别写入到注册表
 */
void MainWindow::writeSettings() {
  qDebug() << "writeSettings";
  qDebug() << "row = " << mineScene->m_sceneRow << "\t"
           << "col = " << mineScene->m_sceneCol << "\t"
           << "level = " << mineScene->m_currentLevel << "\t"
           << "mineNum = " << mineScene->m_mineNum;
  auto settings = new QSettings("MineOrg", "MineClearance", this);
  settings->beginGroup("level");
  settings->setValue("row", mineScene->m_sceneRow);
  settings->setValue("col", mineScene->m_sceneCol);
  settings->setValue("mineNum", mineScene->m_mineNum);
  settings->setValue("level", mineScene->m_currentLevel);
  settings->endGroup();
}

/*
函数功能：点击游戏级别行为开始新游戏槽
函数流程：
1) 如果是初级行为 设置场景的行，列，雷数，级别为初级
2) 如果是中级行为 设置场景的行，列，雷数，级别为中级，
3) 如果是高级行为 设置场景的行，列，雷数，级别为高级，
4) 如果是自定义行为
创建自定义游戏框对象，并运行，并将自定义对话框的发送数据信号连接到接受自定义游戏数据槽
5) 并写入到注册表，开始新游戏
 */
void MainWindow::slot_newGameByLevel(QAction *action) {
  qDebug() << "slot_newGameByLevel";
  if (action == lowLeveAction) {
    qDebug() << "lowLeveAction";
    mineScene->m_mineNum = LOWMINENUM;
    mineScene->m_sceneRow = LOWROWANDCOL;
    mineScene->m_sceneCol = LOWROWANDCOL;
    mineScene->m_currentLevel = LOWLEVEL;
  } else if (action == middleLeveAction) {
    qDebug() << "middleLeveAction";
    mineScene->m_mineNum = MIDDLEMINENUM;
    mineScene->m_sceneRow = MIDDLEROWANDCOL;
    mineScene->m_sceneCol = MIDDLEROWANDCOL;
    mineScene->m_currentLevel = MIDDLELEVEL;
  } else if (action == highLeveAction) {
    qDebug() << "highLeveAction";
    mineScene->m_mineNum = HIGHMINENUM;
    mineScene->m_sceneRow = HIGHROW;
    mineScene->m_sceneCol = HIGHCOL;
    mineScene->m_currentLevel = HIGHLEVEL;
  } else if (action == customAction) {
    qDebug() << "customAction";
    m_timer->stop();
    CustomGameDialog customGameDialog(this);
    connect(&customGameDialog, SIGNAL(signal_sendCustomSet(int, int, int)),
            this, SLOT(slot_acceptCustomVal(int, int, int)));
    customGameDialog.exec();
    m_timer->start(1000);
  }
  if (action != customAction) {
    writeSettings();
    slot_newGame();
  }
}

/*
函数功能：接收自定义游戏设置槽
函数流程：
将自定义数据设置到场景的行，列，雷数，级别，将数据写入到注册表的当前游戏设置中
开始新游戏
 */
void MainWindow::slot_acceptCustomVal(int row, int col, int mineNum) {
  qDebug() << "slot_acceptCustomVal";
  qDebug() << "row = " << row << "\t"
           << "col = " << col << "\t"
           << "mineNum = " << mineNum;
  mineScene->m_mineNum = mineNum;
  mineScene->m_sceneRow = row;
  mineScene->m_sceneCol = col;
  mineScene->m_currentLevel = CUSTOMLEVEL;
  writeSettings();
  slot_newGame();
}

void MainWindow::slot_colorChanged() { qDebug() << "slot_colorChanged"; }

/*
函数功能：设置声音的槽
函数流程：
如果声音行为可选，则将声音行为设置为不可选，未选中，关闭场景声音
否则将声音行为设置为可选，已选中，打开场景声音
 */
void MainWindow::slot_soundChanged() {
  qDebug() << "slot_soundChanged";
  if (soundAction->isCheckable()) {
    soundAction->setCheckable(false);
    soundAction->setChecked(false);
    mineScene->m_soundOpen = false;
  } else {
    soundAction->setCheckable(true);
    soundAction->setChecked(true);
    mineScene->m_soundOpen = true;
  }
  qDebug() << "m_soundOpen = " << mineScene->m_soundOpen;
}

/*
函数功能：显示英雄榜的槽
创建英雄榜对象，并显示
 */
void MainWindow::slot_heroChecked() {
  qDebug() << "slot_heroChecked";
  m_timer->stop();
  HeroDialog heroDialog(this);
  heroDialog.exec();
  m_timer->start(1000);
}

/*
函数功能：显示 about 扫雷的槽
使用消息框中的 about 函数创建消息框
 */
void MainWindow::slot_about() {
  qDebug() << "slot_about";
  QMessageBox::about(centralWidget, "about", "帮助");
}

/*
函数功能：更新英雄榜的槽，根据场景级别和游戏时间决定是否更新英雄榜
函数流程：
1.获取需获取和修改的键名
2.获取时间
3.超记录则写入注册表
4.获取输入名称
5.显示信息，游戏结束，是否继续，如果点继续则重新开始游戏，如果点取消则关闭游戏
 */
void MainWindow::slot_updateHero() {
  qDebug() << "slot_updateHero";
  // 1.获取需获取和修改的键名
  QString name_key, time_key;
  bool flag = true;
  if (mineScene->m_currentLevel == LOWLEVEL) {
    name_key = "low_name";
    time_key = "low_time";
  } else if (mineScene->m_currentLevel == MIDDLELEVEL) {
    name_key = "middle_name";
    time_key = "middle_time";
  } else if (mineScene->m_currentLevel == HIGHLEVEL) {
    name_key = "high_name";
    time_key = "high_time";
  }
  // 如果不是自定义游戏
  if (mineScene->m_currentLevel != CUSTOMLEVEL) {
    // 2.获取记录时间
    auto heroSettings = new QSettings("MineOrg", "MineClearance", this);
    heroSettings->beginGroup("hero");
    auto time = heroSettings->value(time_key, 999).toInt();
    // 3.超记录则写入注册表
    if (m_time < time) {
      // 4.获取输入名称
      bool ok;
      auto name = QInputDialog::getText(this, "输入名称", "名称",
                                        QLineEdit::Normal, "匿名", &ok);
      if (!ok || name.trimmed().isEmpty())
        name = "匿名";
      heroSettings->setValue(name_key, name);
      heroSettings->setValue(time_key, m_time);
    }
    heroSettings->endGroup();
  }
  // 5.显示信息，游戏结束，是否继续，如果点继续则重新开始游戏，如果点取消则关闭游戏
  QMessageBox msgBox(this);
  msgBox.setIconPixmap(QPixmap(":/images/cenWin0.png"));
  msgBox.setWindowTitle("游戏结束");
  msgBox.setText("游戏结束，是否继续");
  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  int continueBtn = msgBox.exec();
  if (continueBtn == QMessageBox::Ok)
    slot_newGame();
  else
    close();
}

/*
函数功能：显示雷数的槽，显示场景中剩余雷数＝雷总数-已标旗雷数
 */
void MainWindow::slot_displayMineNum(int mineNum) {
  qDebug() << "slot_displayMineNum";
  qDebug() << "mineNum = " << mineNum;
  mineNumLcd->display(mineScene->m_mineNum - mineNum);
}

/*
函数功能：显示时间的槽
函数流程：
如果游戏未结束
当前游戏用时加 1,并显示，如果场景为声音打开和声音行为被选中，则播放声音
如果游戏结束，则停止计时器
 */
void MainWindow::slot_displayTime() {
  // qDebug() << "slot_displayTime";
  if (!mineScene->m_isGameOver) {
    // 当前游戏用时加 1,并显示，如果场景为声音打开和声音行为被选中，则播放声音
    timeLcd->display(++m_time);
    if (mineScene->m_soundOpen && soundAction->isChecked()) {
      // qDebug() << "play time.wav"
      //          << "\tstatus : " << MainWindow::timeSound->status();
      MainWindow::timeSound->play();
    }
  } else {
    // 如果游戏结束，则停止计时器
    m_timer->stop();
  }
}

void MainWindow::initMusic() {
  MainWindow::timeSound->setSource(QUrl::fromLocalFile(timeSoundPath));
  MainWindow::timeSound->setLoopCount(2);
  MainWindow::winSound->setSource(QUrl::fromLocalFile(winSoundPath));
  MainWindow::winSound->setLoopCount(1);
  MainWindow::bongSound->setSource(QUrl::fromLocalFile(bongSoundPath));
  MainWindow::bongSound->setLoopCount(1);
}