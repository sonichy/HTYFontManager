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
    QString filename;
    void previewFont(QString sfamily);
    void loadFont();
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);

private slots:
    void on_action_open_triggered();
    void on_action_about_triggered();
    void listWidgetClick(QModelIndex index);
    void preview(QModelIndex index);
    void refreshFonts();

};

#endif // MAINWINDOW_H