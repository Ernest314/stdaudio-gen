#ifndef NOTE_H
#define NOTE_H

#include <QString>

class Note
{
public:
    enum Pitch { REST, A, B, C, D, E, F, G };

    Note( Pitch pitch_in,
          int octave_in,
          bool isSharp_in,
          bool isRepeat_in,
          double duration_in,
          int dots_in );

    QString notate();

    Pitch get_pitch()   { return pitch; }
    int get_octave()    { return octave; }
    bool get_isSharp()  { return isSharp; }
    bool get_isRepeat() { return isRepeat; }
    double get_duration() { return duration; }
    int get_dots()      { return dots; }

private:
    Pitch pitch;
    int octave;
    bool isSharp;
    bool isRepeat;
    double duration;
    int dots;
};

#endif // NOTE_H
