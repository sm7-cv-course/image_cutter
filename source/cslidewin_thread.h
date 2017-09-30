#ifndef __CSLIDEWIN_THREAD_H__
#define __CSLIDEWIN_THREAD_H__

#include <QThread>
#include <QRect>
#include "cslidewin.h"

class CSlideWin_thread : public QThread, public CSlideWindow {
Q_OBJECT 
public: ;
  QImage Image ; //!< ����������� ��� ������
  QVector<QRect> ObjRects ; //!< ������ ���������������, ���������� �������
public: ;
  CSlideWin_thread() ;
  virtual ~CSlideWin_thread() { } ;

  //! ������������� ������� �������� �������
  virtual bool isObject(QImage const&Img) ;

protected: ;
  //! ������ �������� ���������
  virtual void run() ;

signals: ;
  //! ������ �� ������������ ������
  void Signal_ProcessImage(bool result) ;

} ;

#endif
