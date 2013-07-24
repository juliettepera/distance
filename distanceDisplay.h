#ifndef DISTANCEDISPLAY_H
#define DISTANCEDISPLAY_H

// VTK library
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

// QT library
#include <QTextBrowser>

// Other Library
#include <string>

void windowInitialisation( QVTKWidget* widgetMesh , std::string mesh , QSize s );
void initialisation(QTextBrowser* widgetText);


#endif
