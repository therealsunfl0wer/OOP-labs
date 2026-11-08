#include "tablewindow.h"
#include <QVBoxLayout>

void TableWindow::setRows(const QList<TableRow> &rows) {
  int selected = view->currentIndex().row();
  model->setRowCount(0);

  for (const TableRow &row : rows) {
    model->appendRow({new QStandardItem(row.type),
                      new QStandardItem(QString::number(row.x1)),
                      new QStandardItem(QString::number(row.y1)),
                      new QStandardItem(QString::number(row.x2)),
                      new QStandardItem(QString::number(row.y2))});
  }

  if (selected >= 0 && selected < rows.size())
    view->selectRow(selected);
}

TableWindow::TableWindow(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);

  model->setHorizontalHeaderLabels({"Тип", "x1", "y1", "x2", "y2"});
  view->setEditTriggers(QAbstractItemView::NoEditTriggers);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
  view->setModel(model);

  connect(view->selectionModel(), &QItemSelectionModel::currentRowChanged, this,
          [this](const QModelIndex &current) {
            if (current.isValid())
              emit rowSelected(current.row());
          });

  QAction *deleteAction = new QAction("Видалити", this);
  deleteAction->setShortcut(QKeySequence::Delete);
  deleteAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
  view->addAction(deleteAction);
  view->setContextMenuPolicy(Qt::ActionsContextMenu);

  connect(deleteAction, &QAction::triggered, this, [this] {
    const QModelIndex i = view->currentIndex();
    if (i.isValid())
      emit rowDeleteRequested(i.row());
  });

  layout->addWidget(view);
}