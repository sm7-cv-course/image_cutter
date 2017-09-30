#include <stdio.h>
#include <Qt>

#include "cscene.h"

void Cscene::mouseMoveEvent( QGraphicsSceneMouseEvent * mouseEvent ) {

  QPointF MousePt = mouseEvent->scenePos() ;
  emit CurrentPixel(MousePt) ;
} ;

void Cscene::mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent ) {

  Qt::MouseButton what_button = mouseEvent->button() ;
  QPointF MousePt = mouseEvent->scenePos() ;

  if( what_button == Qt::LeftButton ) {
    fprintf(stdout,"Cscene::mouseReleaseEvent: Qt::LeftButton\n") ;
    return ;
  }

  if( what_button == Qt::RightButton ) {
    fprintf(stdout,"Cscene::mouseReleaseEvent: Qt::RightButton\n") ;
    return ;
  }

} ;

