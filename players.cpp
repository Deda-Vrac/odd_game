#include "players.h"
using namespace std;
using namespace irr;

namespace players {


irr::core::vector3df rotiraj(irr::core::vector3df rotacija)
{





if ( rotacija.X >= 360.f || rotacija.X <= -360.f )
     rotacija.X = fmodf( rotacija.X,  360.f );
if ( rotacija.Y >= 360.f || rotacija.Y <= -360.f )
     rotacija.Y = fmodf( rotacija.Y,  360.f );
if ( rotacija.Z >= 360.f || rotacija.Z <= -360.f )
     rotacija.Z = fmodf( rotacija.Z,  360.f );

return rotacija;
}

player::player (irr::scene::ISceneManager *smgr)
{
   body = smgr->getMesh("../../test.obj");

}
void player::setBody(irr::scene::ISceneNode *SN)
{
bodynode = SN;


}
}
