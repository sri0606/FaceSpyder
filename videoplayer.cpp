#include "pch.h"
#include "videoplayer.h"
#include <QCamera>
#include <QVBoxLayout>
#include <QTime>
#include <QToolTip>

VideoPlayer::VideoPlayer(const QString &source, QWidget *parent)
    : QWidget(parent), mediaPlayer(nullptr),positionSlider(nullptr), playPauseButton(nullptr), videoWidget(nullptr)
{
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(parent);

    // Assume it's a file path
    mediaPlayer->setSource(QUrl::fromLocalFile(source));
    mediaPlayer->setVideoOutput(videoWidget);

    // Play/Pause button
    playPauseButton = new QPushButton("Play", parent);
    playPauseButton->setStyleSheet("background-color: #4CAF50;border-radius: 4px;padding: 13px;");

    // Forward button
    forwardButton = new QPushButton("10sec>>>", parent);
    forwardButton->setStyleSheet("background-color: #008CBA;border-radius: 4px;padding: 10px;");

    // Backward button
    backwardButton = new QPushButton("<<<10sec", parent);
    backwardButton->setStyleSheet("background-color: #f44336;border-radius: 4px;padding: 10px;");

    positionSlider = new QSlider(Qt::Horizontal, parent);
    positionSlider->setRange(0, 100);
    positionSlider->setSingleStep(1);  // Set the single step for smoother dragging

    // Labels for start and end durations
    startLabel = new QLabel("0:00", parent);
    endLabel = new QLabel("0:00", parent);

    // Set up layout
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    QHBoxLayout *sliderLayout = new QHBoxLayout(parent);
    sliderLayout->addWidget(startLabel,1);
    sliderLayout->addWidget(positionSlider,25);
    sliderLayout->addWidget(endLabel,1);

    QHBoxLayout *timerLayout = new QHBoxLayout(parent);

    // Add empty space on the left side
    timerLayout->addStretch(3);

    // Add widgets with the specified ratios
    timerLayout->addWidget(backwardButton, 1);
    timerLayout->addWidget(playPauseButton, 1);
    timerLayout->addWidget(forwardButton, 1);

    // Add empty space on the right side
    timerLayout->addStretch(3);


    mainLayout->addWidget(videoWidget,18);
    mainLayout->addLayout(sliderLayout,1);
    mainLayout->addLayout(timerLayout,2);

    parent->setLayout(mainLayout);

    // Connect signals
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &VideoPlayer::mediaStatusChanged);
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::onDurationChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoPlayer::updatePositionSlider);
    connect(playPauseButton, &QPushButton::clicked, this, &VideoPlayer::playPauseClicked);
    connect(backwardButton, &QPushButton::clicked, this, &VideoPlayer::backwardVideo);
    connect(forwardButton, &QPushButton::clicked, this, &VideoPlayer::forwardVideo);
    connect(positionSlider, &QSlider::sliderMoved, this, &VideoPlayer::onSliderMoved);
    connect(positionSlider, &QSlider::sliderReleased, this, &VideoPlayer::onSliderReleased);
    connect(positionSlider, &QSlider::sliderPressed, this, &VideoPlayer::onSliderPressed);
}


VideoPlayer::~VideoPlayer()
{
    stop();
}


void VideoPlayer::onSliderPressed(){
    pause();
}

void VideoPlayer::onDurationChanged()
{
    qint64 duration = static_cast<qint64>(mediaPlayer->duration());
    QTime time = QTime::fromMSecsSinceStartOfDay(duration);
    endLabel->setText(time.toString("mm:ss"));
}

void VideoPlayer::backwardVideo()
{
    //10sec backward
    qint64 duration = static_cast<qint64>(mediaPlayer->duration());
    int value = static_cast<int>((positionSlider->value() * 100) / duration);
    int newPosition = static_cast<int>(((value-5000) / 100.0) * duration);
    updatePositionSlider(newPosition);
}

void VideoPlayer::forwardVideo()
{
    //10sec fowraward
    qint64 duration = static_cast<qint64>(mediaPlayer->duration());
    int value = static_cast<int>((positionSlider->value() * 100) / duration);
    int newPosition = static_cast<int>(((value+5000) / 100.0) * duration);
    updatePositionSlider(newPosition);
}

void VideoPlayer::play()
{
    if (mediaPlayer)
    {
        mediaPlayer->play();
        playPauseButton->setText("Pause");
    }
}

void VideoPlayer::pause()
{
    if (mediaPlayer)
    {
        mediaPlayer->pause();
        playPauseButton->setText("Play");
    }
}

void VideoPlayer::stop()
{
    if (mediaPlayer)
    {
        mediaPlayer->stop();
        playPauseButton->setText("Play");
        positionSlider->setValue(0);
    }
}

void VideoPlayer::mediaStatusChanged(QMediaPlayer::MediaStatus state)
{
    if (state == QMediaPlayer::StoppedState)
    {
        playPauseButton->setText("Play");
    }
}

// Slot to update the label based on the slider's position
void VideoPlayer::onSliderMoved(int value) {
    qint64 duration = mediaPlayer->duration();
    int newTime = static_cast<int>((value / 100.0) * duration);
    positionSlider->setValue(value);
    QTime time = QTime::fromMSecsSinceStartOfDay(newTime);
    startLabel->setText(time.toString("mm:ss"));
}

void VideoPlayer::updatePositionSlider(qint64 position)
{
    if (mediaPlayer)
    {
        qint64 duration = mediaPlayer->duration();
        if (duration > 0)
        {
            int value = static_cast<int>((position * 100) / duration);
            positionSlider->setValue(value);
            int newPosition = static_cast<int>((positionSlider->value() / 100.0) * duration);
            QTime time = QTime::fromMSecsSinceStartOfDay(newPosition);
            startLabel->setText(time.toString("mm:ss"));
        }
    }
}
void VideoPlayer::onSliderReleased()
{
    if (mediaPlayer)
    {
        int position = positionSlider->value();
        qint64 duration = mediaPlayer->duration();
        qint64 newPosition = static_cast<qint64>((position / 100.0) * duration);
        mediaPlayer->setPosition(newPosition);
        play();
    }
}


void VideoPlayer::playPauseClicked()
{
    if (mediaPlayer->isPlaying())
    {
        pause();
    }
    else
    {
        play();
    }
}
