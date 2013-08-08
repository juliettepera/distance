#include "meshDisplay.h"

int main(int argc , char* argv[] )
{
    int NumberOfMesh = ( argc - 1 );
    std::vector <std::string> MeshList;
    int i;
    std::cout << " test 1" << std::endl;

    for( i = 0 ; i < NumberOfMesh ; i++) // get the name of each mesh
    {
        MeshList.push_back( std::string( argv[ i + 1 ] ) );
    }

    meshDisplay myDisplay( NumberOfMesh , MeshList ); // linking the files to the window

    //*****test change size of the window
    /*
    myDisplay.setSizeH( 400 ); // change the size of the window
    myDisplay.setSizeW( 400 ); // change the size of the window
    */

    //******test change the position of the camera
     // left : 1 0 0     | right : -1 0 0
     // front : 0 1 0    | back : 0 -1 0 // doesn't work...
     // up : 0 0 1       | down : 0 0 -1
    /*
    myDisplay.setCameraX( 0 );
    myDisplay.setCameraY( 0 );
    myDisplay.setCameraZ( -1 );
    */

    //******test change the parameters of the differents mesh (here for 2)
    /*
    myDisplay.setParameters( 0 , 1.0 , 0.0 , 0.0 , 1.0 ); // change the parameters of the mesh 0
    myDisplay.setParameters( 1 , 0.5 , 1.0 , 0.0 , 0.0 ); // change the parameters of the mesh 1
    */

    //******test change the only one of the parameters of the differents mesh (here for 2)
    /*
    myDisplay.setParameters( 0 , 0.5 ); // change the oopacity parameter of the mesh 0
    myDisplay.setParameters( 1 , 1.0 , 0.0 , 0.0 ); // change the color parameter of the mesh 1
    */


    myDisplay.windowInit(); // initialize the window and display it


   return 0;
}
