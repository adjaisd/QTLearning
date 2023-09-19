#include "common.h"

void playMusic(const QString &path) {
  auto sound = QSoundEffect();
  sound.setSource(QUrl::fromLocalFile(path));
  sound.play();
}