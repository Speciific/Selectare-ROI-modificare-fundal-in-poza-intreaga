#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_colorButton_clicked() {
    selectedColor = QColorDialog::getColor(selectedColor, this);
    ui->changeBackgroundButton->setEnabled(true);
}

void MainWindow::on_loadImageButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Selecteaza imagine", "", "Imagini (*.png *.jpg *.jpeg *.bmp *.gif)");
    if (!filePath.isEmpty())
    {
        QImage qImage(filePath);
        ui->originalLabel->setPixmap(QPixmap::fromImage(qImage));
        ui->originalLabel->setScaledContents(true);
        originalImage = imread(filePath.toStdString());
    }
}


void MainWindow::on_changeBackgroundButton_clicked() {

    Mat image = originalImage;
    cvtColor(image, image, COLOR_BGR2RGB);

    Mat grayscaleImage;
    cvtColor(image, grayscaleImage, cv::COLOR_BGR2GRAY);

    Mat thresholded;
    cv::threshold(grayscaleImage, thresholded, 205, 255, cv::THRESH_BINARY);

    Mat newBackground(image.size(), image.type(), cv::Scalar(selectedColor.red(), selectedColor.green(), selectedColor.blue()));
    result = image.clone();
    image.copyTo(result, ~thresholded);
    newBackground.copyTo(result, thresholded);

    QImage resImg = QImage((uchar*) result.data, result.cols, result.rows, result.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(resImg);

    ui->resultLabel->setPixmap(pixmap);
    ui->resultLabel->setScaledContents(true);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->changeBackgroundButton->setEnabled(false);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Rect roiRect = selectROI("Select ROI", result);

    roi = result(roiRect);

    Mat newBackground(result.size(), result.type(), cv::Scalar(selectedColor.red(), selectedColor.green(), selectedColor.blue()));

    Rect roi2(roiRect.x, roiRect.y, roi.cols, roi.rows);

    addWeighted(newBackground(roi2), 0.1, roi(Rect(0, 0, roi.cols, roi.rows)), 1.0, 0.0, newBackground(roi2));

    QImage resImg = QImage((uchar*) newBackground.data, newBackground.cols, newBackground.rows, newBackground.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(resImg);

    ui->resultLabel->setPixmap(pixmap);
    ui->resultLabel->setScaledContents(true);

}

