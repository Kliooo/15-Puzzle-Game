#include "loginform.hpp"

bva::LoginForm::LoginForm(QWidget *parent)
    : QDialog(parent)
{
    setupInterface();
    setupConnections();
}

void bva::LoginForm::setupInterface()
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

void bva::LoginForm::setupConnections()
{
    connect(IDInput, &QLineEdit::returnPressed, [this]() { passwordInput->setFocus(); });
    connect(passwordInput, &QLineEdit::returnPressed, this, &bva::LoginForm::onSubmitButtonClicked);
    connect(submitButton, &QPushButton::clicked, this, &bva::LoginForm::onSubmitButtonClicked);
}

void bva::LoginForm::onSubmitButtonClicked()
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

QString bva::LoginForm::getID() const { return userID; }

QString bva::LoginForm::getPassword() const { return userPassword; }
