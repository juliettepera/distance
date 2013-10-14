// My library
#include "meshMetricGui.h"

int main( int argc , char* argv[] )
{

      QApplication app( argc , argv );

      std::string argvStr = argv[0];
      QWidget * parent = 0;
      Qt::WFlags f = 0;

      meshMetricGui myMainWindow( parent , f , argvStr );

      myMainWindow.show();

      return app.exec();

}
