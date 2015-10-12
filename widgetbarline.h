#ifndef WIDGETBARLINE_H
#define WIDGETBARLINE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class WidgetBarline : public QWidget
{
public:
    WidgetBarline();
    ~WidgetBarline();

private:
    QLabel* label;
    QVBoxLayout* layout;
};

#endif // WIDGETBARLINE_H
