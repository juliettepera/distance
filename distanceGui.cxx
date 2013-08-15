// My libraries
#include "distanceGui.h"

distanceGui::distanceGui(QWidget * parent , Qt::WFlags f  ): QMainWindow(parent, f)
{
    // to display the window
    setupUi(this);

    // initialisations
    m_NumberOfMesh = 0;
    m_ChoiceOfError = 0;
    m_MeshSelected = 0;
    m_NumberOfDisplay = 0;
    m_WidgetMesh = new QVTKWidget( this -> scrollAreaMesh );
    m_Smoothing = false;

    // connections
    QObject::connect( pushButtonLoad , SIGNAL( clicked() ) , this , SLOT( OpenBrowseWindow() ) ); // load a new mesh
    QObject::connect( pushButtonDisplay , SIGNAL( clicked() ) , this , SLOT( DisplayInit() ) ); // initialize the display
    QObject::connect( pushButtonFront , SIGNAL( clicked() ) , this , SLOT( buttonFrontClicked() ) ); // set the position of the camera
    QObject::connect( pushButtonBack , SIGNAL( clicked() ) , this , SLOT( buttonBackClicked() ) );
    QObject::connect( pushButtonRight , SIGNAL( clicked() ) , this , SLOT( buttonRightClicked() ) );
    QObject::connect( pushButtonLeft , SIGNAL( clicked() ) , this , SLOT( buttonLeftClicked() ) );
    QObject::connect( pushButtonUp , SIGNAL( clicked() ) , this , SLOT( buttonUpClicked() ) );
    QObject::connect( pushButtonDown , SIGNAL( clicked() ) , this , SLOT( buttonDownClicked() ) );
    QObject::connect( pushButtonApply , SIGNAL( clicked() ) , this , SLOT( ApplyDistance() ) ); // compute the distance error
    QObject::connect( pushButtonReset , SIGNAL( clicked() ) , this , SLOT( DisplayReset() ) ); // reset the window
    QObject::connect( pushButtonQuit , SIGNAL( clicked() ) , qApp , SLOT( quit() ) ); // quit the application

    QObject::connect( horizontalSliderOpacity , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacity() ) ); // change the value of the opacity of one mesh
    QObject::connect( horizontalSliderColor , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueColor() ) ); // change the value of the color of one mesh

    QObject::connect( checkBoxSmoothing , SIGNAL( stateChanged(int) ) , this , SLOT( ApplySmoothing() ) );

    QObject::connect( radioButtonAtoB , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) ); // change the type of error computed
    QObject::connect( radioButtonBtoA , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );
    QObject::connect( radioButtonBoth , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );


                                                                              
}

void distanceGui::OpenBrowseWindow()
{
    std::cout << "in distanceGui : OpenBrowseWindow " << std::endl;

    QString browseMesh = QFileDialog::getOpenFileName( this , "Open a VTK file" , QString() , "vtk mesh (*.vtk)" );

    if( !browseMesh.isEmpty() )
    {
      lineEditLoad -> setText( browseMesh );
    }

    m_MeshList.push_back( ( lineEditLoad -> text() ).toStdString() );

    m_NumberOfMesh = m_MeshList.size();

    m_OpacityList.push_back( 1.0 );

    m_ColorList.push_back( 1.0 );

    listWidgetLoadedMesh -> addItem( new QListWidgetItem( "blabla " ) );
}

void distanceGui::DisplayInit()
{
    std::cout << "in distanceGui : DisplayInit " << std::endl;

    if( m_NumberOfDisplay > 0 )
    {
        std::cout << " clearing  : " << m_NumberOfDisplay << std::endl;
        m_MyWindowMesh.windowClear();
    }
    else
    {
        m_MyWindowMesh.setMeshWidget( m_WidgetMesh );
    }

    m_MyWindowMesh.createTools( m_NumberOfMesh , m_MeshList );
    m_MyWindowMesh.windowInit();
    m_MyWindowMesh.windowUpdate();

    m_NumberOfDisplay++;
}

void distanceGui::DisplayReset()
{
    std::cout << "in distanceGui : DisplayReset " << std::endl;

    m_MyWindowMesh.windowClear();

    m_NumberOfDisplay = 0;
    m_NumberOfMesh = 0;

    horizontalSliderColor -> setSliderPosition( horizontalSliderColor -> maximum() );
    horizontalSliderOpacity -> setSliderPosition( horizontalSliderOpacity -> maximum() );

    listWidgetLoadedMesh -> clear();
    m_MeshList.clear();
    m_OpacityList.clear();
    m_ColorList.clear();

    m_MyWindowMesh.windowUpdate();

}

void distanceGui::DisplayUpdateCamera()
{
    std::cout << "in distanceGui : DistanceUpdateCamera " << std::endl;

    if( m_NumberOfMesh > 0)
    {
        m_MyWindowMesh.updatePositionCamera();
        m_MyWindowMesh.windowUpdate();
    }
}


void distanceGui::ChangeMeshSelected()
{
   std::cout << "in distanceGui : ChangeMeshSelected " << std::endl;

   int Row = listWidgetLoadedMesh -> row( listWidgetLoadedMesh -> selectedItems().at(0) );

   std::cout << " index de selection : " << Row << std::endl;

}

void distanceGui::ChangeValueOpacity()
{
    std::cout << "in distanceGui : ChangeValueOpacity " << std::endl;

    m_OpacityList[ m_MeshSelected ] = horizontalSliderOpacity -> value()/100.;

    m_MyWindowMesh.setOpacity( m_MeshSelected , m_OpacityList[ m_MeshSelected ] );

    m_MyWindowMesh.updateOpacity();
    m_MyWindowMesh.windowUpdate();
}

void distanceGui::ChangeValueColor()
{
    std::cout << "in distanceGui : ChangeValueColor " << std::endl;

    m_ColorList[ m_MeshSelected ] = horizontalSliderColor -> value()/100.;

    m_MyWindowMesh.setColor( m_MeshSelected , 0.0 , 1.0 , m_ColorList[ m_MeshSelected ] );

    m_MyWindowMesh.updateColor();
    m_MyWindowMesh.windowUpdate();

}


void distanceGui::buttonUpClicked()
{
    std::cout << "in distanceGui : Up " << std::endl;

    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = 1;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonDownClicked()
{
    std::cout << "in distanceGui : Down " << std::endl;

    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = -1;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonRightClicked()
{
    std::cout << "in distanceGui : Right " << std::endl;

    m_CameraX = 1 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonLeftClicked()
{
    std::cout << "in distanceGui : Left " << std::endl;

    m_CameraX = -1 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonBackClicked()
{
    std::cout << "in distanceGui : Back " << std::endl;

    m_CameraX = 0 ; m_CameraY = -1 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonFrontClicked()
{
    std::cout << "in distanceGui : Front " << std::endl;

    m_CameraX = 0 ; m_CameraY = 1 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}


void distanceGui::ApplySmoothing()
{
   std::cout << "in distanceGui : ApplySmoothing " << std::endl;
   if( checkBoxSmoothing -> isChecked() )
   {
       m_Smoothing = true;
   }
   else
   {
       m_Smoothing = false;
   }
}


void distanceGui::ChangeValueChoice()
{
    std::cout << "in distanceGui : ChangeValueChoice " << std::endl;

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

void distanceGui::ApplyDistance()
{
    std::cout << "in distanceGui : ApplyDistance " << std::endl;

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




