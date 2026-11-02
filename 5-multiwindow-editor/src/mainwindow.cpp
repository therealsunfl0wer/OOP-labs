#include "mainwindow.h"
#include "canvaswidget.h"
#include "shape.h"
#include "shapefactory.h"
#include "shapefile.h"
#include <QActionGroup>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QSvgRenderer>
#include <QToolBar>
#include <QVBoxLayout>

// This helper does not handle dynamic theme switching,
// so it only picks the color for icons when the program has started
const QIcon tintedIcon(const QString &svgPath, const QColor &color,
                       QSize size = QSize(24, 24)) {
  QPixmap pixmap(size);
  pixmap.fill(Qt::transparent);

  QSvgRenderer renderer(svgPath);
  QPainter painter(&pixmap);
  renderer.render(&painter);

  painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
  painter.fillRect(pixmap.rect(), color);
  painter.end();

  return QIcon(pixmap);
}

static void showErrorMessage(QWidget *parent, const ShapeFile::Result &result) {
  QMessageBox::warning(parent, "Помилка", result.errorMessage,
                       QMessageBox::StandardButton::Ok);
}

void MainWindow::newFile() {
  // TODO: Unsaved changes warning
  currentFilePath.clear();
  ShapeFile::create();
}
void MainWindow::openFile() {
  QFileDialog dialog(this, "Оберіть малюнок");
  dialog.setFileMode(QFileDialog::ExistingFile);
  dialog.setMimeTypeFilters({"text/csv", "application/octet-stream"});
  if (dialog.exec() != QDialog::Accepted)
    return;
  currentFilePath = dialog.selectedFiles().first();

  ShapeFile::Result r = ShapeFile::load(currentFilePath);
  if (!r.ok)
    showErrorMessage(this, r);
  currentFilePath.clear();
}
void MainWindow::saveFile() {
  if (currentFilePath.isEmpty()) {
    saveFile("Зберегти малюнок");
    return;
  }
  ShapeFile::Result r = ShapeFile::save(currentFilePath);
  if (!r.ok)
    showErrorMessage(this, r);
  currentFilePath.clear();
}
void MainWindow::saveFile(const QString &windowTitle) {
  QFileDialog dialog(this, windowTitle);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setMimeTypeFilters({"text/csv", "application/octet-stream"});
  dialog.setDefaultSuffix("csv");
  if (dialog.exec() != QDialog::Accepted)
    return;
  currentFilePath = dialog.selectedFiles().first();
  saveFile();
}
void MainWindow::saveFileAs() { saveFile("Зберегти малюнок як"); }

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setMinimumSize(640, 480);

  const QColor iconColor = palette().color(QPalette::WindowText);
  static const ShapeFactory &factory = ShapeFactory::instance();

  CanvasWidget *canvas = new CanvasWidget(this);
  setCentralWidget(canvas);

  QMenu *fileMenu = menuBar()->addMenu("Файл");
  fileMenu->addAction("Створити", QKeySequence::New, this,
                      &MainWindow::newFile);
  fileMenu->addAction("Відкрити", QKeySequence::Open, this,
                      &MainWindow::openFile);
  fileMenu->addAction(
      "Зберегти", QKeySequence::Save, this,
      qOverload<>(&MainWindow::saveFile)); // Qt has a fancy const_cast<>
  fileMenu->addAction("Зберегти як", QKeySequence::SaveAs, this,
                      &MainWindow::saveFileAs);
  fileMenu->addAction("Вихід", QKeySequence::Quit, this, &QWidget::close);

  QMenu *helpMenu = menuBar()->addMenu("Довідка");
  helpMenu->addAction("Про програму", QKeySequence::WhatsThis, this, [this]() {
    QMessageBox::about(this, "Про програму",
                       "Лабораторна робота №5, варіант 10");
  });

  QToolBar *toolBar = addToolBar("Об'єкти");
  QActionGroup *toolBarActionGroup = new QActionGroup(toolBar);
  toolBarActionGroup->setExclusive(true);

  for (const ShapeEntry &entry : factory.registry()) {

    QAction *action =
        toolBar->addAction(tintedIcon(entry.iconPath, iconColor), entry.name,
                           [this, canvas, entry]() {
                             canvas->selectShape(entry.id);
                             setWindowTitle("Вибрано об'єкт: " + entry.name);
                           });
    toolBarActionGroup->addAction(action);
  }

  if (!toolBarActionGroup->actions().isEmpty())
    toolBarActionGroup->actions().first()->trigger();

  adjustSize();
}
