// Lab 1 - Dev environment & modular C++ project setup
//
// Original assignment target: MS Visual Studio + Win32 API message-driven
// window app. Qt equivalent below: a minimal QApplication + QMainWindow,
// which hides the raw WndProc/message-loop plumbing behind Qt's event loop
// while still being a legitimate "message driven application".
//

#include <QApplication>
#include <QLabel>
#include <QMainWindow>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QMainWindow window;
  window.setWindowTitle("Lab 1 — Modular Qt Project Setup");
  window.setCentralWidget(new QLabel("Hello, Windows message loop (via Qt)!"));
  window.resize(480, 320);
  window.show();

  return app.exec();
}
