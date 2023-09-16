#ifndef SOUNDGUI_H
#define SOUNDGUI_H

#include <QPushButton>
#include <QSoundEffect>
#include <QVBoxLayout>
#include <QWidget>

class SoundGui : public QWidget {
  Q_OBJECT
public:
  explicit SoundGui(QWidget *parent = nullptr);
  ~SoundGui() noexcept override;

public slots:
  void slot_play();
  void slot_stop();

private:
  QSoundEffect *sound;
};

#endif // SOUNDGUI_H