#include "dialog.h"
#include "ui_dialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>

Dialog::Dialog(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Dialog)
{
    ui->setupUi(this);

    file_path = "C:/Users/louis.wang/Desktop/log.txt";
    read_file(file_path);
    ui->label->setText(file_path);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::read_file(QString file_path)
{
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qFatal("file can not open.");
    }
    else
    {
        QTextStream in(&file);
        QString read_in_data = in.readAll();
        qDebug() << "read in data = " << read_in_data;

        QStringList l1, l2; //for split usage
        l1 = read_in_data.split("|");
        row = l1.length()-1;
        foreach (QString str, l1)
        {
            l2 << str.split("/");
        }
        col = l2.length()/row;
        file.close();

        QStandardItemModel *model = new QStandardItemModel;
        int cnt = 0;
        for (int y = 0; y < row; y++)
        {
            for (int x = 0; x < col; x++)
            {
                model->setItem(y, x, new QStandardItem(l2.at(cnt++)));
            }
        }
        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);
    }
}

void Dialog::on_file_path_btn_clicked()
{
    //choose path for read write
    QString file_option_filter = "text files(*.txt);;xml files(*.xml);;all types (*.*);;";
    file_path = QFileDialog::getOpenFileName(this, "open a file", "./", file_option_filter);
    QMessageBox::information(this, "File Path", file_path);
    ui->label->setText(file_path);
}

void Dialog::on_read_data_btn_clicked()
{
    //read data from file
    read_file(file_path);
}

void Dialog::on_write_btn_clicked()
{
    QFile file(file_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qFatal("file can not open.");
    }
    else
    {
        QTextStream out(&file);

        int cnt = 1;
        qDebug() << row << " " << col;
        for (int x = 0; x < row; x++)
            for (int y = 0; y < col; y++)
            {
                QString str = ui->tableView->model()->data(ui->tableView->model()->index(x, y)).toString();
                if (cnt++ % col != 0)
                    out << str + "/";
                else
                    out << str + "|";
            }
        file.close();
    }
}
