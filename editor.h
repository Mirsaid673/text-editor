#pragma once

#include <QtWidgets>

class Editor : public QMainWindow
{
    Q_OBJECT

private:
    QPlainTextEdit *text_editor;
    QString current_file;

    void initMenus();

    bool save();
    bool saveAs();
    void open();

    void loadFile(const QString& file);
    bool saveFile(const QString& file);

    void setCurrentFile(const QString& file);

public:
    Editor(QWidget *parent = nullptr);
};