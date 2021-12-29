TEMPLATE = app
TARGET = Demo
QT += core gui widgets
win32:LIBS += -lopengl32
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += shaders.qrc
HEADERS += *.h 
SOURCES += *.cpp

