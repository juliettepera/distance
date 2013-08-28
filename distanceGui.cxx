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

    //m_MySmoothing.setParent( parentWidget() );

    // shortcuts
    actionAddNewFile -> setShortcut( QKeySequence("Ctrl+A") );
    actionAddNewRepository -> setShortcut( QKeySequence("Ctrl+R") );
    actionSmoothing -> setShortcut( QKeySequence("Ctrl+M") );
    actionSaveFile -> setShortcut( QKeySequence("Ctrl+S") );
    actionQuit -> setShortcut( QKeySequence("Ctrl+Q") );

    // icones
    m_visible = QIcon("/work/jpera/distance/visible.png");
    m_unvisble = QIcon("/work/jpera/distance/unvisible.png");

    // connections
    QObject::connect( actionAddNewFile , SIGNAL( triggered() ) , this , SLOT( OpenBrowseWindowFile() ) );
    QObject::connect( actionAddNewRepository , SIGNAL( triggered() ) , this , SLOT( OpenBrowseWindowRepository() ) );
    QObject::connect( actionSmoothing , SIGNAL( triggered() ) , this , SLOT( OpenSmoothingWindow() ) );
    QObject::connect( actionQuit , SIGNAL( triggered() ) , qApp , SLOT( quit() ) );

    QObject::connect( pushButtonDisplay , SIGNAL( clicked() ) , this , SLOT( DisplayInit() ) );
    QObject::connect( pushButtonFront , SIGNAL( clicked() ) , this , SLOT( buttonFrontClicked() ) );
    QObject::connect( pushButtonBack , SIGNAL( clicked() ) , this , SLOT( buttonBackClicked() ) );
    QObject::connect( pushButtonRight , SIGNAL( clicked() ) , this , SLOT( buttonRightClicked() ) );
    QObject::connect( pushButtonLeft , SIGNAL( clicked() ) , this , SLOT( buttonLeftClicked() ) );
    QObject::connect( pushButtonUp , SIGNAL( clicked() ) , this , SLOT( buttonUpClicked() ) );
    QObject::connect( pushButtonDown , SIGNAL( clicked() ) , this , SLOT( buttonDownClicked() ) );

    QObject::connect( pushButtonApply , SIGNAL( clicked() ) , this , SLOT( ApplyDistance() ) );
    QObject::connect( pushButtonDelete , SIGNAL( clicked() ) , this , SLOT( DisplayReset() ) );

    QObject::connect( horizontalSliderOpacity , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacity() ) );
    QObject::connect( horizontalSliderColor , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueColor() ) );

    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( ChangeMeshSelected() ) );

    QObject::connect( radioButtonAtoB , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );
    QObject::connect( radioButtonBtoA , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );
    QObject::connect( radioButtonBoth , SIGNAL( clicked() ) , this , SLOT( ChangeValueChoice() ) );

}

void distanceGui::OpenBrowseWindowFile()
{
    QStringList browseMesh = QFileDialog::getOpenFileNames( this , "Open a VTK file" , QString() , "vtk mesh (*.vtk)" );
    QLineEdit *lineEditLoad = new QLineEdit;

    if( !browseMesh.isEmpty() )
    {
      for( int i =0 ; i<browseMesh.size() ; i++ )
      {
          lineEditLoad -> setText( browseMesh[ i ] );

        if( !lineEditLoad->text().isEmpty() )
        {
            m_MeshList.push_back( ( lineEditLoad -> text() ).toStdString() );
            m_NumberOfMesh = m_MeshList.size();

            listWidgetLoadedMesh -> addItem( ( lineEditLoad -> text() ).toStdString().c_str() );
            listWidgetLoadedMesh -> item( m_NumberOfMesh - 1 ) -> setIcon( m_unvisble );

            m_OpacityList.push_back( 1.0 );
            m_ColorList.push_back( 1.0 );
        }
      }
    }
        browseMesh.clear();
        lineEditLoad -> deleteLater();
}

void distanceGui::OpenBrowseWindowRepository()
{
   /* QString browseMesh = QFileDialog::getExistingDirectory( this , tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QLineEdit *lineEditLoad = new QLineEdit;

    if( !browseMesh.isEmpty() )
    {

      lineEditLoad -> setText( browseMesh );

        if( !lineEditLoad->text().isEmpty() )
        {
            m_MeshList.push_back( ( lineEditLoad -> text() ).toStdString() );
            m_NumberOfMesh = m_MeshList.size();

            listWidgetLoadedMesh -> addItem( ( lineEditLoad -> text() ).toStdString().c_str() );

            m_OpacityList.push_back( 1.0 );
            m_ColorList.push_back( 1.0 );
        }
    }
    browseMesh.clear();
    lineEditLoad -> deleteLater();*/
}

void distanceGui::OpenSmoothingWindow()
{
    if( !m_MeshList.empty() )
    {
        m_MySmoothing.setMeshList( m_MeshList );
        m_MySmoothing.setWindow( m_MyWindowMesh );
        m_MySmoothing.initialization();
        m_MySmoothing.show();
    }
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
    }
    else
    {
        m_MyWindowMesh.setSizeH(  scrollAreaMesh -> height()  );
        m_MyWindowMesh.setSizeW( scrollAreaMesh -> width() );
        m_MyWindowMesh.setMeshWidget( m_WidgetMesh );
    }

    m_MyWindowMesh.createTools( m_NumberOfMesh , m_MeshList );
    m_MyWindowMesh.windowInit();
    m_MyWindowMesh.windowUpdate();

    m_NumberOfDisplay++;

    ChangeIcon( m_visible );
}

void distanceGui::DisplayReset()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 )
    {
        m_MyWindowMesh.windowClear();

        m_NumberOfDisplay = 0;
        m_NumberOfMesh = 0;

        horizontalSliderColor -> setSliderPosition( horizontalSliderColor -> maximum() );
        lcdNumberColor -> display( horizontalSliderColor -> maximum()  );

        horizontalSliderOpacity -> setSliderPosition( horizontalSliderOpacity -> maximum() );
        lcdNumberOpacity -> display( horizontalSliderOpacity -> maximum()  );

        listWidgetLoadedMesh -> clear();
        m_MeshList.clear();
        m_OpacityList.clear();
        m_ColorList.clear();
        m_MyWindowMesh.windowUpdate();
    }
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
}

void distanceGui::ChangeValueOpacity()
{
    m_OpacityList[ m_MeshSelected ] = horizontalSliderOpacity -> value()/100.;
    lcdNumberOpacity -> display( m_OpacityList[ m_MeshSelected ] );

    m_MyWindowMesh.setOpacity( m_MeshSelected , m_OpacityList[ m_MeshSelected ] );

    if( m_OpacityList[ m_MeshSelected ] == 0 )
    {
        ChangeIcon( m_unvisble , m_MeshSelected );
    }
    else
    {
        ChangeIcon( m_visible , m_MeshSelected );
    }

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
}

void distanceGui::DisableParameters( bool EnableOrNot)
{
    horizontalSliderColor -> setDisabled( EnableOrNot );
    horizontalSliderOpacity -> setDisabled( EnableOrNot );
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
}

void distanceGui::ChangeIcon( QIcon Icon )
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh ++ )
    {
        listWidgetLoadedMesh -> item( IndiceOfMesh ) -> setIcon( Icon );
    }
}

void distanceGui::ChangeIcon( QIcon Icon , int IndiceOfMesh )
{
        listWidgetLoadedMesh -> item( IndiceOfMesh ) -> setIcon( Icon );
}
