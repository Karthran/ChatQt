#include "mainwindow.h"
#include "startscreen.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
int MainWindow::kInstanceCount = 0;

MainWindow::MainWindow(int userID, QString userName, std::shared_ptr<Database> dbPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
  m_userID(userID),
  m_userName(userName)
{
    ++kInstanceCount;

    ui->setupUi(this);

    if(dbPtr)
        m_dbPtr = dbPtr;
    else
        m_dbPtr = std::make_shared<Database>();
}

MainWindow::~MainWindow()
{
    delete ui;
    --kInstanceCount;
    if(kInstanceCount <= 0) qApp->exit();
}

MainWindow *MainWindow::createClient(std::shared_ptr<Database> dbPtr)
{
    dbPtr = std::make_shared<Database>();
    StartScreen s(dbPtr);
    auto result = s.exec();
    if(result == QDialog::Rejected) return nullptr;

    auto w = new MainWindow(s.userID(), s.userName(), dbPtr);
    w->setAttribute(Qt::WA_DeleteOnClose);
    return w;
}


void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}


void MainWindow::on_sendMessageButton_clicked()
{
    m_dbPtr->addChatMessage(m_userName.toStdString(), ui->messageLineEdit->text().toStdString());
}


void MainWindow::on_privateMessageSendButton_clicked()
{
    QDialog dial(this);
    dial.setModal(true);

    auto l = new QVBoxLayout();
    dial.setLayout(l);
    auto userListWdg = new QListWidget(&dial);
    l->addWidget(userListWdg);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dial);
    l->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dial, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dial, &QDialog::reject);

    auto userList = m_dbPtr->getUserList();

    for(auto user : userList)
        userListWdg->addItem(QString::fromStdString(user));

    userListWdg->setCurrentRow(0);

    auto result = dial.exec();
    if(result == QDialog::Accepted && userListWdg->currentItem())
    {
        m_dbPtr->addPrivateMessage(m_userName.toStdString(), userListWdg->currentItem()->text().toStdString(), ui->messageLineEdit->text().toStdString());
    }
}


void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient(m_dbPtr);
    if(w) w->show();
}


void MainWindow::on_actionClose_this_client_triggered()
{

}

