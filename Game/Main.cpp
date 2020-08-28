#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Core/Json.h"
#include "Components/PlayerComponent.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "TileMap.h"

nc::Engine engine;
nc::Scene scene;
//nc::ObjectFactory objectFactory;

int main(int, char**)
{
	engine.Startup();


	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object> );

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);
	scene.Create(&engine);
	scene.Read(document);

	nc::TileMap tileMap;
	nc::json::Load("tileMap.txt", document);
	tileMap.Read(document);
	tileMap.Create(&scene);
	
	/*for (size_t i = 0; i < 10; i++)
	{
		nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
		gameObject->m_transform.position = nc::Vector2{ nc::random(0,800), nc::random(200,400) };
		gameObject->m_transform.angle = nc::random(0, 360);
		scene.AddGameObject(gameObject);
	}*/

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

