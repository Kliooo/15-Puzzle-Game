#include "loginform.h"

VBEK::LoginForm::LoginForm(QWidget *parent)
    : QDialog(parent)
{
    setupInterface();
    setupConnections();
}

void VBEK::LoginForm::setupInterface()
{
    setWindowTitle("Login Form");
    resize(300, 120);
    setMinimumSize(150, 100);

    IDInput = new QLineEdit(this);
    IDInput->setPlaceholderText("Enter your ID");
    IDInput->setMaxLength(20);

    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setPlaceholderText("Enter your password");
    passwordInput->setMaxLength(20);

    submitButton = new QPushButton("Submit", this);
    submitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    submitButton->setStyleSheet("background-color: green; color: white; border-radius: 8px;");

    QVBoxLayout *formLayout = new QVBoxLayout;
    formLayout->addWidget(IDInput);
    formLayout->addWidget(passwordInput);
    formLayout->addWidget(submitButton);

    setLayout(formLayout);
}

void VBEK::LoginForm::setupConnections()
{
    connect(IDInput, &QLineEdit::returnPressed, [this]() { passwordInput->setFocus(); });
    connect(passwordInput, &QLineEdit::returnPressed, this, &VBEK::LoginForm::onSubmitButtonClicked);
    connect(submitButton, &QPushButton::clicked, this, &VBEK::LoginForm::onSubmitButtonClicked);
}

void VBEK::LoginForm::onSubmitButtonClicked()
{
    QString enteredID = IDInput->text();
    QString enteredPassword = passwordInput->text();

    if (enteredID.isEmpty() || enteredPassword.isEmpty()) {
        return;
    }

    userID = enteredID;
    userPassword = enteredPassword;

    emit loginAttempt(userID, userPassword);
    accept();
}

QString VBEK::LoginForm::getID() const {
    return userID;
}

QString VBEK::LoginForm::getPassword() const {
    return userPassword;
}
