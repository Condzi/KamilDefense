/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include "AnimatedDrawable.hpp"

namespace kd
{
	void AnimatedDrawable::setTextureSheet( std::weak_ptr<sf::Texture> tex )
	{
		if ( tex.expired() )
			cgf::Logger::Log( std::string( SHOW_REAL_NAME( this ) ) + " texture is not assigned / is expired", cgf::Logger::ERROR );
		else
			this->textureSheet = tex.lock();
	}

	sf::IntRect AnimatedDrawable::GetFrame( uint16_t id )
	{
		if ( id > this->framesRect.size() - 1 )
		{
			cgf::Logger::Log( "Given id is bigger that amount of frames", cgf::Logger::ERROR );
			return sf::IntRect();
		}

		return this->framesRect[id];
	}

	void AnimatedDrawable::SetAnimationCurrentFrameID( uint16_t id )
	{
		if ( id > this->framesRect.size() - 1 )
		{
			cgf::Logger::Log( "Given id is bigger that amount of frames", cgf::Logger::ERROR );
			return;
		}

		this->animationCurrentFrameID = id;
	}

	void AnimatedDrawable::AddFrame( const sf::IntRect& rect )
	{
		if ( rect.left + rect.width > this->textureSheet.lock()->getSize().x ||
			rect.top + rect.height > this->textureSheet.lock()->getSize().y )
		{
			cgf::Logger::Log( "Given rect is bigger than texture sheet", cgf::Logger::ERROR );
			return;
		}

		this->framesRect.push_back( rect );
	}

	void AnimatedDrawable::setSpriteToApply( sf::Sprite* sprite )
	{
		if ( !sprite )
		{
			cgf::Logger::Log( "Sprite to apply is nullptr", cgf::Logger::ERROR );
			return;
		}

		this->spriteToApply = sprite;
	}

	void AnimatedDrawable::animationUpdate( seconds_t dt )
	{
		if ( !this->spriteToApply || this->textureSheet.expired() || this->framesRect.empty() )
		{
			cgf::Logger::Log( "Cannot update animation, conditions didn't fulfil", cgf::Logger::ERROR );
			return;
		}
		if ( this->animationIsPaused )
			return;
		static bool alreadyUpdated = false;
		if ( !this->animationIsPlaying && !alreadyUpdated )
		{
			this->spriteToApply->setTexture( *this->textureSheet.lock() );
			this->spriteToApply->setTextureRect( this->framesRect[0] );
			alreadyUpdated = true;
			return;
		}
		alreadyUpdated = false;

		this->animationCurrentTime -= dt;
		if ( this->animationCurrentTime <= 0.0f )
		{
			this->animationCurrentTime = this->animationFrameTime - abs( this->animationCurrentTime );

			if ( this->animationCurrentFrameID + 1 < this->framesRect.size() )
				this->animationCurrentFrameID++;
			else
			{
				this->animationCurrentFrameID = 0;
				if ( !this->animationIsLooped )
				{
					this->animationIsPlaying = false;
				}
			}

			this->spriteToApply->setTexture( *this->textureSheet.lock() );
			this->spriteToApply->setTextureRect( this->framesRect[this->animationCurrentFrameID] );
		}
	}
}