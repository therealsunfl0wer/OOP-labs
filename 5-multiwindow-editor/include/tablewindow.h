#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

struct TableRow {
  QString type;
  int x1, y1, x2, y2;
};

class TableWindow : public QWidget {
  Q_OBJECT

  QStandardItemModel *model = new QStandardItemModel(0, 5, this);
  QTableView *view = new QTableView(this);

public:
  TableWindow(QWidget *parent = nullptr);

  void setRows(const QList<TableRow> &);

signals:
void rowSelected(int row);
void rowDeleteRequested(int row);
};

#endif // TABLEWINDOW_H