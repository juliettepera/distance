#ifndef DISTANCEDISPLAY_H
#define DISTANCEDISPLAY_H

// VTK libraries
#include "vtkSmartPointer.h"
#include "vtkGenericDataObjectReader.h"
#include "vtkGenericDataObjectWriter.h"
#include "vtkPolyData.h"
#include "vtkSmoothPolyDataFilter.h"
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataReader.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <QVTKWidget.h>
#include <vtkImageViewer.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

// Qt libraries
#include <QVector3D>

// Other Libraries
#include <string>
#include <iostream>

void windowInit( QVTKWidget* widgetMesh , std::string meshA , std::string meshB );
void windowUpdate( QVTKWidget* widgetMesh , double opacityA , double opacityB , QVector3D positionCam );
void positionCamera( vtkSmartPointer <vtkCamera> camera , int x ,int y , int z );


#endif
