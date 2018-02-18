#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include <vector>

#include <Firework.h>


/**
 * \brief Wrapper class used to gather multiple fireworks in one object
 */
class Fireworks
{
public:
	Fireworks();
	~Fireworks();

public:
	/**
	 * \brief updates each Firework
	 * \see Firework::update()
	 */
	void update();
	/**
	 * \brief draw each Firework
	 * \see Firework::update()
	 */
	void draw();

	/**
	 * \brief handles the mouse click (down) events
	 * \param event the mouse event to evaluate (here, the button pressed)
	 */
	void mouseDown(MouseEvent event);

private:
	std::vector<Firework> m_fireworks;

};

