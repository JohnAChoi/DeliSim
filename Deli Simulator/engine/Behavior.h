
#ifndef _GAME_BEHAVIOR_H_
#define _GAME_BEHAVIOR_H_

#include <string>

#define EngineExpose(_a) (void*(0));
#define ClassType(_a) public: virtual const std::string GetType ( void ) { return std::string( #_a ); }; private:

#include "types/standard_types.h"
#include "math/Vector2d.h"

namespace Engine
{
	class GameState;

	struct transform_t {
		Vector2d	position;
		Real		rotation;
		Vector2d	scale;

		transform_t ( void ) :
			position(0,0), rotation(0), scale(1,1)
		{
			;
		}
	};

	class Behavior
	{
		ClassType(Behavior)
	protected:
				virtual		~Behavior ( void );
	public:
		explicit			Behavior ( void );

		// Overridable behaviors
		virtual void		OnCreate ( void ) {};
		virtual void		OnDestroy ( void ) {};

		virtual void		Update ( void ) {};
		virtual void		LateUpdate ( void ) {};

		virtual void		Draw ( void ) {};

		// Getters
		uint32_t			GetID ( void );
		const std::string&	GetName ( void );
		uint32_t			GetDepth ( void );

	public:
		bool		m_active;
		transform_t	m_transform;

	protected:
		std::string	m_name;
		uint32_t m_render_depth;

	private:
		// System variables
		uint32_t	m_id;
		bool		m_has_init;

		friend GameState;
	};
}

#endif//_GAME_BEHAVIOR_H_
