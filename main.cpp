#include <QApplication>
#include<QScreen>
#include<QGuiApplication>
#include<QtDebug>
#include<QWindowList>
#include<QRect>
#include "mainwindow.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  MainWindow window;
  window.mySetSize();

  window.show();

  return app.exec();
} 
