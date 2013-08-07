#include "meshDisplay.h"

int main(int argc , char* argv[] )
{
    int NumberOfMesh = ( argc - 1 );
    char* meshList[ NumberOfMesh ];
    int i;


    for( i = 0 ; i < NumberOfMesh ; i++) // get the name of each mesh
    {
        meshList[ i ] = argv[ i + 1 ];
    }

    meshDisplay myDisplay( NumberOfMesh , meshList ); // linking the files to the window
    myDisplay.windowInit();

    return 0;
}
