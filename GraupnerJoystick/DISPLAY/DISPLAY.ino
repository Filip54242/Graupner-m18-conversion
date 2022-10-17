#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#define WIDTH 128
#define HEIGHT 128

#define SCL 13
#define SDA 11
#define RES 9
#define DC 10
#define CS 8

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

Adafruit_SSD1351 display = Adafruit_SSD1351(WIDTH, HEIGHT, CS, DC, SDA, SCL, RES);

typedef struct {
  byte row;
  byte column;

  Position(byte row, byte column) {
    this->column = column;
    this->row = row;
  }
} Position;


class MenuItem {
private:
  Position pos;
  int childrenNum;
  int maxChildren;
  char* name;
  MenuItem* parent;
  MenuItem** children;
  void(*function);

  MenuItem(Position position, char* name) {
    this->pos = position;
    this->name = name;
    this->parent = nullptr;
    this->children = nullptr;
    this->childrenNum = 0;
    this->maxChildren = 0;
    this->function = nullptr;
  }

public:
  MenuItem(Position position, char* name, MenuItem* parent, int maxChildren = 5) {
    MenuItem(position, name);
    this->parent = parent;
    if (maxChildren > 0) {
      children = new MenuItem*[maxChildren];
      this->maxChildren = maxChildren;
    }
  };
  MenuItem(Position position, char* name, void(*function)) {
    MenuItem(position, name);
    this->function = function;
  };

  void setPosition(Position position) {
    this->pos = position;
  }
  Position getRow() {
    return this->pos;
  }
  int getChildrenNumber() {
    return this->childrenNum;
  }

  MenuItem* getChild(int index) {
    if (index >= 0 && index < this->childrenNum) {
      return this->children[index];
    }
    return nullptr;
  }

  void addChild(MenuItem* child) {
    if (this->childrenNum == this->maxChildren)
      return;

    this->children[this->childrenNum++] = child;
  }

  void removeChild(int index) {
    if (index < 0 && index >= this->childrenNum)
      return;

    delete this->children[index];
    for (int delIndex = index; delIndex < this->childrenNum - 1; index++) {
      this->children[delIndex] = this->children[delIndex + 1];
    }
    this->childrenNum--;
  }
      
};


class OledMenu {
private:
int titleTextSize;
int textSize;



public:
  OledMenu(Adafruit_SSD1351 display, byte width, byte height) {}
};






void setup() {

  display.begin();
  display.fillRect(0, 0, 128, 128, BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
}