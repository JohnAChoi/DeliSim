
#include "GameState.h"
#include "Behavior.h"
#include "../Renderer/RenderTest.h"
#include <algorithm>

bool descending (Engine::Behavior* first, Engine::Behavior* second)
{
	return (first->GetDepth() > second->GetDepth());
}

namespace Engine
{

	GameState*	pGameState = NULL;


	GameState::GameState ( void )
	{
		m_next_id = 0;
		pGameState = this;

		CTime::Init();
	}

	GameState::~GameState ( void )
	{
		// TODO: go through and free stuff
		for ( auto t_behavior = m_behaviors.begin(); t_behavior != m_behaviors.end(); ++t_behavior ) {
			//delete (*t_behavior);	
			DeleteObject(*t_behavior);
		}
		for ( uint i = 0; i < 2; ++i ) {
			Step();
		}


		if ( pGameState == this ) {
			pGameState = NULL;
		}
	}

	uint32_t GameState::AddBehavior ( Behavior* n_behavior )
	{
		m_next_id += 1;
		m_behaviors_to_add.push_back( n_behavior );
		return m_next_id;
	}
	void GameState::RemoveBehavior ( Behavior* n_behavior )
	{
		// Loop through the list and remove the object
		auto t_behavior = m_behaviors.begin();
		while ( t_behavior != m_behaviors.end() )
		{
			if ( *t_behavior == n_behavior ) {
				t_behavior = m_behaviors.erase(t_behavior);
				// Found object, so return
				return;
			}
			else {
				++t_behavior;
			}
		}
	}

	void GameState::Step ( void )
	{
		CTime::Tick();

		// First delete all behaviors
		auto t_behavior = m_behaviors_to_delete.begin();
		while ( t_behavior != m_behaviors_to_delete.end() )
		{
			t_behavior->m_t -= Time::deltaTime;
			if ( t_behavior->m_t <= 0.0 ) {
				t_behavior->m_o->OnDestroy();
				delete t_behavior->m_o;
				t_behavior = m_behaviors_to_delete.erase(t_behavior);
			}
			else {
				++t_behavior;
			}
		}
		// Now add all behaviors
		for ( auto t_behavior = m_behaviors_to_add.begin(); t_behavior != m_behaviors_to_add.end(); ++t_behavior )
		{
			(*t_behavior)->OnCreate();
			m_behaviors.push_back(*t_behavior);
		}
		m_behaviors_to_add.clear();

		// Now step through behaviors
		for ( auto t_behavior = m_behaviors.begin(); t_behavior != m_behaviors.end(); ++t_behavior ) {
			if ( (*t_behavior)->m_active ) {
				(*t_behavior)->Update();
			}
		}
		for ( auto t_behavior = m_behaviors.begin(); t_behavior != m_behaviors.end(); ++t_behavior ) {
			if ( (*t_behavior)->m_active ) {
				(*t_behavior)->LateUpdate();
			}
		}
	}

	void GameState::Draw ( void )
	{
		SDL_RenderClear ((ren)->render);
		
		std::list<Behavior*> sorted_behaviors = m_behaviors;
		
		// Sort behaviors by render depth
		//THIS DON'T FUCKING WORK CUZ THEY SAID SO!!!!!
		//std::sort(sorted_behaviors.begin(), sorted_behaviors.end(), descending);

		//But this does because std::list has its own sort function. Bitch.
		sorted_behaviors.sort(descending);

		// Step through behaviors
		for ( auto t_behavior = sorted_behaviors.begin(); t_behavior != sorted_behaviors.end(); ++t_behavior ) {
			if ( (*t_behavior)->m_active ) {
				(*t_behavior)->Draw();
			}
		}
		SDL_RenderPresent ((ren)->render);
	}


	void GameState::DeleteObject ( Behavior* n_behavior ) {
		DeleteObjectDelayed( n_behavior, -1 );
	}

	void GameState::DeleteObjectDelayed ( Behavior* n_behavior, const Real n_time ) {
		auto t_behavior = m_behaviors_to_delete.begin();
		while ( t_behavior != m_behaviors_to_delete.end() )
		{
			t_behavior->m_t -= Time::deltaTime;
			if ( t_behavior->m_o == n_behavior ) {
				return;
			}
			else {
				++t_behavior;
			}
		}
		deleteInfo_t del_info;
		del_info.m_o = n_behavior;
		del_info.m_t = n_time;
		m_behaviors_to_delete.push_back( del_info );
	}

}