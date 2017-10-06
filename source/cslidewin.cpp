#include "cslidewin.h"
#include <QFile>
#include <QTextStream>
#include <time.h>

#define __SUCCESS 0

CSlideWindow::CSlideWindow() {

}

int
CSlideWindow::ProcessImage(QImage const&Img) {

  int rez ;
  for( int i = 0 ; i < Img.height() && !is_end() ; i += step_y ) {
    if(i + win_height > Img.height() ) continue ;

    for( int j = 0 ; j < Img.width() && !is_end() ; j += step_x ) {
      if(j + win_height > Img.width()) continue ;

      // Получим очередное изображение для анализа
      QImage ijImage = Img.copy(j, i, win_width, win_height) ;
      
      // Заносим акутальную точку в массив
      //if( isObject( ijImage ) ) ActualPts.push_back(QPoint(j, i)) ;
      if( isObject( ijImage ) ) rez = ijImage.save( QString( savePath + "/" + QString("%1%2").arg(last_session).arg( j + i * Img.width() ) ) + ".png" ) ;
    } ;
  } ;

  return rez ;
} ;

/*QImage 
CImageDescriptor::convertTo8(QImage const&InImg) {
   QImage curImg ( InImg.size(), QImage::Format_Indexed8 );
   
   QVector < QRgb > color_table ;
   for( int k = 0 ; k < 256 ; k++ ) color_table << qRgb( k, k, k ) ;
   curImg.setColorTable( color_table ) ;
   
   if ( InImg.format() != QImage::Format_Indexed8 ) {
      for ( int i = 0; i < InImg.height(); ++i )
         for ( int j = 0; j < InImg.width(); ++j ) {
              curImg.setPixel( j,i, qGray( InImg.pixel(j,i) ) ) ;
           }
   }
   else curImg = InImg ;

   return curImg ;
}*/

bool 
CSlideWindow::isObject(QImage const&Img) {
  // определим, является ли найденный дескриптор объектом
  return true ;
} ;

