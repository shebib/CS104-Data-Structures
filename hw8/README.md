# HW 6
### Daniel Shebib

Twitter GUI, now with MergeSort and Strongly Connected Components (Tarjan's)

Contains:
datetime.cpp: holds and outputs time info
tweet.cpp: fields for a tweet, inc user, hashtags, etc.
twiteng.cpp: twitter engine, holds users, tweets, can search by hashtags, etc.
user.cpp: user object. Holds name, followers, following, etc.
twitdiag.cpp: QT GUI dialog
msort.h: static functions/templates for mergeSort

## Compiling
To compile, run make
To clean, run make clean
To rebuild Makefile, run qmake -project followed by qmake

## Syntax
run ./hw6 [[twitter.dat]]
NOTE: twitter.dat must be in the correct format
