#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT

  QString currentFilePath;
  void newFile();
  void openFile();
  void saveFile();
  void saveFile(const QString &title);
  void saveFileAs();

public:
  MainWindow(QWidget *parent = nullptr);
};

#endif // MAINWINDOW_H
