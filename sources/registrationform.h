#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include <memory.h>

#include "Database.h"

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

    void setDatabase(const std::shared_ptr<Database> &newDbPtr);

signals:
    void loginRequested();
    void accepted(int userID, QString userName);
    void rejected();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_loginPushButton_clicked();

private:
    Ui::RegistrationForm *ui;
    std::shared_ptr<Database> m_dbPtr{nullptr};
};

#endif // REGISTRATIONFORM_H
