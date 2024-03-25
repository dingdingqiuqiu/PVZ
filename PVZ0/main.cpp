/*
开发日志：
1.创建新项目（空项目模板）
2.添加源文件（main.cpp）
3.导入素材（res文件，tools.cpp,tools.h)
4.实现最开始场景构建（9gg）
*/

/*开发日志:
* 植物选择与点击
* 植物种植的实现
*/

/*开发日志：
* 实现植物摇摆
* 启动菜单
* 阳光类（数据层和显示层）随机数与随机种子
* 阳光收集
* 音效
*/

/*开发日志：
* 僵尸行走动画建立
*/

/*待完成：
阳光飞跃优化
阳光池里的阳光点了之后x和y也要归零，不然下次直接在目的位置出现而没有动画了(memet函数应该循环置零)
*/

/*
* 子弹发射
* 碰撞检测和效果实现
*/

/*
* 植物共用一个计数量有BUG
* 僵尸死亡
*/

/*修复僵尸死了之后又死的bug（僵尸死了跳过检测)
* 实现僵尸吃植物
*/

#include <stdio.h>
#include <graphics.h>//关掉VS,安装easyx即可，这是easyx库的头文件
#include <ctime>//随机种子
#include <iostream>
#include <mmsystem.h>//音效
#pragma comment(lib,"winmm.lib")
#include "tools.h"
#include "vector2.h"

using namespace std;

#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define MAX_images 20

int curX, curY;//选中植物在移动中位置
unsigned int curPlants;//植物类型编号0（未选中）；1（植物1）

/*
* 卡牌数这样定义不够灵活，用枚举，贼灵活，加植物卡牌数加一
#define NUM_CARS 3
*///---0---------1--------2--------3----
enum { WAN_DOU, XIANG_RI_KUI, MUO_GU, NUM_CARS };

IMAGE imgBg;//全局变量，放bss段
IMAGE imgBar;//植物卡牌放置栏目
IMAGE imgCards[NUM_CARS];
IMAGE* imgPLANTS[NUM_CARS][MAX_images];

//子弹
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
//子弹池
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
		//x = 260 + rand() % (900 - 260);//260-899间随机数，只有配置随机种子才能得到真正随机数
	}
	int getY() {
		return y;
	}
	void setY(int newY) {
		y = newY;//随机降落在某列草坪
	}
	void newX() {
		x = 0;
	}
	void newY() {
		y = 0;
	}
	void setDestY() {
		destY = 200 + (rand() % 4) * 90;//随机降落在某列草坪
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
	int timer;//停留时间
	double ox, oy;
};

//池的概念生产阳光
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

//收集阳光
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
	//加载图片，放内存变量里会快一些
	//loadimage报错是因为字符集原因造成的，把字符集修改为多字节字符集
	loadimage(&imgBg, "res/bg.jpg");
	loadimage(&imgBar, "res/bar5.png");

	char name[64];
	//sun
	for (int i = 0; i < 29; i++) {
		sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
		loadimage(&imgSunShineBall[i], name);
	}

	memset(imgPLANTS, 0, sizeof(imgPLANTS));//把所有指向植物图片的指针置空
	memset(MapPlants, 0, sizeof(MapPlants));
	memset(MapPlants, 0, sizeof(MapPlants));
	//随机种子
	srand(time(NULL));

	//植物卡牌
	for (int i = 0; i < NUM_CARS; i++) {
		//卡牌放内存
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);
		//植物拖动日常图片放内存
		for (int j = 0; j < 20; j++) {
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//先判断文件是不是存在
			if (fileExist(name)) {
				imgPLANTS[i][j] = new IMAGE;//原先指针都为空，要先分配内存，不然会崩掉。
				loadimage(imgPLANTS[i][j], name);
			}
			else {
				break;//跳出内部for循环
			}
		}
	}
	//这里只是从硬盘加载出来了，还没有显示
	//创建游戏图形窗口
	initgraph(WIN_WIDTH, WIN_HEIGHT, 0);
	//这里打开是黑的

	//设置字体
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 15;
	strcpy(f.lfFaceName, "Segoe UI Black");
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿
	settextstyle(&f);//设置字体
	setbkmode(TRANSPARENT); //背景模式
	setcolor(BLACK);//设置颜色

	//初始化僵尸
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
	BeginBatchDraw();//开始缓冲，不然一直刷新屏幕会闪烁，先打印到内存里，等加载好后全部打印，解决闪烁问题

	putimage(0, 0, &imgBg);//打印图片时要确定坐标，第一个0左边距，第二个0上边距
	//putimage(250, 0, &imgBar);//工具栏，自带的绘图工具整的，不好看，边角不够圆滑
	putimagePNG(250, 0, &imgBar);//用'tools.h'修下边框

	//卡片绘制
	for (int i = 0; i < NUM_CARS; i++) {
		int x = 338 + i * 65;
		int y = 6;
		putimage(x, y, &imgCards[i]);
	}

	
	//种植
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			int x = 256 + j * 81;
			int y = 179 + i * 116;
			int PlantType = MapPlants[i][j].getType() - 1;
			int Plantindex = MapPlants[i][j].getFrameIndex();
			putimagePNG(x, y, imgPLANTS[PlantType][Plantindex]);
		}
	}

	//渲染拖动中的植物,此处的渲染放在种植前，被拖动植物从已经种植植物下方过去，放种植函数后面，被拖动植物在贴图上方经过
	if (curPlants) {
		IMAGE* img = imgPLANTS[curPlants - 1][0];
		putimagePNG(curX - img->getwidth() / 2, curY - img->getheight() / 2, img);
	}
	//绘制阳光
	int ballMax = sizeof(balls) / sizeof(balls[0]);
	for (int i = 0; i < ballMax; i++) {
		if (balls[i].isUsed()) {
			IMAGE* img = &imgSunShineBall[balls[i].getFrameIndex()];
			putimagePNG(balls[i].getX(), balls[i].getY(), img);
		}
		
	}

	//阳光值
	char scoreText[8];
	sprintf_s(scoreText, sizeof(scoreText), "%d", sunshine);
	outtextxy(276, 67, scoreText);//输出阳光值

	//绘制僵尸
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

	EndBatchDraw();//结束缓冲,双缓冲技术
}

void userClick() {

	//peekmessage();//判断有无消息
	ExMessage msg;

	static int status = 0;//选择状态

	if (peekmessage(&msg)) {
		//如果左键按下
		if (msg.message == WM_LBUTTONDOWN) {
			//开始选卡
			if (msg.x > 338 && msg.x < 338 + 65 * NUM_CARS && msg.y < 96) {
				//开始选择第几个卡牌,index是卡牌标号；
				int index = (msg.x - 338) / 65;
				//cout << index << endl;调试看下对不对
				status = 1;//选中
				curPlants = index + 1;//植物标号
			}
			//收集阳光
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

//创建阳光
void createSunshine() {
	static int count = 0;
	static int fre = 400;
	count++;
	if (count >= fre) {
		fre = 200 + rand() % 200;//200-399间随机数帧生成阳光
		count = 0;//计数器清零
		//从阳光池取可用阳光
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
			//更新帧数
			int tFrameIndex = (balls[i].getFrameIndex() + 1) % 29;
			balls[i].setFrameIndex(tFrameIndex);
			//更新位置
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
		//真正创建
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
	//降低速度
	static int count = 0;
	count++;
	if (count >= 2) {
		count = 0;

		for (int i = 0; i < zmMax; i++) {
			if (zms[i].isUsed()) {
				//位置更新
				if (zms[i].getX() > 100) {
					int newX = zms[i].getX() - zms[i].getSpeed();
					zms[i].setX(newX);
				}
				else {
					cout << "GAME OVER!!!!" << endl;
					MessageBox(NULL, "over", "over", 0);//待优化
					exit(0);
				}
				//帧数更新
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
	//某行是否有僵尸
	bool lines[3] = { false };
	for (int i = 0; i < sizeof(zms) / sizeof(zms[0]); i++) {
		if (zms[i].isUsed() && zms[i].getX() < WIN_WIDTH-100) {
			lines[zms[i].getRow()] = true;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			if (MapPlants[i][j].getType() == 1 + WAN_DOU &&lines[i] == true) {
				//发射
				/*共用计数器会有bugstatic int count = 0;
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
			//离屏消失
			if (bullets[i].getX() > WIN_WIDTH) {
				bullets[i].setUsed(false);
			}
			//碰撞消失
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
						MapPlants[zms[i].getRow()][j].setCatched(false);//第二次种植植物血量回满
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
		//检测要在子弹被使用或未爆炸条件下进行
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

//菜单
void startUI() {
	IMAGE imgBg, imgMemu1, imgMemu2;
	loadimage(&imgBg,"res/menu.png");
	loadimage(&imgMemu1, "res/menu1.png");
	loadimage(&imgMemu2, "res/menu2.png");

	bool flag = false;
	while (1) {
		BeginBatchDraw();

		putimage(0, 0, &imgBg);
		putimagePNG(475, 75, flag? &imgMemu2:&imgMemu1);//为真则menu2,否则menu1
		
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
	gameInit();//初始化

	startUI();

	int timer = 0;
	bool flag = true;
	while (1) {
		userClick();
		timer += getDelay();//具体实现在tools.h中定义
		if (timer > 20) {
			flag = true;
			timer = 0;
		}

		if (flag == true) {
			updateWindow();//把图片打印到窗口中

			updateGame();//植物种植后动画实现

			flag = false;
		}

	//	Sleep(30);//动画优化
	}
	system("pause");
	return 0;
}