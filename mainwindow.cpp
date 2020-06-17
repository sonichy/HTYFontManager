#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QDebug>
#include <QDesktopWidget>
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QPainter>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    formPreview = new FormPreview;
    connect(ui->action_quit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    move((QApplication::desktop()->width()-width())/2, (QApplication::desktop()->height()-height())/2);
    connect(ui->listWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(listWidgetClick(QModelIndex)));
    connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(preview(QModelIndex)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(refreshFonts()));
    connect(ui->checkBox_bold, SIGNAL(toggled(bool)), this, SLOT(refreshFonts()));
    connect(ui->checkBox_italic, SIGNAL(toggled(bool)), this, SLOT(refreshFonts()));
    refreshFonts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox MBHelp(QMessageBox::NoIcon,"关于","海天鹰字体管理器 1.1\n\nLinux 平台基于 Qt 的字体管理程序。\n作者：海天鹰\n邮箱：sonichy@163.com\n主页：https://github.com/sonichy");
    MBHelp.setWindowIcon(QIcon(":/icon.png"));
    MBHelp.setIconPixmap(QPixmap(":/icon.png"));
    MBHelp.exec();
}

void MainWindow::listWidgetClick(QModelIndex index)
{
    QString sfamily = index.data(Qt::DisplayRole).toString();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(sfamily);
}

void MainWindow::preview(QModelIndex index)
{
    QString sfamily = index.data(Qt::DisplayRole).toString();
    previewFont(sfamily);
}

void MainWindow::previewFont(QString sFamily)
{
    formPreview->setWindowTitle(sFamily);

    QLayoutItem *layoutItem;
    while ( ( layoutItem = formPreview->ui->verticalLayout->takeAt(0) ) != 0 ) {
        delete layoutItem->widget();
        delete layoutItem;
    }

    QString text;
    QFont font;
    font.setFamily(sFamily);
    font.setPointSize(40);

    QLabel *label;
    label = new QLabel;
    label->setText(sFamily);
    label->setFont(font);
    formPreview->ui->verticalLayout->addWidget(label);

    label = new QLabel;
    text = "abcdefghijklmnopqrstuvwxyz";
    font.setPointSize(30);
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

    for (int i=0; i<8; i++) {
        label = new QLabel;
        text = "深度系统是最好用的Linux系统！";
        label->setText(text);
        font.setPointSize(20+5*i);
        label->setFont(font);
        formPreview->ui->verticalLayout->addWidget(label);
    }

    formPreview->ui->verticalLayout->addStretch();
    formPreview->show();
}

void MainWindow::on_action_open_triggered()
{
    filename = QFileDialog::getOpenFileName(this, "打开字体", filename, "字体文件 (*.ttf *.otf *.ttc)");
    loadFont();
}

void MainWindow::loadFont()
{
    int fontId = QFontDatabase::addApplicationFont(filename);
    qDebug() << fontId;
    if(fontId != -1){
        QString sfamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        previewFont(sfamily);
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    qDebug() << e->mimeData()->formats();
    //if(e->mimeData()->hasFormat("text/uri-list")) //只能打开文本文件
        e->acceptProposedAction(); //可以在这个窗口部件上拖放对象
}

void MainWindow::dropEvent(QDropEvent *e) //释放对方时，执行的操作
{
    QList<QUrl> urls = e->mimeData()->urls();
    if(urls.isEmpty())
        return;

    QString fileName = urls.first().toLocalFile();

    foreach (QUrl u, urls) {
        qDebug() << u.toString();
    }
    qDebug() << urls.size();

    if(fileName.isEmpty())
        return;

    filename = fileName;
    loadFont();
}

void MainWindow::refreshFonts()
{
    ui->listWidget->clear();
    QFontDatabase database;
    foreach (const QString &family, database.families(QFontDatabase::Any)) {
        //qDebug() << family;
        QPixmap pixmap = QPixmap(128,128);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        QFont font;
        font.setPointSize(80);
        font.setFamily(family);
        font.setBold(ui->checkBox_bold->isChecked());
        font.setItalic(ui->checkBox_italic->isChecked());
        painter.setFont(font);
        painter.drawText(0, 100, ui->lineEdit->text());
        QListWidgetItem *LWI = new QListWidgetItem(QIcon(pixmap), family);
        LWI->setToolTip(family);
        LWI->setSizeHint(QSize(100,100));
        ui->listWidget->addItem(LWI);
    }
}