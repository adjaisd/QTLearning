#include "SoundGui.h"

SoundGui::SoundGui(QWidget *parent) : QWidget(parent) {
  setWindowTitle("SoundGUI");
  auto play_button = new QPushButton("播放");
  auto stop_button = new QPushButton("停止");
  auto vLayout = new QVBoxLayout(this);
  vLayout->addWidget(play_button);
  vLayout->addWidget(stop_button);

  sound = new QSoundEffect(this);
  sound->setSource(QUrl::fromLocalFile(":/sounds/start2.wav"));
  connect(play_button, SIGNAL(clicked(bool)), this, SLOT(slot_play()));
  connect(stop_button, SIGNAL(clicked(bool)), this, SLOT(slot_stop()));
}

SoundGui::~SoundGui() noexcept = default;

void SoundGui::slot_play() { sound->play(); }

void SoundGui::slot_stop() { sound->stop(); }