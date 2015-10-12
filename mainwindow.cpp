#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect( ui->pushButton_save,  &QPushButton::clicked,
                      this,                 &MainWindow::saveNotes );
    QObject::connect( ui->pushButton_backspace, &QPushButton::clicked,
                      this,                     &MainWindow::deleteNote );
    QObject::connect( ui->pushButton_clear, &QPushButton::clicked,
                      this,                 &MainWindow::clearNotes );

    QList<QFrame*> octave_frames =
            ui->scrollArea_piano->findChildren<QFrame*>
            (QRegularExpression("^frame_octave_[1-7]$"));
    for (int i=0; i<octave_frames.size(); ++i) {
        QList<QPushButton*> piano_keys =
                octave_frames[i]->findChildren<QPushButton*>();
        for (int j=0; j<piano_keys.size(); ++j) {
            piano_keys[j]->setStyle(QStyleFactory::create("Fusion"));
            QObject::connect( piano_keys[j],    &QPushButton::clicked,
                              this,             &MainWindow::processNote );
        }
        QList<QPushButton*> white_keys =
                octave_frames[i]->findChildren<QPushButton*>
                (QRegularExpression("^pushButton_[A-G][1-7]$"));
        for (int j=0; j<white_keys.size(); ++j) {
            white_keys[j]->setStyleSheet("background-color: ivory;");
        }
        QList<QPushButton*> black_keys =
                octave_frames[i]->findChildren<QPushButton*>
                (QRegularExpression("^pushButton_[A-G][1-7]s$"));
        for (int j=0; j<black_keys.size(); ++j) {
            black_keys[j]->setStyleSheet("background-color: darkGray;");
        }
    }
    QScrollBar* piano_bar = ui->scrollArea_piano->horizontalScrollBar();
    piano_bar->setValue(static_cast<double>(piano_bar->maximum()) / 2.0);

    QObject::connect( ui->pushButton_rest,  &QPushButton::clicked,
                      this,                 &MainWindow::addRest );
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::addRest() {
    // `octave` and `isSharp` aren't written to file
    addNote(Note::REST, 1, false);
}

void MainWindow::addNote(Note::Pitch pitch, int octave, bool isSharp) {
    bool isRepeat = ui->pushButton_repeat->isChecked();
    int dots = 0;
    if (ui->pushButton_dot->isChecked()) {
        dots = 1;
    }
    if (ui->pushButton_dotdot->isChecked()) {
        dots = 2;
    }
    Note new_note(pitch, octave, isSharp, isRepeat, getDuration(), dots);
    if (ui->pushButton_repeat->isChecked()) {
        ui->pushButton_repeat->click();
        // TODO: or should ^this be set programmatically?
    }
    notes.push_back(new_note);
    updateDisplay();
    qDebug() << "Note added:\t" << new_note.notate();
}

void MainWindow::updateDisplay() {
    int size_widgets_original = display_widgets.size();
    for (int i=0; i<size_widgets_original; ++i) {
        ui->layout_display->removeWidget(display_widgets[i]);
        delete display_widgets[i];
    }
    display_widgets.clear();

    double duration_counter = 0.0;
    int display_size = notes.size();
    for (int i_note=0, i_barline=0; i_note+i_barline<display_size; ++i_note) {
        double duration = notes[i_note].get_duration();
        duration /= 60.0 / static_cast<double>(ui->spinBox_tempo->value());
        duration_counter += duration;
        QString note_str;
        if (duration <= 1.75/8.0) {
            note_str = "\U0001D158\U0001D165\U0001D170";
        } else if (duration <= 1.75/4.0) {
            note_str = "\U0001D158\U0001D165\U0001D16F";
        } else if (duration <= 1.75/2.0) {
            note_str = "\U0001D158\U0001D165\U0001D16E";
        } else if (duration <= 1.75) {
            note_str = "\U0001D15F";
        } else if (duration <= 1.75*2.0) {
            note_str = "\U0001D15E";
        } else {
            note_str = "\U0001D15D";
        }
        if (notes[i_note].get_pitch() == Note::REST) {
            if (duration <= 1.75/8.0) {
                note_str = "\U0001D140";
            } else if (duration <= 1.75/4.0) {
                note_str = "\U0001D13F";
            } else if (duration <= 1.75/2.0) {
                note_str = "\U0001D13E";
            } else if (duration <= 1.75) {
                note_str = "\U0001D13D";
            } else if (duration <= 1.75*2.0) {
                note_str = "\U0001D13C";
            } else {
                note_str = "\U0001D13B";
            }
        }
        for (int j=0; j<notes[i_note].get_dots(); ++j) {
            note_str += "\U0001D16D";
        }
        QString pitch_str;
        switch(notes[i_note].get_pitch()) {
            case Note::A : pitch_str = "A"; break;
            case Note::B : pitch_str = "B"; break;
            case Note::C : pitch_str = "C"; break;
            case Note::D : pitch_str = "D"; break;
            case Note::E : pitch_str = "E"; break;
            case Note::F : pitch_str = "F"; break;
            case Note::G : pitch_str = "G"; break;
            case Note::REST : pitch_str = " "; break;
        }
        QString octave_str = QString::number(notes[i_note].get_octave());

        WidgetNote* new_note =
                new WidgetNote( note_str,
                                pitch_str,
                                octave_str,
                                notes[i_note].get_isSharp(),
                                notes[i_note].get_isRepeat() );
        display_widgets.push_back(new_note);
        ui->layout_display->insertWidget(i_note+i_barline, new_note);
        if (ui->comboBox_timeSig->currentText().toInt() - duration_counter < 2.0 / 3.0 / 16.0) {
            i_barline++; display_size++;
            WidgetBarline* barline = new WidgetBarline();
            display_widgets.push_back(barline);
            ui->layout_display->insertWidget(i_note+i_barline, barline);
            duration_counter = 0.0;
        }
    }
    QScrollBar* display_scrollBar = ui->scrollArea_display->horizontalScrollBar();
    display_scrollBar->setValue(display_scrollBar->maximum());
}

void MainWindow::processNote() {
    QPushButton* sender = qobject_cast<QPushButton*>(QObject::sender());
    QString sender_name_qstring = sender->objectName();
    sender_name_qstring.remove("pushButton_");
    Note::Pitch pitch = Note::REST;
    std::string sender_name = sender_name_qstring.toStdString();
    switch(sender_name.c_str()[0]) {
        case 'A' : pitch = Note::A; break;
        case 'B' : pitch = Note::B; break;
        case 'C' : pitch = Note::C; break;
        case 'D' : pitch = Note::D; break;
        case 'E' : pitch = Note::E; break;
        case 'F' : pitch = Note::F; break;
        case 'G' : pitch = Note::G; break;
    }
    int octave = QString(sender_name.c_str()[1]).toInt();
    bool isSharp = (sender_name.size() == 3);
    addNote(pitch, octave, isSharp);
}

void MainWindow::saveNotes() {
    QString save_file = QFileDialog::getSaveFileName(this);
    QFile* saver = new QFile(save_file);
    saver->open(QIODevice::WriteOnly);
    QTextStream streamer(saver);
    for (unsigned int i=0; i<notes.size(); ++i) {
        streamer << notes[i].notate() << "\n";
    }
    streamer.flush();
    saver->close();
}

void MainWindow::deleteNote() {
    if(notes.size() > 0) {
        notes.pop_back();
        updateDisplay();
    }
}

void MainWindow::clearNotes() {
    notes.clear();
    updateDisplay();
}

double MainWindow::getDuration() {
    double tempo_multiplier = 1.0;
    double tempo_quarter =
            60.0 / static_cast<double>(ui->spinBox_tempo->value());
    if (ui->pushButton_thirtysecond->isChecked()) {
        tempo_multiplier = 1.0 / 8.0;
    } else if (ui->pushButton_sixteenth->isChecked()) {
        tempo_multiplier = 1.0 / 4.0;
    } else if (ui->pushButton_eighth->isChecked()) {
        tempo_multiplier = 1.0 / 2.0;
    } else if (ui->pushButton_quarter->isChecked()) {
        tempo_multiplier = 1.0;
    } else if (ui->pushButton_half->isChecked()) {
        tempo_multiplier = 2.0;
    } else if (ui->pushButton_whole->isChecked()) {
        tempo_multiplier = 4.0;
    }
    double duration = tempo_quarter * tempo_multiplier;
    if (ui->pushButton_dot->isChecked()) {
        duration *= 1.5;
        ui->pushButton_dot->click();
        // TODO: or should ^this be set programmatically?

    } else if (ui->pushButton_dotdot->isChecked()) {
        duration *= 1.75;
        ui->pushButton_dotdot->click();
        // TODO: or should ^this be set programmatically?
    }
    if (ui->pushButton_triplet->isChecked()) {
        duration *= 2.0 / 3.0;
    }
    return duration;
}
