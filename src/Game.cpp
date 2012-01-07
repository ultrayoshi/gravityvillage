#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

void Game::readKeyboard(int key, bool pressed)
{
  keys[key] = pressed;
}

void Game::init()
{
  timer.init();

  map.init(25, 30, 8, 10, 32, 32, "res/test.png");

  player.init(3, 8, "res/link.png");
  player.setCols(7);
  player.setTotalFrames(7);
  player.setWidth(16);
  player.setHeight(24);
  player.setAnimationTime(0.5f);

  //item.init(15, 6, "res/apple.png");
  //item.setScale(0.5f);

  //enemy.init(3, 15, "res/enemy.png");
  //enemy.setCols(4);
  //enemy.setTotalFrames(4);
  //enemy.setWidth(32);
  //enemy.setHeight(32);
  //enemy.setAnimationTime(0.5f);
  //enemy.setVelX(-70);
}

void Game::setCamera()
{
  GLfloat aspectRatio;
  aspectRatio = (GLfloat) window_w / (GLfloat) window_h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(90,aspectRatio,1,1000);

  gluLookAt(
      player.getX(), player.getY()+64, 150,
      player.getX(), player.getY()+64, 0,
      0, 1, 0
  );
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Game::render()
{
  setCamera();

  drawAxis();

  map.render();
  player.render();
  //item.render();
  //enemy.render();

  startRenderGUI();
  renderConsole();
  endRenderGUI();
}

void Game::update()
{
  float dt = timer.tick();

  player.update(dt);
  //item.update(dt);
  //enemy.update(dt);

  //if(player.collision(&item))
  //{
  //  item.setAlive(false);
  //}

  //if(player.collision(&enemy))
  //{
  //  exit(0);
  //}

  if(keys[27])
    exit(0);

  if(keys[GLUT_KEY_LEFT])
    player.move_left();
  else if(keys[GLUT_KEY_RIGHT])
    player.move_right();
  else
    player.halt();

  if(keys[32])
    player.jump();
}

void Game::renderConsole()
{
  char message[100];

  glColor3f(1.0f, 1.0f, 1.0f);

  sprintf(message, "FPS: %f", timer.getFPS());
  output(0, 25, message);
  sprintf(message, "Player position: %g,%g", player.getX(), player.getY());
  output(0, 50, message);
  sprintf(message, "Player is jumping: %d", player.isJumping());
  output(0, 75, message);
  sprintf(message, "Tile position: %d,%d", player.getRow(), player.getCol());
  output(0, 100, message);
  sprintf(message, "Tile type: %d", map.getTileType(player.getRow(), player.getCol()));
  output(0, 125, message);
}

void Game::output(int x, int y, char *string)
{
  int len, i;
  void *font = GLUT_BITMAP_TIMES_ROMAN_24;

  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

void Game::startRenderGUI()
{
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, window_w, window_h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void Game::endRenderGUI()
{
  glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void Game::setWindowWidth(int _window_w)
{
  window_w = _window_w;
}

int Game::getWindowWidth()
{
  return window_w; 
}

void Game::setWindowHeight(int _window_h)
{
  window_h = _window_h;
}

int Game::getWindowHeight()
{
  return window_h;
}

void Game::drawAxis()
{
  glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);
  glEnd();
}