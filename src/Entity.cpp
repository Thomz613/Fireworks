#include <Entity.h>

Entity::Entity()
{
	// Default start pos at window's center
	m_pos = DEFAULT_ENTITY_POS;
	m_dir = vec2(0, 0);
	m_size = DEFAULT_PARTICLE_SIZE;
	m_startingSize = m_size;
	m_velocity = 0.0f;
	m_color = Color::white();

	m_lifespan = randomLifespan(DEFAULT_ENTITY_LIFESPAN);

	m_age = 0;
}

Entity::Entity(vec2 pos, Color color, float size, int lifespan)
	: m_pos(pos), m_size(size), m_color(color)
{
	m_age = 0;
	m_dir = ci::Rand::randVec2();

	const float velUpperBound = 10.0f;
	m_velocity = ci::Rand::randFloat(1.0f, velUpperBound);

	if (m_size == 0.0f)	m_size = ci::Rand::randFloat(1.0f, getWindowHeight() / 10.0f);
	m_startingSize = m_size;

	m_lifespan = randomLifespan(lifespan);
}

Entity::Entity(vec2 pos, Color color, float size, vec2 dir, float velocity, int lifespan)
	: m_pos(pos), m_dir(dir), m_size(size), m_velocity(velocity), m_color(color)
{
	m_startingSize = m_size;
	m_age = 0;
	m_lifespan = randomLifespan(lifespan);
}


Entity::~Entity()
{
}

void Entity::update(bool boundInScreen, vec2 forcedDir)
{
	// Forcing direction to parameter
	if (forcedDir != vec2(-10.0f, -10.0f))
	{
		m_dir = forcedDir;
	}

	// Window's borders are linked together case
	// Teleport particle to opposite edge
	if (boundInScreen)
	{
		if (static_cast<int>(m_pos.x) < 0)	m_pos.x = static_cast<float>(getWindowWidth() - 1);
		if (static_cast<int>(m_pos.y) < 0)	m_pos.y = static_cast<float>(getWindowHeight() - 1);

		if (static_cast<int>(m_pos.x) >= getWindowWidth())		m_pos.x = 0.0f;
		if (static_cast<int>(m_pos.y) >= getWindowHeight())		m_pos.y = 0.0f;

		// Update particle position
		m_pos += m_dir * m_velocity;
	}
	else
	{
		// We don't need to update the particle if it goes out of the window
		if (inWindowBounds())	m_pos += m_dir * m_velocity;
	}

	++m_age;
	m_velocity *= PARTICLE_DECAY_FACTOR;
	updateSize();
}


void Entity::draw(DrawShape shape) const
{
	if (inWindowBounds())
	{
		gl::color(m_color);

		switch (shape)
		{
		case Entity::SHAPE_CIRCLE:
		{
			gl::drawSolidCircle(m_pos, m_size);
			break;
		}
		case Entity::SHAPE_SQUARE:
		{
			vec2 start(m_pos - (m_size / 2.0f));
			vec2 end(m_pos + (m_size / 2.0f));

			Rectf rectToDraw(start, end);

			gl::drawSolidRect(rectToDraw);
			break;
		}
		default:
		{
			throw std::invalid_argument("[ERROR][Entity::Draw] Draw shape is not referenced.");
			break;
		}
		}
	}
}

vec2 Entity::getPosition() const
{
	return m_pos;
}

vec2 Entity::getDir() const
{
	return m_dir;
}

bool Entity::isOld() const
{
	return (m_age > m_lifespan);
}

bool Entity::inWindowBounds() const
{
	if ((m_pos.x > 0 && m_pos.x < getWindowWidth() - 1) &&
		(m_pos.y > 0 && m_pos.y < getWindowHeight() - 1))
	{
		return true;
	}
	return false;
}

int Entity::randomLifespan(int baseLifespan) const
{
	const int range = 50;
	return Rand::randInt(baseLifespan - range, baseLifespan + range + 1);
}

void Entity::updateSize()
{
	// Assert lifespan is greater than 0
	if (m_lifespan > 0)
	{
		const float newSize = m_startingSize * (1.0f - (m_age / static_cast<float>(m_lifespan)));
		m_size = newSize;
	}
}
