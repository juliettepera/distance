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

    m_WidgetMesh = new QVTKWidget( this -> scrollAreaMesh );

    m_WorkDirectory = WorkDirectory;
    m_WorkDirectory.erase( m_WorkDirectory.length() - 9 , 9 );

    InitIcon();

    // shortcuts
    actionAddNewFile -> setShortcut( QKeySequence("Ctrl+A") );
    actionAddNewRepository -> setShortcut( QKeySequence("Ctrl+R") );
    actionSaveFile -> setShortcut( QKeySequence("Ctrl+S") );
    actionQuit -> setShortcut( QKeySequence("Ctrl+Q") );

    // connections
    QObject::connect( actionQuit , SIGNAL( triggered() ) , qApp , SLOT( quit() ) );

    QObject::connect( actionAddNewFile , SIGNAL( triggered() ) , this , SLOT( OpenBrowseWindowFile() ) );
    QObject::connect( actionAddNewRepository , SIGNAL( triggered() ) , this , SLOT( OpenBrowseWindowRepository() ) );
    QObject::connect( pushButtonAdd , SIGNAL( clicked() ) , this , SLOT( OpenBrowseWindowFile() ) );

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

    QObject::connect( listWidgetLoadedMesh , SIGNAL( itemClicked( QListWidgetItem* ) ) , this , SLOT( ChangeMeshSelected() ) );
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
}

void meshMetricGui::ChangeIcon( QIcon Icon )
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh ++ )
    {
        listWidgetLoadedMesh -> item( IndiceOfMesh ) -> setIcon( Icon );
    }
}

void meshMetricGui::ChangeIcon( QIcon Icon , int IndiceOfMesh )
{
        listWidgetLoadedMesh -> item( IndiceOfMesh ) -> setIcon( Icon );
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
            listWidgetLoadedMesh -> item( m_NumberOfMesh ) -> setIcon( m_UnvisibleIcon );

            comboBoxMeshB -> addItem( m_NotOkIcon , File.fileName().toStdString().c_str() );

            m_MyWindowMesh.addData( m_DataList[ m_NumberOfMesh ].getActor() );

            m_NumberOfMesh++;

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
            listWidgetLoadedMesh -> item( m_NumberOfMesh - 1 ) -> setIcon( m_UnvisibleIcon );

            comboBoxMeshB -> addItem( m_NotOkIcon , FileList.at(i).fileName().toStdString().c_str() );

            m_MyWindowMesh.addData( m_DataList[ m_NumberOfMesh ].getActor() );

            m_NumberOfMesh++;

        }

        FileList.clear();
        DisplayInit();
    }
}


// ****************************************** functions for delete files
void meshMetricGui::DeleteOneFile()
{
    if( !m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {

        m_DataList.erase( m_DataList.begin() + m_MeshSelected );
        delete listWidgetLoadedMesh->item( m_MeshSelected );
        comboBoxMeshB -> removeItem( m_MeshSelected );

        m_MyWindowMesh.deleteData( m_MeshSelected );

        m_NumberOfMesh--;
        m_MeshSelected = -1;

        horizontalSliderOpacity -> setValue( horizontalSliderOpacity -> maximum() );
        lcdNumberOpacity -> display( horizontalSliderOpacity -> maximum()  );
        spinBoxIteration -> setValue( spinBoxIteration -> maximum() );
        spinBoxDecimate -> setValue( spinBoxDecimate -> maximum() );
        radioButtonPoints -> setChecked( true );
        lineEditMeshA -> clear();

    }

    if( m_DataList.empty() )
    {
        groupBoxCamera -> setEnabled( false );
        tabWidgetVisualization -> setEnabled( false );
        tabWidgetError -> setEnabled( false );

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
        spinBoxIteration -> setValue( spinBoxIteration -> maximum() );
        spinBoxDecimate -> setValue( spinBoxDecimate -> maximum() );
        radioButtonPoints -> setChecked( true );
        listWidgetLoadedMesh -> clear();
        comboBoxMeshB -> clear();
        lineEditMeshA -> clear();
    }

    if( m_DataList.empty() )
    {
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

    ChangeIcon( m_VisibleIcon );

    groupBoxCamera -> setEnabled( true );
    groupBoxVisualization -> setEnabled( true );
    pushButtonDelete -> setEnabled( true );
    pushButtonDeleteOne -> setEnabled( true );
    pushButtonDisplayAll -> setEnabled( true );
    pushButtonHideAll -> setEnabled( true );
    listWidgetLoadedMesh -> setEnabled( true );
    actionSmoothing -> setEnabled( true );
    actionDownSampling -> setEnabled( true );
}

void meshMetricGui::DisplayAll()
{
    int IndiceOfMesh;
    for( IndiceOfMesh = 0 ; IndiceOfMesh < m_NumberOfMesh ; IndiceOfMesh++ )
    {
        m_DataList[ IndiceOfMesh ].setOpacity( 1.0 );
        horizontalSliderOpacity -> setValue( 1.0 );
        lcdNumberOpacity -> display( 100 );
        ChangeIcon( m_VisibleIcon , IndiceOfMesh );
        m_DataList[ IndiceOfMesh ].updateActorProperties();
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
        ChangeIcon( m_UnvisibleIcon , IndiceOfMesh );
        m_DataList[ IndiceOfMesh ].updateActorProperties();
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
void meshMetricGui::ChangeMeshSelected()
{
   m_MeshSelected = listWidgetLoadedMesh -> currentRow();
   horizontalSliderOpacity -> setValue( m_DataList[ m_MeshSelected ].getOpacity()*100 );
   lcdNumberOpacity -> display( m_DataList[ m_MeshSelected ].getOpacity() );

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

   QFileInfo File = QString::fromStdString( m_DataList[ m_MeshSelected ].getName() );
   lineEditMeshA -> setText( File.fileName() );
   AvailableMesh();

   if( m_NumberOfMesh >= 2 )
   {
       tabWidgetError -> setEnabled( true );
   }

   tabWidgetVisualization -> setEnabled( true );

}

void meshMetricGui::ResetSelectedFile()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_DataList[ m_MeshSelected ].initialization();
        m_MyWindowMesh.updateWindow();

    }
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
            ChangeIcon( m_UnvisibleIcon , m_MeshSelected );
        }
        else
        {
            ChangeIcon( m_VisibleIcon , m_MeshSelected );
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
        m_DataList[ m_MeshSelected ].setNumberOfIterationSmooth( spinBoxIteration -> value() );
        pushButtonRunSmoothing -> setEnabled( true );
    }
}

void meshMetricGui::ApplySmoothing()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_MyProcess.processSmoothing( m_DataList[ m_MeshSelected ] );
        m_MyWindowMesh.updateWindow();

        pushButtonRunSmoothing -> setEnabled( false );
        spinBoxIteration -> setValue( spinBoxIteration -> minimum() );
    }
}

// ****************************************** functions for the downSampling
void meshMetricGui::ChangeDecimate()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_DataList[ m_MeshSelected ].setDecimate( spinBoxDecimate -> value()/100. );
        pushButtonRunDecimate -> setEnabled( true );
    }
}

void meshMetricGui::ApplyDecimate()
{
    if( ! m_DataList.empty() && m_NumberOfDisplay != 0 && m_MeshSelected != -1 )
    {
        m_MyProcess.processDownSampling( m_DataList[ m_MeshSelected ] );
        m_MyWindowMesh.updateWindow();

        pushButtonRunDecimate -> setEnabled( false );
        spinBoxDecimate -> setValue( spinBoxDecimate -> minimum() );
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

        m_FileName1 = QString::fromStdString( m_DataList[ m_SelectedItemA ].getName() );
        m_FileName2 = QString::fromStdString( m_DataList[ m_SelectedItemB ].getName() );

        m_MyMeshValmet.SetFileName1( m_FileName1 );
        m_MyMeshValmet.SetFileName2( m_FileName2 );
     }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText( " choose first the file you want to apply the distance error ");
        MsgBox.exec();
    }
}
















