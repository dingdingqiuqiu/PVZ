/*
������־��
1.��������Ŀ������Ŀģ�壩
2.���Դ�ļ���main.cpp��
3.�����زģ�res�ļ���tools.cpp,tools.h)
4.ʵ���ʼ����������9gg��
*/

/*������־:
* ֲ��ѡ������
* ֲ����ֲ��ʵ��
*/

/*������־��
* ʵ��ֲ��ҡ��
* �����˵�
* �����ࣨ���ݲ����ʾ�㣩��������������
* �����ռ�
* ��Ч
*/

/*������־��
* ��ʬ���߶�������
*/

/*����ɣ�
�����Ծ�Ż�
���������������֮��x��yҲҪ���㣬��Ȼ�´�ֱ����Ŀ��λ�ó��ֶ�û�ж�����(memet����Ӧ��ѭ������)
*/

/*
* �ӵ�����
* ��ײ����Ч��ʵ��
*/

/*
* ֲ�ﹲ��һ����������BUG
* ��ʬ����
*/

/*�޸���ʬ����֮��������bug����ʬ�����������)
* ʵ�ֽ�ʬ��ֲ��
*/

#include <stdio.h>
#include <graphics.h>//�ص�VS,��װeasyx���ɣ�����easyx���ͷ�ļ�
#include <ctime>//�������
#include <iostream>
#include <mmsystem.h>//��Ч
#pragma comment(lib,"winmm.lib")
#include "tools.h"
#include "vector2.h"

using namespace std;

#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define MAX_images 20

int curX, curY;//ѡ��ֲ�����ƶ���λ��
unsigned int curPlants;//ֲ�����ͱ��0��δѡ�У���1��ֲ��1��

/*
* �������������岻������ö�٣�������ֲ�￨������һ
#define NUM_CARS 3
*///---0---------1--------2--------3----
enum { WAN_DOU, XIANG_RI_KUI, MUO_GU, NUM_CARS };

IMAGE imgBg;//ȫ�ֱ�������bss��
IMAGE imgBar;//ֲ�￨�Ʒ�����Ŀ
IMAGE imgCards[NUM_CARS];
IMAGE* imgPLANTS[NUM_CARS][MAX_images];

//�ӵ�
class bullet {
private:
	int x, y;
	bool used;
	int speed;
	int row;
	bool boom;
	int boomFrameIndex;
public:
	void setBoomFrameIndex(int newBoomFrameIndex) {
		boomFrameIndex = newBoomFrameIndex;
	}
	int getBoomFrameIndex() {
		return boomFrameIndex;
	}
	void setBoom(bool newBoom) {
		boom = newBoom;
	}
	void setX(int newX) {
		x = newX;
	}
	void setY(int newY) {
		y = newY;
	}
	void setUsed(bool newUsed) {
		used = newUsed;
	}
	void setSpeed(int newSpeed) {
		speed = newSpeed;
	}
	void setRow(int newRow) {
		row = newRow;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	bool isUsed() {
		return used;
	}
	bool isBoom() {
		return boom;
	}
	int getSpeed() {
		return speed;
	}
	int getRow() {
		return row;
	}
};
//�ӵ���
bullet bullets[40];
IMAGE imgBulletNormal;
IMAGE imgBoom[4];


class Plants {
public:
	void setType(int newtype) {
		type = newtype;
	}
	int getType() {
		return type;
	}
	int getFrameIndex() {
		return frameIndex;
	}
	void setFrameIndex(int newFrameIndex) {
		frameIndex = newFrameIndex;
	}
	void addFrameIndex() {
		frameIndex++;
	}
	void setShootTime(int newShootTime) {
		shootTime= newShootTime;
	}
	int getShootTime() {
		return shootTime;
	}
	bool isCatched() {
		return catched;
	}
	void setCatched(bool newCatched) {
		catched = newCatched;
	}
	int getBlood() {
		return blood;
	}
	void setBlood(int newBlood) {
		blood = newBlood;
	}
private:
	int type;//0:null;1:type1.....
	int frameIndex;
	int shootTime;
	int x;
	int y;
	bool catched;
	int blood;
};
class Plants MapPlants[3][9];

class sunshineBall {
public:
	sunshineBall(){
		x = 260;
		y = 60;
		frameIndex = 0;
		ox = 0;
		oy = 0;
		destY = 0;
		used = false;
		timer = 0;
	}
	double getOX() {
		return ox;
	}
	double getOY() {
		return oy;
	}
	void setOX(double newOX) {
		ox = newOX;
	}
	void setOY(double newOY) {
		oy = newOY;
	}
	int getX() {
		return x;
	}
	void setX(int newX) {
		x = newX;
		//x = 260 + rand() % (900 - 260);//260-899���������ֻ������������Ӳ��ܵõ����������
	}
	int getY() {
		return y;
	}
	void setY(int newY) {
		y = newY;//���������ĳ�в�ƺ
	}
	void newX() {
		x = 0;
	}
	void newY() {
		y = 0;
	}
	void setDestY() {
		destY = 200 + (rand() % 4) * 90;//���������ĳ�в�ƺ
	}
	int getDestY() {
		return destY;
	}
	int getFrameIndex() {
		return frameIndex;
	}
	void setFrameIndex(int newFrameIndex) {
		frameIndex = newFrameIndex;
	}
	bool isUsed() {
		return used;
	}
	void setUsed(bool newUsed) {
		used = newUsed;
	}
	int getTimer() {
		return timer;
	}
	void addTimer() {
		timer++;
	}
private:
	int x, y;
	int frameIndex;
	int destY;
	bool used;
	int timer;//ͣ��ʱ��
	double ox, oy;
};

//�صĸ�����������
sunshineBall balls[10];

IMAGE imgSunShineBall[29];

int sunshine = 50;

class zm {
public:
	int getX(){
		return x;
	}
	int getY() {
		return y;
	}
	void setX(int newX) {
		x = newX;
	}
	void setY(int newY) {
		y = newY;
	}
	int getFrameIndex() {
		return frameIndex;
	}
	void setFrameIndex(int newFrameIndex) {
		frameIndex = newFrameIndex;
	}
	bool isUsed() {
		return used;
	}
	void setUsed(bool newUsed) {
		used = newUsed;
	}
	int getSpeed() {
		return speed;
	}
	void setSpeed(int newSpeed) {
		speed = newSpeed;
	}
	void setRow(int newRow) {
		row = newRow;
	}
	int getRow() {
		return row;
	}
	int getBlood() {
		return blood;
	}
	void setBlood(int newBlood) {
		blood = newBlood;
	}
	void setDead(bool newDead) {
		dead = newDead;
	}
	bool isDead() {
		return dead;
	}
	bool isEating() {
		return eating;
	}
	void setEating(bool newEating) {
		eating = newEating;
	}
private:
	int x, y;
	int frameIndex;
	bool used;
	int speed;
	int row;
	int blood;
	bool dead;
	bool eating;
};
zm zms[10];
IMAGE imgZM[22];
IMAGE imgZMDead[10];
IMAGE imgZMEat[21];

//�ռ�����
void collectSunShine(ExMessage *msg) {
	int Maxsunshine = sizeof(balls) / sizeof(balls[0]);
	int w = imgSunShineBall[0].getwidth();
	int h = imgSunShineBall[0].getheight();
	for (int i = 0; i < Maxsunshine; i++) {
		if (balls[i].isUsed()) {
			if (msg->x > balls[i].getX() && msg->x < balls[i].getX() + w
				&& msg->y > balls[i].getY() && msg->y < balls[i].getY() + h) {
				balls[i].setUsed(false);
				sunshine += 25;
				mciSendString("play res/sunshine.mp3",0,0,0);
			}
		}
	}
}

bool fileExist(const char* name) {
	FILE* fp = fopen(name, "r");
	bool re = true;
	if (fp == NULL) {
		re = false;
	}
	else
		fclose(fp);
	return re;
}

void gameInit() {
	//����ͼƬ�����ڴ��������һЩ
	//loadimage��������Ϊ�ַ���ԭ����ɵģ����ַ����޸�Ϊ���ֽ��ַ���
	loadimage(&imgBg, "res/bg.jpg");
	loadimage(&imgBar, "res/bar5.png");

	char name[64];
	//sun
	for (int i = 0; i < 29; i++) {
		sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
		loadimage(&imgSunShineBall[i], name);
	}

	memset(imgPLANTS, 0, sizeof(imgPLANTS));//������ָ��ֲ��ͼƬ��ָ���ÿ�
	memset(MapPlants, 0, sizeof(MapPlants));
	memset(MapPlants, 0, sizeof(MapPlants));
	//�������
	srand(time(NULL));

	//ֲ�￨��
	for (int i = 0; i < NUM_CARS; i++) {
		//���Ʒ��ڴ�
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);
		//ֲ���϶��ճ�ͼƬ���ڴ�
		for (int j = 0; j < 20; j++) {
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//���ж��ļ��ǲ��Ǵ���
			if (fileExist(name)) {
				imgPLANTS[i][j] = new IMAGE;//ԭ��ָ�붼Ϊ�գ�Ҫ�ȷ����ڴ棬��Ȼ�������
				loadimage(imgPLANTS[i][j], name);
			}
			else {
				break;//�����ڲ�forѭ��
			}
		}
	}
	//����ֻ�Ǵ�Ӳ�̼��س����ˣ���û����ʾ
	//������Ϸͼ�δ���
	initgraph(WIN_WIDTH, WIN_HEIGHT, 0);
	//������Ǻڵ�

	//��������
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 15;
	strcpy(f.lfFaceName, "Segoe UI Black");
	f.lfQuality = ANTIALIASED_QUALITY;//�����
	settextstyle(&f);//��������
	setbkmode(TRANSPARENT); //����ģʽ
	setcolor(BLACK);//������ɫ

	//��ʼ����ʬ
	memset(zms, 0, sizeof(zms));
	for (int i = 0; i < 22; i++) {
		sprintf_s(name, sizeof(name), "res/zm/%d.png", i );
		loadimage(&imgZM[i], name);
	}


	memset(bullets, 0, sizeof(bullets));
	loadimage(&imgBulletNormal, "res/bullets/bullet_normal.png");
	
	loadimage(&imgBoom[3], "res/bullets/bullet_blast.png");
	for (int i = 0; i < 3; i++) {
		double k = (i + 1) * 0.2;
		loadimage(&imgBoom[i], "res/bullets/bullet_blast.png",
			imgBoom[3].getwidth() * k,
			imgBoom[3].getheight() * k,
			true);
	}

	for (int i = 0; i < 10; i++) {
		sprintf_s(name, sizeof(name), "res/zm_dead/tt0.top-384308/tt0.top_000%d.png", i);
		loadimage(&imgZMDead[i], name);
	}

	for (int i = 0; i < 21; i++) {
		sprintf_s(name, sizeof(name), "res/zm_eat/%d.png", i + 1);
		loadimage(&imgZMEat[i], name);
	}
}

void drawShoot() {
	for (int i = 0; i < sizeof(bullets) / sizeof(bullets[0]); i++) {
		if (bullets[i].isUsed()) {
			if (bullets[i].isBoom()) {
				IMAGE* img = &imgBoom[bullets[i].getBoomFrameIndex()];
				putimagePNG(bullets[i].getX(), bullets[i].getY(), img);
			}
			else {
				putimagePNG(bullets[i].getX(), bullets[i].getY(), &imgBulletNormal);
			}
		}
	}
}

void updateWindow() {
	BeginBatchDraw();//��ʼ���壬��Ȼһֱˢ����Ļ����˸���ȴ�ӡ���ڴ���ȼ��غú�ȫ����ӡ�������˸����

	putimage(0, 0, &imgBg);//��ӡͼƬʱҪȷ�����꣬��һ��0��߾࣬�ڶ���0�ϱ߾�
	//putimage(250, 0, &imgBar);//���������Դ��Ļ�ͼ�������ģ����ÿ����߽ǲ���Բ��
	putimagePNG(250, 0, &imgBar);//��'tools.h'���±߿�

	//��Ƭ����
	for (int i = 0; i < NUM_CARS; i++) {
		int x = 338 + i * 65;
		int y = 6;
		putimage(x, y, &imgCards[i]);
	}

	
	//��ֲ
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			int x = 256 + j * 81;
			int y = 179 + i * 116;
			int PlantType = MapPlants[i][j].getType() - 1;
			int Plantindex = MapPlants[i][j].getFrameIndex();
			putimagePNG(x, y, imgPLANTS[PlantType][Plantindex]);
		}
	}

	//��Ⱦ�϶��е�ֲ��,�˴�����Ⱦ������ֲǰ�����϶�ֲ����Ѿ���ֲֲ���·���ȥ������ֲ�������棬���϶�ֲ������ͼ�Ϸ�����
	if (curPlants) {
		IMAGE* img = imgPLANTS[curPlants - 1][0];
		putimagePNG(curX - img->getwidth() / 2, curY - img->getheight() / 2, img);
	}
	//��������
	int ballMax = sizeof(balls) / sizeof(balls[0]);
	for (int i = 0; i < ballMax; i++) {
		if (balls[i].isUsed()) {
			IMAGE* img = &imgSunShineBall[balls[i].getFrameIndex()];
			putimagePNG(balls[i].getX(), balls[i].getY(), img);
		}
		
	}

	//����ֵ
	char scoreText[8];
	sprintf_s(scoreText, sizeof(scoreText), "%d", sunshine);
	outtextxy(276, 67, scoreText);//�������ֵ

	//���ƽ�ʬ
	int zmMax = sizeof(zms) / sizeof(zms[0]);
	for (int i = 0; i < zmMax; i++) {
		if (zms[i].isUsed()) {
			int nowFrameIndex = zms[i].getFrameIndex();
			IMAGE* img = NULL;
			//IMAGE* img = (zms[i].isDead()) ? &imgZMDead[nowFrameIndex] : &imgZM[nowFrameIndex];
			if (zms[i].isDead()) {
				img = &imgZMDead[nowFrameIndex];
			}
			else {
				if (zms[i].isEating()) {
					img = &imgZMEat[nowFrameIndex];
				}
				else {
					img = &imgZM[nowFrameIndex];
				}	
			}
			int nowX = zms[i].getX();
			int nowY = zms[i].getY() - img->getheight();
			putimagePNG(nowX, nowY, img);
		}
	}


	drawShoot();

	EndBatchDraw();//��������,˫���弼��
}

void userClick() {

	//peekmessage();//�ж�������Ϣ
	ExMessage msg;

	static int status = 0;//ѡ��״̬

	if (peekmessage(&msg)) {
		//����������
		if (msg.message == WM_LBUTTONDOWN) {
			//��ʼѡ��
			if (msg.x > 338 && msg.x < 338 + 65 * NUM_CARS && msg.y < 96) {
				//��ʼѡ��ڼ�������,index�ǿ��Ʊ�ţ�
				int index = (msg.x - 338) / 65;
				//cout << index << endl;���Կ��¶Բ���
				status = 1;//ѡ��
				curPlants = index + 1;//ֲ����
			}
			//�ռ�����
			else{
				collectSunShine(&msg);
			}
		}
		else if (msg.message == WM_MOUSEMOVE && status == 1) {
			curX = msg.x; curY = msg.y;
		}
		else if (msg.message == WM_LBUTTONUP) {
			if (msg.x > 256 && msg.y > 179 && msg.y < 489) {
				int row = (msg.y - 179) / 102;
				int col = (msg.x - 256) / 81;
				cout << row << "," << col << endl;
				if (MapPlants[row][col].getType() == 0) {
					MapPlants[row][col].setType(curPlants);
					MapPlants[row][col].setShootTime(0);
					MapPlants[row][col].setBlood(50); 
				}	
			}
			curPlants = 0;
			status = 0;
		}
	}
}

//��������
void createSunshine() {
	static int count = 0;
	static int fre = 400;
	count++;
	if (count >= fre) {
		fre = 200 + rand() % 200;//200-399�������֡��������
		count = 0;//����������
		//�������ȡ��������
		int ballMax = sizeof(balls) / sizeof(balls[0]);

		int i = 0;
		for (i = 0; i < ballMax; i++) {
			if (balls[i].isUsed() == false) {
				break;
			}
		}
		if (i > ballMax) {
			return;
		}

		balls[i].setUsed(true);

		balls[i].setFrameIndex(0);

		balls[i].setX(260 + rand() % (900 - 260));

		balls[i].setY(0);

		balls[i].setDestY();

		
	}
}

void updateSunshine() {
	int ballMax = sizeof(balls) / sizeof(balls[0]);
	for (int i = 0; i < ballMax; i++) {
		if (balls[i].isUsed()) {
			//����֡��
			int tFrameIndex = (balls[i].getFrameIndex() + 1) % 29;
			balls[i].setFrameIndex(tFrameIndex);
			//����λ��
			if (balls[i].getTimer() == 0) {
				int tY = balls[i].getY() + 2;
				balls[i].setY(tY);
			}
			if (balls[i].getY() > balls[i].getDestY()) {			
				balls[i].addTimer();
				if (balls[i].getTimer() > 100) {
					balls[i].setUsed(false);
				}

			}
		}
	}
}

void createZM() {
	static int zmFre = 100;
	static int count = 0;
	count++;
	if (count > zmFre) {
		count = 0;
		zmFre = 200 + rand() % 300;
		//��������
		int i;
		int zmMax = sizeof(zms) / sizeof(zms[0]);
		for (i = 0; i < zmMax; i++) {
			if (zms[i].isUsed() == false) {
				break;
			}
		}
		if (i < zmMax) {
			zms[i].setUsed(true);
			zms[i].setX(WIN_WIDTH);
			int Row = rand() % 3;
			zms[i].setRow(Row);
			int newY = 172 + (1 + Row) * 100;
			zms[i].setY(newY);
			zms[i].setSpeed(1);
			zms[i].setBlood(100);
			zms[i].setDead(false);
			zms[i].setEating(false);
		}
	}
}

void updateZM() {
	int zmMax = sizeof(zms) / sizeof(zms[0]);
	//�����ٶ�
	static int count = 0;
	count++;
	if (count >= 2) {
		count = 0;

		for (int i = 0; i < zmMax; i++) {
			if (zms[i].isUsed()) {
				//λ�ø���
				if (zms[i].getX() > 100) {
					int newX = zms[i].getX() - zms[i].getSpeed();
					zms[i].setX(newX);
				}
				else {
					cout << "GAME OVER!!!!" << endl;
					MessageBox(NULL, "over", "over", 0);//���Ż�
					exit(0);
				}
				//֡������
				if (zms[i].isDead()) {
					int newFrameIndex = zms[i].getFrameIndex() + 1;
					zms[i].setFrameIndex(newFrameIndex);
					if (zms[i].getFrameIndex() == 9) {
						zms[i].setUsed(false);
					}
				}
				else if (zms[i].isEating()) {
					int newFrameIndex = (zms[i].getFrameIndex() + 1) % 21;
					zms[i].setFrameIndex(newFrameIndex);
				}
				else {
					int newFrameIndex = (zms[i].getFrameIndex() + 1) % 22;
					zms[i].setFrameIndex(newFrameIndex);
				}
			}
		}
	}
}

void shoot() {
	//ĳ���Ƿ��н�ʬ
	bool lines[3] = { false };
	for (int i = 0; i < sizeof(zms) / sizeof(zms[0]); i++) {
		if (zms[i].isUsed() && zms[i].getX() < WIN_WIDTH-100) {
			lines[zms[i].getRow()] = true;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			if (MapPlants[i][j].getType() == 1 + WAN_DOU &&lines[i] == true) {
				//����
				/*���ü���������bugstatic int count = 0;
				count++;
				if (count > 20) {*/
				int newTime = MapPlants[i][j].getShootTime()+1;
				MapPlants[i][j].setShootTime(newTime);
				if(MapPlants[i][j].getShootTime() > 20){
					MapPlants[i][j].setShootTime(0);
					int k;
					for (k = 0; k < sizeof(bullets) / sizeof(bullets[0]) && bullets[k].isUsed(); k++);
					if (k < sizeof(bullets) / sizeof(bullets[0])) {
						bullets[k].setUsed(true);
						bullets[k].setRow(i);
						bullets[k].setSpeed(4);

						int PlantX = 256 + j * 81;
						int PlantY = 179 + i * 102 + 14;

						int BulletsX = PlantX + imgPLANTS[MapPlants[i][j].getType()-1][0]->getwidth()-10;
						bullets[k].setX(BulletsX);
						int BulletsY = PlantY + 10;
						bullets[k].setY(BulletsY);

						bullets[k].setBoom(false);
						bullets[k].setBoomFrameIndex(0);
					}
				}
			}
		}
	}
}

void updateShoot() {
	for (int i = 0; i < sizeof(bullets) / sizeof(bullets[0]); i++) {
		if (bullets[i].isUsed()) {
			int newX = bullets[i].getX() + bullets[i].getSpeed();
			bullets[i].setX(newX);
			//������ʧ
			if (bullets[i].getX() > WIN_WIDTH) {
				bullets[i].setUsed(false);
			}
			//��ײ��ʧ
			if (bullets[i].isBoom()) {
				int newBoolFrameIndex = bullets[i].getBoomFrameIndex() + 1;
				bullets[i].setBoomFrameIndex(newBoolFrameIndex);
				if (bullets[i].getBoomFrameIndex() == 4) {
					bullets[i].setUsed(false);
				}
			}
		}
	}
}

void checkZm2Plant() {
	int zmsMax = sizeof(zms) / sizeof(zms[0]);
	int plantsMax = sizeof(MapPlants[0]) / sizeof(MapPlants[0][0]);
	for (int i = 0; i < zmsMax; i++) {
		if (zms[i].isDead()) continue;
		for (int j = 0; j < plantsMax; j++) {
			if (MapPlants[zms[i].getRow()][j].getType() == 0) continue;
			int x = zms[i].getX() + 80;
			int plantX = 256 + j * 81;
			int x1 = plantX + 10;
			int x2 = plantX + 60;
			if (zms[i].isDead() == false && x > x1 && x < x2) {
				if (MapPlants[zms[i].getRow()][j].isCatched()) {
					int newBlood = MapPlants[zms[i].getRow()][j].getBlood() - 1;
					MapPlants[zms[i].getRow()][j].setBlood(newBlood);
					if (MapPlants[zms[i].getRow()][j].getBlood() <= 0) {
						MapPlants[zms[i].getRow()][j].setType(0);
						MapPlants[zms[i].getRow()][j].setCatched(false);
						zms[i].setEating(false);
						zms[i].setFrameIndex(0);
						zms[i].setSpeed(1);
					}
			    }
				else {
					MapPlants[zms[i].getRow()][j].setCatched(true);
					int newBlood = MapPlants[zms[i].getRow()][j].getBlood() - 1;
					MapPlants[zms[i].getRow()][j].setBlood(newBlood);
					zms[i].setEating(true);
					zms[i].setSpeed(0);
					zms[i].setFrameIndex(0);
					if (MapPlants[zms[i].getRow()][j].getBlood() <= 0) {
						MapPlants[zms[i].getRow()][j].setType(0);
						MapPlants[zms[i].getRow()][j].setCatched(false);//�ڶ�����ֲֲ��Ѫ������
						zms[i].setEating(false);
						zms[i].setFrameIndex(0);
						zms[i].setSpeed(1);
					}
				}
			}
		}
	}
}

void collisionCheck() {
	int bulletsMax = sizeof(bullets) / sizeof(bullets[0]);
	int zmsMax = sizeof(zms) / sizeof(zms[0]);
	for (int i = 0; i < bulletsMax; i++) {
		//���Ҫ���ӵ���ʹ�û�δ��ը�����½���
		if (bullets[i].isUsed() == false || bullets[i].isBoom())continue;
		for (int j = 0; j < zmsMax; j++) {
			if (zms[j].isUsed() == false)continue;

			int x1 = zms[j].getX() + 80;
			int x2 = zms[j].getX() + 110;
			int x = bullets[i].getX();
			if(zms[j].isDead()==false && bullets[i].getRow()==zms[j].getRow() && x>x1 && x<x2){
				int newBlood = zms[j].getBlood() - 10;
				zms[j].setBlood(newBlood);
				bullets[i].setBoom(true);
				bullets[i].setSpeed(0);
				if (zms[j].getBlood() < 0) {
					zms[j].setDead(true);
					zms[j].setSpeed(0);
					zms[j].setFrameIndex(0);
				}
				break;
			}
		}
	}
	checkZm2Plant();
}

void updateGame() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			if (MapPlants[i][j].getType() > 0) {
				MapPlants[i][j].addFrameIndex();
				int plantsType = MapPlants[i][j].getType() - 1;
				int index = MapPlants[i][j].getFrameIndex();
				if (imgPLANTS[plantsType][index] == NULL) {
					MapPlants[i][j].setFrameIndex(0);
				}
			}
		}
	}
	createSunshine();

	updateSunshine();

	createZM();

	updateZM();

	shoot();

	updateShoot();

	collisionCheck();
}

//�˵�
void startUI() {
	IMAGE imgBg, imgMemu1, imgMemu2;
	loadimage(&imgBg,"res/menu.png");
	loadimage(&imgMemu1, "res/menu1.png");
	loadimage(&imgMemu2, "res/menu2.png");

	bool flag = false;
	while (1) {
		BeginBatchDraw();

		putimage(0, 0, &imgBg);
		putimagePNG(475, 75, flag? &imgMemu2:&imgMemu1);//Ϊ����menu2,����menu1
		
		EndBatchDraw();

		ExMessage msg;
		if (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONDOWN && msg.x > 475 &&
				msg.x < 475 + 330 && msg.y > 75 && msg.y < 75 + 140) {
				flag = true;	
			}
			else if (msg.message == WM_LBUTTONUP && msg.x > 475 &&
				msg.x < 475 + 330 && msg.y > 75 && msg.y < 75 + 140) {
				return;
			}
		}
	}
}

int main(void) {
	gameInit();//��ʼ��

	startUI();

	int timer = 0;
	bool flag = true;
	while (1) {
		userClick();
		timer += getDelay();//����ʵ����tools.h�ж���
		if (timer > 20) {
			flag = true;
			timer = 0;
		}

		if (flag == true) {
			updateWindow();//��ͼƬ��ӡ��������

			updateGame();//ֲ����ֲ�󶯻�ʵ��

			flag = false;
		}

	//	Sleep(30);//�����Ż�
	}
	system("pause");
	return 0;
}