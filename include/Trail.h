#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include <vector>

#include <Entity.h>


/**
 * \brief The Trail class is used to simulate the smoke trail a firework produces when ignited
 *
 * The trail is a line and works using the Entity particle class
 * /see Entity
 */
class Trail
{
public:
	/**
	 * \brief The Direction enum represents the direction in which the trail will travel the window
	 */
	enum Direction
	{
		// Do not forget to update the randomDirection() method when the enum is updated
		DIR_VERTICAL,				///< From bottom to top
		DIR_REVERSE_VERTICAL,		///< From top to bottom
		DIR_HORIZONTAL,				///< From left to right
		DIR_REVERSE_HORIZONTAL		///< From right to left
	};

public:
	Trail(ci::vec2 target, Direction dir);
	~Trail();

public:
	/**
	 * \brief Updates the trail particles (position and lifetime)
	 */
	void update();

	/**
	 * \brief Draws the particles of the trail
	 */
	void draw() const;

	/**
	 * \brief Tests if the targeted detonation height is reached
	 * \return true if the targeted height is reached
	 */
	bool isBlastAltitudeReached() const;

	/**
	 * \brief Tests if the targeted detonation height was reached and all the particles died
	 * \return true if all the particles of the trail died and the blast altiture was reached
	 */
	bool wasDrawn() const;

	/**
	 * \brief Accessor (const) to the position at which the trail should stop being drawn
	 * \return The end position as a glm::vec2 object
	 */
	vec2 getEndPos() const;

	/**
	 * \brief Accessor (const) to the newest trail particle position
	 * \return The current positon as a glm::vec2 object
	 */
	vec2 getHeadPos() const;
	/**
	 * \brief Accessor (const) to the direction in which the trail travels the window
	 * \return The direction in which the particle travels
	 */
	Direction getDirection() const;

public:
	/**
	 * \brief Get a random Trail::Direction value
	 * \return A random direction
	 */
	static Direction randomDirection();

private:
	/**
	 * \brief Adds a particle to the trail at the head position
	 * 
	 * The head position will be updated when a particle is added
	 */
	void addEntity();

private:
	ci::vec2 m_startPos;		///< The coordinates in the window where the trail will start
	ci::vec2 m_endPos;			///< The position at which the trail should stop being drawn
	ci::vec2 m_headPos;			///< The position of the newest generated particle (the head of the trail)

	bool m_blastAltitudeReached;		///< Will be set to true when the detonation altitude will be reached
	Direction m_dir;					///< The direction in which the trail travels the window

	std::vector<Entity> m_entities;		///< Contains all the still alive particles
};

