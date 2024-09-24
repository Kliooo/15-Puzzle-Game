#ifndef LOGINFORM_HPP
#define LOGINFORM_HPP

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

namespace bva {

class LoginForm : public QDialog {
    Q_OBJECT


private:
	QPushButton *loginButton;
	QPushButton *submitButton;

	QLineEdit *IDInput;
	QLineEdit *passwordInput;

	QString userID;
	QString userPassword;

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
};

}

#endif
