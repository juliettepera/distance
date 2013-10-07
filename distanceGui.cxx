// My libraries
#include "distanceGui.h"

distanceGui::distanceGui(QWidget * parent , Qt::WFlags f  , std::string WorkDirectory ): QMainWindow(parent, f)
{
    // to display the window
    setupUi(this);

    // initialisations
    m_NumberOfMesh = 0;
    m_MeshSelected = -1;
    m_NumberOfDisplay = 0;

    m_WidgetMesh = new QVTKWidget( this -> scrollAreaMesh );

    m_SelectedItemA = -1;
    m_SelectedItemB = -1;

    m_WorkDirectory = WorkDirectory;
    m_WorkDirectory.erase( m_WorkDirectory.length() - 9 , 9 );

    m_ComputedData = vtkSmartPointer <vtkPolyData>::New();
    m_Lut = vtkSmartPointer <vtkColorTransferFunction>::New();

    // shortcuts
    actionAddNewFile -> setShortcut( QKeySequence("Ctrl+A") );
    actionAddNewRepository -> setShortcut( QKeySequence("Ctrl+R") );
    actionSmoothing -> setShortcut( QKeySequence("Ctrl+M") );
    actionDownSampling -> setShortcut( QKeySequence("Ctrl+D") );
    actionSaveFile -> setShortcut( QKeySequence("Ctrl+S") );
    actionQuit -> setShortcut( QKeySequence("Ctrl+Q") );

    // icones  
    InitIcon();

    // connections
    QObject::connect( actionAddNewFile , SIGNAL( triggered() ) , this , SLOT( OpenBrowseWindowFile() ) );
    QObject::connect( actionAddNewRepository , SIGNAL( triggered() ) , this , SLOT( OpenBrowseWindowRepository() ) );
    QObject::connect( actionSmoothing , SIGNAL( triggered() ) , this , SLOT( OpenSmoothingWindow() ) );
    QObject::connect( actionDownSampling , SIGNAL( triggered() ) , this , SLOT( OpenDownSamplingWindow() ) );
    QObject::connect( actionQuit , SIGNAL( triggered() ) , qApp , SLOT( quit() ) );

    QObject::connect( pushButtonFront , SIGNAL( clicked() ) , this , SLOT( buttonFrontClicked() ) );
    QObject::connect( pushButtonBack , SIGNAL( clicked() ) , this , SLOT( buttonBackClicked() ) );
    QObject::connect( pushButtonRight , SIGNAL( clicked() ) , this , SLOT( buttonRightClicked() ) );
    QObject::connect( pushButtonLeft , SIGNAL( clicked() ) , this , SLOT( buttonLeftClicked() ) );
    QObject::connect( pushButtonUp , SIGNAL( clicked() ) , this , SLOT( buttonUpClicked() ) );
    QObject::connect( pushButtonDown , SIGNAL( clicked() ) , this , SLOT( buttonDownClicked() ) );
    QObject::connect( pushButtonApply , SIGNAL( clicked() ) , this , SLOT( ApplyDistance() ) );
    QObject::connect( pushButtonDelete , SIGNAL( clicked() ) , this , SLOT( DisplayReset() ) );
    QObject::connect( pushButtonColor , SIGNAL( clicked() ) , this , SLOT( ChooseColor() ) );
    QObject::connect( pushButtonAdd , SIGNAL( clicked() ) , this , SLOT( OpenBrowseWindowFile() ) );
    QObject::connect( pushButtonDeleteOne , SIGNAL( clicked() ) , this , SLOT( DeleteOneFile() ) );
    QObject::connect( pushButtonDisplayAll , SIGNAL( clicked() ) , this , SLOT( DisplayAll() ) );
    QObject::connect( pushButtonHideAll , SIGNAL( clicked() ) , this , SLOT( HideAll() ) );


    QObject::connect( doubleSpinBoxMinSampFreq , SIGNAL( valueChanged( double ) ) , this , SLOT( ChangeMinSampleFrequency() ) );
    QObject::connect( doubleSpinBoxSampStep , SIGNAL( valueChanged( double ) ) , this , SLOT( ChangeSamplingStep() ) );

    QObject::connect( horizontalSliderOpacity , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacity() ) );

    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( ChangeMeshSelected() ) );

    QObject::connect( comboBoxMeshB , SIGNAL( activated( int ) ) , this , SLOT( SelectMeshB() ) );

    QObject::connect( checkBoxSignedDistance , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeSignedDistance() ) );
    QObject::connect( checkBoxError , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeDisplayError() ) );

    QObject::connect( radioButtonSurface , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeTypeOfDisplay() ) );
    QObject::connect( radioButtonPoints , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeTypeOfDisplay() ) );
    QObject::connect( radioButtonWireframe , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeTypeOfDisplay() ) );

}


//************************************ LOADING FILES ************************************************
void distanceGui::OpenBrowseWindowFile()
{
    QStringList browseMesh = QFileDialog::getOpenFileNames( this , "Open a VTK file" , QString() , "vtk mesh (*.vtk)" );
    QLineEdit *lineEditLoad = new QLineEdit;

    if( ! browseMesh.isEmpty() )
    {
      for( int i = 0 ; i < browseMesh.size() ; i++ )
      {
          lineEditLoad -> setText( browseMesh[ i ] );

        if( !lineEditLoad->text().isEmpty() )
        {
            m_MeshList.push_back( ( lineEditLoad -> text() ).toStdString() );
            m_NumberOfMesh++;

            QFileInfo File = ( lineEditLoad -> text() );

            listWidgetLoadedMesh -> addItem( File.fileName().toStdString().c_str() );
            listWidgetLoadedMesh -> item( m_NumberOfMesh - 1 ) -> setIcon( m_UnvisibleIcon );

            comboBoxMeshB -> addItem( m_NotOkIcon , File.fileName().toStdString().c_str() );

            m_OpacityList.push_back( 1.0 );
            m_SignedDistanceList.push_back( false );
            m_MinSampleFrequencyList.push_back( 0.5 );
            m_SamplingStepList.push_back( 2 );
            m_DisplayErrorList.push_back( -1 );
            m_DisplayTypeList.push_back( 1 );

            m_MyWindowMesh.addTool( m_MeshList[ m_NumberOfMesh-1 ] );
            m_MySmoothing.addOne( File.fileName().toStdString() );
            m_MyDownSampling.addOne( File.fileName().toStdString() );

        }
      }
    }

    browseMesh.clear();
    delete lineEditLoad;

    DisplayInit();

}

void distanceGui::OpenBrowseWindowRepository()
{
    QString path;
    QString dir = QFileDialog::getExistingDirectory( this , tr("Open .vtk Directory") , path , QFileDialog::ShowDirsOnly );

    if( !dir.isEmpty() )
    {

        QDir vtkDir( dir );
        vtkDir.setFilter( QDir::NoDotAndDotDot | QDir::Files );
        vtkDir.setNameFilters( QStringList() << "*.vtk" );

        QList <QFileInfo > FileList;
        FileList.append( vtkDir.entryInfoList() );

        for ( int i = 0 ; i < FileList.size() ; i++ )
        {
            QString FileName = FileList.at(i).canonicalFilePath();

            if ( !FileName.endsWith(".vtk") )
            {
                FileList.removeAt(i);
                i--;
            }
        }

        for( int i = 0 ; i < FileList.size() ; i++ )
        {
            m_MeshList.push_back( FileList.at(i).canonicalFilePath().toStdString().c_str()  );
            std::cout << FileList.at(i).canonicalFilePath().toStdString().c_str() << std::endl;
            m_NumberOfMesh++;

            listWidgetLoadedMesh -> addItem( FileList.at(i).fileName().toStdString().c_str() );
            listWidgetLoadedMesh -> item( m_NumberOfMesh - 1 ) -> setIcon( m_UnvisibleIcon );

            comboBoxMeshB -> addItem( m_NotOkIcon , FileList.at(i).fileName().toStdString().c_str() );

            m_OpacityList.push_back( 1.0 );
            m_SignedDistanceList.push_back( false );
            m_MinSampleFrequencyList.push_back( 0.5 );
            m_SamplingStepList.push_back( 2 );
            m_DisplayErrorList.push_back( -1 );
            m_DisplayTypeList.push_back( 1 );

            m_MyWindowMesh.addTool( m_MeshList[ m_NumberOfMesh-1 ] );
            m_MySmoothing.addOne( FileList.at(i).fileName().toStdString() );
            m_MyDownSampling.addOne( FileList.at(i).fileName().toStdString() );

        }

        FileList.clear();
    }

    DisplayInit();
}

//************************************ SELECTING FILES ************************************************
void distanceGui::ChangeMeshSelected()
{
   m_MeshSelected = listWidgetLoadedMesh -> currentRow();
   horizontalSliderOpacity -> setValue( m_OpacityList[ m_MeshSelected ]*100 );
   lcdNumberOpacity -> display( m_OpacityList[ m_MeshSelected ] );
   doubleSpinBoxMinSampFreq -> setValue( m_MinSampleFrequencyList[ m_MeshSelected ] );
   doubleSpinBoxSampStep -> setValue( m_SamplingStepList[ m_MeshSelected ] );
   checkBoxSignedDistance -> setChecked( m_SignedDistanceList[ m_MeshSelected ] );
   m_ActivTool = m_MyWindowMesh.getTool( m_MeshSelected );

   if( m_DisplayTypeList[ m_MeshSelected ] == 1 )
   {
       radioButtonSurface -> setChecked( true );
   }
   else if( m_DisplayTypeList[ m_MeshSelected ] == 2 )
   {
       radioButtonPoints -> setChecked( true );
   }
   else if( m_DisplayTypeList[ m_MeshSelected ] == 3 )
   {
       radioButtonWireframe -> setChecked( true );
   }

   if( m_DisplayErrorList[ m_MeshSelected ] == 0 )
   {
        checkBoxError -> setEnabled( true );
        checkBoxError -> setChecked( false );
   }
   if( m_DisplayErrorList[ m_MeshSelected ] == 1 )
   {
        checkBoxError -> setEnabled( true );
        checkBoxError -> setChecked( true );
   }
   if( m_DisplayErrorList[ m_MeshSelected ] == -1 )
   {
        checkBoxError -> setEnabled( false );
        checkBoxError -> setChecked( false );
   }

   AvailableMesh();

   if( m_NumberOfMesh >= 2 )
   {
       groupBoxDistance -> setEnabled( true );
   }
   groupBoxParameters -> setEnabled( true );
}

void distanceGui::InitIcon()
{
    std::string visible = m_WorkDirectory;
    visible += "/icons/visible.png";

    std::string unvisible = m_WorkDirectory;
    unvisible += "/icons/unvisible.png";

    std::string ok = m_WorkDirectory;
    ok += "/icons/ok.jpeg";

    std::string notok = m_WorkDirectory;
    notok += "/icons/NotOk.jpeg";

    std::string plus = m_WorkDirectory;
    plus += "/icons/plus.png";

    std::string minus = m_WorkDirectory;
    minus += "/icons/minus.png";

    std::string deleteAll = m_WorkDirectory;
    deleteAll += "/icons/deleteAll.jpeg";

    std::string display = m_WorkDirectory;
    display += "/icons/display.jpeg";

    m_Visible = QString::fromStdString( visible );
    m_Unvisible = QString::fromStdString( unvisible );
    m_Ok = QString::fromStdString( ok );
    m_NotOk = QString::fromStdString( notok );
    m_Plus = QString::fromStdString( plus );
    m_Minus = QString::fromStdString( minus );
    m_Delete = QString::fromStdString( deleteAll );
    m_Display = QString::fromStdString( display );

    m_VisibleIcon = QIcon( m_Visible );
    m_UnvisibleIcon = QIcon( m_Unvisible );
    m_OkIcon = QIcon( m_Ok );
    m_NotOkIcon = QIcon( m_NotOk );
    m_PlusIcon = QIcon( m_Plus );
    m_MinusIcon = QIcon( m_Minus );
    m_DeleteIcon = QIcon( m_Delete );
    m_DisplayIcon = QIcon( m_Display );

    pushButtonAdd -> setIcon( m_PlusIcon );
    pushButtonDeleteOne -> setIcon( m_MinusIcon );
    pushButtonDelete -> setIcon( m_DeleteIcon );
    pushButtonDisplayAll -> setIcon( m_VisibleIcon );
    pushButtonHideAll -> setIcon( m_UnvisibleIcon );
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


//************************************ DISPLAYING MESH ************************************************
void distanceGui::DisplayInit()
{
    if( m_NumberOfDisplay == 0 )
    {
        m_MyWindowMesh.setSizeH(  scrollAreaMesh -> height()  );
        m_MyWindowMesh.setSizeW( scrollAreaMesh -> width() );
        m_MyWindowMesh.setMeshWidget( m_WidgetMesh );
    }

    m_MyWindowMesh.windowInit();
    m_MyWindowMesh.windowUpdate();

    m_NumberOfDisplay++;
    ChangeIcon( m_VisibleIcon );

    groupBoxCamera -> setEnabled( true );
    groupBoxVisualization -> setEnabled( true );
    pushButtonDelete -> setEnabled( true );
    pushButtonDeleteOne -> setEnabled( true );
    pushButtonDisplayAll -> setEnabled( true );
    pushButtonHideAll -> setEnabled( true );
    listWidgetLoadedMesh -> setEnabled( true );
    menuAdvancedParameters -> setEnabled( true );
    actionSmoothing -> setEnabled( true );
    actionDownSampling -> setEnabled( true );

}

void distanceGui::DisplayReset()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 )
    {
        m_MyWindowMesh.windowClear();

        m_NumberOfDisplay = 0;
        m_NumberOfMesh = 0;
        m_MeshSelected = -1;
        m_SelectedItemA = -1;
        m_SelectedItemB = -1;

        horizontalSliderOpacity -> setSliderPosition( horizontalSliderOpacity -> maximum() );
        lcdNumberOpacity -> display( horizontalSliderOpacity -> maximum()  );

        listWidgetLoadedMesh -> clear();
        m_MeshList.clear();
        m_OpacityList.clear();
        m_MinSampleFrequencyList.clear();
        m_SamplingStepList.clear();
        m_SignedDistanceList.clear();
        m_DisplayTypeList.clear();
        m_DisplayErrorList.clear();
        comboBoxMeshB->clear();

        m_MySmoothing.reset();
        m_MyDownSampling.reset();

        m_MyWindowMesh.windowUpdate();
    }

    if( m_MeshList.empty() )
    {
        groupBoxCamera -> setEnabled( false );
        groupBoxParameters -> setEnabled( false );
        groupBoxDistance -> setEnabled( false );
        groupBoxErrorParameters -> setEnabled( false );
        menuAdvancedParameters -> setEnabled( false );

        pushButtonAdd -> setEnabled( true );
        pushButtonDeleteOne -> setEnabled( false );
        pushButtonDelete -> setEnabled( false );
        pushButtonDisplayAll -> setEnabled( false );
        pushButtonHideAll -> setEnabled( false );
        listWidgetLoadedMesh -> setEnabled( false );

        actionAddNewFile -> setEnabled( true );
        actionAddNewRepository -> setEnabled( true );
        actionSaveFile -> setEnabled( false );
        actionQuit -> setEnabled( true );
    }
}

void distanceGui::DeleteOneFile()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {

        m_MeshList.erase( m_MeshList.begin() + m_MeshSelected );
        m_OpacityList.erase( m_OpacityList.begin() + m_MeshSelected );
        m_MinSampleFrequencyList.erase( m_MinSampleFrequencyList.begin() + m_MeshSelected );
        m_SamplingStepList.erase( m_SamplingStepList.begin() + m_MeshSelected );
        m_SignedDistanceList.erase( m_SignedDistanceList.begin() + m_MeshSelected );
        m_DisplayErrorList.erase( m_DisplayErrorList.begin() + m_MeshSelected );
        m_DisplayTypeList.erase( m_DisplayTypeList.begin() + m_MeshSelected );

        delete listWidgetLoadedMesh->item( m_MeshSelected );
        comboBoxMeshB -> removeItem( m_MeshSelected );

        m_MySmoothing.deleteOne( m_MeshSelected );
        m_MyDownSampling.deleteOne( m_MeshSelected );
        m_MyWindowMesh.windowClearOne( m_MeshSelected );
        m_MyWindowMesh.windowUpdate();

        m_NumberOfMesh--;
        m_MeshSelected = -1;
        m_SelectedItemA = -1;
        m_SelectedItemB = -1;
    }

    if( m_MeshList.empty() )
    {
        groupBoxCamera -> setEnabled( false );
        groupBoxParameters -> setEnabled( false );
        groupBoxDistance -> setEnabled( false );
        menuAdvancedParameters -> setEnabled( false );

        pushButtonAdd -> setEnabled( true );
        pushButtonDeleteOne -> setEnabled( false );
        pushButtonDelete -> setEnabled( false );
        listWidgetLoadedMesh -> setEnabled( false );

        actionAddNewFile -> setEnabled( true );
        actionAddNewRepository -> setEnabled( true );
        actionSaveFile -> setEnabled( false );
        actionQuit -> setEnabled( true );
    }
}

void distanceGui::DisplayAll()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_OpacityList[ IndiceOfMesh ] = 1.0;
        m_MyWindowMesh.getTool( IndiceOfMesh ).setOpacity( 1.0 );
        horizontalSliderOpacity -> setValue( 1.0 );
        lcdNumberOpacity -> display( 1.0 );
        ChangeIcon( m_VisibleIcon , IndiceOfMesh );
        m_MyWindowMesh.getTool( IndiceOfMesh ).updateActorProperties();
    }
    m_MyWindowMesh.windowUpdate();

    groupBoxParameters -> setEnabled( false );
    groupBoxDistance -> setEnabled( false );
    menuAdvancedParameters -> setEnabled( false );
}

void distanceGui::HideAll()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_ActivTool = m_MyWindowMesh.getTool( IndiceOfMesh );

        m_OpacityList[ IndiceOfMesh ] = 0.0;
        horizontalSliderOpacity -> setValue( 0.0 );
        lcdNumberOpacity -> display( 0.0 );
        ChangeIcon( m_UnvisibleIcon , IndiceOfMesh );

        m_ActivTool.setOpacity( 0.0 );
        m_ActivTool.updateActorProperties();
    }
    m_MyWindowMesh.windowUpdate();

    groupBoxParameters -> setEnabled( false );
    groupBoxDistance -> setEnabled( false );
    menuAdvancedParameters -> setEnabled( false );
}

void distanceGui::ChangeTypeOfDisplay()
{
    if( ! m_MeshList.empty() && m_MeshSelected != -1 )
    {
        if( radioButtonSurface -> isChecked() )
        {
            m_DisplayTypeList[ m_MeshSelected ] = 1;           
        }
        else if( radioButtonPoints -> isChecked() )
        {
            m_DisplayTypeList[ m_MeshSelected ] = 2;
        }
        else if( radioButtonWireframe -> isChecked() )
        {
            m_DisplayTypeList[ m_MeshSelected ] = 3;
        }

        m_ActivTool.setType( m_DisplayTypeList[ m_MeshSelected ] );
        m_ActivTool.updateDisplayProperties();
        m_MyWindowMesh.windowUpdate();
    }
}

//************************************ CHANGING MESH PARAMETERS ************************************************
void distanceGui::ChangeValueOpacity()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_OpacityList[ m_MeshSelected ] = horizontalSliderOpacity -> value()/100.;
        lcdNumberOpacity -> display( m_OpacityList[ m_MeshSelected ] );

        m_ActivTool.setOpacity( m_OpacityList[ m_MeshSelected ] );
        m_ActivTool.updateActorProperties();

        if( m_OpacityList[ m_MeshSelected ] == 0 )
        {
            ChangeIcon( m_UnvisibleIcon , m_MeshSelected );
        }
        else
        {
            ChangeIcon( m_VisibleIcon , m_MeshSelected );
        }

        m_MyWindowMesh.windowUpdate();
    }
}

void distanceGui::ChooseColor()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_DisplayErrorList[ m_MeshSelected ] = 0;
        m_MyWindowMesh.chooseDisplayError( m_MeshSelected , false );

        m_Color = QColorDialog::getColor( Qt::white , this );

        m_ActivTool.setColor( m_Color.redF(), m_Color.greenF() , m_Color.blueF() );
        m_ActivTool.updateActorProperties();

        m_MyWindowMesh.windowUpdate();
    }
}


//************************************ ADVANCED PARAMETERS ************************************************
void distanceGui::OpenSmoothingWindow()
{
    if( !m_MeshList.empty() )
    {
        m_MySmoothing.setWindow( m_MyWindowMesh );
        m_MySmoothing.setIcon( m_VisibleIcon , m_UnvisibleIcon );
        m_MySmoothing.show();
    }
}

void distanceGui::OpenDownSamplingWindow()
{
    if( !m_MeshList.empty() )
    {
        m_MyDownSampling.setWindow( m_MyWindowMesh );
        m_MyDownSampling.show();
    }
}


//************************************ CHANGING CAMERA POSITION ************************************************
void distanceGui::DisplayUpdateCamera()
{
    m_MyWindowMesh.updatePositionCamera();
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


//************************************ CHANGING ERROR PARAMETERS ************************************************
void distanceGui::ChangeSamplingStep()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_SamplingStepList[ m_MeshSelected ] = doubleSpinBoxSampStep -> value();
        m_MyTestMeshValmet.SetSamplingStep( m_SamplingStepList[ m_MeshSelected ] );
    }
}

void distanceGui::ChangeMinSampleFrequency()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_MinSampleFrequencyList[ m_MeshSelected ] = doubleSpinBoxMinSampFreq -> value();
        m_MyTestMeshValmet.SetMinSampleFrequency( m_MinSampleFrequencyList[ m_MeshSelected ] );
    }
}

void distanceGui::ChangeSignedDistance()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_SignedDistanceList[ m_MeshSelected ] = checkBoxSignedDistance -> isChecked();
        m_MyTestMeshValmet.SetSignedDistance( m_SignedDistanceList[ m_MeshSelected ] );
    }
}

void distanceGui::ChangeDisplayError()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        if( checkBoxError -> isEnabled() )
        {
            if( checkBoxError -> isChecked() )
            {
                m_DisplayErrorList[ m_MeshSelected ] = 1 ;
            }

            if( ! checkBoxError -> isChecked() )
            {
                m_DisplayErrorList[ m_MeshSelected ] = 0 ;
            }
        }
        DisplayError();
    }
}

//************************************ COMPUTING ERROR ************************************************
void distanceGui::ApplyDistance()
{
    if( m_SelectedItemA != -1 && m_SelectedItemB != -1 )
    {       
        m_MyTestMeshValmet.CalculateError();

        m_ComputedData = m_MyTestMeshValmet.GetFinalData();
        m_Lut = m_MyTestMeshValmet.GetLut();

        m_DisplayErrorList[ m_SelectedItemA ] = 1;
        checkBoxError -> setChecked( true );
        checkBoxError -> setEnabled( true );

        m_OpacityList[ m_SelectedItemB ] = 0.0;
        horizontalSliderOpacity -> setValue( 0.0 );
        lcdNumberOpacity -> display( 0.0 );
        ChangeIcon( m_UnvisibleIcon , m_SelectedItemB );

        m_ActivTool = m_MyWindowMesh.getTool( m_SelectedItemB );
        m_ActivTool.setOpacity( 0.0 );
        m_ActivTool.updateActorProperties();

        m_MyWindowMesh.windowUpdate();

        m_MyWindowMesh.displayInitError( m_ComputedData , m_Lut , m_SelectedItemA );   
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText( " choose first the reference file to apply the distance error ");
        MsgBox.exec();
    }
}

void distanceGui::DisplayError()
{
    if( ! m_MeshList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        if( m_DisplayErrorList[ m_MeshSelected ] == 0 )
        {
            m_MyWindowMesh.chooseDisplayError( m_MeshSelected , false );
        }
        if( m_DisplayErrorList[ m_SelectedItemA ] == 1 )
        {
            m_MyWindowMesh.chooseDisplayError( m_MeshSelected , true );
        }
    }
}

//************************************ LOADING FILES FOR ERROR ************************************************
void distanceGui::AvailableMesh()
{
    m_SelectedItemA = m_MeshSelected;

    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        if( IndiceOfMesh != m_SelectedItemA )
        {
           comboBoxMeshB -> setItemIcon( IndiceOfMesh , m_OkIcon );
           QStandardItemModel* Model = qobject_cast< QStandardItemModel* >( comboBoxMeshB -> model() );
           QStandardItem* Item = Model -> item( IndiceOfMesh );
           Item -> setSelectable( true );
        }
        else
        {
           comboBoxMeshB ->setItemIcon( IndiceOfMesh , m_NotOkIcon );
           QStandardItemModel* Model = qobject_cast< QStandardItemModel* >( comboBoxMeshB -> model() );
           QStandardItem* Item = Model -> item( IndiceOfMesh );
           Item -> setSelectable( false );
        }
    }
}

void distanceGui::SelectMeshB()
{
    if( m_SelectedItemA != -1 )
    {
        m_SelectedItemB = comboBoxMeshB -> currentItem();

        std::cout << " item A : " << m_SelectedItemA << " item B : " << m_SelectedItemB << std::endl;

        displayTools ToolMeshA = m_MyWindowMesh.getTool( m_SelectedItemA );
        displayTools ToolMeshB = m_MyWindowMesh.getTool( m_SelectedItemB );

        m_FileName1 = QString::fromStdString(ToolMeshA.getName());
        m_FileName2 = QString::fromStdString(ToolMeshB.getName());

        m_MyTestMeshValmet.SetFileName1( m_FileName1 );
        m_MyTestMeshValmet.SetFileName2( m_FileName2 );

        groupBoxErrorParameters -> setEnabled( true );
     }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText( " choose first the file you want to apply the distance error ");
        MsgBox.exec();
    }
}

