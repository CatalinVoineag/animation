#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::size;

using namespace std;
using namespace sf;

tuple<int, int, int, int> getNthElemetOfSet(set<tuple<int, int, int, int> >& setOfTuples, int index) {
  int setIndex = 0;
  tuple<int, int, int, int> tp;

  for (auto x : setOfTuples) {
    tp = x;

    if (setIndex == index) {
      break;
    }
    setIndex++;
  }

  return tp;
}

void iterateForward(vector< vector<int> > vector, bool& forward) {
  for (int i = 0; i < vector.size(); i++) {
    for (int j = 0; j < vector[i].size(); j++) {

      if (i == (vector.size() - 1) && j == (vector[i].size() - 1)) {
        forward = false;
        break;
      }

      cout << vector[i][j] << endl;
    }
  }
}

void iterateBackward(vector< vector<int> > vector, bool& forward) {
  for (int i = vector.size() - 1; i >= 0; i--) {
    for (int j = vector[i].size() - 1; j >= 0; j--) {

      if (i == 0 && j == 0) {
        forward = true;
        break;
      }

      cout << vector[i][j] << endl;
    }
  }
}

void iteratorFunction(vector< vector<int> > vector) {
  bool forward = true;

  while (true) {
    if (forward) {
      iterateForward(vector, forward);
    } else {
      iterateBackward(vector, forward);
    }
  }
}


int main() {
  const int SpriteSheetWidth = 1060;
  const int SpriteSheetHeight = 528;

 // const int xSprites = size(spritesheet[0]);
 // const int ySprites = size(spritesheet);
//  const char spriteSheet[3][4] = {
//    {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
//    {'p', '-', '-', '-', '-', 'n', 'x', 'x', 'x'},
//    {'|', 'o', 'o', 'o', 'o', '|', 'x', 'x', 'x'},
//    {'L', '-', '-', '-', '-', 'j', 'x', 'x', 'x'}
//  };
//
  //vector<int> vector1D = {1, 2, 3, 4};

  vector< vector<int> > vector2D =
  {
    {1, 2, 3, 4},
    {5, 6, 7, 8}
  };


  iteratorFunction(vector2D);

  set< tuple<int, int, int, int> > setOfTuples;

  tuple<int, int, int, int> tuple1;
  tuple1 = make_tuple(0, 0, 265, 176);

  tuple<int, int, int, int> tuple2;
  tuple2 = make_tuple(265, 0, 265, 176);

  tuple<int, int, int, int> tuple3;
  tuple3 = make_tuple(759, 0, 265, 176);

  setOfTuples.insert(tuple1);
  setOfTuples.insert(tuple2);

  cout << get<3>(getNthElemetOfSet(setOfTuples, 1)) << endl;

  RenderWindow window(VideoMode(640, 480), "Demo Game");

  Event event;
  Texture texture;
  IntRect rectSource(0, 0, 265, 176);

  texture.loadFromFile("graphics/player_spritesheet.png");
  Sprite sprite(texture);
  sprite.setTextureRect(rectSource);

  tuple <int, int, int, int> rect;
  rect = make_tuple(0, 1, 2, 3);

  cout << get<0>(rect) << endl;

  Clock clock;

  bool forward = true;
  bool backward = false;

  while(window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Escape) {
          window.close();
        }
      }
    }

    if (clock.getElapsedTime().asSeconds() > 0.15f) {

      if (rectSource.left >= 795) {
        forward = false;
        backward = true;
      } else if (rectSource.left == 0 && backward) {
        forward = true;
        backward = false;
      }

      if (forward) {
        rectSource.left += 265;
      } else if (backward) {
        rectSource.left -= 265;
      }

      cout << rectSource.left << endl;

      sprite.setTextureRect(rectSource);

      clock.restart();
    }


    window.clear();
    window.draw(sprite);
    window.display();
  }
  return 0;
}
