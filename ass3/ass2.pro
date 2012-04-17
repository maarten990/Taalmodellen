TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -L/usr/lib -lboost_regex

SOURCES += main.cpp \
    ngram_requency.cpp \
    probabilities.cpp

HEADERS += \
    ngram_requency.h \
    probabilities.h

QMAKE_CXXFLAGS += -std=c++0x
