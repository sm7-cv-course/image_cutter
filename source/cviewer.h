#ifndef __CVIEWER_H__
#define __CVIEWER_H__

#include <QThread>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include "ui_viewer.h"
#include "cscene.h"

class CViewer : public QWidget, private Ui_Form {
Q_OBJECT 

private: ;
  double _scale ;
  Cscene*_pScene ;
  QThread*_pProcessingThread ;   //!< нить обработки
  QGraphicsPixmapItem*_pPMitem ; //!< объект сцены
  // The last destination path
  QString last_dest_path;
  // Number of cutting processes for the same destination path. It is needed to append new cutted fragments, not replace
  unsigned int cur_session;

public: ;
  CViewer( Cscene* = 0, QWidget* = 0 ) ;    
  ~CViewer() ;  

  void SetImage( QImage const&Img) ;

  void Read(QString const&Path) ;
  void Save(QString const&Path) ;

public slots : ;
  void ScaleFit() { graphicsView_viewer->fitInView( _pScene->itemsBoundingRect(), Qt::KeepAspectRatio ) ; } ;
  void ScalePlus() { graphicsView_viewer->scale( _scale, _scale ) ; } ;
  void ScaleMinus() { graphicsView_viewer->scale( 1./_scale, 1./_scale ) ;  } ;

  void Browse_raster() ;
  void Browse_classifier() ;

  void Show_raster() ;
  void ShowPercent(bool is_obj_res) ;
  
  void start_process() ;
  void stop_process() ;

};


#endif
