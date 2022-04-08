#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <memory>
#include "Database.h"

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(std::shared_ptr<Database> dbPtr = nullptr, QWidget *parent = nullptr);
    ~StartScreen();

    void setLoginForm();
    void setRegistrationForm();
    int userID() const;

    const QString &userName() const;

public slots:
    void onLoggedIn(int userID, QString userName);
    void onRejectRequested();

private:
    Ui::StartScreen *ui;
    int m_userID;
    QString m_userName;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // STARTSCREEN_H
