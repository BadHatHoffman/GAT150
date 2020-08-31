#include "pch.h"
#include "Enemy.h"
#include "Components/PhysicsComponents.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"

namespace nc
{
	bool Enemy::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
		return true;
	}

	void Enemy::Destroy()
	{
	}

	void Enemy::Update()
	{
		GameObject* player = m_owner->m_scene->Find("Player");
		if (player)
		{
			Vector2 direction = player->m_transform.position - m_owner->m_transform.position;
			Vector2 force = direction.Normalized() * 5.0f;

			PhysicsComponent* physicsComponent = m_owner->GetComponent<PhysicsComponent>();
			physicsComponent->ApplyForce(force);
		}
	}
}
