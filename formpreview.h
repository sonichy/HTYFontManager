#ifndef FORMPREVIEW_H
#define FORMPREVIEW_H

#include <QWidget>

namespace Ui {
class FormPreview;
}

class FormPreview : public QWidget
{
    Q_OBJECT

public:
    explicit FormPreview(QWidget *parent = 0);
    ~FormPreview();

public:
    Ui::FormPreview *ui;

};

#endif // FORMPREVIEW_H
