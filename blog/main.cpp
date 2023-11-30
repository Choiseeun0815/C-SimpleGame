#include <iostream>
#include <ctime>
using namespace std;

class GameObject { //�߻� Ŭ����
protected:
	int distance, x, y; //�� �� �̵� �Ÿ�, ���� ��ġ
public:
	GameObject(int startX, int startY, int distance)
	{
		this->x = startX; this->y = startY;
		this->distance = distance;
	}
	virtual ~GameObject() {}; //���� �Ҹ���

	virtual void move() = 0; //�̵��� �� ���ο� ��ġ�� x,y ����
	virtual char getShape() = 0; //��ü�� ����� ��Ÿ���� ���� ����

	int getX() { return x; } int getY() { return y; }

	bool collide(GameObject* p) { //�� ��ü�� ��ü p�� �浹������ true ����
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
		cout << "����(a), �Ʒ�(s), ��(d), ������(f)>> ";
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

		//x�� y�� ���� �迭 ������ �ʰ����� ����� ���� ó��
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
		int rnd = rand() % 4; //0~3������ ������ ����. ����� �迭 �ּҷ� Ȱ���� ��ȹ

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
	int preAdd = -1, currentAdd = 0; //���� �ʱ⿡ �� ������ ���� �޶�� �ϹǷ� �ƹ� ���̳� �Ҵ�.
	int stateArray[5] = { 0,0,0,0,0 }; //5���忡 ���� �̵�/���� ���¸� ������ �迭 ����
public:
	Food(int x, int y, int distance) : GameObject(x, y, distance) {};
	void move() {

		if (i > 4) //������ ���°� ����� �迭�� ��� �ּҿ� ������ �Ϸ�Ǿ��ٸ�, 
		{
			moveSet = 0;
			preAdd = -1; currentAdd = 0;
			for (int j = 0; j < 5; j++) stateArray[j] = 0;
			i = 0;
			//�������� ���¸� �ʱ�ȭ�Ͽ� �ϱ��� �̵� ������ �����ϴ� while���� �����
		}
		while (moveSet != 2) //�� �ּҿ� �Ҵ��� �Ϸ�� ������ �ݺ�
		{
			//�迭�� 0~4���� �� �� ������ �������� �̵��� ������ ������ ����. 
			//������ ���� ������ ������ ���� ������ �ٸ� ���� ���� (���� �ּҿ� �� �� �Ҵ� X)

			currentAdd = rand() % 5;//0~4������ ������ ����. ����� �迭 �ּҷ� Ȱ���� ��ȹ
			if (currentAdd != preAdd) {
				stateArray[currentAdd] = 1;
				preAdd = currentAdd;
				moveSet++;
			}
		}

		if (stateArray[i++] == 1) //�̵� ������ ���¶��, 
		{
			char randDirection[4] = { 'a','s','d','f' };
			int rnd = rand() % 4; //0~3������ ������ ����. ����� �迭 �ּҷ� Ȱ���� ��ȹ

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

void setScreen(GameObject* h, GameObject* m, GameObject* f); //�������� �����ϱ� ���� �Լ� ����

int main() {
	srand((unsigned)time(0)); //���� �ð��� ���� ���� �߻��� ���� ���� ����

	GameObject* human = new Human(0, 0, 1);

	//monster�� Food�� ��� ���α׷��� ����� �� 0~19�� ������ x����, 0~9�� ������ y���� ������ ����.
	GameObject* monster = new Monster(rand() % 20, rand() % 10, 2);
	GameObject* food = new Food(rand() % 20, rand() % 10, 1);


	setScreen(human, monster, food); //�ʱ� �������� �ܼ� â�� ���

	while (true)
	{
		human->move(); monster->move(); food->move();
		setScreen(human, monster, food);

		if (human->collide(monster)) { //human�� monster���� ������ ��,
			cout << "You were caught by a monster!" << endl;
			break;
		}
		else if (human->collide(food)) //human�� food�� �Ծ��� ��,
		{
			cout << "Human is Winner!" << endl;
			break;
		}
		else if (monster->collide(food)) { //monster�� food�� �Ծ��� ��,
			cout << "Monster is Winner!" << endl;
			break;
		}
	}

	delete human; delete monster; delete food;
	return 0;
}

void setScreen(GameObject* h, GameObject* m, GameObject* f) {
	system("cls"); //�ܼ�â�� �ʱ�ȭ �����ִ� �Լ� 
	cout << "** Human�� Food �Ա� ������ �����մϴ�. **\n";
	char screenArray[10][20];

	//10x20 �������� '-'�� �ʱ�ȭ
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