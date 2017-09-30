#ifndef __CSLIDEWIN_THREAD_H__
#define __CSLIDEWIN_THREAD_H__

#include <QThread>
#include <QRect>
#include "cslidewin.h"

class CSlideWin_thread : public QThread, public CSlideWindow {
Q_OBJECT 
public: ;
  QImage Image ; //!< изображение для обхода
  QVector<QRect> ObjRects ; //!< массив прямоугольников, содержащих объекты
public: ;
  CSlideWin_thread() ;
  virtual ~CSlideWin_thread() { } ;

  //! переопределим функцию проверки объекта
  virtual bool isObject(QImage const&Img) ;

protected: ;
  //! запуск процесса обработки
  virtual void run() ;

signals: ;
  //! сигнал об обработанном образе
  void Signal_ProcessImage(bool result) ;

} ;

#endif
