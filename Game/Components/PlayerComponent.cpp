#include "pch.h"
#include "PlayerComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"

namespace nc
{
	bool nc::PlayerComponent::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
		return true;
	}

	void nc::PlayerComponent::Destroy()
	{
	}

	void nc::PlayerComponent::Update()
	{
		auto contacts = m_owner->GetContactsWithTag("Floor");
		bool onGround = !contacts.empty();

		//player controller
		nc::Vector2 force{ 0,0 };
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = -100;
			//m_owner->m_transform.angle = m_owner->m_transform.angle - 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			force.x = 100;
			//m_owner->m_transform.angle = m_owner->m_transform.angle + 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
		{
			force.y = -1500;
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				audioComponent->Play();
			}

		}

		PhysicsComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);

			Vector2 velocity = component->GetVelocity();

			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
			if (velocity.x <= -0.15f) spriteComponent->Flip();
			if (velocity.x >= 0.15f) spriteComponent->Flip(false);
		}

		auto coinContacts = m_owner->GetContactsWithTag("Coin");
		for (GameObject* contact : coinContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}

		//auto enemyContacts = m_owner->GetContactsWithTag("Enemy");
		//for (GameObject* contact : coinContacts)
		//{
		//	AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		//	if (audioComponent)
		//	{
		//		
		//		//play audio
		//	}
		//}

	}
}
