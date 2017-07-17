#include "twitlogin.h"

TwitLogin::TwitLogin(TwitEng* eng) : QDialog()
{
  this->eng = eng;
  //create pieces
  createButtons();

  QVBoxLayout* layout = new QVBoxLayout();
  nameText = new QLineEdit(tr("Username"));
  passwordText = new QLineEdit(tr("Password (8 char max)"));
  infoLabel = new QLabel();
  layout->addWidget(nameText);
  layout->addWidget(passwordText);
  layout->addWidget(infoLabel);
  layout->addWidget(buttonGroupbox);
  setLayout(layout);

  //connect everything
  connect(loginButton, SIGNAL(released()), this, SLOT(login()));
  connect(registerButton, SIGNAL(released()), this, SLOT(registerUser()));
  connect(quitButton, SIGNAL(released()), this, SLOT(close()));

  setWindowTitle(tr("Twitter Login"));
}

TwitLogin::~TwitLogin() {}

void TwitLogin::setDiag(TwitDiag* diag)
{
  this->diag = diag;
}

void TwitLogin::createButtons()
{
  buttonGroupbox = new QGroupBox();
  buttonGroupbox->setFlat(true);
  QHBoxLayout* layout = new QHBoxLayout();
  loginButton = new QPushButton(tr("Login"));
  registerButton = new QPushButton(tr("Register"));
  quitButton = new QPushButton(tr("Quit"));
  layout->addWidget(loginButton);
  layout->addWidget(registerButton);
  layout->addWidget(quitButton);
  buttonGroupbox->setLayout(layout);
}

void TwitLogin::login()
{
  std::string name = nameText->text().toStdString();
  std::string password = passwordText->text().toStdString();
  if(eng->login(name, password))
    openDiag(name);
  else
    infoLabel->setText("Error: Invalid login info");
}
    
void TwitLogin::registerUser()
{
  std::string name = nameText->text().toStdString();
  std::string password = passwordText->text().toStdString();
  if(eng->registerUser(name, password))
  {
    //Have to recreate layout for new user
    delete diag;
    diag = new TwitDiag(eng);
    diag->setLogin(this);
    openDiag(name);
  }
  else
    infoLabel->setText("Error: Username already exists");
}

void TwitLogin::openDiag(std::string name)
{
  diag->setUser(name);
  diag->show();
  this->hide();
}






