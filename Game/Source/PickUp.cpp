#include "PickUp.h"
#include "Player.h"

void PickUp::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		dynamic_cast<Player*>(actor)->SetFireModifer(2.0f);
		m_destroyed = true;
	}
}
