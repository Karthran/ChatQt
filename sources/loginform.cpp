#include "loginform.h"
#include "ui_loginform.h"
#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) : QWidget(parent), ui(new Ui::LoginForm) {
  ui->setupUi(this);
}

LoginForm::~LoginForm() { delete ui; }

void LoginForm::on_buttonBox_accepted() {
  auto userID = m_dbPtr->checkPassword(ui->loginEdit->text().toStdString(),
                                       ui->passwordEdit->text().toStdString());
  if (userID == -1){
    QMessageBox::critical(this, tr("Error"), tr("Password is wrong"));
    return;
  }
  emit accepted(userID, ui->loginEdit->text());
}

void LoginForm::on_buttonBox_rejected() { emit rejected(); }

void LoginForm::on_registrationPushButton_clicked() {
  emit registerRequested();
}

void LoginForm::setDatabase(const std::shared_ptr<Database> &newDbPtr) {
  m_dbPtr = newDbPtr;
}
