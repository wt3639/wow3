// exp1.cpp : 定义控制台应用程序的入口点。
//

/* 武器有三个位置第一个位置放剑第二个放炸弹第三个放箭
*/


#include "stdafx.h"
#include <iostream>
#include<iomanip>
using namespace std;
#define DEATH 0
#define LIVE 1
#define RED 1
#define BLUE 2
enum{ DRAGON, NINJA, ICEMAN, LION, WOLF };
int Mlife, Ncity, Rarrow, Klion, Ttime;
int Dlife, Nlife, Ilife, Llife, Wlife;
int Dfor, Nfor, Ifor, Lfor, Wfor;
int timem;

class Creature;
class Dragon;
class Ninja;
class Iceman;
class Lion;
class Wolf;

int born(int to, int life){
	if (to - life >= 0) return 0;
	else return 1;
}

void priname(int a){
	switch (a)
	{
	case DRAGON:cout << "dragon"; break;
	case NINJA:cout << "ninja"; break;
	case ICEMAN:cout << "iceman"; break;
	case LION:cout << "lion"; break;
	case WOLF:cout << "wolf"; break;
	default:
		break;
	}
}

//城市
class City{
public:
	int life;
	int num;
	int flag;
	int monu;
	int master;
	int rwin;
	int bwin;
	Creature *cr[2];
	Creature *cb[2];
	City(int r){
		rwin = 0;
		bwin = 0;
		life = 0;
		num = r;
		flag = 0;
		monu = 0;
		master = 0;
		cr[0] = NULL;
		cr[1] = NULL;
		cb[0] = NULL;
		cb[1] = NULL;
	}
};
//武器
class Weapon{
public:
	int weanum;
	int force;
	friend class Creature;
	virtual int check() = 0;
	virtual void use(Creature *c) = 0;
};
class Sword :public Weapon{
public:

	Sword(int f){
		weanum = 0;
		force = (int)f*0.2;
	}
	int check(){
		if (force == 0)return 1;
		else{
			return force + 1;
		}
	}
	void use(Creature *c);
};

class Arrow :public Weapon{
public:

	int r;
	int used;

	Arrow(){
		weanum = 2;
		used = 3;
		r = Rarrow;
	}
	void use(Creature *c);
	int check(){
		if (used <= 0)return 1;
		else{
			if (used == 1)return 2;
			if (used == 2)return 3;
			if (used == 3)return 4;
		}
	}
};

class Bomb :public Weapon{
public:
	Bomb(){
		weanum = 1;
	}
	void use(Creature *c){}
	int check(){ return 0; }
};
//生物

class Creature{
public:
	int life;
	int num;
	int force;
	int status;
	int step;
	int tape;
	int belong;
	double morale;
	friend class Weapon;
	Weapon * weapon[3];
	virtual void attack(Creature *p, City *c) = 0;
	virtual void hurt(int force,int once) = 0;
	virtual void fightback(Creature *p, City *c) = 0;
	virtual void move() = 0;
	virtual int escape(){ return 0; }
	virtual void getweapon(Creature *p){}
	virtual void dead(Creature *p){}
};

class Dragon :public Creature{
public:
	
	Dragon(int l, int n, int f, double m, int b) {
		tape = DRAGON;
		life = l;
		num = n;
		force = f;
		status = LIVE;
		step = 0;
		morale = m;
		belong = b;
		switch (n % 3){
		case 0:weapon[0] = new Sword(f); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } weapon[1] = NULL; weapon[2] = NULL; break;
		case 1:weapon[1] = new Bomb; weapon[0] = NULL; weapon[2] = NULL; break;
		case 2:weapon[2] = new Arrow; weapon[1] = NULL; weapon[0] = NULL; break;
		default:break;
		}

	}
	void attack(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " dragon " << num << " attacked ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << " with " << life << " elements and force " << force << endl;
		p->hurt(force,1);
		if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } }
		if (p->status == LIVE){
			p->fightback(this, c);
		}
		//print死亡信息
		if (p->status == DEATH){
			if (p->tape == LION){ p->dead(this); }
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (p->belong == RED)cout << "red "; else cout << "blue ";
			priname(p->tape);
			cout << " " << p->num << " was killed in city " << c->num << endl;
			//red lion 2 was killed in 1
		}
		if (status == DEATH){
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (belong == RED)cout << "red"; else cout << "blue";
			cout << " dragon " << num << " was killed in city " << c->num << endl;
		}
		if (p->status == DEATH){
			morale += 0.2;
		}
		else morale -= 0.2;
		if (status == LIVE&&morale > 0.8){
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (belong == RED)cout << "red"; else cout << "blue";
			cout << " dragon " << num << " yelled in city " << c->num << endl;
		}//活着且士气大于0.8即欢呼

		//获得奖励

	}
	void hurt(int force,int once){
		life -= force;
		if (life <= 0){
			status = DEATH;
		}//死亡以后要干嘛，待补充
	}
	void fightback(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " dragon " << num << " fought back against ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << endl;
		p->hurt(force / 2,1);
		if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } }
		if (p->status == DEATH){
			morale += 0.2;
		}
		else morale -= 0.2;
	}
	void move(){
		step++;
	}
};

class Ninja :public Creature{
public:
	Ninja(int l, int n, int f, int b) {
		tape = NINJA;
		life = l;
		num = n;
		force = f;
		status = LIVE;
		step = 0;
		belong = b;
		switch (n % 3){
		case 0:weapon[0] = new Sword(f); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } weapon[1] = new Bomb; weapon[2] = NULL; break;
		case 1:weapon[1] = new Bomb; weapon[2] = new Arrow; weapon[0] = NULL; break;
		case 2:weapon[2] = new Arrow; weapon[0] = new Sword(f); if (weapon[0]->check() == 1){
			delete weapon[0]; weapon[0] = NULL;
		} weapon[1] = NULL; break;
		default:break;
		}

	}
	void attack(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " ninja " << num << " attacked ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << " with " << life << " elements and force " << force << endl;
		p->hurt(force,1);
		if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } }
		if (p->status == LIVE){
			p->fightback(this, c);
		}
		if (p->status == DEATH){
			if (p->tape == LION){ p->dead(this); }
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (p->belong == RED)cout << "red "; else cout << "blue ";
			priname(p->tape);
			cout << " " << p->num << " was killed in city " << c->num << endl;
			//red lion 2 was killed in 1
		}
		if (status == DEATH){
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (belong == RED)cout << "red"; else cout << "blue";
			cout << " ninja " << num << " was killed in city " << c->num << endl;
		}

	}
	void hurt(int force,int once){
		life -= force;
		if (life <= 0){
			status = DEATH;
		}//死亡以后要干嘛，待补充
	}
	void fightback(Creature *p, City *c){

	}
	void move(){
		step++;
	}

};

class Iceman :public Creature{
public:
	Iceman(int l, int n, int f, int b) {
		tape = ICEMAN;
		life = l;
		num = n;
		force = f;
		status = LIVE;
		step = 0;
		belong = b;
		switch (n % 3){
		case 0:weapon[0] = new Sword(f); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } weapon[1] = NULL; weapon[2] = NULL; break;
		case 1:weapon[1] = new Bomb; weapon[0] = NULL; weapon[2] = NULL; break;
		case 2:weapon[2] = new Arrow; weapon[1] = NULL; weapon[0] = NULL; break;
		default:break;
		}

	}
	void attack(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " iceman " << num << " attacked ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << " with " << life << " elements and force " << force << endl;
		p->hurt(force,1);
		if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } }
		if (p->status == LIVE){
			p->fightback(this, c);
		}
		if (p->status == DEATH){
			if (p->tape == LION){ p->dead(this); }
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (p->belong == RED)cout << "red "; else cout << "blue ";
			priname(p->tape);
			cout << " " << p->num << " was killed in city " << c->num << endl;
			//red lion 2 was killed in 1
		}
		if (status == DEATH){
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (belong == RED)cout << "red"; else cout << "blue";
			cout << " iceman " << num << " was killed in city " << c->num << endl;
		}
	}
	void hurt(int force,int once){
		life -= force;
		if (life <= 0){
			status = DEATH;
		}//死亡以后要干嘛，待补充
	}
	void fightback(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " iceman " << num << " fought back against ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << endl;
		p->hurt(force / 2,1);
		if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } }
	}
	void move(){
		step++;
		if (step % 2 == 0){
			if (life - 9 <= 0){ life = 1; }
			else {
				life -= 9;
			}
			force += 20;
		}

	}
};

class Lion :public Creature{
public:
	int loyalty;
	int k;
	int left;
	Lion(int l, int n, int f, int lef, int b) {
		tape = LION;
		life = l;
		num = n;
		force = f;
		status = LIVE;
		step = 0;
		loyalty = lef;
		k = Klion;
		belong = b;
		weapon[0] = NULL;
		weapon[1] = NULL;
		weapon[2] = NULL;

	}
	void attack(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " lion " << num << " attacked ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << " with " << life << " elements and force " << force << endl;
		p->hurt(force,1);
		//if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1)delete weapon[0]; weapon[0] = NULL; }
		if (p->status == LIVE){
			p->fightback(this, c);
		}
		if (p->status == LIVE){
			loyalty -= k;
		}
		//print死亡信息
		if (p->status == DEATH){
			if (p->tape == LION){ p->dead(this); }
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (p->belong == RED)cout << "red "; else cout << "blue ";
			priname(p->tape);
			cout << " " << p->num << " was killed in city " << c->num << endl;
			//red lion 2 was killed in 1
		}
		if (status == DEATH){
			dead(p);
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (belong == RED)cout << "red"; else cout << "blue";
			cout << " lion " << num << " was killed in city " << c->num << endl;
		}
	}
	void hurt(int force,int once){
		if(once==1)left = life;
		life -= force;
		if (life <= 0){
			status = DEATH;
		}//死亡以后要干嘛，待补充
	}
	void fightback(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " lion " << num << " fought back against ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << endl;
		p->hurt(force / 2,1);
		if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } }
		if (p->status == LIVE){
			loyalty -= k;
		}
	}
	void move(){
		step++;
	}
	int escape(){
		if (loyalty <= 0 && step != Ncity + 1){
			status = DEATH;
			return 1;
		}
		return 0;
	}
	void dead(Creature *p){
		p->life += left;
	}
};

class Wolf :public Creature{
public:
	Wolf(int l, int n, int f, int b) {
		tape = WOLF;
		life = l;
		num = n;
		force = f;
		status = LIVE;
		step = 0;
		belong = b;
		weapon[0] = NULL;
		weapon[1] = NULL;
		weapon[2] = NULL;
	}
	void attack(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " wolf " << num << " attacked ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << " with " << life << " elements and force " << force << endl;
		p->hurt(force,1);
		if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } }
		if (p->status == LIVE){
			p->fightback(this, c);
		}
		//print死亡信息
		if (p->status == DEATH){
			if (p->tape == LION){ p->dead(this); }
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (p->belong == RED)cout << "red "; else cout << "blue ";
			priname(p->tape);
			cout << " " << p->num << " was killed in city " << c->num << endl;
			//red lion 2 was killed in 1
		}
		if (status == DEATH){
			c->monu--;
			cout << setfill('0') << setw(3) << timem << ":40 ";
			if (belong == RED)cout << "red"; else cout << "blue";
			cout << " wolf " << num << " was killed in city " << c->num << endl;
		}
	}
	void getweapon(Creature *p){
		if (p->status == DEATH){
			for (int i = 0; i < 3; i++){
				if (p->weapon[i] != NULL&&weapon[i] == NULL)weapon[i] = p->weapon[i];
				//if (weapon == NULL){ weapon = p->weapon; } 夺武器 待完善
			}
		}
	}
	void hurt(int force,int once){
		life -= force;
		if (life <= 0){
			status = DEATH;
		}//死亡以后要干嘛，待补充
	}
	void fightback(Creature *p, City *c){
		cout << setfill('0') << setw(3) << timem << ":40 ";
		if (belong == RED)cout << "red"; else cout << "blue";
		//priname(c[z]->cr[1]->tape);
		cout << " wolf " << num << " fought back against ";
		if (p->belong == RED)cout << "red "; else cout << "blue ";
		priname(p->tape);
		cout << " " << p->num << " in city " << c->num << endl;
		p->hurt(force / 2,1);
		if (weapon[0] != NULL){ weapon[0]->use(p); if (weapon[0]->check() == 1){ delete weapon[0]; weapon[0] = NULL; } }
	}
	void move(){
		step++;
	}
};

void Sword::use(Creature *c){
	c->hurt(force,2);
	force = (int)(force*0.8);
}
void Arrow::use(Creature *c)
{
	c->hurt(r,2);
	used--;
}

class Control{
public:
	int lifetotal;
	//int time;
	int count;
	Creature *mo[10005];
	int sign;
	int winner;
	Control(){
		winner = 0;
	}
};

class Red :public Control{
public:
	int start(int num){
		sign = 0;
		if (born(lifetotal, Ilife) == 0 && num == 0){
			sign = 1;
			lifetotal -= Ilife;
			mo[count] = new Iceman(Ilife, count + 1, Ifor, RED);
			count++;

			//ir.cnt++;
			cout << setfill('0') << setw(3) << timem << ":00 red iceman " << count << " born" << endl;
			//time++;
		}
		if (born(lifetotal, Llife) == 0 && num == 1){
			lifetotal -= Llife;
			sign = 1;
			mo[count] = new Lion(Llife, count + 1, Lfor, lifetotal, RED);
			count++;

			//lr.cnt++;
			cout << setfill('0') << setw(3) << timem << ":00 red lion " << count << " born" << endl;
			cout << "Its loyalty is " << lifetotal << endl;
			//time++;
		}
		if (born(lifetotal, Wlife) == 0 && num == 2){
			lifetotal -= Wlife;
			sign = 1;
			mo[count] = new Wolf(Wlife, count + 1, Wfor, RED);

			//wr.cnt++;
			count++;
			cout << setfill('0') << setw(3) << timem << ":00 red wolf " << count << " born" << endl;
			//time++;
		}
		if (born(lifetotal, Nlife) == 0 && num == 3){
			lifetotal -= Nlife;
			sign = 1;
			mo[count] = new Ninja(Nlife, count + 1, Nfor, RED);

			//nr.cnt++;
			count++;
			cout << setfill('0') << setw(3) << timem << ":00 red ninja " << count << " born" << endl;
			//time++;
		}
		if (born(lifetotal, Dlife) == 0 && num == 4){
			lifetotal -= Dlife;
			sign = 1;
			mo[count] = new Dragon(Dlife, count + 1, Dfor, (double)lifetotal / Dlife, RED);
			count++;

			//dr.cnt++;
			cout << setfill('0') << setw(3) << timem << ":00 red dragon " << count << " born" << endl;
			cout << "Its morale is ";
			cout << fixed << setprecision(2) << (double)lifetotal / Dlife << endl;
			//time++;
		}
		return sign;


	}
	
};

class Blue :public Control{
public:
	int start(int num){
		sign = 0;

		if (born(lifetotal, Llife) == 0 && num == 0){
			lifetotal -= Llife;
			sign = 1;
			mo[count] = new Lion(Llife, count + 1, Lfor, lifetotal, BLUE);
			count++;

			//lr.cnt++;
			cout << setfill('0') << setw(3) << timem << ":00 blue lion " << count << " born" << endl;
			cout << "Its loyalty is " << lifetotal << endl;
			//time++;
		}
		if (born(lifetotal, Dlife) == 0 && num == 1){
			lifetotal -= Dlife;
			sign = 1;
			mo[count] = new Dragon(Dlife, count + 1, Dfor, (double)lifetotal / Dlife, BLUE);
			count++;
			//lifetotal -= Dlife;
			//dr.cnt++;
			cout << setfill('0') << setw(3) << timem << ":00 blue dragon " << count << " born" << endl;
			cout << "Its morale is ";
			cout << fixed << setprecision(2) << (double)lifetotal / Dlife << endl;
			//time++;
		}
		if (born(lifetotal, Nlife) == 0 && num == 2){
			lifetotal -= Nlife;
			sign = 1;
			mo[count] = new Ninja(Nlife, count + 1, Nfor, BLUE);
			//lifetotal -= Nlife;
			//nr.cnt++;
			count++;
			cout << setfill('0') << setw(3) << timem << ":00 blue ninja " << count << " born" << endl;
			//time++;
		}
		if (born(lifetotal, Ilife) == 0 && num == 3){
			lifetotal -= Ilife;
			sign = 1;
			mo[count] = new Iceman(Ilife, count + 1, Ifor, BLUE);
			count++;

			//ir.cnt++;
			cout << setfill('0') << setw(3) << timem << ":00 blue iceman " << count << " born" << endl;
			//time++;
		}
		if (born(lifetotal, Wlife) == 0 && num == 4){
			lifetotal -= Wlife;
			sign = 1;
			mo[count] = new Wolf(Wlife, count + 1, Wfor, BLUE);

			//wr.cnt++;
			count++;
			cout << setfill('0') << setw(3) << timem << ":00 blue wolf " << count << " born" << endl;
			//time++;
		}


		return sign;


	}

	
};



int main(){
	Red *r;
	Blue *b;
	int n;
	//	int min;
	int i = 0;
	int j = 0;
	int k = 0;
	int z = 0;
	int redstatus = 1, bluestatus = 1;
	City *c[22];
	//int q, p;
	cin >> n;
	for (k = 0; k < n; k++){
		redstatus = 1, bluestatus = 1;
		r = new Red;
		b = new Blue;
		r->count = 0; b->count = 0;
		r->sign = 0; b->sign = 0;
		i = 0;
		j = 0;
		timem = 0;
		cin >> Mlife >> Ncity >> Rarrow >> Klion >> Ttime;
		cin >> Dlife >> Nlife >> Ilife >> Llife >> Wlife;
		cin >> Dfor >> Nfor >> Ifor >> Lfor >> Wfor;
		r->lifetotal = Mlife;
		b->lifetotal = r->lifetotal;
		for (z = 0; z <= Ncity + 1; z++){
			c[z] = new City(z);
		}
		cout << "Case " << k + 1 << ":" << endl;
		if (Ttime / 60 >= timem){
			
			while (redstatus || bluestatus){
				
				//产生
				if (r->start(i % 5)){
					i++;
					c[0]->cr[1] = r->mo[r->count - 1];
				}
				if (b->start(j % 5)){
					j++;
					c[Ncity + 1]->cb[1] = b->mo[b->count - 1];
				}
				if (Ttime % 60 < 5&&Ttime / 60 == timem)break;
				//逃跑
				for (z = 0; z <= Ncity + 1; z++){
					if (c[z]->cr[1] != NULL&&c[z]->cr[1]->tape == LION&&c[z]->cr[1]->escape() == 1 && z < Ncity + 1){
						cout << setfill('0') << setw(3) << timem << ":05 red lion " << c[z]->cr[1]->num << " ran away" << endl;
						c[z]->monu--;
						c[z]->cr[1] = NULL;
					}
					if (c[z]->cb[1] != NULL&&c[z]->cb[1]->tape == LION&&c[z]->cb[1]->escape() == 1 && z > 0){
						cout << setfill('0') << setw(3) << timem << ":05 blue lion " << c[z]->cb[1]->num << " ran away" << endl;
						c[z]->monu--;
						c[z]->cb[1] = NULL;
					}
				}


				//r->escap();
				//b->escap();
				if (Ttime % 60 < 10 && Ttime / 60 == timem)break;

				//前进按城市顺序从小号到大号，再按从红到蓝  以目的地为准！！！

				for (z = 0; z <= Ncity + 1; z++){
					//red
					if (z > 0 && c[z - 1]->cr[1] != NULL){
						c[z - 1]->cr[1]->move();
						if (z != Ncity + 1){
							cout << setfill('0') << setw(3) << timem << ":10 red ";
							priname(c[z - 1]->cr[1]->tape);
							cout << " " << c[z - 1]->cr[1]->num << " marched to city " << c[z]->num << " with " << c[z - 1]->cr[1]->life << " elements and force " << c[z - 1]->cr[1]->force << endl;
							c[z]->monu++;
							c[z]->cr[0] = c[z - 1]->cr[1];
							c[z - 1]->monu--;
							c[z - 1]->cr[1] = NULL;

							
						}
						else{
							cout << setfill('0') << setw(3) << timem << ":10 red ";
							priname(c[z - 1]->cr[1]->tape);
							cout << " " << c[z - 1]->cr[1]->num << " reached blue headquarter with " << c[z - 1]->cr[1]->life << " elements and force " << c[z - 1]->cr[1]->force << endl;
							c[Ncity + 1]->monu++;
							c[Ncity + 1]->cr[1] = c[Ncity]->cr[1];
							c[Ncity]->monu--;
							c[Ncity]->cr[1] = NULL;
							r->winner++;
							if (r->winner == 2){
								cout << setfill('0') << setw(3) << timem << ":10 blue headquarter was taken" << endl;
							}
							
						}
					}
					if (z > 0 && c[z - 1]->cr[0] != NULL){
						c[z - 1]->cr[1] = c[z - 1]->cr[0];
						c[z - 1]->cr[0] = NULL;
					}

					//blue
					if (z < Ncity + 1 && c[z + 1]->cb[1] != NULL){
						c[z + 1]->cb[1]->move();
						if (z != 0){
							cout << setfill('0') << setw(3) << timem << ":10 blue ";
							priname(c[z + 1]->cb[1]->tape);
							cout << " " << c[z + 1]->cb[1]->num << " marched to city " << c[z]->num << " with " << c[z + 1]->cb[1]->life << " elements and force " << c[z + 1]->cb[1]->force << endl;
							c[z]->monu++;

							c[z]->cb[0] = c[z + 1]->cb[1];
							c[z + 1]->monu--;
							c[z + 1]->cb[1] = NULL;

							
						}
						else{
							//c[z+1]->cb[1]->move();
							cout << setfill('0') << setw(3) << timem << ":10 blue ";
							priname(c[z + 1]->cb[1]->tape);
							cout << " " << c[z + 1]->cb[1]->num << " reached red headquarter with " << c[z + 1]->cb[1]->life << " elements and force " << c[z + 1]->cb[1]->force << endl;
							c[0]->monu++;
							c[0]->cb[1] = c[1]->cb[1];
							c[1]->monu--;
							c[1]->cb[1] = NULL;

							b->winner++;
							if (b->winner == 2){
								cout << setfill('0') << setw(3) << timem << ":10 red headquarter was taken" << endl;

							}
						}
					}
					if (z < Ncity + 1 && c[z]->cb[0] != NULL){
						c[z]->cb[1] = c[z]->cb[0];
						c[z]->cb[0] = NULL;
					}
				}

				//r->forword(c);
				//b->forword(c);



				//结束
				if (r->winner == 2){
					break;
				}
				if (b->winner == 2){
					break;
				}


				//城市生产生命元
				for (z = 1; z <= Ncity; z++){
					c[z]->life += 10;
				}

				if (Ttime % 60 < 30 && Ttime / 60 == timem)break;
				//武士夺取生命
				for (z = 1; z <= Ncity; z++){
					if (c[z]->monu == 1){
						if (c[z]->cr[1] != NULL){
							cout << setfill('0') << setw(3) << timem << ":30 red ";
							priname(c[z]->cr[1]->tape);
							cout << " " << c[z]->cr[1]->num << " earned " << c[z]->life << " elements for his headquarter" << endl;
							r->lifetotal += c[z]->life;
							c[z]->life = 0;
						}
						if (c[z]->cb[1] != NULL){
							cout << setfill('0') << setw(3) << timem << ":30 blue ";
							priname(c[z]->cb[1]->tape);
							cout << " " << c[z]->cb[1]->num << " earned " << c[z]->life << " elements for his headquarter" << endl;
							b->lifetotal += c[z]->life;
							c[z]->life = 0;
						}
					}
				}

				if (Ttime % 60 < 35 && Ttime / 60 == timem)break;
				//射箭
				for (z = 1; z <= Ncity; z++){
					if (c[z]->cr[1] != NULL&&c[z]->cr[1]->weapon[2] != NULL&&c[z + 1]->cb[1] != NULL){
						c[z]->cr[1]->weapon[2]->use(c[z + 1]->cb[1]);
						if (c[z]->cr[1]->weapon[2]->check() == 1){ delete c[z]->cr[1]->weapon[2]; c[z]->cr[1]->weapon[2] = NULL; }
						if (c[z + 1]->cb[1]->status == DEATH){
							cout << setfill('0') << setw(3) << timem << ":35 red ";
							priname(c[z]->cr[1]->tape);
							cout << " " << c[z]->cr[1]->num << " shot and killed blue ";
							priname(c[z + 1]->cb[1]->tape);
							cout << " " << c[z + 1]->cb[1]->num << endl;
							//delete c[z + 1]->cb[1];
							c[z + 1]->monu--;
						}
						else {
							cout << setfill('0') << setw(3) << timem << ":35 red ";
							priname(c[z]->cr[1]->tape);
							cout << " " << c[z]->cr[1]->num << " shot" << endl;
						}

					}
					if (c[z]->cb[1] != NULL&&c[z]->cb[1]->weapon[2] != NULL&&c[z - 1]->cr[1] != NULL){
						c[z]->cb[1]->weapon[2]->use(c[z - 1]->cr[1]);
						if (c[z]->cb[1]->weapon[2]->check() == 1){ delete c[z]->cb[1]->weapon[2]; c[z]->cb[1]->weapon[2] = NULL; }
						if (c[z - 1]->cr[1]->status == DEATH){
							cout << setfill('0') << setw(3) << timem << ":35 blue ";
							priname(c[z]->cb[1]->tape);
							cout << " " << c[z]->cb[1]->num << " shot and killed red ";
							priname(c[z - 1]->cr[1]->tape);
							cout << " " << c[z - 1]->cr[1]->num << endl;
							c[z - 1]->monu--;
						}
						else {
							cout << setfill('0') << setw(3) << timem << ":35 blue ";
							priname(c[z]->cb[1]->tape);
							cout << " " << c[z]->cb[1]->num << " shot" << endl;
						}
					}
				}
				if (Ttime % 60 < 38 && Ttime / 60 == timem)break;
				//爆炸

				for (z = 1; z <= Ncity; z++){
					if (c[z]->monu == 2 && c[z]->cr[1] != NULL&&c[z]->cr[1]->weapon[1] != NULL){
						if (c[z]->flag == RED ||(c[z]->flag==0&& c[z]->num % 2 != 0)){//红方发动攻击
							if (c[z]->cr[1]->weapon[0] != NULL){//自己有剑
								if (c[z]->cr[1]->force + c[z]->cr[1]->weapon[0]->force < c[z]->cb[1]->life&&c[z]->cb[1]->tape != NINJA){//杀不死对方且对方不是忍者
									if (c[z]->cb[1]->weapon[0] != NULL){//对方有剑
										if (c[z]->cb[1]->force / 2 + c[z]->cb[1]->weapon[0]->force >= c[z]->cr[1]->life){
											cout << setfill('0') << setw(3) << timem << ":38 blue ";
											priname(c[z]->cr[1]->tape);
											cout << " " << c[z]->cr[1]->num << " used a bomb and killed red ";
											priname(c[z]->cb[1]->tape);
											cout << " " << c[z]->cb[1]->num << endl;
											c[z]->monu = 0;
											c[z]->cb[1] = NULL;
											c[z]->cr[1] = NULL;
											//lion 7
										}
									}
									else{//对方没剑
										if (c[z]->cb[1]->force / 2 >= c[z]->cr[1]->life){
											cout << setfill('0') << setw(3) << timem << ":38 red ";
											priname(c[z]->cr[1]->tape);
											cout << " " << c[z]->cr[1]->num << " used a bomb and killed blue ";
											priname(c[z]->cb[1]->tape);
											cout << " " << c[z]->cb[1]->num << endl;
											c[z]->monu = 0;
											c[z]->cb[1] = NULL;
											c[z]->cr[1] = NULL;
											//lion 7
										}
									}
								}
							}//带剑
							else{
								if (c[z]->cr[1]->force < c[z]->cb[1]->life&&c[z]->cb[1]->tape != NINJA){//杀不死对方且对方不是忍者
									if (c[z]->cb[1]->weapon[0] != NULL){//对方有剑
										if (c[z]->cb[1]->force / 2 + c[z]->cb[1]->weapon[0]->force >= c[z]->cr[1]->life){
											cout << setfill('0') << setw(3) << timem << ":38 red ";
											priname(c[z]->cr[1]->tape);
											cout << " " << c[z]->cr[1]->num << " used a bomb and killed blue ";
											priname(c[z]->cb[1]->tape);
											cout << " " << c[z]->cb[1]->num << endl;
											c[z]->monu = 0;
											c[z]->cb[1] = NULL;
											c[z]->cr[1] = NULL;
											//lion 7
										}
									}
									else{//对方没剑
										if (c[z]->cb[1]->force / 2 >= c[z]->cr[1]->life){
											cout << setfill('0') << setw(3) << timem << ":38 red ";
											priname(c[z]->cr[1]->tape);
											cout << " " << c[z]->cr[1]->num << " used a bomb and killed blue ";
											priname(c[z]->cb[1]->tape);
											cout << " " << c[z]->cb[1]->num << endl;
											c[z]->monu = 0;
											c[z]->cb[1] = NULL;
											c[z]->cr[1] = NULL;
											//lion 7
										}
									}
								}
							}//不带剑
						}
						else{//蓝方发动攻击
							if (c[z]->cb[1]->weapon[0] == NULL){
								if (c[z]->cr[1]->life <= c[z]->cb[1]->force){
									cout << setfill('0') << setw(3) << timem << ":38 red ";
									priname(c[z]->cr[1]->tape);
									cout << " " << c[z]->cr[1]->num << " used a bomb and killed blue ";
									priname(c[z]->cb[1]->tape);
									cout << " " << c[z]->cb[1]->num << endl;
									c[z]->monu = 0;
									c[z]->cb[1] = NULL;
									c[z]->cr[1] = NULL;
								}
							}//对方不带剑
							else{
								if (c[z]->cr[1]->life <= c[z]->cb[1]->force + c[z]->cb[1]->weapon[0]->force){
									cout << setfill('0') << setw(3) << timem << ":38 red ";
									priname(c[z]->cr[1]->tape);
									cout << " " << c[z]->cr[1]->num << " used a bomb and killed blue ";
									priname(c[z]->cb[1]->tape);
									cout << " " << c[z]->cb[1]->num << endl;
									c[z]->monu = 0;
									c[z]->cb[1] = NULL;
									c[z]->cr[1] = NULL;
								}
							}//对方带
						}
					}
					//蓝方
					if (c[z]->monu == 2 && c[z]->cb[1] != NULL&&c[z]->cb[1]->weapon[1] != NULL){
						if (c[z]->flag == BLUE || (c[z]->flag==0&&c[z]->num % 2 == 0)){//lan方发动攻击
							if (c[z]->cb[1]->weapon[0] != NULL){//自己有剑
								if (c[z]->cb[1]->force + c[z]->cb[1]->weapon[0]->force < c[z]->cr[1]->life&&c[z]->cr[1]->tape != NINJA){//杀不死对方且对方不是忍者
									if (c[z]->cr[1]->weapon[0] != NULL){//对方有剑
										if (c[z]->cr[1]->force / 2 + c[z]->cr[1]->weapon[0]->force >= c[z]->cb[1]->life){
											cout << setfill('0') << setw(3) << timem << ":38 blue ";
											priname(c[z]->cb[1]->tape);
											cout << " " << c[z]->cb[1]->num << " used a bomb and killed red ";
											priname(c[z]->cr[1]->tape);
											cout << " " << c[z]->cr[1]->num << endl;
											c[z]->monu = 0;
											c[z]->cb[1] = NULL;
											c[z]->cr[1] = NULL;
											//lion 7
										}
									}
									else{//对方没剑
										if (c[z]->cr[1]->force / 2 >= c[z]->cb[1]->life){
											cout << setfill('0') << setw(3) << timem << ":38 blue ";
											priname(c[z]->cb[1]->tape);
											cout << " " << c[z]->cb[1]->num << " used a bomb and killed red ";
											priname(c[z]->cr[1]->tape);
											cout << " " << c[z]->cr[1]->num << endl;
											c[z]->monu = 0;
											c[z]->cb[1] = NULL;
											c[z]->cr[1] = NULL;
											//lion 7
										}
									}
								}
							}//带剑
							else{
								if (c[z]->cb[1]->force < c[z]->cr[1]->life&&c[z]->cr[1]->tape != NINJA){//杀不死对方且对方不是忍者
									if (c[z]->cr[1]->weapon[0] != NULL){//对方有剑
										if (c[z]->cr[1]->force / 2 + c[z]->cr[1]->weapon[0]->force >= c[z]->cb[1]->life){
											cout << setfill('0') << setw(3) << timem << ":38 blue ";
											priname(c[z]->cb[1]->tape);
											cout << " " << c[z]->cb[1]->num << " used a bomb and killed red ";
											priname(c[z]->cr[1]->tape);
											cout << " " << c[z]->cr[1]->num << endl;
											c[z]->monu = 0;
											c[z]->cb[1] = NULL;
											c[z]->cr[1] = NULL;
											//lion 7
										}
									}
									else{//对方没剑
										if (c[z]->cr[1]->force / 2 >= c[z]->cb[1]->life){
											cout << setfill('0') << setw(3) << timem << ":38 blue ";
											priname(c[z]->cb[1]->tape);
											cout << " " << c[z]->cb[1]->num << " used a bomb and killed red ";
											priname(c[z]->cr[1]->tape);
											cout << " " << c[z]->cr[1]->num << endl;
											c[z]->monu = 0;
											c[z]->cb[1] = NULL;
											c[z]->cr[1] = NULL;
											//lion 7
										}
									}
								}
							}//不带剑
						}
						else{//蓝方发动攻击
							if (c[z]->cr[1]->weapon[0] == NULL){
								if (c[z]->cb[1]->life <= c[z]->cr[1]->force){
									cout << setfill('0') << setw(3) << timem << ":38 blue ";
									priname(c[z]->cb[1]->tape);
									cout << " " << c[z]->cb[1]->num << " used a bomb and killed red ";
									priname(c[z]->cr[1]->tape);
									cout << " " << c[z]->cr[1]->num << endl;
									c[z]->monu = 0;
									c[z]->cb[1] = NULL;
									c[z]->cr[1] = NULL;
								}
							}//对方不带剑
							else{
								if (c[z]->cb[1]->life <= c[z]->cr[1]->force + c[z]->cr[1]->weapon[0]->force){
									cout << setfill('0') << setw(3) << timem << ":38 blue ";
									priname(c[z]->cb[1]->tape);
									cout << " " << c[z]->cb[1]->num << " used a bomb and killed red ";
									priname(c[z]->cr[1]->tape);
									cout << " " << c[z]->cr[1]->num << endl;
									c[z]->monu = 0;
									c[z]->cb[1] = NULL;
									c[z]->cr[1] = NULL;
								}
							}//对方带
						}
					}

				}

				if (Ttime % 60 < 40 && Ttime / 60 == timem)break;
				//进攻
				for (z = 1; z <= Ncity; z++){
					if (c[z]->monu == 1){//开战前被射死
						if (c[z]->cb[1] != NULL&&c[z]->cb[1]->status == DEATH){//蓝方被射死
							c[z]->rwin++;
							c[z]->bwin = 0;

							if (c[z]->cr[1]->tape == DRAGON&&c[z]->cr[1]->morale > 0.8){
								if (c[z]->flag == RED || (c[z]->flag == 0 && c[z]->num % 2 != 0)){
									cout << setfill('0') << setw(3) << timem << ":40 ";
									cout << "red";
									cout << " dragon " << c[z]->cr[1]->num << " yelled in city " << c[z]->num << endl;
								}
							}//活着且士气大于0.8即欢呼

							cout << setfill('0') << setw(3) << timem << ":40 red ";
							priname(c[z]->cr[1]->tape);
							cout << " " << c[z]->cr[1]->num << " earned " << c[z]->life << " elements for his headquarter" << endl;
							//c[z]->life = 0;
							if (c[z]->rwin == 2&&c[z]->flag!=RED){
								cout << setfill('0') << setw(3) << timem << ":40 red flag raised in city " << c[z]->num << endl;
								c[z]->flag = RED;
							}
							if (c[z]->cr[1]->tape == WOLF){
								c[z]->cr[1]->getweapon(c[z]->cb[1]);
							}
						}
						if (c[z]->cr[1] != NULL&&c[z]->cr[1]->status == DEATH){//红方射死
							
							c[z]->bwin++;
							c[z]->rwin = 0;
							//b->lifetotal += c[z]->life;
							if ((c[z]->flag == BLUE || (c[z]->flag == 0 && c[z]->num % 2 == 0))&&c[z]->cb[1]->tape == DRAGON&&c[z]->cb[1]->morale > 0.8){
								cout << setfill('0') << setw(3) << timem << ":40 ";
								cout << "blue";
								cout << " dragon " << c[z]->cb[1]->num << " yelled in city " << c[z]->num << endl;
							}//活着且士气大于0.8即欢呼

							cout << setfill('0') << setw(3) << timem << ":40 blue ";
							priname(c[z]->cb[1]->tape);
							cout << " " << c[z]->cb[1]->num << " earned " << c[z]->life << " elements for his headquarter" << endl;
							//c[z]->life = 0;
							if (c[z]->bwin == 2&&c[z]->flag!=BLUE){
								cout << setfill('0') << setw(3) << timem << ":40 blue flag raised in city " << c[z]->num << endl;
								c[z]->flag = BLUE;
							}
							if (c[z]->cb[1]->tape == WOLF){
								c[z]->cb[1]->getweapon(c[z]->cr[1]);
							}
						}
					}
					if (c[z]->monu == 2){//开战
						if (c[z]->flag == RED ||( c[z]->flag==0&&c[z]->num % 2 != 0)){//红方进攻
							c[z]->cr[1]->attack(c[z]->cb[1], c[z]);
						}
						else{
							c[z]->cb[1]->attack(c[z]->cr[1], c[z]);
						}
						if (c[z]->monu == 1){//奖励生命
							if (c[z]->cr[1]->status == DEATH){
								
								c[z]->bwin++;
								c[z]->rwin = 0;
								//b->lifetotal += c[z]->life;

								cout << setfill('0') << setw(3) << timem << ":40 blue ";
								priname(c[z]->cb[1]->tape);
								cout << " " << c[z]->cb[1]->num << " earned " << c[z]->life << " elements for his headquarter" << endl;
								//c[z]->life = 0;
								if (c[z]->bwin == 2 && c[z]->flag != BLUE){
									cout << setfill('0') << setw(3) << timem << ":40 blue flag raised in city " << c[z]->num << endl;
									c[z]->flag = BLUE;
									
									}
								if (c[z]->cb[1]->tape == WOLF){
									c[z]->cb[1]->getweapon(c[z]->cr[1]);
								}
								//001:40 blue dragon 210
							}//蓝胜
							else{
								
								c[z]->rwin++;
								c[z]->bwin = 0;
								//r->lifetotal += c[z]->life;
								cout << setfill('0') << setw(3) << timem << ":40 red ";
								priname(c[z]->cr[1]->tape);
								cout << " " << c[z]->cr[1]->num << " earned " << c[z]->life << " elements for his headquarter" << endl;
								//c[z]->life = 0;
								if (c[z]->rwin == 2&&c[z]->flag!=RED){
									cout << setfill('0') << setw(3) << timem << ":40 red flag raised in city " << c[z]->num << endl;
									c[z]->flag = RED;
								}
								if (c[z]->cb[1]->tape == WOLF){
									c[z]->cb[1]->getweapon(c[z]->cr[1]);
								}
							}//红胜
						}//奖励生命
						else{
							c[z]->rwin = 0;
							c[z]->bwin = 0;
						}
					}//开战
				}//进攻
				//奖励红方
				for (z = Ncity; z >0; z--){
					if (c[z]->monu == 1){//开战前被射死
						if (c[z]->cb[1] != NULL&&c[z]->cb[1]->status == DEATH){//蓝方败
							
							if (born(r->lifetotal, 8) == 0){
								r->lifetotal -= 8;
								c[z]->cr[1]->life += 8;
							}
							

							if (c[z]->cr[1]->tape == WOLF){
								c[z]->cr[1]->getweapon(c[z]->cb[1]);
							}
							
						}
					}
				}
					//奖励蓝方
					for (z = 1; z <= Ncity; z++){
						if (c[z]->monu == 1){//开战前被射死
							if (c[z]->cr[1] != NULL&&c[z]->cr[1]->status == DEATH){//红方败
								if (born(b->lifetotal, 8) == 0){
									b->lifetotal -= 8;
									c[z]->cb[1]->life += 8;
								}


								if (c[z]->cb[1]->tape == WOLF){
									c[z]->cb[1]->getweapon(c[z]->cr[1]);
								}
							}
						}
					}

					//回收生命元
					for (z = 1; z <= Ncity; z++){
						if (c[z]->monu == 1){//开战前被射死
							if (c[z]->cb[1] != NULL&&c[z]->cb[1]->status == DEATH){//蓝方被射死
								
								
								r->lifetotal += c[z]->life;

								/*cout << setfill('0') << setw(3) << timem << ":40 red ";
								priname(c[z]->cr[1]->tape);
								cout << " " << c[z]->cr[1]->num << " earned " << c[z]->life << " elements for his headquarter" << endl;*/
								c[z]->life = 0;
								
								
							}
							if (c[z]->cr[1] != NULL&&c[z]->cr[1]->status == DEATH){//红方射死
								
							
								b->lifetotal += c[z]->life;
								/*
								cout << setfill('0') << setw(3) << timem << ":40 blue ";
								priname(c[z]->cb[1]->tape);
								cout << " " << c[z]->cb[1]->num << " earned " << c[z]->life << " elements for his headquarter" << endl;*/
								c[z]->life = 0;
								
								
							}
						}
					}

					//插旗
					/*
					for (z = 1; z <= Ncity; z++){
						if (c[z]->bwin == 2){
							cout << setfill('0') << setw(3) << timem << ":40 blue flag raised in city " << c[z]->num << endl;
							c[z]->flag = BLUE;
						}
						if (c[z]->rwin == 2){
							cout << setfill('0') << setw(3) << timem << ":40 red flag raised in city " << c[z]->num << endl;
							c[z]->flag = RED;
						}
					}*/

				if (Ttime % 60 < 50 && Ttime / 60 == timem)break;
				//报告生命元
				cout << setfill('0') << setw(3) << timem << ":50 " << r->lifetotal << " elements in red headquarter" << endl;
				cout << setfill('0') << setw(3) << timem << ":50 " << b->lifetotal << " elements in blue headquarter" << endl;
				if (Ttime % 60 < 55 && Ttime / 60 == timem)break;
				//报告武器
				for (z = 0; z <= Ncity+1; z++){
					int sss = 0;
					if (c[z]->cr[1] != NULL&&c[z]->cr[1]->status == LIVE){
						sss = 1;
						cout << setfill('0') << setw(3) << timem << ":55 red ";
						priname(c[z]->cr[1]->tape);
						cout << " " << c[z]->cr[1]->num << " has ";
						if (c[z]->cr[1]->weapon[2] != NULL){
							cout << "arrow(" << c[z]->cr[1]->weapon[2]->check() - 1 << ")";
							if (c[z]->cr[1]->weapon[1] != NULL){
								cout << ",bomb";
								if (c[z]->cr[1]->weapon[0] != NULL){
									cout << ",sword(" << c[z]->cr[1]->weapon[0]->check() - 1 << ")";
								}//has sword
							}//has bomb
							else{
								if (c[z]->cr[1]->weapon[0] != NULL){
									cout << ",sword(" << c[z]->cr[1]->weapon[0]->check() - 1 << ")";
								}//has sword
							}//no bomb
						}//has arrow 
						else{
							if (c[z]->cr[1]->weapon[1] != NULL){
								cout << "bomb";
								if (c[z]->cr[1]->weapon[0] != NULL){
									cout << ",sword(" << c[z]->cr[1]->weapon[0]->check() - 1 << ")";
								}//has sword
							}//has bomb
							else{
								if (c[z]->cr[1]->weapon[0] != NULL){
									cout << "sword(" << c[z]->cr[1]->weapon[0]->check() - 1 << ")";
								}//has sword
								else{
									cout << "no weapon";
								}
							}//no bomb
						}//no arrow
						
					}//红清算
					if (sss == 1)cout << endl;
				}//for
				for (z = 0; z <= Ncity+1; z++){
					int sss = 0;
					if (c[z]->cb[1] != NULL&&c[z]->cb[1]->status == LIVE){
						sss = 1;
						cout << setfill('0') << setw(3) << timem << ":55 blue ";
						priname(c[z]->cb[1]->tape);
						cout << " " << c[z]->cb[1]->num << " has ";
						if (c[z]->cb[1]->weapon[2] != NULL){
							cout << "arrow(" << c[z]->cb[1]->weapon[2]->check() - 1 << ")";
							if (c[z]->cb[1]->weapon[1] != NULL){
								cout << ",bomb";
								if (c[z]->cb[1]->weapon[0] != NULL){
									cout << ",sword(" << c[z]->cb[1]->weapon[0]->check() - 1 << ")";
								}//has sword
							}//has bomb
							else{
								if (c[z]->cb[1]->weapon[0] != NULL){
									cout << ",sword(" << c[z]->cb[1]->weapon[0]->check() - 1 << ")";
								}//has sword
							}//no bomb
						}//has arrow 
						else{
							if (c[z]->cb[1]->weapon[1] != NULL){
								cout << "bomb";
								if (c[z]->cb[1]->weapon[0] != NULL){
									cout << ",sword(" << c[z]->cb[1]->weapon[0]->check() - 1 << ")";
								}//has sword
							}//has bomb
							else{
								if (c[z]->cb[1]->weapon[0] != NULL){
									cout << "sword(" << c[z]->cb[1]->weapon[0]->check() - 1 << ")";
								}//has sword
								else{
									cout << "no weapon";
								}
							}//no bomb
						}//no arrow
					}//蓝结算
					if (sss == 1)cout << endl;
				}//for
				timem++;
				//清除尸体
				for (z = 1; z <= Ncity; z++){
					if ((c[z]->cr[1] != NULL) && c[z]->cr[1]->status == DEATH){
						//c[z]->monu--;
						c[z]->cr[1] = NULL;
					}
					if ((c[z]->cb[1] != NULL) && c[z]->cb[1]->status == DEATH){
						//c[z]->monu--;
						c[z]->cb[1] = NULL;
					}
				}
			}//while
		}//if
		delete r;
		delete b;
	}

	return 0;
}