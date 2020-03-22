
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
#include "vtkImageMapper.h"
#include "vtkActor2D.h"
#include "vtkInteractorStyleImage.h"

//-------------------------------------------------------------------------------------------------

#include "mkVisualizeAlgorithmOutput.h"

//-------------------------------------------------------------------------------------------------

void mkUtilities::mkVisualizeVtkImageData (vtkImageData* vtkData)
{
    vtkSmartPointer<vtkImageMapper> imageMapper = vtkSmartPointer<vtkImageMapper>::New ();
    imageMapper->SetInputData (vtkData);

    imageMapper->SetColorWindow (1500);
    imageMapper->SetColorLevel (-500);

    vtkSmartPointer<vtkActor2D> imageActor = vtkSmartPointer<vtkActor2D>::New ();
    imageActor->SetMapper (imageMapper);
    imageActor->SetPosition (20, 20);

    // Setup renderers
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New ();

    // Setup render window
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New ();

    renderWindow->SetSize (1000, 1000);

    renderWindow->AddRenderer (renderer);

    // Setup render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New ();

    vtkSmartPointer<vtkInteractorStyleImage> style =
        vtkSmartPointer<vtkInteractorStyleImage>::New ();

    renderWindowInteractor->SetInteractorStyle (style);

    // Render and start interaction
    renderWindowInteractor->SetRenderWindow (renderWindow);

    //renderer->AddViewProp(imageActor);
    renderer->AddActor2D (imageActor);

    renderWindow->Render ();

    renderWindowInteractor->Start ();
}

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
