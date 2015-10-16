#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <string>

#include <QObject>
#include <QList>
#include <QString>

#include <QTextStream>
#include <QFile>
#include <QDebug>

#include <QRegularExpression>

#include <QFontDatabase>
#include <QStyleFactory>

#include <QScrollBar>
#include <QFrame>
#include <QWidget>
#include <QPushButton>

#include <QMainWindow>
#include <QFileDialog>

#include "note.h"

#include "widgetbarline.h"
#include "widgetnote.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addRest();
    void processNote();

    void deleteNote();
    void clearNotes();
    void saveNotes();

private:
    Ui::MainWindow *ui;
    std::vector<Note> notes;
    std::vector<QWidget*> display_widgets;

    double getDuration();
    void addNote(Note::Pitch pitch, int octave, bool isSharp);
    void updateDisplay();
};

#endif // MAINWINDOW_H
