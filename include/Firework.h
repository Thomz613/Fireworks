#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include <vector>

#include <Trail.h>
#include <Blast.h>

/**
 * \brief The Firework class is the combination of a trail and a blast.
 * 
 * The trail will be drawn first, then when the detonation window position is reached,
 * the blast will be shown and updated.
 */
class Firework
{
public:
	Firework(const vec2& target, Trail::Direction direction, int blast_particles_count);
	~Firework();

public:
	/**
	 * \brief Updates a firework (trail + blast position and lifetime)
	 */
	void update();

	/**
	 * \brief Draws a firework (trail + blast particles)
	 */
	void draw() const;

	/**
	 * \brief Test to check if particles of the blast are still "alive"
	 * \return true if every particle of the blast died
	 */
	bool wasDrawn() const;

private:
	/**
	 * \brief Detonate the firework if the expected height is reached
	 */
	void detonate();

private:
	Trail m_trail;	///< The trail part of the firework
	Blast m_blast;	///< The blast part of the firework

	int m_blastParticlesCount;	///< The count of the particles the blast should have
	bool m_blasted;				///<  Will be set to true when the blast will have detonated
};

