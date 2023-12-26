#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QSlider>
#include <QVideoWidget>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(const QString &source, QWidget *parent = nullptr);
    ~VideoPlayer();
    void play();
    void pause();
    void stop();
public slots:


private slots:
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onSliderMoved(int value);
    void playPauseClicked();
    void updatePositionSlider(qint64 position);
    void onSliderReleased();
    void onDurationChanged();
    void backwardVideo();
    void forwardVideo();
    void onSliderPressed();

private:
    QMediaPlayer *mediaPlayer;
    QSlider *positionSlider;
    QVideoWidget *videoWidget;
    QPushButton *playPauseButton;
    QPushButton *forwardButton;
    QPushButton *backwardButton;
    // Labels for start and end durations
    QLabel* startLabel;
    QLabel* endLabel;
};

#endif // VIDEOPLAYER_H
