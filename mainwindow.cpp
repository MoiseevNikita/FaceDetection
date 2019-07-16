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

    images_to_process = images_processed = 0;
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
        ++images_to_process;
        updateProgressBar();

        ImageViewer* viewer = new ImageViewer(this, filename);
        ui->tabWidget->addTab(
            viewer,
            QFileInfo(filename).fileName()
        );
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    }
}

void MainWindow::onOneImageProcessingFinished()
{
    ++images_processed;
    updateProgressBar();
}

void MainWindow::updateProgressBar()
{
    if (images_processed != images_to_process) {
        ui->progressBar->setRange(0, images_to_process);
        ui->progressBar->setValue(images_processed);
        ui->progressBar->setFormat(QString("%v/%0").arg(images_to_process));
        ui->progressBar->show();
    } else {
        ui->progressBar->hide();
        images_to_process =images_processed = 0;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList filelist = QFileDialog::getOpenFileNames(this, "Choose a jpeg image", "", "Images (*.jpg *.jpeg)");
    foreach (QString filename, filelist) {
        processOneImage(filename);
    }
}

void MainWindow::on_actionDirectory_triggered()
{
    QString dirname = QFileDialog::getExistingDirectory(this, "Choose folder with jpeg images");
    if (QString::compare(dirname, QString()) != 0)
    {
        QDir dir(dirname);
        QFileInfoList filelist = dir.entryInfoList(QStringList{"*.jpg", "*.jpeg"});
        foreach (QFileInfo fileinfo, filelist) {
            processOneImage(fileinfo.absoluteFilePath());
        }
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

