#include <ctime>

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>


#include "MainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    std::srand(std::time(nullptr));

    // Загрузка стилей
    QFile styleFile(":/res/stylesheet/style.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    styleFile.close();

    app.setStyleSheet(style);

    // Проверка на предмет запуска нескольких программ
    QLockFile lockFile(QDir::temp().absoluteFilePath("<uniq id>.lock"));

    if(!lockFile.tryLock(100)){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QObject::tr("Программа уже запущена"));
        msgBox.exec();
        return 1;
    }

    MainWindow mainWindow;

    mainWindow.move(QApplication::desktop()->screen()->rect().center()
                    - mainWindow.frameGeometry().center());
    mainWindow.show();

    return app.exec();
}
