#include <Blast.h>

Blast::Blast()
{
	m_behavior = Behavior::BHV_FREE_WILL;
}

Blast::Blast(int amount)
{
	m_behavior = Behavior::BHV_FREE_WILL;
	m_blast.reserve(amount);
	addEntities(amount);
}


Blast::~Blast()
{
}

Color Blast::getRandomColor()
{
	// Don't forget to update the rand bound if colors are added/deleted
	Color color(Color::white());
	int colorIndex = Rand::randInt(7);

	switch (colorIndex)
	{
	case 0:
		break;
	case 1:
		color = Color(1.0f, 0.0f, 0.0f);
		break;
	case 2:
		color = Color(0.0f, 1.0f, 0.0f);
		break;
	case 3:
		color = Color(0.0f, 0.0f, 1.0f);
		break;
	case 4:
		color = Color(1.0f, 1.0f, 0.0f);
		break;
	case 5:
		color = Color(1.0f, 0.0f, 1.0f);
		break;
	case 6:
		color = Color(0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

	return color;
}

void Blast::update(bool boundInScreen)
{
	for (std::vector<Entity>::iterator it = m_blast.begin(); it != m_blast.end();)
	{
		// Entity is too old => remove it from the blast
		if (it->isOld())
		{
			it = m_blast.erase(it);
		}
		else
		{
			vec2 dir = it->getDir();
			if (m_behavior == Behavior::BHV_FOLLOW_CURSOR)
			{
				dir = glm::normalize(m_destination - it->getPosition());
			}

			it->update(boundInScreen, dir);
			++it;
		}
	}
}

void Blast::draw() const
{
	for(auto & entity : m_blast)
	{
		entity.draw();
	}
}

size_t Blast::count() const
{
	return m_blast.size();
}

void Blast::removeEntities(int amount)
{
	// It should be wise to remove the oldests particles and not the newests
	if (m_blast.size() >= amount)
	{
		for (int i = 0; i < amount; ++i)
		{
			m_blast.pop_back();
		}
	}
}

void Blast::keyDown(KeyEvent event)
{
	// When 't' is pressed, the particles will follow the cursor
	if (event.getCode() == KeyEvent::KEY_t)
	{
		m_behavior = Behavior::BHV_FOLLOW_CURSOR;
		console() << "Behavior set to " << m_behavior << std::endl;
	}
	// When 'f' is pressed, the particles will follow their course
	else if (event.getCode() == KeyEvent::KEY_f)
	{
		m_behavior = Behavior::BHV_FREE_WILL;
		console() << "Behavior set to " << m_behavior << std::endl;
	}
}

void Blast::mouseDown(MouseEvent event)
{
	// Add entities when left mouse button is pressed
	if (event.isLeftDown())
	{
		const int count = ENTITIES_TO_ADD;

		Color color = getRandomColor();
		addEntities(count, color, DEFAULT_PARTICLE_SIZE, event.getPos());
	}
	// Remove entities when right mouse button is pressed
	else if (event.isRightDown())
	{
		const int amount = 1;
		removeEntities(amount);
	}
}

void Blast::mouseMove(MouseEvent event)
{
	m_destination = event.getPos();
}

void Blast::addEntity(Color color, float size, vec2 pos, vec2 dir, float velocity, int lifespan)
{
	m_blast.push_back(Entity(pos, color, size, dir, velocity, lifespan));
}

void Blast::addEntities(int amount, Color color, float size, vec2 pos, int lifespan)
{
	// Generate a random velocity within acceptable bounds
	const float velUpperBound = 5.0f;
	for (size_t i = 0; i < amount; ++i)
	{
		vec2 dir = Rand::randVec2();
		float velocity = Rand::randFloat(1.0f, velUpperBound);

		addEntity(color, size, pos, dir, velocity, lifespan);
	}
}
