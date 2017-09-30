#include <stdio.h>
#include <QApplication>
#include <QTextCodec>

#include "cviewer.h"
#include "cscene.h"

int main(int argc, char** argv) {

  int n = 0 ;
  QApplication app( n, 0 ) ; 

#ifdef WIN32
  // вывод сообщений на русском языке в консоль
  QTextCodec::setCodecForTr(QTextCodec::codecForName ("Windows-1251")) ;
#endif

  Cscene scene ;
  CViewer Viewer(&scene) ;
  Viewer.show() ;

  return app.exec() ;
} ;

