#include "MainWindow.h"
#include <QApplication>
#include <QSoundEffect>
#include <QtConcurrent/QtConcurrent>
#include <unistd.h>

QSoundEffect *MainWindow::timeSound = new QSoundEffect;
QSoundEffect *MainWindow::winSound = new QSoundEffect;
QSoundEffect *MainWindow::bongSound = new QSoundEffect;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
#define choice 4
#if choice == 1 // 测试CustomGameDialog
#include "CustomGameDialog.h"
  CustomGameDialog customGameDialog;
  customGameDialog.show();
#elif choice == 2 // 测试HeroDialog
#include "HeroDialog.h"
  HeroDialog heroDialog;
  heroDialog.show();
#elif choice == 3 // 测试声音
#include "common.h"
  // initMusic
  auto timeSound = new QSoundEffect;
  auto winSound = new QSoundEffect;
  auto bongSound = new QSoundEffect;
  timeSound->setSource(QUrl::fromLocalFile(timeSoundPath));
  timeSound->setLoopCount(2);
  winSound->setSource(QUrl::fromLocalFile(winSoundPath));
  winSound->setLoopCount(1);
  bongSound->setSource(QUrl::fromLocalFile(bongSoundPath));
  bongSound->setLoopCount(1);

  QtConcurrent::run([=]() {
    timeSound->play();
    qDebug() << "is playing 1"
             << "\t" << timeSound->status() << "\t"
             << timeSound->loopsRemaining();
    sleep(2);
  }).then([=]() {
    timeSound->stop();
    timeSound->play();
    qDebug() << "is playing 2"
             << "\t" << timeSound->status() << "\t"
             << timeSound->loopsRemaining();
  });
  qDebug() << "outer";
//  timeSound->play();
//  winSound->play();
//  bongSound->play();
#elif choice == 4 // 测试主程序
  // initMusic
  MainWindow::initMusic();
  // main
  MainWindow mainWindow(nullptr);
  mainWindow.show();
#endif
  return a.exec();
}