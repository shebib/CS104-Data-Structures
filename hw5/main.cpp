#include <qapplication.h>
#include "twitdiag.h"
#include "twiteng.h"

int main(int argc, char *argv[])
{
  TwitEng* eng = new TwitEng();
  if(argc < 2)
  { std::cout << "Usage: ./hw5 [twitter.dat]\n"; exit(1);}
  if(eng->parse(argv[1]))
    exit(1);
  QApplication app(argc, argv);
  TwitDiag td(eng);
  td.show();
  return app.exec();
}
