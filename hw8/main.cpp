#include <qapplication.h>
#include "twitdiag.h"
#include "twiteng.h"
#include "twitlogin.h"

int main(int argc, char *argv[])
{
  TwitEng* eng = new TwitEng();
  if(argc < 2)
  { std::cout << "Usage: ./hw8 [twitter.dat]\n"; exit(1);}
  if(eng->parse(argv[1]))
    exit(1);
  QApplication app(argc, argv);
  TwitLogin* tl = new  TwitLogin(eng);
  TwitDiag* td = new TwitDiag(eng);
  tl->setDiag(td);
  td->setLogin(tl);
  td->hide();
  tl->show();
  return app.exec();
  delete eng;
}
