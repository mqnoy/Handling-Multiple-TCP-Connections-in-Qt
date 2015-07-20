CONFIG    += console
QT += network
TEMPLATE = app

INCLUDEPATH += . \
           include \

DESTDIR = ./bin

HEADERS += TcpServer.h \
               NLTcpSocket.h

SOURCES += TcpServer.cpp \
           NLTcpSocket.cpp
