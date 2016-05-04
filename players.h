#include <irrlicht.h>
#include <string>



namespace players {

irr::core::vector3df rotiraj(irr::core::vector3df rotacija);

class player{
    public:

    std::string name;
    std::string surname;
    player (irr::scene::ISceneManager *smgr);
    irr::scene::IMesh *body;
    irr::scene::ISceneNode *bodynode;
    void setBody(irr::scene::ISceneNode *SN);



    private:

    std::string ID;




};
}
