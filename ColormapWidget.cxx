#include <ColormapWidget.h>
#include <iostream>

ColormapWidget::ColormapWidget( QWidget *parent, const char *name ):QWidget( parent , name )
{
  setSizePolicy( QSizePolicy( QSizePolicy::Minimum,QSizePolicy::Expanding ) );
  setBackgroundColor( Qt::black );
  
  for (float i=0;i<256;i++) 
  {
    looktable[(int)i].B = 255*((-((i-128)*(i-128))/(float)4096)+((i-128)/(float)32));
    if (looktable[(int)i].B<0)looktable[(int)i].B =0;

    looktable[(int)i].G = 255*((-((i-64)*(i-64))/(float)4096)+((i-64)/(float)32));
    if (looktable[(int)i].G<0)looktable[(int)i].G =0;

    looktable[(int)i].R = 255*((-(i*i)/(float)4096)+(i/32));
    if (looktable[(int)i].R<0)looktable[(int)i].R =0;
  }
    
}

ColormapWidget::~ColormapWidget()
{

}

void ColormapWidget::paintEvent(QPaintEvent *) 
{

  QPainter p;
  p.begin(this); 

  for (int i=18,j=238;i<238;i+=1,j-=1)
  {
   QColor color((int)looktable[(int)j].R,(int)looktable[(int)j].G,(int)looktable[(int)j].B);
   QPen pen(color,1,Qt::SolidLine );
   p.setPen(pen);
   p.drawLine( (i-18) , 0 , (i-18) , height() );

  }
  p.end();
}
