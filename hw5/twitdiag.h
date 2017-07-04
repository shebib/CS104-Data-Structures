#ifndef TWITDIAG_H
#define TWITDIAG_H

#include <qlistwidget.h>
#include <qradiobutton.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qdialog.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qstackedwidget.h>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtextedit.h>

#include <algorithm>
#include <sstream>

#include "twiteng.h"

class TwitDiag : public QDialog
{
  Q_OBJECT

  public:
    TwitDiag(TwitEng* eng);

  public slots:
    void selectUser(const QString& name);
    void followUser(int i);
    void searchTweets();
    void searchResults();
    void sendTweet();
    void saveFile();
    void searchDiagQuit();

  private:
    //Functions
    void createUserSelect();
    void createFollowing();
    void createSearch();
    void createSearchDiag();
    void createUserColumn();
    void createFeedColumn();
    void createDMFeedColumn();
    void createAddTweet();
    void createControls();

    void getNames();
    void updateFeed();
    void updateDMFeed();
    void updateFollowButtons();

    //variables
    TwitEng* eng;
    std::vector<std::string> names;
    std::string currUser;
    
    QGroupBox* userSelectGroupbox;
    QGroupBox* followingGroupbox;
    QGroupBox* searchGroupbox;
    QGroupBox* userColumnGroupbox;
    QGroupBox* feedColumnGroupbox;
    QGroupBox* dmFeedColumnGroupbox;
    QGroupBox* topUserGroupbox;
    QGroupBox* addTweetGroupbox;
    QGroupBox* controlsGroupbox;

    QComboBox* usrComboBox;
    QStackedWidget** followButtonStack;
    QButtonGroup* followButtonGroup;
    QPushButton* searchButton;
    
    QDialog* searchDiag;
    QRadioButton* andSearchRadioButton;
    QRadioButton* orSearchRadioButton;
    QLineEdit* searchLineText;
    QPushButton* searchDiagSearchButton;
    QPushButton* searchDiagQuitButton;
    QListWidget* searchText;

    QTextEdit* feedColumnText;
    QTextEdit* dmFeedColumnText;

    QTextEdit* addTweetText;
    QPushButton* addTweetButton;

    QPushButton* saveButton;
    QPushButton* quitButton;
};

#endif
