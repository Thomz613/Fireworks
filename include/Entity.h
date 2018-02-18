#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/Rand.h>


#define DEFAULT_PARTICLE_SIZE 2.5f		///< The default size a particle should have when generated
#define PARTICLE_DECAY_FACTOR 0.99f		///< The rate at which the particle dies

#define DEFAULT_ENTITY_POS getWindowSize() / 2	///< Default particle start position
#define DEFAULT_ENTITY_LIFESPAN 500				///< The default lifespan of a particle

using namespace ci;
using namespace ci::app;

class Entity
{
public:
	/**
	 * \brief The DrawShape enum represents the shape the particle should be represented with
	 */
	enum DrawShape
	{
		SHAPE_CIRCLE,
		SHAPE_SQUARE
	};

public:
	Entity();
	Entity(vec2 pos, Color color = Color::white(), float size = 0.0f, int baseLifespan = DEFAULT_ENTITY_LIFESPAN);
	Entity(vec2 pos, Color color, float size, vec2 dir, float velocity, int baseLifespan = DEFAULT_ENTITY_LIFESPAN);
	~Entity();

public:
	/**
	 * \brief Updates a particle (position + lifetime)
	 * \param boundInScreen Should the particle always stay in window bounds?
	 * \param forcedDir The direction where the particle should be attracted to
	 * 
	 * Optional parameters can be set to override the particle's behavior
	 */
	void update(bool boundInScreen = false, vec2 forcedDir = vec2(-10.0f, -10.0f));
	
	/**
	 * \brief Draws the particle
	 * \param shape The shape used to draw the particle
	 */
	void draw(DrawShape shape = SHAPE_CIRCLE) const;

	/**
	 * \brief Accessor (value) to the position of the particle
	 * \return The position of the particle
	 */
	vec2 getPosition() const;
	
	/**
	 * \brief Accessor (value) to the direction of the particle
	 * \return The direction of the particle
	 */
	vec2 getDir() const;

	/**
	 * \brief Test to check if the particle should still be drawn
	 * \return True if the particle reached its lifespan
	 */
	bool isOld() const;

private:
	/**
	 * \brief Test to check if the particle position is in window's bounds
	 * \return True if the particle position is in window's bounds
	 */
	bool inWindowBounds() const;

	/**
	 * \brief Get a random lifespan for a particle
	 * \param baseLifespan The base lifespan to use as a starting value
	 * \return A randomized lifespan
	 * 
	 * The randomized lifespan will be computed using a base one, and
	 * bound around this value
	 */
	int randomLifespan(int baseLifespan) const;

	// Will update size regarding age
	/**
	 * \brief Updates the size of the particle regarding its current age
	 * 
	 * As the particle ages, its size disminish
	 */
	void updateSize();

private:
	vec2 m_pos;				///< The position of the particle
	vec2 m_dir;				///< The direction of the particle
	float m_size;			///< The current size of the particle
	float m_startingSize;	///< The Start size of the particle. Used with size regarding age
	float m_velocity;		///< The velocity of the particle
	Color m_color;			///< The color of the particle
	int m_lifespan;			///< The max lifespan of the particle
	int m_age;				///< The current age of the particle
};

