#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

namespace VBEK {

class LoginForm : public QDialog {
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);

    QString getID() const;
    QString getPassword() const;

signals:
    void loginSuccessful(const QString &userId);
    void loginAttempt(const QString &userId, const QString &password);

private slots:
    void onSubmitButtonClicked();

private:
    void setupInterface();
    void setupConnections();
    QLineEdit *IDInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *submitButton;

    QString userID;
    QString userPassword;
};

}

#endif // LOGINFORM_H
