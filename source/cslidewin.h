#ifndef __CSLIDEWIN_H__
#define __CSLIDEWIN_H__

#include <QVector>
#include <QString>
#include <QImage>

/** �������� �������������
*/
/*class CBinaryClassifier {
public: ;
  QVector<SStump> StumData ; //!< ������ ��������������
  int DecisionRule ; //!< ������� �������� �������
  int oldFormat ; //!< ���� ������� ������� ��������������
public: ;
  CBinaryClassifier() : DecisionRule(1), oldFormat(0) { } ;
  virtual ~CBinaryClassifier() { } ;

  //! ������ ���������� ��������������
  bool Read(QString const&Path) ;

  //! �������� ������� ��������� ��������������
  virtual bool isObject(QVector<double> &Descriptor) ;
} ;*/

/** ���������� �����������
*/
/*class CImageDescriptor {
public: ;
  CImageDescriptor() ;
  virtual ~CImageDescriptor() {} ;
  //! ���������� ����������� ��� ���� �����������
  virtual QVector<double> CalculateDescriptor(QImage const&Img)const ;

  static QImage convertTo8 (QImage const&argb32);
} ; */

/** ��������� ����������� ����
*/
struct SSlideWindowSettings {
  int win_width ;  //!< ������ ����
  int win_height ; //!< ������ ����
  int step_x ; //!< ��� ������ �� ������
  int step_y ; //!< ��� ������ �� ������
  unsigned int last_session;

  SSlideWindowSettings() : win_width(64), win_height(64), step_x(4), step_y(4) { } ;

  //! ���������� �������������� ���� �� �����������
  int CalculateNumWindows(QSize const&Size)const {
    if(Size.isNull()) return 0 ;

    int corr_width = Size.width() - win_width ;
    int corr_height = Size.height() - win_height ;

    int num_step_x = int(double(corr_width)  / double(step_x)) ;
    int num_step_y = int(double(corr_height) / double(step_y)) ;

    return num_step_x*num_step_y ;
  } ;
  
} ;

/** ����� ������ ����������� ���������� �����:
      - ��� ������� ���� �������� ����������;
      - �������������� ����������.    
*/
class CSlideWindow : public SSlideWindowSettings {
public: ;
  //CBinaryClassifier BinaryClassifier ;
  //CImageDescriptor  ImageDescriptor ; //!< ������ ��� ���������� �����������
  QString savePath ;
public: ;
  CSlideWindow() ;
  virtual ~CSlideWindow() { } ;

  //! ����� ����������� ���������� �����
  virtual int ProcessImage(QImage const&Img) ;

  //! �������� ������� ��� ������ �����������
  virtual bool isObject(QImage const&Image) ;

  //! ������� ��������� �������� ���������
  virtual bool is_end()const { return false ; }

} ;

#endif
