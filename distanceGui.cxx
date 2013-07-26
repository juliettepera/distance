// My libraries
#include "distanceGui.h"
#include "distanceDisplay.h"
#include "distanceCompute.h"

//************************************************* CLASS ****************************************************
distanceGui::distanceGui(std::string meshA, std::string meshB)
{
    // to display the window?
    setupUi(this);
           
    //******** GLOBAL VARIABLES ********
    m_meshA = meshA;
    m_meshB = meshB;
    m_distance = 0;
    m_colorA.setRed( 0.0 ); m_colorA.setGreen( 1.0 ); m_colorA.setBlue( 1.0 );
    m_colorB.setRed( 0.0 ); m_colorB.setGreen( 0.0 ); m_colorB.setBlue( 1.0 );
    m_opacityA = 1.0;
    m_opacityB = 1.0;
    m_positionCam.setX( 0 ); m_positionCam.setY( 0 ); m_positionCam.setZ( 1 );


    //******** CONNECTION ********
    //MESH A BUTTON TO MESH A LINE EDIT
    QObject::connect( buttonMeshA , SIGNAL( clicked() ) , this , SLOT( OpenMeshBrowseWindowA() ) );
            
    //MESH B BUTTON TO MESH B LINE EDIT
    QObject::connect( buttonMeshB , SIGNAL( clicked() ) , this , SLOT( OpenMeshBrowseWindowB() ) );
    
    //RADIO BUTTON A to B
    QObject::connect( radioAtoB , SIGNAL( clicked() ) , this , SLOT( ChangeValue() ) );

    //RADIO BUTTON B to A
    QObject::connect( radioBtoA , SIGNAL( clicked() ) , this , SLOT( ChangeValue() ) );

    //RADIO BUTTON B to A
    QObject::connect( radioBoth , SIGNAL( clicked() ) , this , SLOT( ChangeValue() ) );

    // SPINBOX OPACITY A TO VALUE OF OPACITY
    QObject::connect( spinBoxOpacityA , SIGNAL( valueChanged( double ) ), this, SLOT( ChangeValueOpacityA() ) );

    // SPINBOX OPACITY B TO VALUE OF OPACITY
    QObject::connect( spinBoxOpacityB , SIGNAL( valueChanged( double ) ), this, SLOT( ChangeValueOpacityB() ) );

    //RADIO BUTTON FRONT
    QObject::connect( buttonFront , SIGNAL( clicked() ) , this , SLOT( buttonFrontClicked() ) );

    //RADIO BUTTON BACK
    QObject::connect( buttonBack , SIGNAL( clicked() ) , this , SLOT( buttonBackClicked() ) );

    //RADIO BUTTON RIGHT
    QObject::connect( buttonRight , SIGNAL( clicked() ) , this , SLOT( buttonRightClicked() ) );

    //RADIO BUTTON LEFT
    QObject::connect( buttonLeft , SIGNAL( clicked() ) , this , SLOT( buttonLeftClicked() ) );

    //DISPLAY BUTTON
    QObject::connect( buttonDisplay , SIGNAL( clicked() ) , this , SLOT( Display() ) );

    //APPLY BUTTON 
    QObject::connect( buttonApply , SIGNAL( clicked() ) , this , SLOT( ApplyDistance() ) );
                
    //QUIT BUTTON 
    QObject::connect( buttonQuit , SIGNAL( clicked() ) , qApp , SLOT( quit() ) );
          
    //IF THE PARAMETERS ARE ALLREADY GIVEN BY THE USER
    if( !meshA.empty() )
    {
      lineMeshA->setText( QString( meshA.c_str() ) );
    }
          
    if( !meshB.empty() )
    {
      lineMeshB->setText( QString( meshB.c_str() ) );
    }
                                                                              
}


//************************************************* SLOTS ****************************************************   
// display on the edit line "lineMeshA" the file selected
void distanceGui::OpenMeshBrowseWindowA() 
{
      QString browseMeshA = QFileDialog::getOpenFileName( this , "Open mesh A" , QString() , "vtk mesh (*.vtk)" );
      if( !browseMeshA.isEmpty() )
      {
            lineMeshA -> setText( browseMeshA );
      }
      m_meshA = ( lineMeshA -> text() ).toStdString();
}




// display on the edit line "lineMeshB" the file selected
void distanceGui::OpenMeshBrowseWindowB() 
{
      QString browseMeshB = QFileDialog::getOpenFileName( this , "Open mesh B" , QString() , "vtk mesh (*.vtk)" );
      if( !browseMeshB.isEmpty() )
      {
            lineMeshB -> setText( browseMeshB );
      }
      m_meshB = ( lineMeshB -> text() ).toStdString();
}




// change the value of m_distance
void distanceGui::ChangeValue()
{
    if( this -> radioAtoB -> isChecked() )
    {
        m_distance = 1;
    }
    if( this -> radioBtoA -> isChecked() )
    {
        m_distance = 2;
    }
    if( this -> radioBoth -> isChecked() )
    {
        m_distance = 3;
    }
}




// change the value of m_opacityA
void distanceGui::ChangeValueOpacityA()
{
    m_opacityA = spinBoxOpacityA -> value();
}




// change the value of m_opacityB
void distanceGui::ChangeValueOpacityB()
{
    m_opacityB = spinBoxOpacityB -> value();
}

// change the value of the position of the camera
void distanceGui::buttonFrontClicked()
{
    m_positionCam.setX(0); m_positionCam.setY(0); m_positionCam.setZ(1);
    Display();
}

void distanceGui::buttonBackClicked()
{
    m_positionCam.setX(0); m_positionCam.setY(0); m_positionCam.setZ(-1);
    Display();
}

void distanceGui::buttonRightClicked()
{
    m_positionCam.setX(1); m_positionCam.setY(0); m_positionCam.setZ(0);
    Display();
}

void distanceGui::buttonLeftClicked()
{
    m_positionCam.setX(0); m_positionCam.setY(-1); m_positionCam.setZ(0);
    Display();
}



// display the two files selected on the box "meshWidget"
void distanceGui::Display()
{
    if( m_meshA != "\0" && m_meshB != "\0")
    {
        //QVTKWIDGETS
        QVTKWidget *widgetMeshA = new QVTKWidget( this -> scrollAreaMeshA );
        QVTKWidget *widgetMeshB = new QVTKWidget( this -> scrollAreaMeshB );
        QVTKWidget *widgetMeshBoth = new QVTKWidget( this -> scrollAreaBoth );

        //SIZES
        // set size automaticly ??????
        QSize sizeA( 351 , 311 );
        QSize sizeBoth( 711 , 381 );

        //VISUALISATION
        windowUpdate( widgetMeshA , m_meshA , sizeA , m_colorA , m_opacityA , m_positionCam );
        windowUpdate( widgetMeshB , m_meshB , sizeA , m_colorB , m_opacityB , m_positionCam );
        windowUpdate( widgetMeshBoth , m_meshA , m_meshB , sizeBoth , m_colorA , m_colorB , m_opacityA , m_opacityB );
     }
}




// apply the good calculated distance
void distanceGui::ApplyDistance()
{
    switch( m_distance )
    {
        case 0:
            std::cout << std::endl << "you have to select the distance you want to compute " << std::endl;
            break;

        case 1:
            computeDistanceAtoB();
            break;

        case 2:
            computeDistanceBtoA();
            break;

        case 3:
            computeDistanceBoth();
            break;
    }
}



