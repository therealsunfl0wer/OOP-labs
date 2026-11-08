#include "mainwindow.h"
#include "canvaswidget.h"
#include "editor.h"
#include "shape.h"
#include "shapefactory.h"
#include "shapefile.h"
#include "tablewindow.h"
#include <QActionGroup>
#include <QDockWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QMenuBar>
#include <QMessageBox>
#include <QSvgRenderer>
#include <QToolBar>

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

void MainWindow::setCurrentPath(const QString &path) {
  currentFilePath = path;
  setWindowTitle(QFileInfo(path).fileName() + " — " + WINDOW_TITLE);
}

bool MainWindow::maybeSave() {
  if (editor.revision() == savedRevision)
    return true;

  const QMessageBox::StandardButton answer = QMessageBox::question(
      this, "Зберегти зміни?", "Малюнок має незбережені зміни.",
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
      QMessageBox::Save);

  switch (answer) {
  case QMessageBox::Save:
    return saveFile();
  case QMessageBox::Discard:
    return true;
  case QMessageBox::Cancel:
  default:
    return false;
  }
}

void MainWindow::newFile() {
  if (!maybeSave())
    return;

  const ShapeFile::Result result = ShapeFile::create();
  if (!result.ok)
    return;
  savedRevision = editor.revision();
  currentFilePath.clear();
  setWindowTitle(WINDOW_TITLE);
}

void MainWindow::openFile() {
  if (!maybeSave())
    return;

  QFileDialog dialog(this, "Оберіть малюнок");
  dialog.setFileMode(QFileDialog::ExistingFile);
  dialog.setMimeTypeFilters({"text/csv", "application/octet-stream"});

  if (dialog.exec() != QDialog::Accepted) {
    return;
  }

  const QString path = dialog.selectedFiles().first();
  ShapeFile::Result r = ShapeFile::load(path);
  if (!r.ok) {
    showErrorMessage(this, r);
    return;
  }

  setCurrentPath(path);
  savedRevision = editor.revision();
}

bool MainWindow::saveFile() {
  if (currentFilePath.isEmpty()) {
    return saveFile("Зберегти малюнок");
  }

  ShapeFile::Result r = ShapeFile::save(currentFilePath);

  if (!r.ok) {
    showErrorMessage(this, r);
    return false;
  }
  savedRevision = editor.revision();
  return true;
}

bool MainWindow::saveFile(const QString &windowTitle) {
  QFileDialog dialog(this, windowTitle);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setMimeTypeFilters({"text/csv", "application/octet-stream"});
  dialog.setDefaultSuffix("csv");

  if (dialog.exec() != QDialog::Accepted)
    return false;

  const QString path = dialog.selectedFiles().first();
  const ShapeFile::Result result = ShapeFile::save(path);
  if (!result.ok) {
    showErrorMessage(this, result);
    return false;
  }
  setCurrentPath(path);
  savedRevision = editor.revision();
  return true;
}

void MainWindow::saveFileAs() { saveFile("Зберегти малюнок як"); }

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle(WINDOW_TITLE);
  setMinimumSize(640, 480);

  const QColor iconColor = palette().color(QPalette::WindowText);
  static const ShapeFactory &factory = ShapeFactory::instance();

  CanvasWidget *canvas = new CanvasWidget(this);
  setCentralWidget(canvas);

  TableWindow *table = new TableWindow(this);
  QDockWidget *dock = new QDockWidget("Таблиця", this);
  dock->setWidget(table);
  addDockWidget(Qt::RightDockWidgetArea, dock);
  dock->setFloating(true);
  dock->hide();

  editor.subscribe([this, table] {
    QList<TableRow> rows;
    for (int i = 0; i < editor.entries(); i++) {
      ShapeParams p = editor.getShape(i)->getParams();
      TableRow r = {p.id, p.x1, p.y1, p.x2, p.y2};
      rows.append(r);
    }
    table->setRows(rows);
  });
  connect(table, &TableWindow::rowSelected, this,
          [this](int row) { editor.select(row); });
  connect(table, &TableWindow::rowDeleteRequested, this,
          [this](int row) { editor.removeAt(row); });

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

  QMenu *viewMenu = menuBar()->addMenu("Вигляд");
  QAction *tableAction = dock->toggleViewAction();
  tableAction->setShortcut(QKeySequence("Ctrl+T"));
  viewMenu->addAction(tableAction);

  QMenu *helpMenu = menuBar()->addMenu("Довідка");
  helpMenu->addAction("Про програму", QKeySequence::WhatsThis, this, [this]() {
    QMessageBox::about(this, "Про програму", HELP_TITLE);
  });

  QToolBar *toolBar = addToolBar("Об'єкти");
  QActionGroup *toolBarActionGroup = new QActionGroup(toolBar);
  toolBarActionGroup->setExclusive(true);

  for (const ShapeEntry &entry : factory.registry()) {

    QAction *action = toolBar->addAction(tintedIcon(entry.iconPath, iconColor),
                                         entry.name, [this, canvas, entry]() {
                                           canvas->selectShape(entry.id);
                                           // setWindowTitle("Вибрано об'єкт: "
                                           // + entry.name);
                                         });
    toolBarActionGroup->addAction(action);
    action->setCheckable(true);
  }

  if (!toolBarActionGroup->actions().isEmpty())
    toolBarActionGroup->actions().first()->trigger();

  adjustSize();
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (maybeSave())
    event->accept();
  else
    event->ignore();
}
