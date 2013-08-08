#ifndef MESHQTDISPLAY_H
#define MESHQTDISPLAY_H

// VTK libraries
#include <QVTKWidget.h>

// Qt libraries

// My libraries
#include "meshDisplay.h"

class meshQtDisplay: public meshDisplay
{
    public:
        meshQtDisplay( QWidget *MeshWidget , int NumberOfMesh, std::vector<std::string> MeshList );
        void setCameraX( int x ); // accessor x value of the camera position
        void setCameraY( int y ); // accessor y value of the camera position
        void setCameraZ( int z ); // accessor z value of the camera position
        void setSizeH( int Height ); // accessor to the height value of the window's size
        void setSizeW( int Width ); // accessor to the width value of the window's size
        void setOpacity( int IndiceOfMesh , double Opacity ); // accessor to the opacity value of one mesh
        void setRed(int IndiceOfMesh , double Red ); // accessor to the red value of one mesh
        void setGreen(int IndiceOfMesh , double Green ); // accessor to the Green value of one mesh
        void setBlue(int IndiceOfMesh , double Blue ); // accessor to the Blue value of one mesh

        void createLinks( int IndiceOfMesh ); // load the file and link it to the actor
        void windowInit(); // link all the actors to the same renderer and renderWindow and display the mesh
        void windowUpdate(); // update the window with the new camera position

        void positionCamera(int PositionX , int PositionY , int PositionZ ); // set the new position of the camera

    private:
        QVTKWidget *m_MeshWidget;

};

#endif
