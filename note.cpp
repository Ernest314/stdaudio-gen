#include "note.h"

Note::Note( Pitch pitch_in,
            int octave_in,
            bool isSharp_in,
            bool isRepeat_in,
            double duration_in,
            int dots_in ) :
    pitch(pitch_in),
    octave(octave_in),
    isSharp(isSharp_in),
    isRepeat(isRepeat_in),
    duration(duration_in),
    dots(dots_in)
{ }

QString Note::notate() {
    QString output = QString::number(duration, 'f', 6);
    output += " ";
    switch (pitch) {
        case A : output += "A"; break;
        case B : output += "B"; break;
        case C : output += "C"; break;
        case D : output += "D"; break;
        case E : output += "E"; break;
        case F : output += "F"; break;
        case G : output += "G"; break;
        case REST : output += "R"; break;
    }
    if (pitch == REST) {
        output += "           ";
    } else {
        output += " ";
        output += QString::number(octave);
        output += " ";
        output += isSharp ? "SHARP  " : "NATURAL";
        output += " ";
    }
    output += isRepeat ? "true" : "false" ;

    return output;
}
