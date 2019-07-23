#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onImageAnnotationFinished();

private slots:
    void on_actionOpenFile_triggered();
    void on_actionOpenDirectory_triggered();
    void on_tabWidget_tabCloseRequested(int index);

private:
    void processOneImage(QString filename);
    void updateProgressBar();

    Ui::MainWindow *ui;
    unsigned imagesToProcess, imagesProcessed;
};

#endif // MAINWINDOW_H
