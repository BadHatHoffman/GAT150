#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Core/Json.h"
#include "Components/PlayerComponent.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"

nc::Engine engine;
nc::Scene scene;
//nc::ObjectFactory objectFactory;

int main(int, char**)
{
	engine.Startup();

	scene.Create(&engine);

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);

	rapidjson::Document document;
	nc::json::Load("json.txt", document);

	nc::json::Load("scene.txt", document);
	scene.Read(document);
	
	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		//update
		engine.Update();
		scene.Update();

		//draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();
		
		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();//END
	}
	
	scene.Destroy();
	engine.Shutdown();

	return 0;
}

