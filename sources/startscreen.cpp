#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(std::shared_ptr<Database> dbPtr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    if(dbPtr)
        m_dbPtr = dbPtr;
    else
        m_dbPtr = shared_ptr<Database>(new Database());//    make_shared<Database>();

    ui->loginWidget->setDatabase(dbPtr);
    ui->registerWidget->setDatabase(dbPtr);

    connect(ui->loginWidget, &LoginForm::registerRequested, this, &StartScreen::setRegistrationForm);
    connect(ui->loginWidget, &LoginForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->loginWidget, &LoginForm::rejected, this, &StartScreen::onRejectRequested);
    connect(ui->registerWidget, &RegistrationForm::loginRequested, this, &StartScreen::setLoginForm);
    connect(ui->registerWidget, &RegistrationForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->registerWidget, &RegistrationForm::rejected, this, &StartScreen::onRejectRequested);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::setLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::setRegistrationForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartScreen::onLoggedIn(int userID, QString userName)
{
    m_userID = userID;
    m_userName = userName;
    accept();
}

void StartScreen::onRejectRequested()
{
    reject();
}

const QString &StartScreen::userName() const
{
    return m_userName;
}

int StartScreen::userID() const
{
    return m_userID;
}
