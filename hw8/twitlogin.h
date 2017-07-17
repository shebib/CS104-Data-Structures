
#ifndef TWITLOGIN_H
#define TWITLOGIN_H

#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qstring.h>
#include <qlineedit.h>
#include <qlabel.h>

#include <sstream>

#include "twiteng.h"
#include "twitdiag.h"

class TwitLogin : public QDialog
{
  Q_OBJECT

  public:
    TwitLogin(TwitEng* eng);
    ~TwitLogin();
    void setDiag(TwitDiag* diag);

  public slots:
    void login();
    void registerUser();

 
  private:
    //functions
    void createButtons();
    void openDiag(std::string name);

    //variables
    TwitEng* eng;
    TwitDiag* diag;

    QGroupBox* buttonGroupbox;
    QGroupBox* mainGroupbox;

    QPushButton* loginButton;
    QPushButton* registerButton;
    QPushButton* quitButton;

    QLineEdit* nameText;
    QLineEdit* passwordText;

    QLabel* infoLabel;
};

#endif
