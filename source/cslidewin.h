#ifndef __CSLIDEWIN_H__
#define __CSLIDEWIN_H__

#include <QVector>
#include <QString>
#include <QImage>

/** бинарный классификатор
*/
/*class CBinaryClassifier {
public: ;
  QVector<SStump> StumData ; //!< данные классификатора
  int DecisionRule ; //!< правило принятия решения
  int oldFormat ; //!< флаг старого формата классификатора
public: ;
  CBinaryClassifier() : DecisionRule(1), oldFormat(0) { } ;
  virtual ~CBinaryClassifier() { } ;

  //! чтение параметров классификатора
  bool Read(QString const&Path) ;

  //! решающее правило бинарного классификатора
  virtual bool isObject(QVector<double> &Descriptor) ;
} ;*/

/** дескриптор изображения
*/
/*class CImageDescriptor {
public: ;
  CImageDescriptor() ;
  virtual ~CImageDescriptor() {} ;
  //! вычисление дескриптора для окна изображения
  virtual QVector<double> CalculateDescriptor(QImage const&Img)const ;

  static QImage convertTo8 (QImage const&argb32);
} ; */

/** настройки скользящего окна
*/
struct SSlideWindowSettings {
  int win_width ;  //!< ширина окна
  int win_height ; //!< высота окна
  int step_x ; //!< шаг обхода по ширине
  int step_y ; //!< шаг обхода по высоте
  unsigned int last_session;

  SSlideWindowSettings() : win_width(64), win_height(64), step_x(4), step_y(4) { } ;

  //! количество обрабатываемых окон на изображении
  int CalculateNumWindows(QSize const&Size)const {
    if(Size.isNull()) return 0 ;

    int corr_width = Size.width() - win_width ;
    int corr_height = Size.height() - win_height ;

    int num_step_x = int(double(corr_width)  / double(step_x)) ;
    int num_step_y = int(double(corr_height) / double(step_y)) ;

    return num_step_x*num_step_y ;
  } ;
  
} ;

/** класс обхода изображения скользящим окном:
      - для каждого окна вычислим дескриптор;
      - идентифицируем дескриптор.    
*/
class CSlideWindow : public SSlideWindowSettings {
public: ;
  //CBinaryClassifier BinaryClassifier ;
  //CImageDescriptor  ImageDescriptor ; //!< объект для вычисления дескриптора
  QString savePath ;
public: ;
  CSlideWindow() ;
  virtual ~CSlideWindow() { } ;

  //! обход изображения скользящим окном
  virtual int ProcessImage(QImage const&Img) ;

  //! решающая функция для обхода изображения
  virtual bool isObject(QImage const&Image) ;

  //! условие окончания процесса обработки
  virtual bool is_end()const { return false ; }

} ;

#endif
