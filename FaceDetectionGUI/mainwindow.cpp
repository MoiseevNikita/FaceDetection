#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageviewer.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QString>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->clear();

    setWindowTitle("Face Detection Application");

    imagesToProcess = imagesProcessed = 0;
    updateProgressBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processOneImage(QString filename)
{
    QImage image;
    bool valid = image.load(filename);
    if (valid)
    {
        ++imagesToProcess;
        updateProgressBar();

        ImageViewer* viewer = new ImageViewer(this, filename);
        connect(viewer, &ImageViewer::imageAnnotated, this, &MainWindow::onImageAnnotationFinished);
        ui->tabWidget->addTab(
            viewer,
            QFileInfo(filename).fileName()
        );
    }
}

void MainWindow::onImageAnnotationFinished()
{
    ++imagesProcessed;
    updateProgressBar();
}

void MainWindow::updateProgressBar()
{
    if (imagesProcessed != imagesToProcess) {
        ui->progressBar->setRange(0, imagesToProcess);
        ui->progressBar->setValue(imagesProcessed);
        ui->progressBar->setFormat(QString("%v/%0").arg(imagesToProcess));
        ui->progressBar->show();
    } else {
        ui->progressBar->hide();
        imagesToProcess =imagesProcessed = 0;
    }
}

void MainWindow::on_actionOpenFile_triggered()
{
    QStringList filelist = QFileDialog::getOpenFileNames(this, "Choose image(s)", "", "Images (*.bmp *.jpg *.jpeg)");
    foreach (QString filename, filelist) {
        processOneImage(filename);
    }
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}

void MainWindow::on_actionOpenDirectory_triggered()
{
    QString dirname = QFileDialog::getExistingDirectory(this, "Choose folder with images");
    if (QString::compare(dirname, QString()) != 0)
    {
        QDir dir(dirname);
        QFileInfoList filelist = dir.entryInfoList(QStringList{"*.bmp", "*.jpg", "*.jpeg"});
        foreach (QFileInfo fileinfo, filelist) {
            processOneImage(fileinfo.absoluteFilePath());
        }
    }
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

