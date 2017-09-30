#include "cslidewin_thread.h"

CSlideWin_thread::CSlideWin_thread() {
  fprintf(stdout,"CSlideWin_thread::CSlideWin_thread()\n") ;
} ;

bool 
CSlideWin_thread::isObject(QImage const&Img) {
  bool result = CSlideWindow::isObject(Img) ;
  emit Signal_ProcessImage(result) ;
  return result ;
} ;


void 
CSlideWin_thread::run() {

  //fprintf(stdout,"CSlideWin_thread::run : Image.isNull() = %d\n", Image.isNull()) ;
  if ( ! ProcessImage(Image) ) {
    printf("Image haven't been saved\n"); 
    return ;
  }

  //заполняем массив прямоугольников, содержащих объекты
  /*for( int i = 0 ; i < NewObjPts.size() ; i ++ ) {
    ObjRects.push_back( QRect(NewObjPts[i], QSize(win_width, win_height))) ;
  } ;*/

} ;

