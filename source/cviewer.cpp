#include "cviewer.h"
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QTextStream>

#include <QPainter>
#include <QPen>
#include <QRect>

#include "cslidewin_thread.h"

QImage DrawRects(QImage const&Img, QVector<QRect> const&Rects) ;
QImage DrawRects(QImage const&Img, QVector<QPoint> const&Pts, int win_width, int win_height) ;

QImage DrawRects(QImage const&Img, QVector<QPoint> const&Pts, int win_width, int win_height) {

  QVector<QRect> Rects ;
  for( int i = 0 ; i < Pts.size() ; i ++ ) {
    Rects.push_back(QRect(Pts[i].x(), Pts[i].y(), win_width, win_height)) ;
  } ;

  return DrawRects(Img, Rects) ;
} ;


QImage DrawRects(QImage const&Img, QVector<QRect> const&Rects) {
  if(Img.isNull()) return QImage() ;

  QPainter p ;
  QImage BackGround(Img.size(), QImage::Format_RGB32) ;

  p.begin(&BackGround) ;
  p.drawImage(0, 0, Img) ;
  p.setPen(QPen(Qt::red)) ;

  for( int i = 0 ; i < Rects.size() ; i ++ ) {
    p.drawRect(Rects[i]) ; // рисуем прмоугольник
  } ;
  p.end() ;

  return BackGround ;
} ;

void 
CViewer::Read(QString const&Path) {

  QFile file(Path);    
  if (!file.open(QIODevice::ReadOnly)) {
    fprintf(stdout,"CViewer::Read : Can't read <%s>\n", qPrintable(Path)) ;
    return ;
  } ;

  QString Path1 ;
  QString Path2 ;
  int step_x, step_y ;
  int width0, height0 ;
  double scale_coeff ;
  int num_scales ;
  double angle1, angle2, angle_step ;

  //читаем данные из файла
  {
    QTextStream ts(&file);
    ts>>Path1 ;
    ts>>Path2 ;
    ts>>step_x>>step_y ;
    ts>>width0>>height0 ;
    ts>>scale_coeff>>num_scales ;
    ts>>angle1>>angle2>>angle_step ;
    ts>>cur_session;

    last_dest_path = Path2;

    fprintf(stdout,"SDialogSettings::Read : Path1 = <%s>\n", qPrintable(Path1)) ;
    fprintf(stdout,"SDialogSettings::Read : Path2  = <%s>\n", qPrintable(Path2)) ;
    fprintf(stdout,"SDialogSettings::Read : step_x = %d ; step_y = %d\n", step_x, step_y) ;
    fprintf(stdout,"SDialogSettings::Read : width0 = %d ; height0 = %d\n", width0, height0) ;
    fprintf(stdout,"SDialogSettings::Read : scale_coeff = %lf ; num_scales = %d\n", scale_coeff, num_scales) ;
    fprintf(stdout,"SDialogSettings::Read : angle1 = %lf - angle2 = %lf - angle_step = %lf\n", angle1, angle2, angle_step) ;
  } ;

  lineEdit_raster_path->setText(Path1) ;  
  lineEdit_classifier_path->setText(Path2) ;

  spinBox_step_x->setValue(step_x) ;
  spinBox_step_y->setValue(step_y) ;

  spinBox_width0->setValue(width0) ;
  spinBox_height0->setValue(height0) ;

  doubleSpinBox_scale_coefficient->setValue(scale_coeff) ;
  spinBox_num_scales->setValue(num_scales) ;

  doubleSpinBox_angle1->setValue(angle1) ;
  doubleSpinBox_angle2->setValue(angle2) ;
  doubleSpinBox_angle_step->setValue(angle_step) ;
} ;

void 
CViewer::Save(QString const&Path) {

  QFile file(Path);    
  if(!file.open(QIODevice::WriteOnly)) {
    printf("CViewer::Save : there is not <%s>\n", qPrintable(Path)) ;
    return ;
  } ;

  QTextStream ts(&file) ;
  ts<<lineEdit_raster_path->text()<<endl ;
  ts<<lineEdit_classifier_path->text()<<endl ;
  ts<<spinBox_step_x->value()<<" "<<spinBox_step_y->value()<<endl ;
  ts<<spinBox_width0->value()<<" "<<spinBox_height0->value()<<endl ;
  ts<<doubleSpinBox_scale_coefficient->value()<<" "<<spinBox_num_scales->value()<<endl ;

  ts<<doubleSpinBox_angle1->value()<<" "<<doubleSpinBox_angle2->value()<<" "<<doubleSpinBox_angle_step->value()<<endl ;
  ts<<cur_session;
} ;



CViewer::CViewer( Cscene* pScene, QWidget*parent) : _scale(1.25),
                                                    _pScene(NULL),
                                                    _pProcessingThread(NULL),
                                                    _pPMitem(NULL) {
  // установим диалоги ui-формы
  setupUi(this) ;

  // устанавливаем сцену
  if(pScene)
  {
    _pScene = pScene ;
    QGraphicsScene*GScene = dynamic_cast<QGraphicsScene*>(pScene) ;
    if(!GScene) return ;

    graphicsView_viewer->setScene(GScene) ;
    graphicsView_viewer->setMouseTracking(true) ;
  } ;

  // ограничим доступ к кнопкам
  //pushButton_start->setEnabled(false) ;
  //pushButton_stop->setEnabled(false) ;
  pushButton_stop->hide() ;

  // viewing functions
  connect( pushButton_scaleplus,    SIGNAL(clicked()), SLOT(ScalePlus()) ) ;
  connect( pushButton_scaleminus,   SIGNAL(clicked()), SLOT(ScaleMinus()) ) ;
  connect( pushButton_fitscale,     SIGNAL(clicked()), SLOT(ScaleFit()) ) ;

  connect( pushButton_raster_path,      SIGNAL(clicked()), SLOT(Browse_raster()) ) ;
  connect( pushButton_classifier_path,  SIGNAL(clicked()), SLOT(Browse_classifier()) ) ;

  connect( pushButton_raster_show,  SIGNAL(clicked()), SLOT(Show_raster()) ) ;
  connect( pushButton_start,        SIGNAL(clicked()), SLOT(start_process()) ) ;

  // If isn't set in file to predict erroros
  cur_session=0;

  Read("init.txt") ;
} ;

CViewer::~CViewer() {
  if(_pProcessingThread) delete _pProcessingThread ;
  Save("init.txt") ;
} ;

void
CViewer::SetImage( QImage const&Image) {

  QPixmap pixmap = QPixmap::fromImage(Image) ;

  if(_pPMitem) _pPMitem->setPixmap(QPixmap::fromImage(Image)) ;
  else {
    _pPMitem = _pScene->addPixmap(pixmap) ;  
    _pPMitem->setZValue(-1) ;
  } ;
} ;

void
CViewer::Browse_raster() {
  QString path = QFileDialog::getOpenFileName(this, QObject::tr("¬ыберите растр"), lineEdit_raster_path->text(), QObject::tr("(*)")) ;
  if(path.isNull()) return ;
  lineEdit_raster_path->setText(path) ;
} ;

void
CViewer::Browse_classifier() {
  QString path = QFileDialog::getExistingDirectory(this, QObject::tr("¬ыберите путь к сохранемым фрагментам"), lineEdit_classifier_path->text()) ;
  if(path.isNull()) return ;
  lineEdit_classifier_path->setText(path) ;
} ;

void
CViewer::Show_raster() {
  if(_pScene) {_pScene->clear() ; _pPMitem =  NULL ; }
  QImage Raster(lineEdit_raster_path->text()) ;
  fprintf(stdout,"Raster.isNull() = %d\n", Raster.isNull()) ;
  SetImage(Raster) ; 
} ;

void
CViewer::stop_process() {

  // получим нить обработки
  CSlideWin_thread*pThread = dynamic_cast<CSlideWin_thread*> (_pProcessingThread) ;
  if(!pThread) return ;

  //QImage MarkedImg = DrawRects(pThread->Image, pThread->ObjRects) ;
  //fprintf(stdout,"MarkedImg.isNull() = %d : pThread->Image.isNull() = %d\n", MarkedImg.isNull(), pThread->Image.isNull()) ;

  //SetImage(MarkedImg) ;


  //разморозим кнопку начала процесса обработки
  pushButton_start->setEnabled(true) ;
} ;

void
CViewer::ShowPercent(bool is_obj_res) {
  progressBar->setValue(progressBar->value() + 1) ;
} ;

void
CViewer::start_process() {
  fprintf(stdout,"CViewer::start_process\n") ;
  if(!_pScene) return ;

  // удалим предудыщую нить обработки
  if(_pProcessingThread) delete _pProcessingThread ;
  _pProcessingThread = NULL ;

  QImage Img ;
  //CBinaryClassifier BinaryClassifier ;

  // проверки корректности исходных данных
  {
    if(!_pPMitem) return ;
    Img = _pPMitem->pixmap().toImage() ;
    if(Img.isNull()) return ;

  } ;

  CSlideWin_thread*pThread = new CSlideWin_thread ;
  pThread->Image = Img ;

  pThread->step_x = spinBox_step_x->value() ;
  pThread->step_y = spinBox_step_y->value() ;

  pThread->win_width  = spinBox_width0->value() ;
  pThread->win_height = spinBox_height0->value() ;

  pThread->savePath = lineEdit_classifier_path->text() ;

  if (last_dest_path == pThread->savePath) {
    cur_session++;
    pThread->last_session = cur_session;
  }
  else {
    cur_session = 0;
    pThread->last_session = cur_session;
  }
  

  // количество просматриваемых окон
  int NumWindows = pThread->CalculateNumWindows(Img.size()) ;
  if(NumWindows == 0) { delete pThread ; return ;}

  // инициализируем нить обработки
  _pProcessingThread = (QThread*)pThread ;

  // установим связи сигналов
  connect( pThread, SIGNAL(Signal_ProcessImage(bool)), this, SLOT(ShowPercent(bool)) ) ;
  connect( pThread, SIGNAL(finished()), this, SLOT(stop_process()) ) ;

  // инициализируем диапазон обрабатываемых пар кадров
  progressBar->setRange(0, NumWindows) ;
  progressBar->setValue(0) ;

  //заморозим кнопку начала процесса обработки
  pushButton_start->setEnabled(false) ;

  //запуск процесса обработки
  _pProcessingThread->start() ;

  fprintf(stdout,"CViewer::start_process - end\n") ;
} ;
