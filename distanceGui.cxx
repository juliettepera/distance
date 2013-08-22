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

    // connections
    QObject::connect( pushButtonLoad , SIGNAL( clicked() ) , this , SLOT( OpenBrowseWindow() ) );
    QObject::connect( pushButtonDisplay , SIGNAL( clicked() ) , this , SLOT( DisplayInit() ) );
    QObject::connect( pushButtonFront , SIGNAL( clicked() ) , this , SLOT( buttonFrontClicked() ) );
    QObject::connect( pushButtonBack , SIGNAL( clicked() ) , this , SLOT( buttonBackClicked() ) );
    QObject::connect( pushButtonRight , SIGNAL( clicked() ) , this , SLOT( buttonRightClicked() ) );
    QObject::connect( pushButtonLeft , SIGNAL( clicked() ) , this , SLOT( buttonLeftClicked() ) );
    QObject::connect( pushButtonUp , SIGNAL( clicked() ) , this , SLOT( buttonUpClicked() ) );
    QObject::connect( pushButtonDown , SIGNAL( clicked() ) , this , SLOT( buttonDownClicked() ) );
    QObject::connect( pushButtonApply , SIGNAL( clicked() ) , this , SLOT( ApplyDistance() ) );
    QObject::connect( pushButtonDelete , SIGNAL( clicked() ) , this , SLOT( DisplayReset() ) );
    QObject::connect( pushButtonHide , SIGNAL( clicked() ) , this , SLOT( HideOne() ) );
    QObject::connect( pushButtonQuit , SIGNAL( clicked() ) , qApp , SLOT( quit() ) );
    QObject::connect( pushButtonRefresh , SIGNAL( clicked() ) , this , SLOT( ApplySmoothing() ) );

    QObject::connect( horizontalSliderOpacity , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacity() ) );
    QObject::connect( horizontalSliderColor , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueColor() ) );

    QObject::connect( spinBoxSmoothing , SIGNAL( valueChanged( int ) ) , this , SLOT( ChangeValueSmoothing() ) );

    QObject::connect( checkBoxSmoothing , SIGNAL( stateChanged( int ) ) , this , SLOT( DisableAll() ) );

    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( ChangeMeshSelected() ) );

    QObject::connect( radioButtonAtoB , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );
    QObject::connect( radioButtonBtoA , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );
    QObject::connect( radioButtonBoth , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );

    DisableDisplay( true );
    DisableParameters( true );
    DisableCamera( true );
    DisableDistance( true );
                                                                              
}

void distanceGui::OpenBrowseWindow()
{
    QString browseMesh = QFileDialog::getOpenFileName( this , "Open a VTK file" , QString() , "vtk mesh (*.vtk)" );

    if( !browseMesh.isEmpty() )
    {
      lineEditLoad -> setText( browseMesh );
    }
    if( !lineEditLoad->text().isEmpty() )
    {
        m_MeshList.push_back( ( lineEditLoad -> text() ).toStdString() );
        m_NumberOfMesh = m_MeshList.size();

        listWidgetLoadedMesh -> addItem( ( lineEditLoad -> text() ).toStdString().c_str() );

        m_OpacityList.push_back( 1.0 );
        m_ColorList.push_back( 1.0 );
        m_NumberOfIterationList.push_back( 100 );
        m_DoSmoothList.push_back( false );
    }
        DisableDisplay( false );
        pushButtonHide -> setDisabled( true );

    browseMesh.clear();
    lineEditLoad->clear();
}

void distanceGui::DisplayInit()
{
    if( m_NumberOfDisplay > 0 )
    {
        m_MyWindowMesh.windowClear();

        horizontalSliderColor -> setSliderPosition( horizontalSliderColor -> maximum() );
        lcdNumberColor -> display( horizontalSliderColor -> maximum()  );

        horizontalSliderOpacity -> setSliderPosition( horizontalSliderOpacity -> maximum() );
        lcdNumberOpacity -> display( horizontalSliderOpacity -> maximum()  );

        spinBoxSmoothing -> setValue( spinBoxSmoothing -> maximum() );
        checkBoxSmoothing -> setChecked( false );
    }
    else
    {
        std::cout << " height " << scrollAreaMesh -> height() << std::endl;
        std::cout << " width " << scrollAreaMesh -> width() << std::endl;
        m_MyWindowMesh.setSizeH(  scrollAreaMesh -> height()  );
        m_MyWindowMesh.setSizeW( scrollAreaMesh -> width() );
        m_MyWindowMesh.setMeshWidget( m_WidgetMesh );
    }

    m_MyWindowMesh.createTools( m_NumberOfMesh , m_MeshList );
    m_MyWindowMesh.windowInit();
    m_MyWindowMesh.windowUpdate();

    m_NumberOfDisplay++;

    DisableCamera( false );

    if( m_NumberOfMesh >= 2 )
    {
        DisableDistance( false );
    }

    DisableDisplay( false );
    pushButtonHide -> setDisabled( true );
    DisableParameters( true );
}

void distanceGui::DisplayReset()
{
    m_MyWindowMesh.windowClear();

    m_NumberOfDisplay = 0;
    m_NumberOfMesh = 0;

    horizontalSliderColor -> setSliderPosition( horizontalSliderColor -> maximum() );
    lcdNumberColor -> display( horizontalSliderColor -> maximum()  );

    horizontalSliderOpacity -> setSliderPosition( horizontalSliderOpacity -> maximum() );
    lcdNumberOpacity -> display( horizontalSliderOpacity -> maximum()  );

    spinBoxSmoothing -> setValue( spinBoxSmoothing -> maximum() );
    checkBoxSmoothing -> setChecked( false );

    listWidgetLoadedMesh -> clear();
    m_MeshList.clear();
    m_OpacityList.clear();
    m_ColorList.clear();
    m_NumberOfIterationList.clear();
    m_DoSmoothList.clear();

    m_MyWindowMesh.windowUpdate();

    DisableCamera( true );
    DisableDisplay( true );
    DisableDistance( true );
    DisableParameters( true );
}

void distanceGui::HideOne()
{
    std::cout << " deleteTool " << std::endl;
    m_MyWindowMesh.hideOne( m_MeshSelected );
    m_MyWindowMesh.windowUpdate();

}

void distanceGui::DisplayUpdateCamera()
{
    m_MyWindowMesh.updatePositionCamera();
    m_MyWindowMesh.windowUpdate();
}

void distanceGui::ChangeMeshSelected()
{
   m_MeshSelected = listWidgetLoadedMesh -> currentRow();

   horizontalSliderColor -> setValue( m_ColorList[ m_MeshSelected ]*100 );
   lcdNumberColor -> display( m_ColorList[ m_MeshSelected ] );

   horizontalSliderOpacity -> setValue( m_OpacityList[ m_MeshSelected ]*100 );
   lcdNumberOpacity -> display( m_OpacityList[ m_MeshSelected ] );

   spinBoxSmoothing -> setValue( m_NumberOfIterationList[ m_MeshSelected ] );
   checkBoxSmoothing -> setChecked( m_DoSmoothList[ m_MeshSelected ] );

   DisableParameters( false );
   pushButtonHide -> setDisabled( false );
}

void distanceGui::ChangeValueOpacity()
{
    m_OpacityList[ m_MeshSelected ] = horizontalSliderOpacity -> value()/100.;
    lcdNumberOpacity -> display( m_OpacityList[ m_MeshSelected ] );

    m_MyWindowMesh.setOpacity( m_MeshSelected , m_OpacityList[ m_MeshSelected ] );

    m_MyWindowMesh.updateOpacity();
    m_MyWindowMesh.windowUpdate();
}

void distanceGui::ChangeValueColor()
{
    m_ColorList[ m_MeshSelected ] = horizontalSliderColor -> value()/100.;
    lcdNumberColor -> display( m_ColorList[ m_MeshSelected ] );

    m_MyWindowMesh.setColor( m_MeshSelected , ( 1.0 - m_ColorList[ m_MeshSelected ] ) , 1.0 , m_ColorList[ m_MeshSelected ] );

    m_MyWindowMesh.updateColor();
    m_MyWindowMesh.windowUpdate();
}

void distanceGui::ChangeValueSmoothing()
{
    m_NumberOfIterationList[ m_MeshSelected ] = spinBoxSmoothing -> value();
    m_MyWindowMesh.setNumberOfIteration( m_MeshSelected , m_NumberOfIterationList[ m_MeshSelected ] );

    DisableCamera( true );
    DisableDisplay( true );
    DisableParameters( true );
    DisableDistance( true );

    pushButtonRefresh -> setDisabled( false );
    checkBoxSmoothing -> setDisabled( false );
    spinBoxSmoothing -> setDisabled( false );
}

void distanceGui::ApplySmoothing()
{
   if( checkBoxSmoothing -> isChecked() )
   {
       m_DoSmoothList[ m_MeshSelected ] = true;
   }
   else
   {
       m_DoSmoothList[ m_MeshSelected ] = false;
   }
   m_MyWindowMesh.setSmoothing( m_MeshSelected , m_DoSmoothList[ m_MeshSelected ] );

   m_MyWindowMesh.updateSmoothing();
   m_MyWindowMesh.windowUpdate();

   DisableCamera( false );
   DisableDisplay( false );
   DisableParameters( false );
   DisableDistance( false );

}

void distanceGui::buttonUpClicked()
{
    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = 1;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonDownClicked()
{
    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = -1;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonRightClicked()
{
    m_CameraX = 1 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonLeftClicked()
{
    m_CameraX = -1 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonBackClicked()
{
    m_CameraX = 0 ; m_CameraY = -1 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

void distanceGui::buttonFrontClicked()
{
    m_CameraX = 0 ; m_CameraY = 1 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );

    DisplayUpdateCamera();
}

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

void distanceGui::ApplyDistance()
{
    switch( m_ChoiceOfError )
    {
        case 0:
            std::cout << std::endl << "you have to select the distance you want to compute " << std::endl;
            break;

        case 1:
            m_MyCompute.computeDistanceAtoB();
            break;

        case 2:
            m_MyCompute.computeDistanceBtoA();
            break;

        case 3:
            m_MyCompute.computeDistanceBoth();
            break;
    }
}

void distanceGui::DisableDisplay( bool EnableOrNot )
{
    pushButtonDisplay -> setDisabled( EnableOrNot );
    pushButtonDelete -> setDisabled( EnableOrNot );
    pushButtonHide -> setDisabled( EnableOrNot );
}

void distanceGui::DisableParameters( bool EnableOrNot)
{
    horizontalSliderColor -> setDisabled( EnableOrNot );
    horizontalSliderOpacity -> setDisabled( EnableOrNot );
    spinBoxSmoothing -> setDisabled( EnableOrNot );
    checkBoxSmoothing -> setDisabled( EnableOrNot );
    pushButtonRefresh -> setDisabled( EnableOrNot );
}

void distanceGui::DisableCamera( bool EnableOrNot )
{
    pushButtonUp -> setDisabled( EnableOrNot );
    pushButtonDown -> setDisabled( EnableOrNot );
    pushButtonRight -> setDisabled( EnableOrNot );
    pushButtonLeft -> setDisabled( EnableOrNot );
    pushButtonFront -> setDisabled( EnableOrNot );
    pushButtonBack -> setDisabled( EnableOrNot );
}

void distanceGui::DisableDistance( bool EnableOrNot )
{
    comboBoxMeshA -> setDisabled( EnableOrNot );
    comboBoxMeshB -> setDisabled( EnableOrNot );
    radioButtonAtoB -> setDisabled( EnableOrNot );
    radioButtonBtoA -> setDisabled( EnableOrNot );
    radioButtonBoth -> setDisabled( EnableOrNot );
    doubleSpinBoxMinSampFreq -> setDisabled( EnableOrNot );
    doubleSpinBoxSampStep -> setDisabled( EnableOrNot );
    pushButtonApply -> setDisabled( EnableOrNot );
}

void distanceGui::DisableAll()
{
    DisableCamera( true );
    DisableDisplay( true );
    DisableDistance( true );
    DisableParameters( true );

    pushButtonRefresh -> setDisabled( false );
    spinBoxSmoothing -> setDisabled( false );
    checkBoxSmoothing -> setDisabled( false );
}
