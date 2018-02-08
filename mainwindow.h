#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "formpreview.h"
#include "ui_formpreview.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FormPreview *formPreview;

private slots:
    void preview(QModelIndex modelIndex);

};

#endif // MAINWINDOW_H
