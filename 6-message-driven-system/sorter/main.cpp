#include "../reusable/protocol.h"

#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QLocalServer>
#include <QLocalSocket>
#include <QRegularExpression>
#include <QTableWidget>
#include <QVBoxLayout>
#include <algorithm>

class Object3Window : public QWidget {
  QTableWidget *table = new QTableWidget(this);
  QLocalServer server;
  QLocalSocket *client = nullptr;
  bool quitting = false;

  void reply(const QString &message) {
    if (client) {
      client->write(message.toUtf8() + '\n');
      client->flush();
    }
  }

  void sortClipboard() {
    const QStringList lines = QApplication::clipboard()->text().split(
        QRegularExpression("[\\r\\n]+"), Qt::SkipEmptyParts);
    QVector<double> values;
    values.reserve(lines.size());
    for (const QString &line : lines) {
      bool ok = false;
      const double value = line.trimmed().toDouble(&ok);
      if (!ok) {
        reply("ERROR clipboard contains invalid number");
        return;
      }
      values.append(value);
    }
    if (values.isEmpty()) {
      reply("ERROR clipboard is empty");
      return;
    }

    std::sort(values.begin(), values.end());
    table->setRowCount((values.size() + 3) / 4);
    table->clearContents();
    for (qsizetype index = 0; index < values.size(); ++index) {
      const QString text = QString::number(values[index], 'f', 2);
      table->setItem(index / 4, index % 4, new QTableWidgetItem(text));
    }
    reply("DONE");
  }

  void readCommands() {
    while (client && client->canReadLine()) {
      const QString line = QString::fromUtf8(client->readLine()).trimmed();
      if (line == "SORT")
        sortClipboard();
      else if (line == "QUIT") {
        quitting = true;
        reply("DONE");
        QApplication::quit();
      } else if (!line.isEmpty())
        reply("ERROR unknown command");
    }
  }

public:
  Object3Window() {
    setWindowTitle("Object3 - Сортування");
    resize(560, 300);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"1", "2", "3", "4"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table);

    QLocalServer::removeServer(Lab6Protocol::Object3Server);
    connect(&server, &QLocalServer::newConnection, this, [this] {
      if (client)
        client->disconnectFromServer();
      client = server.nextPendingConnection();
      connect(client, &QLocalSocket::readyRead, this,
              &Object3Window::readCommands);
      connect(client, &QLocalSocket::disconnected, this, [this] {
        client->deleteLater();
        client = nullptr;
        if (!quitting)
          QApplication::quit();
      });
    });
    server.listen(Lab6Protocol::Object3Server);
  }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Object3Window window;
  window.show();
  return app.exec();
}