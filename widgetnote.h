#ifndef WIDGETNOTE_H
#define WIDGETNOTE_H

#include <QString>

#include <QFont>

#include <QWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QHBoxLayout>

class WidgetNote : public QWidget
{
public:
    WidgetNote(QString note, QString pitch, QString octave, bool isSharp, bool isRepeat);
    ~WidgetNote();

private:
    QLabel* label_note;
    QLabel* label_pitch;
    QLabel* label_octave;
    QVBoxLayout* layout_main;
    QHBoxLayout* layout_pitch;
    QSpacerItem* spacer_top;
    QSpacerItem* spacer_bottom;
    QSpacerItem* spacer_L;
    QSpacerItem* spacer_R;
};

#endif // WIDGETNOTE_H
