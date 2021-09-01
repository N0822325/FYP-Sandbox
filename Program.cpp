#define SOUND
#include "FYP/Engine.h"

class FYP : public Engine
{
private:
  std::vector<Texture*> textureList;
  std::vector<Object*> objectList;

  Object* pointer;
  Object* hudItem;

  ProCamera camera;
  OrthCamera camera2;

  float ir = 0.1f; float ig = 0.5f; float ib = 0.9f;

public:

  FYP(int width, int height)
  {
    camera2.setProjection(0,width,0,height,-1,1);
    camera2.setCamera(glm::vec3(0,0,0));
    // camera.setProjection();
    camera.setCamera(glm::vec3(0,0,0));

    construct(width, height, "FYP", 60);
    start();
  }

  void userInitialse() override
  {
    float colour1[4] { 1.0, 1.0, 1.0, 1.0 };
    float colour2[4] { 0.0, 1.0, 1.0, 1.0 };
    // float colour3[4] { 0.3, 0.6, 0.2, 1.0 };
    float colour4[4] { 0.7, 0.3, 0.0, 1.0 };
    float bgc[4] { 0.4, 0.01, 0.2 };
    setBackgroundColour(bgc);

    textureList.push_back(new Texture("Resources/FYP.png"));
    textureList.push_back(new Texture("Resources/ntu.png"));

    hudItem = Plane(250,250,0, 5,5, colour2);
    pointer = Line(0,0,0, 0,0,1000, colour2);


    objectList.push_back(Cube(0,0,-20, 5,3,2, colour1));
    objectList.back()->setRotate(0,0,0);

    objectList.push_back(Cube(3,5,-10, 5,3,3, colour2));
    objectList.back()->setRotate(0,0,30);

    objectList.push_back(Cube(-5,0,-20, 5,5,5, colour4, textureList.front()));
    objectList.back()->setRotate(0,0,40);

    objectList.push_back(Plane(0,-10,-50, 50,50,colour1, textureList.back()));
    objectList.back()->setRotate(270,0,0);

  }


  void userInput(XEvent events) override
  {
    camera.cameraInput(events, getMousePos(&events));

    if(events.type == KeyPress)
    {
      if (events.xkey.keycode == 111) { //up
        objectList.front()->addTranslation(0, 1, 0);
      }
      if (events.xkey.keycode == 116) { // down
        objectList.front()->addTranslation(0, -1, 0);
      }
      if (events.xkey.keycode == 113) { // left
        objectList.front()->addTranslation(-1, 0, 0);
      }
      if (events.xkey.keycode == 114) { // right
        objectList.front()->addTranslation(1, 0, 0);
      }

      if (events.xkey.keycode == 80) { //up
        objectList.front()->addRotate(1,0,0);
      }
      if (events.xkey.keycode == 88) { // down
        objectList.front()->addRotate(-1,0,0);
      }
      if (events.xkey.keycode == 83) { // left
        objectList.front()->addRotate(0,1,0);
      }
      if (events.xkey.keycode == 85) { // right
        objectList.front()->addRotate(0,-1,0);

      }
    }
  }


  void userUpdate(float deltaTime) override
  {

    pointer->setTranslation(camera.getTranslation() + glm::vec3(0,0,0));
    pointer->setRotate(camera.getPitch(), -(camera.getYaw()+90), 0.0f);

    Object* o = objectList.front();
    bool b = pointer->overlaps(o);
    if(b){ o->setColour(0.2, 0.5, 0.3, 1.0); }
    else { o->setColour(1,1,1,1); }


    float r = sin(ir) / 2.0f + 0.5f;
    float g = sin(ig) / 2.0f + 0.5f;
    float bb = sin(ib) / 2.0f + 0.5f;
    ir = ir + 0.01f; ig = ig + 0.02f; ib = ib + 0.03f;
    objectList.back()->setColour( r, g, bb, 1);

  }

  void userDraw() override
  {
    setCamera(&camera);
    for(Object* o : objectList) {
      o->draw();
    }

    setCamera(&camera2);
    hudItem->draw();
  }

};



int main()
{
  FYP nGin(500,500);

  return 1;
}
