#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include <vector>

#include <Entity.h>


/**
 * \brief The default number of particles to add when a blast is generated
 */
#define ENTITIES_TO_ADD 10

using namespace ci;
using namespace ci::app;

/**
* \brief The Blast class is used to simulate an explosion of particles
* \see Entity
* 
* The Blast class uses the Entity class as particles
*/
class Blast
{
public:
	/**
	 * \brief The Behavior enum tells how the particles should behave
	 */
	enum Behavior
	{
		BHV_FREE_WILL,		///< The particles will follow their course
		BHV_FOLLOW_CURSOR	///< The particles will follow the mouse cursor
	};

public:
	Blast();
	Blast(int amount);
	~Blast();

public:
	/**
	 * \brief Get a random color to use for the particles
	 * \return A random color between a selection
	 */
	static Color getRandomColor();

public:
	/**
	 * \brief Updates each particle (position + lifetime)
	 * \param boundInScreen Are the particles bound to the window?
	 * 
	 * If the boundInScreen param is set to true, when a particle
	 * reaches a window edge, it will be placed at the opposite one
	 */
	void update(bool boundInScreen = false);
	
	/**
	 * \brief Draws the particles of the blast
	 */
	void draw() const;

	/**
	 * \brief Accessor (value) to the number of still alive particles of the blast 
	 * \return the count of the still alive particles of the blast
	 */
	size_t count() const;

	/**
	 * \brief Add a particle to the blast
	 * \param color Its color
	 * \param size Its starting size
	 * \param pos Its starting position on the window
	 * \param dir The direction to follow
	 * \param velocity Its initial velocity
	 * \param lifespan Its maximum lifespan (If ommited, the Entity::DEFAULT_ENTITY_LIFESPAN will be used)
	 */
	void addEntity(Color color, float size, vec2 pos, vec2 dir, float velocity, int lifespan = DEFAULT_ENTITY_LIFESPAN);

	/**
	 * \brief Add multiple particles to the blast
	 * \param amount The number of particles to add
	 * \param color The color of the particles (if ommited, white will be used)
	 * \param size The starting size of the particles (if ommited, Entity::DEFAULT_PARTICLE_SIZE will be used)
	 * \param pos The starting position on the window (if ommited, Entity::DEFAULT_ENTITY_POS will be used)
	 * \param lifespan The maximum lifespan of the particles (if ommited, Entity::DEFAULT_ENTITY_LIFESPAN will be used)
	 */
	void addEntities(int amount, Color color = Color::white(), float size = DEFAULT_PARTICLE_SIZE, vec2 pos = DEFAULT_ENTITY_POS, int lifespan = DEFAULT_ENTITY_LIFESPAN);

	/**
	 * \brief Remove particles from the blast (they will be deleted)
	 * \param amount The amount of particles to remove
	 */
	void removeEntities(int amount);

	/**
	 * \brief Handles the keyboard key pressed (down) events
	 * \param event The keyboard key event to evaluate
	 */
	void keyDown(KeyEvent event);

	/**
	 * \brief Handles the mouse click (down) events
	 * \param event The mouse event to evaluate (here, the button pressed)
	 */
	void mouseDown(MouseEvent event);


	/**
	 * \brief Handles the mouse movement events
	 * \param event The mouse event to evaluate (here, the cursor moving)
	 */
	void mouseMove(MouseEvent event);

private:
	std::vector<Entity> m_blast;	///< The particles container of the blast
	vec2 m_destination;				///< The Target destination of the particles (used when they should follow the cursor)
	Behavior m_behavior;			///< The behavior the particles should adopt
};

