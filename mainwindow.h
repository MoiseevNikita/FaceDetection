#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class ImageViewer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionDirectory_triggered();
    void on_tabWidget_tabCloseRequested(int index);

private:
    void processOneImage(QString filename);
    void onOneImageProcessingFinished();
    void updateProgressBar();

    Ui::MainWindow *ui;
    int images_to_process, images_processed;

    friend class ImageViewer;
};

#endif // MAINWINDOW_H
