#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSettings *_settings      ;
    QSettings *_settingsTap   ;
    QString    _path       ="";

private slots:
    void updateCaption();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
