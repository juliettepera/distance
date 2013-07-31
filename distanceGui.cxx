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

    //m_colorA.setRed( 0.0 ) ; m_colorA.setGreen( 1.0 ) ; m_colorA.setBlue( 1.0 );
   // m_colorB.setRed( 0.0 ) ; m_colorB.setGreen( 0.0 ) ; m_colorB.setBlue( 1.0 );

    m_opacityA = 1.0;
    m_opacityB = 1.0;

    m_choixdistance = 0;

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
    QObject::connect( sliderOpacityMeshA , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacityA() ) );

    // SPINBOX OPACITY B TO VALUE OF OPACITY
    QObject::connect( sliderOpacityMeshB , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacityB() ) );

    //RADIO BUTTON FRONT
    QObject::connect( buttonFront , SIGNAL( clicked() ) , this , SLOT( buttonFrontClicked() ) );

    //RADIO BUTTON BACK
    QObject::connect( buttonBack , SIGNAL( clicked() ) , this , SLOT( buttonBackClicked() ) );

    //RADIO BUTTON RIGHT
    QObject::connect( buttonRight , SIGNAL( clicked() ) , this , SLOT( buttonRightClicked() ) );

    //RADIO BUTTON LEFT
    QObject::connect( buttonLeft , SIGNAL( clicked() ) , this , SLOT( buttonLeftClicked() ) );

    //RADIO BUTTON UP
    QObject::connect( buttonUp , SIGNAL( clicked() ) , this , SLOT( buttonUpClicked() ) );

    //RADIO BUTTON DOWN
    QObject::connect( buttonDown , SIGNAL( clicked() ) , this , SLOT( buttonDownClicked() ) );

    //DISPLAY BUTTON
    QObject::connect( buttonDisplay , SIGNAL( clicked() ) , this , SLOT( DisplayInit() ) );

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




// change the value of m_choixdistance
void distanceGui::ChangeValue()
{
    if( this -> radioAtoB -> isChecked() )
    {
        m_choixdistance = 1;
    }
    if( this -> radioBtoA -> isChecked() )
    {
        m_choixdistance = 2;
    }
    if( this -> radioBoth -> isChecked() )
    {
        m_choixdistance = 3;
    }
}




// change the value of m_opacityA
void distanceGui::ChangeValueOpacityA()
{
    m_opacityA = sliderOpacityMeshA -> value()/100.;
    DisplayUpdate();
}




// change the value of m_opacityB
void distanceGui::ChangeValueOpacityB()
{
    m_opacityB = sliderOpacityMeshB -> value()/100.;
    DisplayUpdate();
}



// change the value of the position of the camera
void distanceGui::buttonFrontClicked()
{
    m_positionCam.setX(0); m_positionCam.setY(0); m_positionCam.setZ(1);
    DisplayUpdate();
}

void distanceGui::buttonBackClicked()
{
    m_positionCam.setX(0); m_positionCam.setY(0); m_positionCam.setZ(-1);
    DisplayUpdate();
}

void distanceGui::buttonRightClicked()
{
    m_positionCam.setX(1); m_positionCam.setY(0); m_positionCam.setZ(0);
    DisplayUpdate();
}

void distanceGui::buttonLeftClicked()
{
    m_positionCam.setX(-1); m_positionCam.setY(0); m_positionCam.setZ(0);
    DisplayUpdate();
}

void distanceGui::buttonUpClicked()
{
    m_positionCam.setX(0); m_positionCam.setY(-1); m_positionCam.setZ(0);
    DisplayUpdate();
}

void distanceGui::buttonDownClicked()
{
    m_positionCam.setX(0); m_positionCam.setY(1); m_positionCam.setZ(0);
    DisplayUpdate();
}


// display the two files selected on the box "meshWidget"
void distanceGui::DisplayInit()
{
    if( m_meshA != "\0" && m_meshB != "\0")
    {
        QVTKWidget *widgetMeshBoth = new QVTKWidget( this -> scrollAreaBoth );
        windowInit( widgetMeshBoth , m_meshA , m_meshB );
     }
}

void distanceGui::DisplayUpdate()
{
    if( m_meshA != "\0" && m_meshB != "\0")
    {
        QVTKWidget *widgetMeshBoth = new QVTKWidget( this -> scrollAreaBoth );
        windowUpdate( widgetMeshBoth , m_opacityA , m_opacityB , m_positionCam );
    }
}



// apply the good calculated distance
void distanceGui::ApplyDistance()
{
    switch( m_choixdistance )
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



