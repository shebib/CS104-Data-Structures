#include "twitdiag.h"

TwitDiag::TwitDiag(TwitEng* eng) : QDialog()
{
  this->eng = eng;
  //create pieces
  getNames();
  currUser = names[0];
  createUserSelect();
  createFollowing();
  updateFollowButtons();
  createSearch();
  createSearchDiag();
  createUserColumn();
  createFeedColumn();
  updateFeed();
  createTrending();
  refreshTrending();
  createDMFeedColumn();
  updateDMFeed();

  topUserGroupbox = new QGroupBox();
  topUserGroupbox->setFlat(true);
  QHBoxLayout* topUserLayout = new QHBoxLayout;
  topUserLayout->addWidget(userColumnGroupbox);
  topUserLayout->addWidget(feedColumnGroupbox);
  topUserLayout->addWidget(rightColumnGroupbox);
  topUserGroupbox->setLayout(topUserLayout);

  createAddTweet();
  createControls();

  //connect everything
  connect(usrComboBox, SIGNAL(activated(const QString &)), this, SLOT(selectUser(const QString &)));
  connect(followButtonGroup, SIGNAL(buttonReleased(int)), this, SLOT(followUser(int)));
  connect(searchButton, SIGNAL(released()), this, SLOT(searchTweets()));
  connect(addTweetButton, SIGNAL(released()), this, SLOT(sendTweet()));
  connect(saveButton, SIGNAL(released()), this, SLOT(saveFile()));
  connect(quitButton, SIGNAL(released()), this, SLOT(close()));
  connect(searchDiagSearchButton, SIGNAL(released()), this, SLOT(searchResults()));
  connect(searchLineText, SIGNAL(returnPressed()), this, SLOT(searchResults()));
  connect(searchDiagQuitButton, SIGNAL(released()), this, SLOT(searchDiagQuit()));
  connect(connectButton, SIGNAL(released()), this, SLOT(saveComponents()));
  connect(refreshTrendingButton, SIGNAL(released()), this, SLOT(refreshTrending()));

  //add everything to main layout
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(topUserGroupbox);
  mainLayout->addWidget(addTweetGroupbox);
  mainLayout->addWidget(controlsGroupbox);
  setLayout(mainLayout);

  setWindowTitle(tr("Twitter"));
}

TwitDiag::~TwitDiag()
{
  delete searchDiag;
  delete followButtonGroup;
  delete [] followButtonStack;
}

void TwitDiag::selectUser(const QString& name)
{
  currUser = name.toStdString();
  updateFeed();
  updateDMFeed();
  updateFollowButtons();
}

void TwitDiag::followUser(int i)
{
  followButtonStack[i]->setCurrentIndex(1);
  eng->follows(currUser, names[i]);
  updateFollowButtons();
  updateFeed();
  updateDMFeed();
}

void TwitDiag::searchTweets()
{
  searchDiag->show();
}

void TwitDiag::searchResults()
{
  searchText->clear();
  std::vector<std::string> terms;
  std::stringstream ss;
  ss.str(searchLineText->text().toStdString());
  std::string tmp = "";
  while(ss >> tmp)
  {
    terms.push_back(tmp);
  }
  int stype = 1;
  if(andSearchRadioButton->isChecked())
    stype = 0;
  std::vector<std::string> tweets = eng->searchTweets(terms, stype);
  for(unsigned int i = 0; i < tweets.size(); i++)
  {
    searchText->addItem(QString::fromStdString(tweets[i]));
  }
}

void TwitDiag::searchDiagQuit()
{
  searchText->clear();
  searchLineText->setText("");
  searchLineText->text();
  searchDiag->hide();
}

void TwitDiag::sendTweet()
{
  time_t rawtime;
  struct tm * tim;
  time (&rawtime);
  tim = localtime(&rawtime);
  DateTime dt(tim->tm_hour, tim->tm_min, tim->tm_sec, tim->tm_year+1900, tim->tm_mon+1, tim->tm_mday);

  std::string tmptext = addTweetText->toPlainText().toStdString();
  eng->addTweet(currUser, dt, tmptext);
  updateFeed();
  updateDMFeed();
  refreshTrending();
  addTweetText->setText("");
}

void TwitDiag::saveFile()
{
  QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), ".", "");
  eng->saveToFile(filename.toStdString());
}

void TwitDiag::saveComponents()
{
  QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), ".", "");

  eng->saveComponentsToFile(filename.toStdString());
}

void TwitDiag::getNames()
{
  names = eng->getUserNames(); 
}

void TwitDiag::refreshTrending()
{
  trendingText->clear();
  std::vector<std::string> tags = eng->getTrending();
  for(unsigned int i = 0; i < tags.size(); i++)
  {
    trendingText->addItem(QString::fromStdString(tags[i]));
  }

}

void TwitDiag::createUserSelect()
{
  userSelectGroupbox = new QGroupBox(tr("Select User"));
  usrComboBox = new QComboBox();
  std::vector<std::string> names = eng->getUserNames();
  for(std::vector<std::string>::iterator it = names.begin(); it != names.end(); it++)
  {
    usrComboBox->addItem(QString::fromStdString(*it));
  }
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(usrComboBox);
  userSelectGroupbox->setLayout(layout);
}

void TwitDiag::createFollowing()
{
  followingGroupbox = new QGroupBox(tr("Following"));
  QGridLayout* layout = new QGridLayout();

  followButtonGroup = new QButtonGroup();
  followButtonStack = new QStackedWidget*[names.size()];
  for(unsigned int i = 0; i < names.size(); i++)
  {
    followButtonStack[i] = new QStackedWidget();
  }

  for(unsigned int i = 0; i < names.size(); i++)
  {
    layout->addWidget(new QLabel(QString::fromStdString(names[i])), i, 0);
    QPushButton * followButton = new QPushButton(tr("Follow"));
    followButtonGroup->addButton(followButton, i);

    followButtonStack[i]->insertWidget(0, followButton);
    followButtonStack[i]->insertWidget(1, new QLabel(tr("Followed")));
    layout->addWidget(followButtonStack[i], i, 1);
  }

  updateFollowButtons();

  followingGroupbox->setLayout(layout);
}

void TwitDiag::updateFollowButtons()
{
  std::vector<std::string> following = eng->getFollowing(currUser);

  for(unsigned int i = 0; i < names.size(); i++)
  {
    followButtonStack[i]->show();
    followButtonStack[i]->setCurrentIndex(0);
    for(unsigned int j = 0; j < following.size(); j++) //check if user is already followed
    { if(following[j].compare(names[i]) == 0) { followButtonStack[i]->setCurrentIndex(1);
      }
    }
    if(names[i].compare(currUser) == 0) //current user
    {
      followButtonStack[i]->hide();
    }
  }
}

void TwitDiag::createSearch()
{
  searchGroupbox = new QGroupBox(tr("Search"));
  searchButton = new QPushButton("Search Tweets");
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(searchButton);
  searchGroupbox->setLayout(layout);
}

void TwitDiag::createSearchDiag()
{
  searchDiag = new QDialog();
  searchDiag->setModal(true);
  QGroupBox* searchDiagGroupbox = new QGroupBox();
  searchDiagGroupbox->setFlat(true);
  QVBoxLayout* layout = new QVBoxLayout();
  QHBoxLayout* layoutTop = new QHBoxLayout();
  QGroupBox* radioButtons = new QGroupBox();
  QVBoxLayout* radiolayout = new QVBoxLayout();
  andSearchRadioButton = new QRadioButton(tr("AND"));
  orSearchRadioButton = new QRadioButton(tr("OR"));
  radiolayout->addWidget(andSearchRadioButton);
  radiolayout->addWidget(orSearchRadioButton);
  orSearchRadioButton->setChecked(true);
  searchLineText = new QLineEdit();
  searchDiagSearchButton = new QPushButton(tr("Search"));
  searchDiagQuitButton = new QPushButton(tr("Quit"));
  radioButtons->setLayout(radiolayout);
  layoutTop->addWidget(radioButtons);
  layoutTop->addWidget(searchLineText);
  layoutTop->addWidget(searchDiagSearchButton);
  searchDiagGroupbox->setLayout(layoutTop);
  searchText = new QListWidget();
  layout->addWidget(searchDiagGroupbox);
  layout->addWidget(searchText);
  layout->addWidget(searchDiagQuitButton);
  searchDiag->setLayout(layout);
}

void TwitDiag::createUserColumn()
{
  userColumnGroupbox = new QGroupBox();
  userColumnGroupbox->setFlat(true);
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(userSelectGroupbox);
  layout->addWidget(followingGroupbox);
  layout->addWidget(searchGroupbox);
  userColumnGroupbox->setLayout(layout);
}

void TwitDiag::createFeedColumn()
{
  feedColumnGroupbox = new QGroupBox(tr("Feed"));
  QVBoxLayout *layout = new QVBoxLayout;
  feedColumnText = new QTextEdit();
  feedColumnText->setReadOnly(true);
  layout->addWidget(feedColumnText);
  feedColumnGroupbox->setLayout(layout);
}

void TwitDiag::updateFeed()
{
  feedColumnText->setText(QString::fromStdString(eng->getFeed(currUser)));
}

void TwitDiag::createTrending()
{
  trendingGroupbox = new QGroupBox(tr("Trending Hashtags"));
  QVBoxLayout *layout = new QVBoxLayout;
  trendingText = new QListWidget();
  refreshTrendingButton = new QPushButton(tr("Refresh"));
  layout->addWidget(trendingText);
  layout->addWidget(refreshTrendingButton);
  trendingGroupbox->setLayout(layout);
}

void TwitDiag::createDMFeedColumn()
{
  dmFeedGroupbox = new QGroupBox(tr("Mention Feed"));
  QVBoxLayout *layout = new QVBoxLayout;
  dmFeedColumnText = new QTextEdit();
  dmFeedColumnText->setReadOnly(true);
  layout->addWidget(dmFeedColumnText);
  dmFeedGroupbox->setLayout(layout);

  rightColumnGroupbox = new QGroupBox();
  rightColumnGroupbox->setFlat(true);
  QVBoxLayout *rlayout = new QVBoxLayout;
  rlayout->addWidget(dmFeedGroupbox);
  rlayout->addWidget(trendingGroupbox);
  rightColumnGroupbox->setLayout(rlayout);
}

void TwitDiag::updateDMFeed()
{
  dmFeedColumnText->setText(QString::fromStdString(eng->getDMFeed(currUser)));
}

void TwitDiag::createAddTweet()
{
  addTweetGroupbox = new QGroupBox();
  addTweetGroupbox->setFlat(true);
  QHBoxLayout *layout = new QHBoxLayout();
  addTweetText = new QTextEdit();
  addTweetButton = new QPushButton("Send Tweet");
  layout->addWidget(addTweetText);
  layout->addWidget(addTweetButton);
  addTweetGroupbox->setLayout(layout);
}

void TwitDiag::createControls()
{
  controlsGroupbox = new QGroupBox();
  controlsGroupbox->setFlat(true);
  QHBoxLayout *layout = new QHBoxLayout;
  saveButton = new QPushButton("Save to File");
  quitButton = new QPushButton("Quit");
  connectButton = new QPushButton("Save Connected Components");
  layout->addWidget(saveButton);
  layout->addWidget(connectButton);
  layout->addWidget(quitButton);
  controlsGroupbox->setLayout(layout);
}


