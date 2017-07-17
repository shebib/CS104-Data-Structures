# HW 8
### Daniel Shebib

Twitter GUI, now with a login screen and trending hashtags

Contains:
datetime.cpp: holds and outputs time info
tweet.cpp: fields for a tweet, inc user, hashtags, etc.
twiteng.cpp: twitter engine, holds users, tweets, can search by hashtags, etc.
user.cpp: user object. Holds name, followers, following, etc.
twitdiag.cpp: QT GUI dialog
msort.h: static functions/templates for mergeSort
twitlogin.cpp: login dialog
heap.h: heap data structure

## Compiling
To compile, run make
To clean, run make clean
To rebuild Makefile, run qmake -project, add QMAKE_CXXFLAGS += -std=c++11
to project file, then run qmake

## Syntax
run ./hw8 [[twitter.dat]]
NOTE: twitter.dat must be in the correct format
