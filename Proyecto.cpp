#include <iostream>
#include <cstdarg>
#include <cctype>
#include <map>

using namespace std;

class Exits {
    public:
        Exits();
        int N, E, S, W, NE, SE, NW, SW, UP, DOWN;
};

Exits::Exits() {
    this->N    = -1;
    this->E    = -1;
    this->S    = -1;
    this->W    = -1;
    this->NE   = -1;
    this->SE   = -1;
    this->NW   = -1;
    this->SW   = -1;
    this->UP   = -1;
    this->DOWN = -1;
}


class Room {
    private:
        bool dark, locked, combat;
        int value;
        string name;
        string description;
    public:
        Room(int _value, string _name, string _description);
        Exits exits;
        void printInfo();
        bool isDark();
        bool isLocked();
        bool isCombat();
        int  getValue();
        void setDark(bool _dark);
        void setLocked(bool _locked);
        void setCombat(bool _combat);
        void setName(string str);
        void setDescription(string str);
        void addExit(char* direction, int roomValue);
        void addExits(int count, ...);
};

Room::Room(int _value, string _name, string _description) {
    this->name = _name;
    this->description = _description;
    this->value = _value;
}

void Room::printInfo() {
    cout << this->name << endl
         << this->description << endl << endl;
}


bool Room::isDark() {return this->dark;}
bool Room::isLocked() {return this->locked;}
bool Room::isCombat() {return this->combat;}
int  Room::getValue() {return this->value;}
void Room::setDark(bool _dark) {this->dark = _dark;}
void Room::setLocked(bool _locked) {this->locked = _locked;}
void Room::setCombat(bool _combat) {this->combat = _combat;}
void Room::setName(string _name) {this->name = _name;}
void Room::setDescription(string _description) {this->description = _description;}
void Room::addExit(char* direction, int roomValue) {
    if      (direction == "N")    this->exits.N    = roomValue;
    else if (direction == "E")    this->exits.E    = roomValue;
    else if (direction == "S")    this->exits.S    = roomValue;
    else if (direction == "W")    this->exits.W    = roomValue;
    else if (direction == "NE")   this->exits.NE   = roomValue;
    else if (direction == "SE")   this->exits.SE   = roomValue;
    else if (direction == "NW")   this->exits.NW   = roomValue;
    else if (direction == "SW")   this->exits.SW   = roomValue;
    else if (direction == "UP")   this->exits.UP   = roomValue;
    else if (direction == "DOWN") this->exits.DOWN = roomValue;
}

void Room::addExits(int amount, ...) {
    va_list _exits;
    va_start(_exits, amount);
    for (int i = 0; i < amount; i+=2) {
        char* _direction = va_arg(_exits, char*);
        int _roomValue = va_arg(_exits, int);
        this->addExit(_direction, _roomValue);
    }
    va_end(_exits);
}

class Rooms {
    private:
        int currentRoomIndex;
        map<int, Room*> rooms;
    public:
        Room * currentRoom;
        void addRoom(Room *room);
        void changeRoom(int roomNumber);
        void changeRoom(string direction);
};

void Rooms::addRoom(Room *room) {
    this->rooms[room->getValue()] = room;
}

void Rooms::changeRoom(int roomNumber) {
    this->currentRoom = this->rooms[roomNumber];
    this->currentRoomIndex = roomNumber;
}

void Rooms::changeRoom(string direction) {
    for (unsigned int i = 0; i < direction.length(); i++)
        direction[i] = toupper(direction[i]);

    if (direction == "N" && this->currentRoom->exits.N != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.N;
    else if (direction == "E" && this->currentRoom->exits.E != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.E;
    else if (direction == "S" && this->currentRoom->exits.S != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.S;
    else if (direction == "W" && this->currentRoom->exits.W != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.W;
    else if (direction == "NE" && this->currentRoom->exits.NE != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.NE;
    else if (direction == "SE" && this->currentRoom->exits.SE != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.SE;
    else if (direction == "NW" && this->currentRoom->exits.NW != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.NW;
    else if (direction == "SW" && this->currentRoom->exits.SW != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.SW;
    else if (direction == "UP" && this->currentRoom->exits.UP != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.UP;
    else if (direction == "DOWN" && this->currentRoom->exits.DOWN != -1)
        this->currentRoomIndex = this->rooms[this->currentRoomIndex]->exits.DOWN;

    this->currentRoom = this->rooms[this->currentRoomIndex];
}

int main() {
    Rooms myMap;
    Room *Docks = new Room(1, "Puertos", "Los puertos, hay algunos barcos aqui y alla.");
    Docks->addExit("S", 2);
    myMap.addRoom(Docks);
    Room *GuildHall = new Room(2, "Centro", "Centro de la ciudad, hay mucha gente caminando.");
    GuildHall->addExits(2, "N", 1, "S", 3);
    myMap.addRoom(GuildHall);
    Room *NorthPlaza = new Room(3, "Plaza", "La plaza del norte, hay algunas personas sentadas.");
    NorthPlaza->addExit("N", 2);
    NorthPlaza->addExit("E", 4);
    myMap.addRoom(NorthPlaza);
    Room *Temple = new Room(4, "Templo", "El templo, a donde vienen las personas religiosas.");
    Temple->addExit("W", 3);
    myMap.addRoom(Temple);

    //
    myMap.changeRoom(1);
    while (true) { // main game loop
        myMap.currentRoom->printInfo();
        string response;
        cout << endl << "En que direccion voy a ir? ";
        cin >> response;
        myMap.changeRoom(response);
    }
}
