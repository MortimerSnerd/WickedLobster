#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

class GameApplication : public wi::Application
{

public:
	// This is where application-wide updates get executed once per frame.
	//  RenderPath::Update is also called from here for the active component
    void Update(float dt) override;

	// This is where application-wide updates get executed in a fixed timestep based manner.
	//  RenderPath::FixedUpdate is also called from here for the active component
    void FixedUpdate() override;


};

#endif
