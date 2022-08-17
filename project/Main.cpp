
#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
const int H = 21;
const int W = 19;
const int ts = 25;

int q = 0;
bool life = true;

String TileMap[H] = {
"AAAAAAAAAAAAAAAAAAA",
"A1       A      2A",
"A AA AAA A AAA AA A",
"A        A        A",
"A AA A AAAAA A AA A",
"A    A   A   A    A",
"AAAA AAA A AAA AAAA",
"BBBA A       A ABBB",
"AAAA A AAAAA A AAAA",
"BBBB   ABBBA   BBBB",
"AAAA A AAAAA A AAAA",
"BBBA A       A ABBB",
"AAAA A AAAAA A AAAA",
"A        A        A",
"A AA AAA A AAA AA A",
"A  A     C     A  A",
"AA A A AAAAA A A AA",
"A    A   A   A    A",
"A AAAAAA A AAAAAA A",
"A3                A",
"AAAAAAAAAAAAAAAAAAA",
};


class Player {
public:
	float frame = 0;
	int x = 9, y = 15;
	int newx = 0, newy = 0;
	int rotate = 1, ti = 0;
	void update() {
		frame += float(0.01);    //type casting
		if (frame > 5)
			frame -= 5;
		ti++;
		if (ti >= 300) {
			switch (rotate)
			{
			case 1:
				if (TileMap[y][newx + 1] != 'A')
					newx += 1;
				break;
			case 2:
				if (TileMap[y][newx - 1] != 'A')
					newx -= 1;
				break;
			case 3:
				if (TileMap[y][newy - 1] != 'A')
					newx -= 1;
				break;
			case 4:
				if (TileMap[y][newy + 1] != 'A')
					newy += 1;
				break;
			}
			ti = 0;
		}
		if (TileMap[newy][newx] == ' ' || TileMap[newy][newx] == 'B') {
			if (TileMap[newy][newx] == ' ')
				q++;
			if (TileMap[newy][newx] == '1' || TileMap[newy][newx] == '2' || TileMap[newy][newx] == '3' || TileMap[newy][newx] == '4')
				life = false;
			TileMap[y][x] = 'B';
			TileMap[newy][newx] = 'C';
			x = newx;
			y = newy;

		}
		if (newy == 9 && (newx == 0 || newx == 18)) {
			if (newx == 0)
				newx = 17;
			else
				newx = 1;
			TileMap[y][x] = 'B';
			TileMap[newy][newx] = 'C';
			x = newx;
			y = newy;
		}
	}
	};
class Enemy {
public:
	int x[4] = { 1, 17, 1, 17 }, y[4] = { 1, 1, 19, 19 };
	int newx[4] = { 0,0 ,0 , 0 }, newy[4] = { 0,0, 0, 0 };
	int rotate[4] = { 1,1,1,1 }, ti = 0;

	void update() {
		ti++;
		if (ti >= 300) {
			for (int i = 0; i < 2; i++) {
				rotate[i] = rand() % 4 + 1;
				newx[i] = x[i];
				newy[i] = y[i];
				switch (rotate[i])
				{
				case 1:
					if (TileMap[y[i]][newx[i] + 1] != 'A')
						newx[i] += 1;
					break;
				case 2:
					if (TileMap[y[i]][newx[i] - 1] != 'A')
						newx[i] -= 1;
					break;
				case 3:
					if (TileMap[y[i]][newy[i] - 1] != 'A')
						newx[i] -= 1;
					break;
				case 4:
					if (TileMap[y[i]][newy[i] + 1] != 'A')
						newy[i] += 1;
					break;
				}
			}
			ti = 0;
		}
		for (int i = 0; i < 4;i++) {
			if (TileMap[newy[i]][newx[i]] == ' ' || TileMap[newy[i]][newx[i]] == 'B') {
				if (TileMap[newy[i]][newx[i]] = 'B')
					TileMap[y[i]][x[i]] = 'B';

				else if (TileMap[newy[i]][newx[i]] == ' ')
					TileMap[newy[i]][newx[i]] = ' ';
				else if (TileMap[newy[i]][newy[i]] == 'C')
					life = false;
				if (i == 0)
					TileMap[newy[i]][newx[i]] = '1';
				if (i == 1)
					TileMap[newy[i]][newx[i]] = '2';
				if (i == 2)
					TileMap[newy[i]][newx[i]] = '3';
				if (i == 3)
					TileMap[newy[i]][newx[i]] = '4';
				x[i] = newx[i];
				y[i] = newy[i];

			}
			if (newy[i] == 9 && (newx[i] == 0 || newx[i] == 18)) {
				if (newx[i] == 0)
					newx[i] = 17;
				else
					newx[i] = 1;

				TileMap[newy[i]][newx[i]] = 'B';
				if (i == 0)
					TileMap[newy[i]][newx[i]] = '1';
				if (i == 1)
					TileMap[newy[i]][newx[i]] = '2';
				x[i] = newx[i];
				y[i] = newy[i];
			}

		}

	};
	int main()
	{
	
		srand (time (NULL));
		RenderWindow window(VideoMode(W * ts, H * ts), "Maze!");
		Texture t;
		t.loadFromFile("C:/Users/ASUS/OneDrive/Desktop/PACCCC/title.png");
		Sprite plat(t);
		Texture yw;
		yw.loadFromFile("C:/Users/ASUS/OneDrive/Desktop/PACCCC/youwin.png");
		Sprite youwin(yw);
		youwin.setPosition(100, 210);  // function overwrites previous position
		Texture yl;
		yl.loadFromFile("C:/Users/ASUS/OneDrive/Desktop/PACCCC/youlose.png");
		Sprite youlose(yl);
		youlose.setPosition(100, 210);
		
		Player p;
		Enemy en;
		
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (q < 171 && life)

					if (event.type == Event::KeyPressed) {
						p.newx = p.x;
						p.newy = p.y;
						if (event.key.code == Keyboard::Right)
							p.rotate = 1;
						if (event.key.code == Keyboard::Left)
							p.rotate = 2;
						if (event.key.code == Keyboard::Up)
							p.rotate = 3;
						if (event.key.code == Keyboard::Down)
							p.rotate = 4;
					}
			}
			if (q < 171 && life) {
				p.update();
				en.update();
			}
			window.clear(Color::Black);
			for (int i = 0; i < H; i++)
				for (int j = 0; j < W; j++) {
					if (TileMap[i][j] == 'A')
						plat.setTextureRect(IntRect(0, 0, ts, ts));
					if (TileMap[i][j] == 'C')
						plat.setTextureRect(IntRect(ts * int(p.frame), ts * p.rotate, ts, ts));
					if (TileMap[i][j] == ' ')
						plat.setTextureRect(IntRect(ts, 0, ts, ts));
					if (TileMap[i][j] == '1')
						plat.setTextureRect(IntRect(ts * 5, ts * en.rotate[0], ts, ts));
					if (TileMap[i][j] == '2')
						plat.setTextureRect(IntRect(ts * 5, ts * en.rotate[1], ts, ts));
					if (TileMap[i][j] == '3')
						plat.setTextureRect(IntRect(ts * 5, ts * en.rotate[2], ts, ts));
					if (TileMap[i][j] == '4')
						plat.setTextureRect(IntRect(ts * 5, ts * en.rotate[3], ts, ts));
					if (TileMap[i][j] == 'B')
						continue;
					plat.setPosition(float(j * ts), float(i * ts));
					window.draw(plat);

				}
			if (q == 171)
				window.draw(youwin);
			if (!life)
				window.draw(youlose);
			window.display();
		}
		return 0;
	}
};






