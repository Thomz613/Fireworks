#include <Trail.h>

Trail::Trail(ci::vec2 target, Direction dir)
{
	m_dir = dir;
	m_endPos = target;

	// Set the starting position (screen border)
	switch (dir)
	{
	case Trail::DIR_REVERSE_VERTICAL:
		m_startPos = vec2(target.x, 0);
		break;
	case Trail::DIR_VERTICAL:
		m_startPos = vec2(target.x, getWindowHeight() - 1);
		break;
	case Trail::DIR_REVERSE_HORIZONTAL:
		m_startPos = vec2(getWindowWidth() - 1, target.y);
		break;
	case Trail::DIR_HORIZONTAL:
		m_startPos = vec2(0, target.y);
		break;
	default:
		throw std::invalid_argument("[ERROR][Trail::Trail] Direction is not referenced.");
	}

	m_headPos = m_startPos;

	m_blastAltitudeReached = false;
}

Trail::~Trail()
{
}

void Trail::update()
{
	// Don't keep trace of particles who died
	for (std::vector<Entity>::iterator entity_it = m_entities.begin(); entity_it != m_entities.end();)
	{
		if (entity_it->isOld())
		{
			entity_it = m_entities.erase(entity_it);
		}
		else
		{
			entity_it->update();
			++entity_it;
		}
	}

	// Add new entity to the trail if the head hasn't reached its end position,
	//  else set the boolean accordingly
	if (m_headPos != m_endPos)
	{
		addEntity();
	}
	else
	{
		m_blastAltitudeReached = true;
	}
}

void Trail::draw() const
{
	for(auto & entity : m_entities)
	{
		entity.draw(Entity::DrawShape::SHAPE_SQUARE);
	}
}

bool Trail::isBlastAltitudeReached() const
{
	return m_blastAltitudeReached;
}

bool Trail::wasDrawn() const
{
	return (m_blastAltitudeReached && !m_entities.size());
}

vec2 Trail::getEndPos() const
{
	return m_endPos;
}

vec2 Trail::getHeadPos() const
{
	return m_headPos;
}

Trail::Direction Trail::getDirection() const
{
	return m_dir;
}

Trail::Direction Trail::randomDirection()
{
	const int dir = Rand::randInt(4);
	switch (dir)
	{
	case 0:
		return Trail::DIR_VERTICAL;
	case 1:
		return Trail::DIR_REVERSE_VERTICAL;
	case 2:
		return Trail::DIR_HORIZONTAL;
	case 3:
		return Trail::DIR_REVERSE_HORIZONTAL;
	default:
		throw std::runtime_error("[ERROR][Trail::randomDirection] tried to access an unknown direction");
	}
}

void Trail::addEntity()
{
	// Pos
	const vec2 pos = m_headPos;
	switch (m_dir)
	{
	case Trail::DIR_VERTICAL:
		--m_headPos.y;
		break;
	case Trail::DIR_REVERSE_VERTICAL:
		++m_headPos.y;
		break;
	case Trail::DIR_HORIZONTAL:
		++m_headPos.x;
		break;
	case Trail::DIR_REVERSE_HORIZONTAL:
		--m_headPos.x;
		break;
	default:
		throw std::invalid_argument("[ERROR][Trail::addEntity] Direction is not referenced.");
		break;
	}

	// Color
	const Color col = Color::white();

	// Size
	const float size = 2.5f;

	// Dir
	const vec2 dir(0.0f, 0.0f);

	// Velocity
	const float vel = 0.0f;

	// Lifespan
	const int lifespan = 30;

	Entity newEntity(pos, col, size, dir, vel, lifespan);
	m_entities.emplace_back(newEntity);
}
