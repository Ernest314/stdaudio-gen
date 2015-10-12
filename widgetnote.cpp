#include "widgetnote.h"

WidgetNote::WidgetNote(QString note, QString pitch, QString octave, bool isSharp, bool isRepeat) :
    label_note(new QLabel(note)),
    label_pitch(new QLabel()),
    label_octave(new QLabel(octave)),
    layout_main(new QVBoxLayout()),
    layout_pitch(new QHBoxLayout()),
    spacer_top(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding)),
    spacer_bottom(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding)),
    spacer_L(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed)),
    spacer_R(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed))
{
    this->setLayout(layout_main);
    layout_main->addSpacerItem(spacer_top);
    layout_main->addWidget(label_note);
    layout_main->addLayout(layout_pitch);
    layout_main->addSpacerItem(spacer_bottom);
    layout_pitch->addSpacerItem(spacer_L);
    layout_pitch->addWidget(label_pitch);
    layout_pitch->addWidget(label_octave);
    layout_pitch->addSpacerItem(spacer_R);

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setMinimumSize(160, 240);
    this->setMaximumSize(160, 240);

    layout_main->setSpacing(0);

    label_note->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    label_note->setMaximumHeight(80);
    label_note->setFont(QFont("FreeSerif", 60));
    if (isRepeat) {
        label_note->setStyleSheet("color: darkGreen;");
    }
    label_note->setAlignment(Qt::AlignCenter);

    label_pitch->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    label_pitch->setMinimumHeight(60);
    label_pitch->setFont(QFont("FreeSerif", 36, QFont::Bold));
    label_pitch->setAlignment(Qt::AlignCenter);
    QString pitch_text = pitch;
    if (isSharp) {
        pitch_text = "\u266F" + pitch;
    }
    label_pitch->setText(pitch_text);

    label_octave->setFont(QFont("FreeSerif", 24, QFont::Bold));
    label_octave->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
}

WidgetNote::~WidgetNote()
{
//    delete layout_main;
//    delete layout_pitch;
//    delete spacer_L;
//    delete spacer_R;
//    delete spacer_bottom;
//    delete spacer_top;
//    delete label_octave;
//    delete label_pitch;
//    delete label_note;
}
