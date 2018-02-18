#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include <vector>

#include <Fireworks.h>

using namespace ci;
using namespace ci::app;

class FireworksApp : public App {
public:
	static void prepareSettings(App::Settings* settings);

public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;

private:
	Fireworks m_fireworks;
};

void FireworksApp::prepareSettings(App::Settings * settings)
{
	settings->setWindowSize(800, 600);
	settings->setFrameRate(60.0f);
}

void FireworksApp::setup()
{
}

void FireworksApp::mouseDown(MouseEvent event)
{
	m_fireworks.mouseDown(event);
}

void FireworksApp::update()
{
	m_fireworks.update();
}

void FireworksApp::draw()
{
	gl::clear(Color(0, 0, 0));

	m_fireworks.draw();
}

CINDER_APP(FireworksApp, RendererGl, FireworksApp::prepareSettings)
