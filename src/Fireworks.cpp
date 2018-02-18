#include <Fireworks.h>

Fireworks::Fireworks()
{
}


Fireworks::~Fireworks()
{
}

void Fireworks::update()
{
	for (std::vector<Firework>::iterator fireworks_it = m_fireworks.begin(); fireworks_it != m_fireworks.end();)
	{
		// If a firework was drawn, and each of its particles died, it is no longer needed to keep trace of it
		if (fireworks_it->wasDrawn())
		{
			fireworks_it = m_fireworks.erase(fireworks_it);
		}
		else
		{
			fireworks_it->update();
			++fireworks_it;
		}
	}
}

void Fireworks::draw()
{
	for (auto & firework : m_fireworks)
	{
		firework.draw();
	}
}

void Fireworks::mouseDown(MouseEvent event)
{
	// Left mouse button case: add 1 firework
	if (event.isLeftDown())
	{
		// Store mouse click position on window, then use it as the detonation height
		const vec2& mousePos = event.getPos();
		const Trail::Direction direction = Trail::Direction::DIR_VERTICAL;
		const int particles = 40;

		m_fireworks.push_back(Firework(mousePos, direction, particles));
	}
	// Right mouse button case: add multiple fireworks at random positions
	else if (event.isRightDown())
	{
		const size_t fireworksToAdd = 5;
		const ivec2 particlesBounds(30, 100);

		for (size_t i = 0; i < fireworksToAdd; ++i)
		{
			// Generate a random number of particles
			const int particles = particlesBounds.x + Rand::randInt(particlesBounds.y - particlesBounds.x + 1);

			// Generate a random "in window" position
			const vec2 randomPos(Rand::randInt(getWindowWidth()), Rand::randInt(getWindowHeight()));
			// Generate a random direction
			const Trail::Direction direction = Trail::randomDirection();
			m_fireworks.push_back(Firework(randomPos, direction, particles));
		}
	}
}
