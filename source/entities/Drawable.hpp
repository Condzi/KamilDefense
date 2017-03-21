/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#pragma once

#include <cinttypes>
#include <memory>

namespace sf
{
	class Texture;
	class RenderTarget;
}

namespace kd
{
	class Drawable
	{
	public:
		Drawable() :
			drawLayer( 0 )
		{}
		virtual ~Drawable() = default;

		virtual void SetTexture( std::weak_ptr<sf::Texture> tex ) = 0;
		virtual void SetDrawLayer( int8_t val )
		{
			this->drawLayer = val;
		}
		virtual int8_t GetDrawLayer()
		{
			return this->drawLayer;
		}

		virtual void Draw( sf::RenderTarget& target ) = 0;

	protected:
		int8_t drawLayer;
	};
}
