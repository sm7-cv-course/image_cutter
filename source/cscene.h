#ifndef __CSCENE_H__
#define __CSCENE_H__

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

class Cscene: public QGraphicsScene {
Q_OBJECT
public: ;

public: ;
  Cscene(QObject*parent = 0) : QGraphicsScene(parent) { } ;
  ~Cscene() {} ;

protected: ;
  //void mousePressEvent( QGraphicsSceneMouseEvent * mouseEvent ) ;
  void mouseMoveEvent( QGraphicsSceneMouseEvent * mouseEvent ) ;
  void mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent ) ;  
  
signals : ;
  void CurrentPixel(QPointF const&Pixel) ;

};

#endif
