#include "pch.h"
#include "WickedEngine.h"
#include "GameApplication.h"
#include "lobutil.h"

// This is where application-wide updates get executed in a fixed timestep based manner.
//  RenderPath::FixedUpdate is also called from here for the active component
void GameApplication::FixedUpdate()
{
    lobster_fixed_update();
    wi::Application::FixedUpdate();
}


// This is where application-wide updates get executed once per frame.
//  RenderPath::Update is also called from here for the active component
void GameApplication::Update(float dt)
{
    lobster_variable_update(dt);
    wi::Application::Update(dt);
}
