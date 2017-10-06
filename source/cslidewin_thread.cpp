#include <stdlib.h>
#include <stdio.h>
#include "cslidewin_thread.h"

CSlideWin_thread::CSlideWin_thread() {
  fprintf(stdout, "CSlideWin_thread::CSlideWin_thread()\n") ;
} ;

bool 
CSlideWin_thread::isObject(QImage const&Img) {
  bool result = CSlideWindow::isObject(Img) ;
  emit Signal_ProcessImage(result) ;
  return result ;
} ;


void 
CSlideWin_thread::run() {

  if ( ! ProcessImage(Image) ) {
    printf("Image haven't been saved\n"); 
    return ;
  }

} ;

