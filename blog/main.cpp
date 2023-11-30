#include <iostream>
#include <ctime>
using namespace std;

class GameObject { //추상 클래스
protected:
	int distance, x, y; //한 번 이동 거리, 현재 위치
public:
	GameObject(int startX, int startY, int distance)
	{
		this->x = startX; this->y = startY;
		this->distance = distance;
	}
	virtual ~GameObject() {}; //가상 소멸자

	virtual void move() = 0; //이동한 후 새로운 위치로 x,y 변경
	virtual char getShape() = 0; //객체의 모양을 나타내는 문자 리턴

	int getX() { return x; } int getY() { return y; }

	bool collide(GameObject* p) { //이 객체가 객체 p와 충돌했으면 true 리턴
		if (this->x == p->getX() && this->y == p->getY())
			return true;
		else
			return false;
	}
};

class Human : public GameObject {
public:
	Human(int x, int y, int distance) : GameObject(x, y, distance) {};
	void move() {
		char input;
		cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f)>> ";
		cin >> input; cin.ignore();

		switch (input)
		{
		case 'a':
			x -= distance; break;
		case'f':
			x += distance; break;
		case 's':
			y += distance; break;
		case 'd':
			y -= distance; break;
		default:
			break;
		}

		//x와 y의 값이 배열 범위를 초과했을 경우의 예외 처리
		if (x <= 0)
			x = 0;
		else if (x >= 19)
			x = 19;

		if (y <= 0)
			y = 0;
		else if (y >= 9)
			y = 9;
	}
	char getShape() { return 'H'; }
};

class Monster : public GameObject {
public:
	Monster(int x, int y, int distance) : GameObject(x, y, distance) {};
	void move() {
		char randDirection[4] = { 'a','s','d','f' };
		int rnd = rand() % 4; //0~3까지의 랜덤한 숫자. 상기의 배열 주소로 활용할 계획

		switch (randDirection[rnd])
		{
		case 'a':
			x -= distance; break;
		case'f':
			x += distance; break;
		case 's':
			y += distance; break;
		case 'd':
			y -= distance; break;
		default:
			break;
		}

		if (x <= 0)
			x = 0;
		else if (x >= 19)
			x = 19;

		if (y <= 0)
			y = 0;
		else if (y >= 9)
			y = 9;
	}

	char getShape() { return 'M'; }
};

class Food : public GameObject {
	int moveSet = 0, i = 0;
	int preAdd = -1, currentAdd = 0; //실행 초기에 두 변수의 값이 달라야 하므로 아무 값이나 할당.
	int stateArray[5] = { 0,0,0,0,0 }; //5라운드에 대한 이동/정지 상태를 저장할 배열 선언
public:
	Food(int x, int y, int distance) : GameObject(x, y, distance) {};
	void move() {

		if (i > 4) //랜덤한 상태가 저장된 배열의 모든 주소에 접근이 완료되었다면, 
		{
			moveSet = 0;
			preAdd = -1; currentAdd = 0;
			for (int j = 0; j < 5; j++) stateArray[j] = 0;
			i = 0;
			//변수들의 상태를 초기화하여 하기의 이동 정보를 저장하는 while문을 재실행
		}
		while (moveSet != 2) //두 주소에 할당이 완료될 때까지 반복
		{
			//배열의 0~4번지 中 두 군데에 랜덤으로 이동이 가능한 정보를 저장. 
			//이전의 랜덤 변수와 현재의 랜덤 변수가 다를 때만 실행 (같은 주소에 두 번 할당 X)

			currentAdd = rand() % 5;//0~4까지의 랜덤한 숫자. 상기의 배열 주소로 활용할 계획
			if (currentAdd != preAdd) {
				stateArray[currentAdd] = 1;
				preAdd = currentAdd;
				moveSet++;
			}
		}

		if (stateArray[i++] == 1) //이동 가능한 상태라면, 
		{
			char randDirection[4] = { 'a','s','d','f' };
			int rnd = rand() % 4; //0~3까지의 랜덤한 숫자. 상기의 배열 주소로 활용할 계획

			switch (randDirection[rnd])
			{
			case 'a':
				x -= distance; break;
			case'f':
				x += distance; break;
			case 's':
				y += distance; break;
			case 'd':
				y -= distance; break;
			default:
				break;
			}

			if (x <= 0)
				x = 0;
			else if (x >= 19)
				x = 19;

			if (y <= 0)
				y = 0;
			else if (y >= 9)
				y = 9;
		}

	}

	char getShape() { return '@'; }
};

void setScreen(GameObject* h, GameObject* m, GameObject* f); //격자판을 갱신하기 위한 함수 선언

int main() {
	srand((unsigned)time(0)); //현재 시간에 따른 난수 발생을 위한 씨드 설정

	GameObject* human = new Human(0, 0, 1);

	//monster와 Food의 경우 프로그램이 실행될 때 0~19의 랜덤한 x값을, 0~9의 랜덤한 y값을 갖도록 지정.
	GameObject* monster = new Monster(rand() % 20, rand() % 10, 2);
	GameObject* food = new Food(rand() % 20, rand() % 10, 1);


	setScreen(human, monster, food); //초기 격자판을 콘솔 창에 출력

	while (true)
	{
		human->move(); monster->move(); food->move();
		setScreen(human, monster, food);

		if (human->collide(monster)) { //human이 monster에게 잡혔을 때,
			cout << "You were caught by a monster!" << endl;
			break;
		}
		else if (human->collide(food)) //human이 food를 먹었을 때,
		{
			cout << "Human is Winner!" << endl;
			break;
		}
		else if (monster->collide(food)) { //monster가 food를 먹었을 때,
			cout << "Monster is Winner!" << endl;
			break;
		}
	}

	delete human; delete monster; delete food;
	return 0;
}

void setScreen(GameObject* h, GameObject* m, GameObject* f) {
	system("cls"); //콘솔창을 초기화 시켜주는 함수 
	cout << "** Human의 Food 먹기 게임을 시작합니다. **\n";
	char screenArray[10][20];

	//10x20 격자판을 '-'로 초기화
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
			screenArray[i][j] = '-';

	screenArray[f->getY()][f->getX()] = f->getShape();
	screenArray[h->getY()][h->getX()] = h->getShape();
	screenArray[m->getY()][m->getX()] = m->getShape();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++)
			cout << screenArray[i][j];
		cout << endl;
	}

}