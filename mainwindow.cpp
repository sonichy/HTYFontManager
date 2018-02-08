#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QDebug>
#include <QDesktopWidget>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
    QFontDatabase database;
    foreach (const QString &family, database.families(QFontDatabase::Any)) {
        //qDebug() << family;
        QListWidgetItem *LWI = new QListWidgetItem(QIcon(":/icon.svg"), family);
        LWI->setToolTip(family);
        LWI->setSizeHint(QSize(100,100));
        ui->listWidget->addItem(LWI);
    }
    connect(ui->listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(preview(QModelIndex)));
    formPreview = new FormPreview;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::preview(QModelIndex modelIndex)
{
    QLayoutItem *layoutItem;
    while ( ( layoutItem = formPreview->ui->verticalLayout->takeAt(0) ) != 0 ) {
        delete layoutItem->widget();
        delete layoutItem;
    }

    QString sfamily = modelIndex.data(Qt::DisplayRole).toString();
    formPreview->setWindowTitle(sfamily);
    QString text;

    QFont font;
    font.setFamily(sfamily);
    font.setPixelSize(30);

    QLabel *label;
    label = new QLabel;
    text = "abcdefghijklmnopqrstuvwxyz";
    label->setText(text);
    label->setFont(font);
    formPreview->ui->verticalLayout->addWidget(label);

    label = new QLabel;
    text = "ABCDEFGHIJKLMNOPQRSTUVWXZY";
    label->setText(text);
    label->setFont(font);
    formPreview->ui->verticalLayout->addWidget(label);

    label = new QLabel;
    text = "0123456789.:,;(*!?')";
    label->setText(text);
    label->setFont(font);
    formPreview->ui->verticalLayout->addWidget(label);

    for(int i=0; i<10; i++){
        label = new QLabel;
        text = "深度系统是最好用的Linux系统！";
        label->setText(text);
        font.setPixelSize(10+10*i);
        label->setFont(font);
        formPreview->ui->verticalLayout->addWidget(label);
    }

    formPreview->ui->verticalLayout->addStretch();
    formPreview->show();
}
