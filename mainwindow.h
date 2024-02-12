#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_colorButton_clicked();
    void on_changeBackgroundButton_clicked();

    void on_pushButton_clicked();

    void on_loadImageButton_clicked();

private:
    Ui::MainWindow *ui;
    QColor selectedColor;
    Mat originalImage;
    Mat result;
    Mat roi;
};

#endif // MAINWINDOW_H
