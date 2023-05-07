#include "editor.h"

#include <QMenu>

Editor::Editor(QWidget *parent) : text_editor(new QPlainTextEdit)
{
    initMenus();
    setCentralWidget(text_editor);
    setMinimumSize(400, 320);
    setCurrentFile("");
}

void Editor::initMenus()
{
    QAction *save = new QAction(tr("Save"));
    QAction *save_as = new QAction(tr("Save as"));
    QAction *open = new QAction(tr("Open"));

    connect(save, &QAction::triggered, this, &Editor::save);
    connect(save_as, &QAction::triggered, this, &Editor::saveAs);
    connect(open, &QAction::triggered, this, &Editor::open);

    QMenu *file_menu = menuBar()->addMenu(tr("&File"));
    file_menu->addAction(save);
    file_menu->addAction(save_as);
    file_menu->addAction(open);
}

bool Editor::save()
{
    if (current_file.isEmpty())
        return saveAs();
    else
        return saveFile(current_file);
}

bool Editor::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

void Editor::open()
{
    //if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    //}
}

void Editor::loadFile(const QString &file_name)
{
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(file_name), file.errorString()));
        return;
    }
    QTextStream in(&file);

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    text_editor->setPlainText(in.readAll());
    QGuiApplication::restoreOverrideCursor();

    setCurrentFile(file_name);
}

bool Editor::saveFile(const QString &file_name)
{
    QString error_message;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(file_name);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&file);
        out << text_editor->toPlainText();
        if (!file.commit())
        {
            error_message = tr("Cannot write file %1:\n%2.")
                                .arg(QDir::toNativeSeparators(file_name), file.errorString());
        }
    }
    else
    {
        error_message = tr("Cannot open file %1 for writing:\n%2.")
                            .arg(QDir::toNativeSeparators(file_name), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!error_message.isEmpty())
    {
        QMessageBox::warning(this, tr("Application"), error_message);
        return false;
    }

    setCurrentFile(file_name);
    return true;
}

void Editor::setCurrentFile(const QString &file)
{
    current_file = file;
    text_editor->document()->setModified(false);
    setWindowModified(false);

    QString shown_mame = current_file;
    if (current_file.isEmpty())
        shown_mame = "untitled.txt";
    setWindowFilePath(shown_mame);
    setWindowTitle(shown_mame);
}