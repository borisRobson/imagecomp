#ifndef COMPARISON_H
#define COMPARISON_H

#include <QObject>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <vector>
#include <string>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;


class comparison
{
public:
    comparison();
    bool loadimages(string refimage, string compimage);
    void compareimages();
    void drawthresh();
};

class Task: public QObject{
    Q_OBJECT
public:
    Task(QObject* parent=0) : QObject(parent){}
private:

public slots:
    void run();
signals:
    void finished();
};

#endif // COMPARISON_H
