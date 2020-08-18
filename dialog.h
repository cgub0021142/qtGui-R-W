#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int row;
    int col;
    QString file_path;
    QStandardItemModel *model;
    QString data;
    void read_file(QString);
private slots:
    void on_write_btn_clicked();
    void on_read_data_btn_clicked();
    void on_file_path_btn_clicked();
};

#endif // DIALOG_H
