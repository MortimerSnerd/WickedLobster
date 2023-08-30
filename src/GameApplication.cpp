#include "pch.h"
#include "WickedEngine.h"
#include "GameApplication.h"
#include "lobutil.h"

// This is where application-wide updates get executed in a fixed timestep based manner.
//  RenderPath::FixedUpdate is also called from here for the active component
void GameApplication::FixedUpdate()
{
    wi::Application::FixedUpdate();
    lobster_fixed_update();
}

