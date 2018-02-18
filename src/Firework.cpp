#include <Firework.h>


Firework::Firework(const vec2 & target, Trail::Direction direction, int blast_particles_count)
	: m_trail(target, direction), m_blastParticlesCount(blast_particles_count)
{
	m_blast = Blast();
	m_blasted = false;
}

Firework::~Firework()
{
}

void Firework::update()
{
	m_trail.update();
	m_blast.update();

	// Detonate only once
	if (m_trail.isBlastAltitudeReached() && !m_blasted)
	{
		detonate();
		m_blasted = true;
	}
}

void Firework::draw() const
{
	m_trail.draw();
	m_blast.draw();
}

bool Firework::wasDrawn() const
{
	return (!m_blast.count() && m_trail.wasDrawn());
}

void Firework::detonate()
{
	const Color color = Blast::getRandomColor();
	const float size = 3.0f;
	const vec2 blastPosition = m_trail.getEndPos();

	m_blast.addEntities(m_blastParticlesCount, color, size, blastPosition);
}
