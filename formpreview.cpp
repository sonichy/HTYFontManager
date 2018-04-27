#include "formpreview.h"
#include "ui_formpreview.h"

FormPreview::FormPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPreview)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
}

FormPreview::~FormPreview()
{
    delete ui;
}
