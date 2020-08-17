#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Core/Json.h"
#include "Components/PhysicsComponents.h"
#include "Components/SpriteComponent.h"
#include "Components/PlayerComponent.h"
#include "Core/Factory.h"

nc::Engine engine;
nc::GameObject player;
nc::Factory<nc::Object, std::string> objectFactory;

int main(int, char**)
{
	engine.Startup();

	objectFactory.Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
	objectFactory.Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);
	objectFactory.Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);
	objectFactory.Register("SpriteComponent", nc::Object::Instantiate<nc::SpriteComponent>);

	nc::GameObject* player = objectFactory.Create<nc::GameObject>("GameObject");

	rapidjson::Document document;
	nc::json::Load("json.txt", document);

	std::string str;
	nc::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	nc::json::Get(document, "bool", b);
	std::cout << b << std::endl;

	int i1;
	nc::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	nc::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	nc::json::Get(document, "float", f);
	std::cout << f << std::endl;

	nc::Vector2 v2;
	nc::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	nc::Color color;
	nc::json::Get(document, "color", color);
	std::cout << color << std::endl;



	player->Create(&engine);
	nc::json::Load("player.txt", document);
	player->Read(document);

	nc::Component* component = objectFactory.Create<nc::Component>("PhysicsComponent");
	player->AddComponent(component);
	component->Create();

	component = objectFactory.Create<nc::Component>("SpriteComponent");
	player->AddComponent(component);
	nc::json::Load("sprite.txt", document);
	component->Read(document);
	component->Create();

	component = objectFactory.Create<nc::Component>("PlayerComponent");
	player->AddComponent(component);
	component->Create();
	//texture
	
	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());
	
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
		player->Update();




		//draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();
		
		background->Draw({ 0, 0 }, {1.0f, 1.0f }, 0);
		
		player->Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();//END
	}
	
	engine.Shutdown();

	return 0;
}

