
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <vector>
#include <list>
#include <string>
#include "types/standard_types.h"

#include "time/CTime.h"

namespace Engine
{
	class Behavior;

	class GameState
	{
	public:
					GameState ( void );
					~GameState ( void );

		void		Step ( void );
		void		Draw ( void );

		Behavior*	FindWithID ( const uint32_t );
		Behavior*	FindFirstWithName ( const std::string& );
		void		FindAllWithName ( const std::string&, std::vector<Behavior*>& );
		Behavior*	FindFirstWithTypename ( const std::string& );
		void		FindAllWithTypename ( const std::string&, std::vector<Behavior*>& );

		template<typename TYPE>
		Behavior*	CreateObject ( void ) { return new TYPE; };

		void		DeleteObject ( Behavior* );
		void		DeleteObjectDelayed ( Behavior*, const Real );
		
	private:
		friend Behavior;
		std::list<Behavior*>	m_behaviors;
		std::list<Behavior*>	m_behaviors_to_add;
		struct deleteInfo_t {
			Behavior*	m_o;
			Real		m_t;
		};
		std::list<deleteInfo_t>	m_behaviors_to_delete;

		uint32_t	AddBehavior ( Behavior* );
		uint32_t	m_next_id;
		void		RemoveBehavior ( Behavior* );
	};
	extern GameState* pGameState;
}

#endif//_GAME_STATE_H_