#include "Global.h"

void Global::setPlayer(Player *player) {
	_player = player;
}
Player* Global::getPlayer() {
	return _player;
}
void Global::setRoom(Room *room) {
	_room = room;
}
Room *Global::getRoom() {
	return _room;
}
Player* Global::_player = nullptr;
Room* Global::_room = nullptr;