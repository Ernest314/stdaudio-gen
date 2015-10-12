#include "widgetbarline.h"

WidgetBarline::WidgetBarline() :
    label(new QLabel("|")),
    layout(new QVBoxLayout())
{
    this->setLayout(layout);
    layout->addWidget(label);

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setMinimumSize(30, 150);
    this->setMaximumSize(30, 150);

    layout->setSpacing(0);

    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: lightGray; font-size: 96pt;");
    label->setMaximumHeight(80);
}


WidgetBarline::~WidgetBarline() {
    //delete layout;
    //delete label;
}
