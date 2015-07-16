#ifndef __GLOBAL_H_
#define __GLOBAL_H

class Player;
#include "Player.h"
class Room;
#include "Room.h"


class Global {
private:
	//Global * instance;
	static Player *_player;
	static Room *_room;
public:
	Global();
	~Global();
	//Global * getInstance();
	static Room * getRoom();
	static void setRoom(Room *_room);
	static Player * getPlayer();
	static void setPlayer(Player *_player);
};
#endif // !__GLOBAL_H_
