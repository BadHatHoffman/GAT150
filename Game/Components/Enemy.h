#pragma once
#include "Components/Component.h"

namespace nc
{
	class Enemy : public Component
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new Enemy{ *this }; }

		virtual void Update() override;
	};
}