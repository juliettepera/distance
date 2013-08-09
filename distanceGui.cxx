// My libraries
#include "distanceGui.h"

distanceGui::distanceGui(int test)
{
    // to display the window
    setupUi(this);

    // initialisations
    m_NumberOfMesh = 0;
    m_ChoiceOfError = 0;
    m_MeshSelected = 0;
    m_WidgetMesh = new QVTKWidget( this -> scrollAreaMesh );

    // connections
    QObject::connect( pushButtonLoad , SIGNAL( clicked() ) , this , SLOT( OpenBrowseWindow() ) ); // load a new mesh
    QObject::connect( pushButtonDisplay , SIGNAL( clicked() ) , this , SLOT( DisplayInit() ) ); //initialize the display
    QObject::connect( horizontalSliderOpacity , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacity() ) ); // change the value of the opacity of one mesh
    QObject::connect( horizontalSliderSmoothing , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueSmoothing() ) ); // change the value of the smoothing of one mesh
    QObject::connect( pushButtonFront , SIGNAL( clicked() ) , this , SLOT( buttonFrontClicked() ) ); // set the position of the camera
    QObject::connect( pushButtonBack , SIGNAL( clicked() ) , this , SLOT( buttonBackClicked() ) );
    QObject::connect( pushButtonRight , SIGNAL( clicked() ) , this , SLOT( buttonRightClicked() ) );
    QObject::connect( pushButtonLeft , SIGNAL( clicked() ) , this , SLOT( buttonLeftClicked() ) );
    QObject::connect( pushButtonUp , SIGNAL( clicked() ) , this , SLOT( buttonUpClicked() ) );
    QObject::connect( pushButtonDown , SIGNAL( clicked() ) , this , SLOT( buttonDownClicked() ) );
    QObject::connect( radioButtonAtoB , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) ); // change the type of error computed
    QObject::connect( radioButtonBtoA , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );
    QObject::connect( radioButtonBoth , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );
    QObject::connect( pushButtonApply , SIGNAL( clicked() ) , this , SLOT( ApplyDistance() ) ); // compute the distance error             
    QObject::connect( pushButtonQuit , SIGNAL( clicked() ) , qApp , SLOT( quit() ) ); // quit the application
                                                                              
}



// display on the edit line "lineMeshA" the file selected
void distanceGui::OpenBrowseWindow()
{
      QString browseMesh = QFileDialog::getOpenFileName( this , "Open a VTK file" , QString() , "vtk mesh (*.vtk)" );

      if( !browseMesh.isEmpty() )
      {
            lineEditLoad -> setText( browseMesh );
      }

      m_MeshList.push_back( ( lineEditLoad -> text() ).toStdString() );
      m_NumberOfMesh++;
}

// change the value of m_choixdistance
void distanceGui::ChangeValueChoice()
{
    if( this -> radioButtonAtoB -> isChecked() )
    {
        m_ChoiceOfError = 1;
    }
    if( this -> radioButtonBtoA -> isChecked() )
    {
        m_ChoiceOfError = 2;
    }
    if( this -> radioButtonBoth -> isChecked() )
    {
        m_ChoiceOfError = 3;
    }
}

void distanceGui::ChangeMeshSelected()
{

}

// change the value of m_opacityA
void distanceGui::ChangeValueOpacity()
{
    m_Opacity = horizontalSliderOpacity -> value()/100.;
    m_MyWindowMesh.setOpacity( m_MeshSelected , m_Opacity );
    DisplayUpdate();
}

void distanceGui::ChangeValueSmoothing()
{

}

// change the value of the position of the camera
void distanceGui::buttonFrontClicked()
{
    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = 1;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdate();
}

void distanceGui::buttonBackClicked()
{
    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = -1;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdate();
}

void distanceGui::buttonRightClicked()
{
    m_CameraX = 1 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdate();
}

void distanceGui::buttonLeftClicked()
{
    m_CameraX = -1 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdate();
}

void distanceGui::buttonUpClicked()
{
    m_CameraX = 0 ; m_CameraY = -1 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdate();
}

void distanceGui::buttonDownClicked()
{
    m_CameraX = 0 ; m_CameraY = 1 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdate();
}


// display the two files selected on the box "meshWidget"
void distanceGui::DisplayInit()
{
    if( m_NumberOfMesh > 0)
    {
       m_MyWindowMesh.setMeshWidget( m_WidgetMesh );

        // list, links, init and update
       m_MyWindowMesh.setMeshList( m_NumberOfMesh , m_MeshList );
       m_MyWindowMesh.createLinks();
       m_MyWindowMesh.windowInit();
       m_MyWindowMesh.windowUpdate();
    }
}

void distanceGui::DisplayUpdate()
{
    if( m_NumberOfMesh > 0)
    {
        m_MyWindowMesh.windowUpdate();
    }
}



// apply the good calculated distance
void distanceGui::ApplyDistance()
{
    switch( m_ChoiceOfError )
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



