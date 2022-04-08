#include "mainwindow.h"
#include "startscreen.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<Database> dbPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(dbPtr)
        m_dbPtr = dbPtr;
    else
        m_dbPtr = std::make_shared<Database>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::createClient(std::shared_ptr<Database> dbPtr)
{
    StartScreen s(dbPtr);
    auto result = s.exec();
    if(result == QDialog::Rejected) return nullptr;

    return new MainWindow(dbPtr);
}


void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}


void MainWindow::on_sendMessageButton_clicked()
{

}


void MainWindow::on_privateMessageSendButton_clicked()
{

}


void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient(m_dbPtr);
    w->show();
}


void MainWindow::on_actionClose_this_client_triggered()
{

}

