
/*-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>

//-------------------------------------------------------------------------------------------------

#include "vtkSmartPointer.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkActor.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"

//-------------------------------------------------------------------------------------------------

#include "mkVisualizeAlgorithmOutput.h"

//-------------------------------------------------------------------------------------------------

void mkUtilities::mkVisualizeAlgorithmOutput (vtkAlgorithmOutput* in)
{
    // TODO: First implementation done for poly data. Generalize as needed.

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New ();
    mapper->SetInputConnection (in);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New ();
    actor->SetMapper (mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New ();

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New ();
    renderWindow->AddRenderer (renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New ();

    renderWindowInteractor->SetRenderWindow (renderWindow);

    renderer->AddActor (actor);

    renderer->SetBackground (.3, .6, .3); // Background color green

    renderWindow->Render ();
    renderWindowInteractor->Start ();
}

//-------------------------------------------------------------------------------------------------
