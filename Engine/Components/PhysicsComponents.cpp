#include "pch.h"
#include "PhysicsComponents.h"
#include "Objects/GameObject.h"

namespace nc
{
	bool nc::PhysicsComponent::Create(void* data)
	{
		m_drag = 0.95f;
		return false;
	}

	void nc::PhysicsComponent::Destroy()
	{
	}

	void nc::PhysicsComponent::Update()
	{
		m_velocity = m_velocity + m_force * m_owner->m_engine->GetTimer().DeltaTime();
		m_velocity = m_velocity * m_drag;
		m_owner->m_transform.position = m_owner->m_transform.position + m_velocity * m_owner->m_engine->GetTimer().DeltaTime();
	}
}

