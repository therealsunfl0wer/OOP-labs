#include "../reusable/protocol.h"

#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QLocalServer>
#include <QLocalSocket>
#include <QRandomGenerator>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

class Object2Window : public QWidget {
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

  void generate(const QStringList &arguments) {
    if (arguments.size() != 3) {
      reply("ERROR expected: GENERATE n Min Max");
      return;
    }
    bool nOk = false;
    bool minOk = false;
    bool maxOk = false;
    const int count = arguments[0].toInt(&nOk);
    const double minimum = arguments[1].toDouble(&minOk);
    const double maximum = arguments[2].toDouble(&maxOk);
    if (!nOk || !minOk || !maxOk || count <= 0 || minimum > maximum) {
      reply("ERROR invalid generation parameters");
      return;
    }

    QStringList values;
    table->setRowCount((count + 3) / 4);
    table->clearContents();
    for (int index = 0; index < count; ++index) {
      const double value = minimum +
                           QRandomGenerator::global()->generateDouble() *
                               (maximum - minimum);
      const QString text = QString::number(value, 'f', 2);
      values.append(text);
      table->setItem(index / 4, index % 4, new QTableWidgetItem(text));
    }
    QApplication::clipboard()->setText(values.join('\n'));
    reply("DONE");
  }

  void readCommands() {
    while (client && client->canReadLine()) {
      const QString line = QString::fromUtf8(client->readLine()).trimmed();
      const QStringList parts = line.split(' ', Qt::SkipEmptyParts);
      if (parts.isEmpty())
        continue;
      if (parts.first() == "GENERATE")
        generate(parts.mid(1));
      else if (parts.first() == "QUIT") {
        quitting = true;
        reply("DONE");
        QApplication::quit();
      } else
        reply("ERROR unknown command");
    }
  }

public:
  Object2Window() {
    setWindowTitle("Object2 - Генератор");
    resize(560, 300);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"1", "2", "3", "4"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(table);

    QLocalServer::removeServer(Lab6Protocol::Object2Server);
    connect(&server, &QLocalServer::newConnection, this, [this] {
      if (client)
        client->disconnectFromServer();
      client = server.nextPendingConnection();
      connect(client, &QLocalSocket::readyRead, this,
              &Object2Window::readCommands);
      connect(client, &QLocalSocket::disconnected, this, [this] {
        client->deleteLater();
        client = nullptr;
        if (!quitting)
          QApplication::quit();
      });
    });
    server.listen(Lab6Protocol::Object2Server);
  }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Object2Window window;
  window.show();
  return app.exec();
}