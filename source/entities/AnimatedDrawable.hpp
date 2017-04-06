/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Drawable.hpp"
#include "framework/Config.hpp"
#include "framework/Logger.hpp"
#include "Types.hpp"

namespace kd
{
	/*
	===============================================================================
		Extension for Drawable class that help animate Entities.

	===============================================================================
	*/
	class AnimatedDrawable :
		public Drawable
	{
	public:
		AnimatedDrawable() :
			animationFrameTime( 0.0f ),
			animationCurrentTime( 0.0f ),
			animationCurrentFrameID( 0 ),
			animationIsPaused( false ),
			animationIsLooped( false ),
			animationIsPlaying( false ),
			spriteToApply( nullptr )
		{}
		virtual ~AnimatedDrawable() = default;

		sf::IntRect GetFrame( uint16_t id );
		seconds_t GetFrameTime()
		{
			return this->animationFrameTime;
		}
		uint16_t GetAnimationCurrentFrameID()
		{
			return this->animationCurrentFrameID;
		}
		bool IsAnimationPaused()
		{
			return this->animationIsPaused;
		}
		bool IsAnimationPlaying()
		{
			return this->animationIsPlaying;
		}
		bool IsAnimationLooped()
		{
			return this->animationIsLooped;
		}

		void SetFrameTime( seconds_t time )
		{
			this->animationFrameTime = time;
		}
		void SetAnimationCurrentFrameID( uint16_t id );
		void SetAnimationLooped( bool val )
		{
			this->animationIsLooped = val;
		}
		void Play()
		{
			this->animationIsPlaying = true;
		}
		void Stop()
		{
			this->animationIsPlaying = false;
			this->animationCurrentFrameID = 0;
			this->animationCurrentTime = 0.0f;
		}
		void Pause()
		{
			this->animationIsPaused = true;
		}

		void AddFrame( const sf::IntRect& rect );

	protected:
		seconds_t animationFrameTime;
		seconds_t animationCurrentTime;
		uint16_t animationCurrentFrameID;
		bool animationIsPaused;
		bool animationIsLooped;
		bool animationIsPlaying;

		void setSpriteToApply( sf::Sprite* sprite );
		void setTextureSheet( std::weak_ptr<sf::Texture> tex );
		void animationUpdate( seconds_t dt );

	private:
		std::vector<sf::IntRect> framesRect;
		std::weak_ptr<sf::Texture> textureSheet;
		sf::Sprite* spriteToApply;
	};
}