#ifndef GUITARTUNER_H
#define GUITARTUNER_H

#include <QDialog>
#include <QAudioInput>
#include <QByteArray>
#include <QComboBox>
#include <QMainWindow>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

class AudioInfo : public QIODevice
{
    Q_OBJECT

public:
    AudioInfo(const QAudioFormat &format, QObject *parent);
    ~AudioInfo();

    void start();
    void stop();

    qreal level() const { return m_level; }

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    const QAudioFormat m_format;
    quint32 m_maxAmplitude;
    qreal m_level; // 0.0 <= m_level <= 1.0

signals:
    void update();
};


class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);

    void setLevel(qreal value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    qreal m_level;
    QPixmap m_pixmap;
};

namespace Ui {
class GuitarTuner;
}

class GuitarTuner : public QDialog
{
    Q_OBJECT

public:
    explicit GuitarTuner(QWidget *parent = 0);
    ~GuitarTuner();

private:
    void initializeWindow();
    void initializeAudio();
    void createAudioInput();

private slots:
    void refreshDisplay();
    void refreshDisplay2();
    void readMore();
    void sliderChanged(int value);

private:
    // Owned by layout
    RenderArea *m_canvas;
    QSlider *m_volumeSlider;
    QLineEdit * m_display;

    QAudioDeviceInfo m_device;
    AudioInfo *m_audioInfo;
    QAudioFormat m_format;
    QAudioInput *m_audioInput;
    QIODevice *m_input;
    bool m_pullMode;
    QByteArray m_buffer;

private:
    Ui::GuitarTuner *ui;
};






#endif // GUITARTUNER_H
