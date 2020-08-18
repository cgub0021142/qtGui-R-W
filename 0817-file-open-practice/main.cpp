#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QFile file("C:\\Qt\\qtcreator-2.0.1\\GUI\\MyActions\\ModViewTest\\0817-file-open-practice\\1.2.3.4.5.6.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open file failed.";
        return -1;
    } else {
        while (!file.atEnd()) {
            qDebug() << file.readLine();
        }
    }

//    QFileInfo info(file);
//    qDebug() << info.isDir();
//    qDebug() << info.isExecutable();
//    qDebug() << info.baseName();
//    qDebug() << info.completeBaseName();
//    qDebug() << info.suffix();
//    qDebug() << info.completeSuffix();

    return app.exec();
}
