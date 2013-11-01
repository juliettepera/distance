#include "meshMetricGui.h"

meshMetricGui::meshMetricGui( QWidget *parent , Qt::WFlags f , std::string WorkDirectory )
{
    setupUi(this);

    // initialisation of the attributs
    m_NumberOfMesh = 0;
    m_MeshSelected = -1;
    m_CameraX = 1 ;
    m_CameraY = 0;
    m_CameraZ = 0;
    m_NumberOfDisplay = 0;
    m_SelectedItemA = -1;
    m_SelectedItemB = -1;
    m_nbDecimate = 10;
    m_nbIteration = 200;
    m_Min = -1.0;
    m_Max = 1.0;

    m_WidgetMesh = new QVTKWidget( this -> scrollAreaMesh );

    m_WorkDirectory = WorkDirectory;
    m_WorkDirectory.erase( m_WorkDirectory.length() - 9 , 9 );

    InitIcon();

    // shortcuts
    actionAddNewFile -> setShortcut( QKeySequence("Ctrl+A") );
    actionAddNewRepository -> setShortcut( QKeySequence("Ctrl+R") );
    actionSaveFile -> setShortcut( QKeySequence("Ctrl+S") );
    actionQuit -> setShortcut( QKeySequence("Ctrl+Q") );

    QStringList List;
    List << "2" << "0.5" << "0.2" << "0.1" << "0.05" << "0.02" ;
    comboBoxSamplingStep -> addItems( List );
    comboBoxSamplingStep -> setCurrentItem( 1 );

    // connections
    QObject::connect( actionQuit , SIGNAL( triggered() ) , qApp , SLOT( quit() ) );

    QObject::connect( actionAddNewFile , SIGNAL( triggered() ) , this , SLOT( OpenBrowseWindowFile() ) );
    QObject::connect( actionAddNewRepository , SIGNAL( triggered() ) , this , SLOT( OpenBrowseWindowRepository() ) );
    QObject::connect( pushButtonAdd , SIGNAL( clicked() ) , this , SLOT( OpenBrowseWindowFile() ) );
    QObject::connect( actionSaveFile , SIGNAL( triggered() ) , this , SLOT( SaveFile() ) );

    QObject::connect( pushButtonDeleteOne , SIGNAL( clicked() ) , this , SLOT( DeleteOneFile() ) );
    QObject::connect( pushButtonDelete , SIGNAL( clicked() ) , this , SLOT( DeleteAllFiles() ) );

    QObject::connect( pushButtonDisplayAll , SIGNAL( clicked() ) , this , SLOT( DisplayAll() ) );
    QObject::connect( pushButtonHideAll , SIGNAL( clicked() ) , this , SLOT( HideAll() ) );

    QObject::connect( pushButtonFront , SIGNAL( clicked() ) , this , SLOT( buttonFrontClicked() ) );
    QObject::connect( pushButtonBack , SIGNAL( clicked() ) , this , SLOT( buttonBackClicked() ) );
    QObject::connect( pushButtonRight , SIGNAL( clicked() ) , this , SLOT( buttonRightClicked() ) );
    QObject::connect( pushButtonLeft , SIGNAL( clicked() ) , this , SLOT( buttonLeftClicked() ) );
    QObject::connect( pushButtonUp , SIGNAL( clicked() ) , this , SLOT( buttonUpClicked() ) );
    QObject::connect( pushButtonDown , SIGNAL( clicked() ) , this , SLOT( buttonDownClicked() ) );

    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( UpdateDisplayedMesh( QListWidgetItem* ) ) );

    QObject::connect( pushButtonResetAll , SIGNAL( clicked() ) , this , SLOT( ResetSelectedFile() ) );
    QObject::connect( horizontalSliderOpacity , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacity() ) );
    QObject::connect( pushButtonColor , SIGNAL( clicked() ) , this , SLOT( ChooseColor() ) );
    QObject::connect( radioButtonSurface , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeTypeOfDisplay() ) );
    QObject::connect( radioButtonPoints , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeTypeOfDisplay() ) );
    QObject::connect( radioButtonWireframe , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeTypeOfDisplay() ) );
    QObject::connect( horizontalSliderOpacity , SIGNAL( sliderReleased() ), this, SLOT( ChangeValueOpacity() ) );

    QObject::connect( spinBoxIteration , SIGNAL( valueChanged( int ) ), this, SLOT( ChangeNumberOfIteration() ) );
    QObject::connect( pushButtonRunSmoothing , SIGNAL( clicked() ) , this , SLOT( ApplySmoothing() ) );

    QObject::connect( spinBoxDecimate , SIGNAL( valueChanged( int ) ), this, SLOT( ChangeDecimate() ) );
    QObject::connect( pushButtonRunDecimate , SIGNAL( clicked() ) , this , SLOT( ApplyDecimate() ) );

    QObject::connect( comboBoxMeshB , SIGNAL( activated( int ) ) , this , SLOT( SelectMeshB() ) );
    QObject::connect( spinBoxMinSampFreq , SIGNAL( valueChanged( int ) ), this, SLOT( ChangeMinSampleFrequency() ) );
    QObject::connect( comboBoxSamplingStep , SIGNAL( activated( int ) ), this, SLOT( ChangeSamplingStep() ) );
    QObject::connect( radioButtonSignedDistance , SIGNAL( toggled( bool ) ), this, SLOT( ChangeSignedDistance() ) );
    QObject::connect( radioButtonAbsoluteDistance , SIGNAL( toggled( bool ) ), this, SLOT( ChangeSignedDistance() ) );
    QObject::connect( doubleSpinBoxMin , SIGNAL( valueChanged( double ) ) , this , SLOT( ChangeValueMin() ) );
    QObject::connect( doubleSpinBoxMax , SIGNAL( valueChanged( double ) ) , this , SLOT( ChangeValueMax() ) );
    QObject::connect( checkBoxError , SIGNAL( toggled( bool ) ) , this , SLOT( ChangeDisplayError() ) );
    QObject::connect( pushButtonApply , SIGNAL( clicked() ) , this , SLOT( ApplyDistance() ) );
    QObject::connect( pushButtonUpdateColor , SIGNAL( clicked() ) , this , SLOT( UpdateColor() ) );
}

// ****************************************** functions for the icons
void meshMetricGui::InitIcon()
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

    std::string reset = m_WorkDirectory;
    reset += "/icons/reset.png";

    m_Visible = QString::fromStdString( visible );
    m_Unvisible = QString::fromStdString( unvisible );
    m_Ok = QString::fromStdString( ok );
    m_NotOk = QString::fromStdString( notok );
    m_Plus = QString::fromStdString( plus );
    m_Minus = QString::fromStdString( minus );
    m_Delete = QString::fromStdString( deleteAll );
    m_Display = QString::fromStdString( display );
    m_Reset = QString::fromStdString( reset );

    m_VisibleIcon = QIcon( m_Visible );
    m_UnvisibleIcon = QIcon( m_Unvisible );
    m_OkIcon = QIcon( m_Ok );
    m_NotOkIcon = QIcon( m_NotOk );
    m_PlusIcon = QIcon( m_Plus );
    m_MinusIcon = QIcon( m_Minus );
    m_DeleteIcon = QIcon( m_Delete );
    m_DisplayIcon = QIcon( m_Display );
    m_ResetIcon = QIcon( m_Reset );

    pushButtonAdd -> setIcon( m_PlusIcon );
    pushButtonDeleteOne -> setIcon( m_MinusIcon );
    pushButtonDelete -> setIcon( m_DeleteIcon );
    pushButtonDisplayAll -> setIcon( m_VisibleIcon );
    pushButtonHideAll -> setIcon( m_UnvisibleIcon );
    pushButtonResetAll -> setIcon( m_ResetIcon );

    // pb access icons and size
    std::string styleSheetLoadedMesh = "QListWidget::indicator:checked{ image: url(";
    styleSheetLoadedMesh += m_WorkDirectory;
    styleSheetLoadedMesh += "/icons/visible.png);} QListWidget::indicator:unchecked{ image: url(";
    styleSheetLoadedMesh += m_WorkDirectory;
    styleSheetLoadedMesh += "/icons/unvisible.png);}";
    listWidgetLoadedMesh -> setStyleSheet( QString::fromStdString( styleSheetLoadedMesh ) );
}

// ****************************************** functions for loadind files
void meshMetricGui::OpenBrowseWindowFile()
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
            m_DataList.push_back( ( lineEditLoad -> text() ).toStdString() );
            m_DataList[ m_NumberOfMesh ].initialization();

            QFileInfo File = ( lineEditLoad -> text() );

            listWidgetLoadedMesh -> addItem( File.fileName().toStdString().c_str() );

            QListWidgetItem* CurrentItem = listWidgetLoadedMesh -> item( m_NumberOfMesh );
            CurrentItem -> setFlags( listWidgetLoadedMesh -> item( m_NumberOfMesh ) -> flags() | Qt::ItemIsUserCheckable );
            CurrentItem -> setCheckState( Qt::Checked );

            comboBoxMeshB -> addItem( m_NotOkIcon , File.fileName().toStdString().c_str() );

            m_MyWindowMesh.addData( m_DataList[ m_NumberOfMesh ].getActor() );

            m_ErrorComputed.push_back( false );
            m_Visibility.push_back( true );

            m_MeshSelected = m_NumberOfMesh;
            m_NumberOfMesh++;
            listWidgetLoadedMesh -> setCurrentRow( m_MeshSelected );

            PreviousError();

        }
      }

      browseMesh.clear();
      delete lineEditLoad;
      DisplayInit();
    }
}

void meshMetricGui::OpenBrowseWindowRepository()
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
            m_DataList.push_back( FileList.at(i).canonicalFilePath().toStdString() );
            m_DataList[ m_NumberOfMesh ].initialization();

            listWidgetLoadedMesh -> addItem( FileList.at(i).fileName().toStdString().c_str() );
            QListWidgetItem* CurrentItem = listWidgetLoadedMesh -> item( m_NumberOfMesh );
            CurrentItem -> setFlags( listWidgetLoadedMesh -> item( m_NumberOfMesh ) -> flags() | Qt::ItemIsUserCheckable );
            CurrentItem -> setCheckState( Qt::Checked );

            comboBoxMeshB -> addItem( m_NotOkIcon , FileList.at(i).fileName().toStdString().c_str() );

            m_MyWindowMesh.addData( m_DataList[ m_NumberOfMesh ].getActor() );

            m_ErrorComputed.push_back( false );
            m_Visibility.push_back( true );

            m_MeshSelected = m_NumberOfMesh;
            m_NumberOfMesh++;
            listWidgetLoadedMesh -> setCurrentRow( m_MeshSelected );

            PreviousError();
        }

        FileList.clear();
        DisplayInit();
    }
}

void meshMetricGui::SaveFile()
{
    if( !m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        QString fileName = QFileDialog::getSaveFileName( this , " Create a new vtk file or open an existing one" , "./untitled.vtk" , "vtk mesh (*.vtk)" );
        std::cout << fileName.toStdString() << std::endl;
        m_MyProcess.SaveFile( fileName.toStdString() , m_DataList[ m_MeshSelected ] );
    }
}


// ****************************************** functions for delete files
void meshMetricGui::DeleteOneFile()
{
    if( !m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_DataList.erase( m_DataList.begin() + m_MeshSelected );
        m_ErrorComputed.erase( m_ErrorComputed.begin() + m_MeshSelected );
        m_Visibility.erase( m_Visibility.begin() + m_MeshSelected );
        delete listWidgetLoadedMesh->item( m_MeshSelected );
        comboBoxMeshB -> removeItem( m_MeshSelected );

        m_MyWindowMesh.deleteData( m_MeshSelected );

        m_NumberOfMesh--;
        m_MeshSelected = 0;

        horizontalSliderOpacity -> setValue( m_DataList[ m_MeshSelected ].getOpacity()/100.0 );
        lcdNumberOpacity -> display( m_DataList[ m_MeshSelected ].getOpacity() );
        spinBoxIteration -> setValue( 200 );
        spinBoxDecimate -> setValue( 10 );
        if( m_DataList[ m_MeshSelected ].getType() == 1 )
        {
            radioButtonSurface -> setChecked( true );
        }
        else if( m_DataList[ m_MeshSelected ].getType() == 2 )
        {
            radioButtonPoints -> setChecked( true );
        }
        else if( m_DataList[ m_MeshSelected ].getType() == 3 )
        {
            radioButtonWireframe -> setChecked( true );
        }
        checkBoxError -> setChecked( m_ErrorComputed[ m_MeshSelected ] );
        lineEditMeshA -> clear();
        tabWidgetVisualization -> setEnabled( false );
        tabWidgetError -> setEnabled( false );
        pushButtonDeleteOne -> setEnabled( false );
    }

    if( m_DataList.empty() )
    {
        groupBoxCamera -> setEnabled( false );
        pushButtonDelete -> setEnabled( false );
        listWidgetLoadedMesh -> setEnabled( false );
        actionSaveFile -> setEnabled( false );

        pushButtonAdd -> setEnabled( true );
        actionAddNewFile -> setEnabled( true );
        actionAddNewRepository -> setEnabled( true );
        actionQuit -> setEnabled( true );
        m_MeshSelected = -1;
    }
}


void meshMetricGui::DeleteAllFiles()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 )
    {
        m_MyWindowMesh.deleteAll();

        m_NumberOfDisplay = 0;
        m_NumberOfMesh = 0;
        m_MeshSelected = -1;
        m_SelectedItemA = -1;
        m_SelectedItemB = -1;

        horizontalSliderOpacity -> setSliderPosition( horizontalSliderOpacity -> maximum() );
        lcdNumberOpacity -> display( horizontalSliderOpacity -> maximum()  );
        spinBoxIteration -> setValue( 200 );
        spinBoxDecimate -> setValue( 10 );
        radioButtonPoints -> setChecked( true );
        checkBoxError -> setChecked( false );
        listWidgetLoadedMesh -> clear();
        comboBoxMeshB -> clear();
        lineEditMeshA -> clear();
        m_DataList.clear();
        m_ErrorComputed.clear();
        m_Visibility.clear();

        groupBoxCamera -> setEnabled( false );
        tabWidgetVisualization -> setEnabled( false );
        tabWidgetError -> setEnabled( false );

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


// ****************************************** functions for display files
void meshMetricGui::DisplayInit()
{
    if( m_NumberOfDisplay == 0 )
    {
       m_MyWindowMesh.setSizeH(  scrollAreaMesh -> height()  );
       m_MyWindowMesh.setSizeW( scrollAreaMesh -> width() );
       m_MyWindowMesh.setMeshWidget( m_WidgetMesh );
    }

    m_MyWindowMesh.initWindow();
    m_MyWindowMesh.updateWindow();
    m_NumberOfDisplay++;

    groupBoxCamera -> setEnabled( true );

    groupBoxVisualization -> setEnabled( true );
    checkBoxError -> setEnabled( false );

    pushButtonDelete -> setEnabled( true );
    pushButtonDisplayAll -> setEnabled( true );
    pushButtonHideAll -> setEnabled( true );
    listWidgetLoadedMesh -> setEnabled( true );

    //PreviousError();
}

void meshMetricGui::DisplayAll()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
       m_DataList[ IndiceOfMesh ].setOpacity( 1.0 );
       horizontalSliderOpacity -> setValue( 1.0 );
       lcdNumberOpacity -> display( 100 );
       listWidgetLoadedMesh -> item( IndiceOfMesh ) -> setCheckState( Qt::Checked );
       m_DataList[ IndiceOfMesh ].updateActorProperties();
       m_Visibility[ IndiceOfMesh ] = true;
    }
    m_MyWindowMesh.updateWindow();

    tabWidgetVisualization -> setEnabled( false );
    tabWidgetError -> setEnabled( false );
}

void meshMetricGui::HideAll()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_DataList[ IndiceOfMesh ].setOpacity( 0.0 );
        horizontalSliderOpacity -> setValue( 0.0 );
        lcdNumberOpacity -> display( 0.0 );
        listWidgetLoadedMesh -> item( IndiceOfMesh ) -> setCheckState( Qt::Unchecked );
        m_DataList[ IndiceOfMesh ].updateActorProperties();
        m_Visibility[ IndiceOfMesh ] = false;
    }
    m_MyWindowMesh.updateWindow();

    tabWidgetVisualization -> setEnabled( false );
    tabWidgetError -> setEnabled( false );
}

// ****************************************** functions to change the camera
void meshMetricGui::buttonUpClicked()
{
    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = 1;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );
    m_MyWindowMesh.updatePositionCamera();
    m_MyWindowMesh.updateWindow();
}

void meshMetricGui::buttonDownClicked()
{
    m_CameraX = 0 ; m_CameraY = 0 ; m_CameraZ = -1;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );
    m_MyWindowMesh.updatePositionCamera();
    m_MyWindowMesh.updateWindow();
}

void meshMetricGui::buttonRightClicked()
{
    m_CameraX = 1 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );
    m_MyWindowMesh.updatePositionCamera();
    m_MyWindowMesh.updateWindow();
}

void meshMetricGui::buttonLeftClicked()
{
    m_CameraX = -1 ; m_CameraY = 0 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );
    m_MyWindowMesh.updatePositionCamera();
    m_MyWindowMesh.updateWindow();
}

void meshMetricGui::buttonBackClicked()
{
    m_CameraX = 0 ; m_CameraY = -1 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );
    m_MyWindowMesh.updatePositionCamera();
    m_MyWindowMesh.updateWindow();
}

void meshMetricGui::buttonFrontClicked()
{
    m_CameraX = 0 ; m_CameraY = 1 ; m_CameraZ = 0;

    m_MyWindowMesh.setCameraX( m_CameraX );
    m_MyWindowMesh.setCameraY( m_CameraY );
    m_MyWindowMesh.setCameraZ( m_CameraZ );
    m_MyWindowMesh.updatePositionCamera();
    m_MyWindowMesh.updateWindow();
}


// ****************************************** functions to change files properties
void meshMetricGui::UpdateDisplayedMesh( QListWidgetItem *itemClicked )
{
    QListWidgetItem* CurrentItem = itemClicked;
    int ItemRow = 0;

    if( listWidgetLoadedMesh -> currentItem() == CurrentItem )
    {
        ChangeMeshSelected();
        ItemRow = m_MeshSelected;
    }
    else
    {
        ItemRow = listWidgetLoadedMesh->row( CurrentItem );
    }

    if( CurrentItem -> checkState() == Qt::Unchecked && m_Visibility[ ItemRow ] == true )
    {
        m_DataList[ ItemRow  ].setOpacity( 0.0 );
        m_Visibility[ ItemRow ] = false;

        m_DataList[ ItemRow ].updateActorProperties();
        m_MyWindowMesh.updateWindow();
    }

    if( CurrentItem -> checkState() == Qt::Checked && m_Visibility[ ItemRow ] == false )
    {
        m_DataList[ ItemRow  ].setOpacity( 1.0 );
        m_Visibility[ ItemRow ] = true;

        m_DataList[ ItemRow ].updateActorProperties();
        m_MyWindowMesh.updateWindow();
    }
}

void meshMetricGui::ChangeMeshSelected()
{
   m_nbIteration = 200;
   m_nbDecimate = 10;
   m_MeshSelected = listWidgetLoadedMesh -> currentRow();   

   horizontalSliderOpacity -> setValue( m_DataList[ m_MeshSelected ].getOpacity()*100 );
   lcdNumberOpacity -> display( m_DataList[ m_MeshSelected ].getOpacity() );
   spinBoxIteration -> setValue( 200 );
   spinBoxDecimate -> setValue( 10 );

   if( m_DataList[ m_MeshSelected ].getType() == 1 )
   {
       radioButtonSurface -> setChecked( true );
   }
   else if( m_DataList[ m_MeshSelected ].getType() == 2 )
   {
       radioButtonPoints -> setChecked( true );
   }
   else if( m_DataList[ m_MeshSelected ].getType() == 3 )
   {
       radioButtonWireframe -> setChecked( true );
   }

   spinBoxMinSampFreq -> setValue( m_DataList[ m_MeshSelected ].getMinSamplingFrequency() );

   if( m_DataList[ m_MeshSelected ].getSignedDistance() == true )
   {
       radioButtonSignedDistance -> setChecked( true );
   }
   else if( m_DataList[ m_MeshSelected ].getSignedDistance() == false )
   {
       radioButtonAbsoluteDistance -> setChecked( true );
   }

   if( m_ErrorComputed[ m_MeshSelected ] == true )
   {
       checkBoxError -> setEnabled( true );
       if( m_DataList[ m_MeshSelected ].getDisplayError() == true )
       {
           checkBoxError -> setChecked( true );
       }
       else if( m_DataList[ m_MeshSelected ].getDisplayError() == false )
       {
           checkBoxError -> setChecked( false );
       }
       tabWidgetError -> setCurrentWidget( tabResults );
       tabResults -> setEnabled( true );
   }
   else
   {
       checkBoxError -> setEnabled( false );
       checkBoxError -> setChecked( false );
       tabWidgetError -> setCurrentWidget( tabDistance );
       tabResults -> setEnabled( false );
   }

   QFileInfo File = QString::fromStdString( m_DataList[ m_MeshSelected ].getName() );
   lineEditMeshA -> setText( File.fileName() );
   AvailableMesh();

   if( m_NumberOfMesh >= 2 )
   {
       tabWidgetError -> setEnabled( true );
       tabResults -> setEnabled( false );
   }

   tabWidgetVisualization -> setEnabled( true );
   pushButtonDeleteOne -> setEnabled( true );   
   actionSaveFile -> setEnabled( true );
}

void meshMetricGui::ResetSelectedFile()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_DataList[ m_MeshSelected ].initialization();
        m_MyWindowMesh.updateWindow();
    }
    m_DataList[ m_MeshSelected ].setOpacity( 1.0 );
    lcdNumberOpacity -> display( m_DataList[ m_MeshSelected ].getOpacity() );
    horizontalSliderOpacity -> setValue( 100 );
    m_Visibility[ m_MeshSelected ] = true;

    m_DataList[ m_MeshSelected ].updateActorProperties();
    listWidgetLoadedMesh -> item( m_MeshSelected ) -> setCheckState( Qt::Checked );

    m_ErrorComputed[ m_MeshSelected ] = false;
    checkBoxError -> setEnabled( false );
    checkBoxError -> setChecked( false );
}

void meshMetricGui::ChangeValueOpacity()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_DataList[ m_MeshSelected ].setOpacity( horizontalSliderOpacity -> value()/100. );
        lcdNumberOpacity -> display( m_DataList[ m_MeshSelected ].getOpacity() );

        m_DataList[ m_MeshSelected ].updateActorProperties();

        if( m_DataList[ m_MeshSelected ].getOpacity() == 0.0 )
        {
            listWidgetLoadedMesh -> item( m_MeshSelected ) -> setCheckState( Qt::Unchecked );
            m_Visibility[ m_MeshSelected ] = false;
        }
        else
        {
            listWidgetLoadedMesh -> item( m_MeshSelected ) -> setCheckState( Qt::Checked );
            m_Visibility[ m_MeshSelected ] = true;
        }

        m_MyWindowMesh.updateWindow();
    }
}

void meshMetricGui::ChooseColor()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_Color = QColorDialog::getColor( Qt::white , this );

        m_DataList[ m_MeshSelected ].setColor( m_Color.redF(), m_Color.greenF() , m_Color.blueF() );
        m_DataList[ m_MeshSelected ].updateActorProperties();

        m_MyWindowMesh.updateWindow();
    }
}

void meshMetricGui::ChangeTypeOfDisplay()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        if( radioButtonSurface -> isChecked() )
        {
            m_DataList[ m_MeshSelected ].setType( 1 );
        }
        else if( radioButtonPoints -> isChecked() )
        {
             m_DataList[ m_MeshSelected ].setType( 2 );
        }
        else if( radioButtonWireframe -> isChecked() )
        {
             m_DataList[ m_MeshSelected ].setType( 3 );
        }

        m_DataList[ m_MeshSelected ].updateTypeOfDisplay();
        m_MyWindowMesh.updateWindow();
    }
}

// ****************************************** functions for the smoothing
void meshMetricGui::ChangeNumberOfIteration()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_nbIteration = spinBoxIteration -> value();
        pushButtonRunSmoothing -> setEnabled( true );
    }
}

void meshMetricGui::ApplySmoothing()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        vtkSmartPointer <vtkPolyData> smoothedData = vtkSmartPointer <vtkPolyData>::New();
        vtkSmartPointer <vtkPolyData> originalData = vtkSmartPointer <vtkPolyData>::New();

        originalData = m_DataList[ m_MeshSelected ].getPolyData();
        smoothedData = m_MyProcess.processSmoothing( originalData , m_nbIteration );

        m_DataList[ m_MeshSelected ].setPolyData( smoothedData );
        m_DataList[ m_MeshSelected ].changeMapperInput();

        m_MyWindowMesh.updateWindow();

        pushButtonRunSmoothing -> setEnabled( false );
        spinBoxIteration -> setValue( 200 );
    }
}

// ****************************************** functions for the downSampling
void meshMetricGui::ChangeDecimate()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_nbDecimate = spinBoxDecimate -> value()/100.0;
        pushButtonRunDecimate -> setEnabled( true );
    }
}

void meshMetricGui::ApplyDecimate()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        vtkSmartPointer <vtkPolyData> decimatedData = vtkSmartPointer <vtkPolyData>::New();
        vtkSmartPointer <vtkPolyData> originalData = vtkSmartPointer <vtkPolyData>::New();

        originalData = m_DataList[ m_MeshSelected ].getPolyData();
        decimatedData = m_MyProcess.processDownSampling( originalData , m_nbDecimate );

        m_DataList[ m_MeshSelected ].setPolyData( decimatedData );
        m_DataList[ m_MeshSelected ].changeMapperInput();

        m_MyWindowMesh.updateWindow();

        pushButtonRunDecimate -> setEnabled( false );
        spinBoxDecimate -> setValue( 10 );
    }
}

// ****************************************** functions for the distance
void meshMetricGui::AvailableMesh()
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

void meshMetricGui::SelectMeshB()
{
    if( m_SelectedItemA != -1 )
    {
        m_SelectedItemB = comboBoxMeshB -> currentItem();
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText( " choose first the file you want to apply the distance error ");
        MsgBox.exec();
    }
}

void meshMetricGui::ChangeMinSampleFrequency()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_DataList[ m_MeshSelected ].setMinSamplingFrequency( spinBoxMinSampFreq -> value() );
    }
}

void meshMetricGui::ChangeSamplingStep()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        double value;
        value = ( comboBoxSamplingStep -> currentText() ).toDouble();
        m_DataList[ m_MeshSelected ].setSamplingStep( value );
    }
}

void meshMetricGui::ChangeSignedDistance()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        if( radioButtonSignedDistance -> isChecked() )
        {
            m_DataList[ m_MeshSelected ].setSignedDistance( true );
        }
        else if( radioButtonAbsoluteDistance -> isChecked() )
        {
            m_DataList[ m_MeshSelected ].setSignedDistance( false );
        }
    }
}

void meshMetricGui::ChangeDisplayError()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        if( checkBoxError -> isChecked() )
        {
            m_DataList[ m_MeshSelected ].setDisplayError( true );
        }
        else if( ! checkBoxError -> isChecked() )
        {
            m_DataList[ m_MeshSelected ].setDisplayError( false );
        }

        m_DataList[ m_MeshSelected ].changeActivScalar();
        m_MyWindowMesh.updateWindow();
    }
}

void meshMetricGui::ChangeValueMax()
{
    if( m_SelectedItemA != -1 && m_SelectedItemB != -1 )
    {
        if( doubleSpinBoxMax -> value() <= m_DataList[ m_SelectedItemA ].getMin() )
        {
            doubleSpinBoxMax -> setValue( m_DataList[ m_SelectedItemA ].getMax() );
        }
        else
        {
            m_Max = doubleSpinBoxMax -> value();
        }
    }
}

void meshMetricGui::ChangeValueMin()
{
    if( m_SelectedItemA != -1 && m_SelectedItemB != -1 )
    {
        if( doubleSpinBoxMin -> value() >= m_DataList[ m_SelectedItemA ].getMax() )
        {
            doubleSpinBoxMin -> setValue( m_DataList[ m_SelectedItemA ].getMin() );
        }
        else
        {
            m_Min = doubleSpinBoxMin -> value();
        }
    }
}

void meshMetricGui::ApplyDistance()
{
    if( m_SelectedItemA != -1 && m_SelectedItemB != -1 )
    {
        checkBoxError -> setChecked( true );
        checkBoxError -> setEnabled( true );
        m_ErrorComputed[ m_MeshSelected ] = true;

        m_MyProcess.processError( m_DataList[ m_SelectedItemA ] , m_DataList[ m_SelectedItemB ] );

        m_DataList[ m_SelectedItemB ].setOpacity( 0.0 );
        m_Visibility[ m_SelectedItemB ] = false;
        listWidgetLoadedMesh -> item( m_SelectedItemB ) -> setCheckState( Qt::Unchecked );
        m_DataList[ m_SelectedItemB ].updateActorProperties();
        QFileInfo File = QString::fromStdString( m_DataList[ m_SelectedItemB ].getName() );
        lineEditB -> setText( File.fileName() );

        m_DataList[ m_SelectedItemA ].setOpacity( 1.0 );
        m_Visibility[ m_SelectedItemA ] = true;
        listWidgetLoadedMesh -> item( m_SelectedItemA ) -> setCheckState( Qt::Checked );
        m_DataList[ m_SelectedItemA ].updateActorProperties();
        File = QString::fromStdString( m_DataList[ m_SelectedItemA ].getName() );
        lineEditA -> setText( File.fileName() );

        lineEditMin -> setText( QString::number( m_DataList[ m_SelectedItemA ].getMin() ) );
        lineEditMax -> setText( QString::number( m_DataList[ m_SelectedItemA ].getMax() ) );

        doubleSpinBoxMin -> setValue( m_DataList[ m_SelectedItemA ].getMin() );
        doubleSpinBoxMax -> setValue( m_DataList[ m_SelectedItemA ].getMax() );

        //m_MyWindowMesh.setLut( m_DataList[ m_SelectedItemA ].getMapper()->GetLookupTable() );
        //m_MyWindowMesh.updateLut();
        m_MyWindowMesh.updateWindow();

        ChangeMeshSelected();
    }
}

void meshMetricGui::UpdateColor()
{
    if( m_SelectedItemA != -1 && m_SelectedItemB != -1 )
    {
        m_MyProcess.updateColor( m_Min , m_Max , m_DataList[ m_SelectedItemA ] );
        m_MyWindowMesh.updateWindow();
    }
}


void meshMetricGui::PreviousError()
{
    if( ! m_DataList.empty() && m_MeshSelected != -1 )
    {
        int out = m_MyProcess.CheckPreviousError( m_DataList[ m_MeshSelected ] );
        QMessageBox MsgBox;
        QFileInfo File;

        switch( out )
        {
            case 1:               
                MsgBox.setText( " the original scalar is missing ");
                MsgBox.exec();
            break;

            case 2:
                MsgBox.setText( " the error scalar is missing ");
                MsgBox.exec();
            break;

            case 3:
                checkBoxError -> setEnabled( true );
                checkBoxError -> setChecked( true );                
                m_ErrorComputed[ m_MeshSelected ] = true;
                m_DataList[ m_MeshSelected ].setDisplayError( true );

                m_MyProcess.updateColor( m_DataList[ m_MeshSelected ].getMin() , m_DataList[ m_MeshSelected ].getMax() , m_DataList[ m_MeshSelected ] );

                tabWidgetError -> setCurrentWidget( tabResults );
                tabResults -> setEnabled( true );

                File = QString::fromStdString( m_DataList[ m_MeshSelected ].getName() );
                lineEditA -> setText( File.fileName() );
                lineEditB -> setText( QString::fromStdString( " Unknowned ") );
            break;

            case 4:
                MsgBox.setText( " problem ");
                MsgBox.exec();
            break;
        }        
    }
}












