// My library
#include "distanceGui.h"
#include "mainCLP.h"

int main( int argc , char* argv[] )
{

      PARSE_ARGS;
      
      QApplication app( argc , argv );

      distanceGui myMainWindow( test );
      
      myMainWindow.show();
      
      return app.exec();

}
