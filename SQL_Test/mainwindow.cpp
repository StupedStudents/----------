#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QMessageBox>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTableWidget* table = new QTableWidget();
        table->setWindowTitle("Connect to Mysql Database Example");

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("menudb");
        db.setUserName("root");
        db.setPassword("root");
        if (!db.open())
        {
          QMessageBox::critical(0, QObject::tr("Database Error"),
                    db.lastError().text());
        }

        QSqlQuery query("SELECT * FROM test");
        table->setColumnCount(query.record().count());
        table->setRowCount(query.size());

        int index=0;
        while (query.next())
        {
        table->setItem(index,0,new QTableWidgetItem(query.value(0).toString()));
        table->setItem(index,1,new QTableWidgetItem(query.value(1).toString()));
        index++;
        }

        table->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
