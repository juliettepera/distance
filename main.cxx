// My library
#include "distanceGui.h"
#include "mainCLP.h"

int main( int argc , char* argv[] )
{

      PARSE_ARGS;
      
      QApplication app( argc , argv );

      distanceGui mainWindow( meshA , meshB );
      
      mainWindow.show();
      
      return app.exec();

}
