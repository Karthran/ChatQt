#include "registrationform.h"
#include "ui_registrationform.h"
#include <QMessageBox>

RegistrationForm::RegistrationForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::RegistrationForm) {
  ui->setupUi(this);
}

RegistrationForm::~RegistrationForm() { delete ui; }

void RegistrationForm::on_buttonBox_accepted() {
  if (ui->passwordEdit->text() != ui->passwordConfirmEdit->text()) {
    QMessageBox::critical(this, tr("Error"), tr("Password not match"));
    return;
  }

  auto userID = m_dbPtr->addUser(ui->loginEdit->text().toStdString(),
                                 ui->passwordEdit->text().toStdString());

  switch (userID) {
  case -1:
    QMessageBox::critical(this, tr("Error"), tr("Incorrect login"));
    return;

  case -2:
      QMessageBox::critical(this, tr("Error"), tr("Login alredy exists"));
      return;

  default:
      emit accepted(userID, ui->loginEdit->text());
  }

}

void RegistrationForm::on_buttonBox_rejected() { emit rejected(); }

void RegistrationForm::on_loginPushButton_clicked() { emit loginRequested(); }

void RegistrationForm::setDatabase(const std::shared_ptr<Database> &newDbPtr) {
  m_dbPtr = newDbPtr;
}
