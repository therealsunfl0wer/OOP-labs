#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editor.h"
#include <QCloseEvent>
#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT
  static const inline QString WINDOW_TITLE = "ЛР №5 В10";
  static const inline QString HELP_TITLE = "Лабораторна робота №5, варіант 10";

  Editor &editor = *Editor::instance();
  int savedRevision = 0;

  QString currentFilePath;
  void setCurrentPath(const QString &path);
  bool maybeSave();
  void newFile();
  void openFile();
  bool saveFile();
  bool saveFile(const QString &title);
  void saveFileAs();

public:
  MainWindow(QWidget *parent = nullptr);

protected:
  void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
