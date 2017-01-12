
#include "GameState.h"
#include "Behavior.h"

using namespace Engine;

Behavior::Behavior ( void )
	: m_id(0), m_render_depth(0), m_name("Behavior"), m_active(true)
{
	m_id = pGameState->AddBehavior(this);
}

Behavior::~Behavior ( void )
{
	if ( m_id != 0 ) {
		// Remove immediately from list
		pGameState->RemoveBehavior(this);
	}
}

// Getters
uint32_t Behavior::GetID ( void )
{
	return m_id;
}

const std::string& Behavior::GetName ( void )
{
	return m_name;
}

uint32_t Behavior::GetDepth (void)
{
	return m_render_depth;
}