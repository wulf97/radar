#include <ctime>

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>

#include "MainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    std::srand(std::time(nullptr));

    MainWindow mainWindow;

    QFile styleFile(":/res/stylesheet/style.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    styleFile.close();

    app.setStyleSheet(style);

    mainWindow.move(QApplication::desktop()->screen()->rect().center()
                    - mainWindow.frameGeometry().center());
    mainWindow.show();

    return app.exec();
}
