/*
The program will show how to use the
basics of the VideoDriver, the GUIEnvironment and the
SceneManager.

To use the engine, we will have to include the header file
irrlicht.h, which can be found in the Irrlicht Engine SDK
directory \include.
*/
#include"iostream"
#include <irrlicht.h>
#include <time.h>
#include "players.h"
/*
In the Irrlicht Engine, everything can be found in the namespace
'irr'. So if you want to use a class of the engine, you have to
write an irr:: before the name of the class. For example to use
the IrrlichtDevice write: irr::IrrlichtDevice. To get rid of the
irr:: in front of the name of every class, we tell the compiler
that we use that namespace from now on, and we will not have to
write that 'irr::'.
*/
using namespace std;
using namespace irr;
//using namespace players;
/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look
at them, you can read a detailed description of them in the
documentation by clicking on the top menu item 'Namespace List'
or using this link: http://irrlicht.sourceforge.net/docu/namespaces.html.
Like the irr Namespace, we do not want these 5 sub namespaces now,
to keep this example simple. Hence we tell the compiler again
that we do not want always to write their names:
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
This is the main method. We can use void main() on every platform.
On Windows platforms, we could also use the WinMain method
if we would want to get rid of the console window, which pops up when
starting a program with main(), but to keep this example simple,
we use main().
*/


class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main(int argc, char** argv)
{
 //irr.core.dimension2d dimension(640,480);
 MyEventReceiver receiver;
    /*
    The most important function of the engine is the 'createDevice'
    function. The Irrlicht Device can be created with it, which is the
    root object for doing everything with the engine.
    createDevice() has 7 paramters:
    deviceType: Type of the device. This can currently be the Null-device,
       the Software device, DirectX8, DirectX9, or OpenGL. In this example we use
       EDT_SOFTWARE, but to try out, you might want to change it to
       EDT_NULL, EDT_DIRECTX8 , EDT_DIRECTX9, or EDT_OPENGL.
    windowSize: Size of the Window or FullscreenMode to be created. In this
       example we use 640x480.
    bits: Amount of bits per pixel when in fullscreen mode. This should
       be 16 or 32. This parameter is ignored when running in windowed mode.
    fullscreen: Specifies if we want the device to run in fullscreen mode
       or not.
    stencilbuffer: Specifies if we want to use the stencil buffer for drawing shadows.
    vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen
      mode.
    eventReceiver: An object to receive events. We do not want to use this
       parameter here, and set it to 0.
    */

    IrrlichtDevice *device =
        createDevice(EDT_OPENGL,dimension2d<u32>(640,480), 16,
            false, false, false, &receiver);

    /*
    Set the caption of the window to some nice text. Note that there is
    a 'L' in front of the string. The Irrlicht Engine uses wide character
    strings when displaying text.
    */
    device->setWindowCaption(L"Hello World! - Irrlicht Demo");

    /*
    Get a pointer to the video driver, the SceneManager and the
    graphical user interface environment, so that
    we do not always have to write device->getVideoDriver(),
    device->getSceneManager() and device->getGUIEnvironment().
    */
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    /*
    We add a hello world label to the window, using the GUI environment.
    */
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        rect<int>(10,10,200,22), true);

    /*
    To display something interesting, we load a Quake 2 model
    and display it. We only have to get the Mesh from the Scene
    Manager (getMesh()) and add a SceneNode to display the mesh.
    (addAnimatedMeshSceneNode()). Instead of writing the filename
    sydney.md2, it would also be possible to load a Maya object file
    (.obj), a complete Quake3 map (.bsp) or a Milshape file (.ms3d).
    By the way, that cool Quake 2 model called sydney was modelled
    by Brian Collins.
    */
   //IAnimatedMesh* mesh = smgr->getMesh("../test.obj");

//IMesh* mesh = smgr->getMesh("../../test.obj");
  //  ISceneNode* node = smgr-> addMeshSceneNode(mesh,0,-1, core::vector3df(0, 0, 0), core::vector3df(0, 0, 0),core::vector3df(10.0f,10.0f,10.0f),false);// getMesh("./test.obj"); //->addAnimatedMeshSceneNode( mesh );
//cout << device->getFileSystem()->getWorkingDirectory().c_str() ;
// add camera

    // disable mouse cursor
    device->getCursorControl()->setVisible(false);
    scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
        "../../../irrtest/fractal.bmp",
        0,                  // parent node
        -1,                 // node id
        core::vector3df(0.f, 0.f, 0.f),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(40.1f, 4.01f, 40.1f),  // scale
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,             // patchSize
        4                   // smoothFactor
        );
        terrain->setPosition(terrain->getTerrainCenter());

   terrain->setMaterialFlag(irr::video::EMF_WIREFRAME,true);
        terrain->setMaterialType(video::EMT_SOLID); //EMT_DETAIL_MAP



        // create triangle selector for the terrain
    scene::ITriangleSelector* selector
        = smgr->createTerrainTriangleSelector(terrain, 0);
    terrain->setTriangleSelector(selector);

    // create collision response animator and attach it to the camera

    /*
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        selector, camera, core::vector3df(60,100,60),
        core::vector3df(0,0,0),
        core::vector3df(0,50,0));
    selector->drop();
    camera->addAnimator(anim);
    anim->drop();

    */
    /*
    To let the mesh look a little bit nicer, we change its material a
    little bit: We disable lighting because we do not have a dynamic light
    in here, and the mesh would be totally black. Then we set the frame
    loop, so that the animation is looped between the frames 0 and 310.
    And at last, we apply a texture to the mesh. Without it the mesh
    would be drawn using only a color.
    */

   //     if (node)
  //  {
    //    node->setMaterialFlag(irr::video::EMF_WIREFRAME,true);   //   EMF_LIGHTING, false);
       // node->setFrameLoop(0, 310);
      //  node->setMaterialTexture( 0,); driver->getTexture("../../media/sydney.bmp") );
        //node
   // }

   /*
   scene::ISceneNode * sunce = smgr->addSphereSceneNode(1500.f,16,0,-1, core::vector3df(-100,0,100)); //SUNCE
   irr::scene::IDummyTransformationSceneNode* dummy = smgr->addDummyTransformationSceneNode();
   dummy->getRelativeTransformationMatrix().setRotationDegrees(core::vector3df(30.f, 0.f, 0.f));

   sunce = smgr->addLightSceneNode(dummy, core::vector3df(0,0,0),
           video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 600.0f);
   scene::ISceneNodeAnimator* anim1 = 0;
   anim1 = smgr->createFlyCircleAnimator (core::vector3df(0,150,0),2500.0f);
   sunce->addAnimator(anim1);
   anim1->drop();
   */



/*


if (sunce)
{
sunce->setMaterialFlag(irr::video::EMF_WIREFRAME,true);
//sunce->setPosition(core::vector3df(-8000,10,100));

    scene::ISceneNodeAnimator* anim = smgr-> createFlyCircleAnimator(core::vector3df(300.f,0.f,300.f), 20000.0f,0.00001f,core::vector3df(0.f, 0.f, 1.f));
        if (anim)
        {
            sunce->addAnimator(anim);
            anim->drop();
        }
    }
*/
    /*
    To look at the mesh, we place a camera into 3d space at the position
    (0, 30, -40). The camera looks from there to (0,5,0).
    */
    //smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
//smgr->addCameraSceneNodeFPS();
    /*
    Ok, now we have set up the scene, lets draw everything:
    We run the device in a while() loop, until the device does not
    want to run any more. This would be when the user closed the window
    or pressed ALT+F4 in windows.
    */


    // This is the movemen speed in units per second.
    const f32 MOVEMENT_SPEED = 50.f;
    players::player play(smgr);
    scene::ISceneNode * igrac = smgr->addMeshSceneNode(play.body,0,-1,
        core::vector3df(0,0,0),
        core::vector3df(0, 0, 0),
        core::vector3df(10.0f,10.0f,10.0f),
        false);// getMesh("./test.obj"); //->addAnimatedMeshSceneNode( mesh ););

    igrac->setMaterialFlag(irr::video::EMF_WIREFRAME,true);

    scene::ICameraSceneNode* camera =
        smgr->addCameraSceneNodeFPS();

    //camera->setPosition(igrac->getPosition());
    //camera->setTarget();
    camera->setFarValue(4200.0f);














     u32 then = device->getTimer()->getTime();


    while(device->run())
{

        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;
        core::vector3df nodePosition = igrac->getPosition();
        core::vector3df nodeRotation = igrac-> getRotation();

        if(receiver.IsKeyDown(irr::KEY_KEY_W))
{
            nodeRotation.X += 1;
            nodeRotation = players::rotiraj(nodeRotation);
            //irr::core::vector3df facing( sin( ( igrac->getRotation().Y + 90.0f ) * PI/180.0f ), 0, cos( ( igrac->getRotation().Y + 90.0f ) * PI/180.0f ) );
            //facing.normalize();
            //irr::core::vector3df newPos = (facing*4.0f) + igrac->getPosition();
            //igrac->setPosition( newPos );
 }
        else if(receiver.IsKeyDown(irr::KEY_KEY_S))
            {
            nodeRotation.X -= 1;
            nodeRotation = players::rotiraj(nodeRotation);
            }
        if(receiver.IsKeyDown(irr::KEY_KEY_A))
            {
            nodeRotation.Y -= 1;
            nodeRotation = players::rotiraj(nodeRotation);
        }
        else if(receiver.IsKeyDown(irr::KEY_KEY_D))
         {
                    nodeRotation.Y += 1;
            nodeRotation = players::rotiraj(nodeRotation);
          }
            if(receiver.IsKeyDown(irr::KEY_KEY_L))
            camera->setTarget(nodePosition);

        igrac->setPosition(nodePosition);
        igrac->setRotation(nodeRotation);

   /*
        Anything can be drawn between a beginScene() and an endScene()
        call. The beginScene clears the screen with a color and also the
        depth buffer if wanted. Then we let the Scene Manager and the
        GUI Environment draw their content. With the endScene() call
        everything is presented on the screen.
        */


        driver->beginScene(true, true,SColor(0,150,150,150));  //beginScene(true, true, SColor(0,200,200,200));

        smgr->drawAll();

        core::line3d<f32> ray;
        ray.start = igrac->getPosition();
        ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;

        guienv->drawAll();

    driver->endScene();
}

    /*
    After we are finished, we have to delete the Irrlicht Device
    created before with createDevice(). In the Irrlicht Engine,
    you will have to delete all objects you created with a method or
    function which starts with 'create'. The object is simply deleted
    by calling ->drop().
    See the documentation at
    http://irrlicht.sourceforge.net//docu/classirr_1_1IUnknown.html#a3
    for more information.
    */




    device->drop();

    return 0;
}

