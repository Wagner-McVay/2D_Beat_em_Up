#include <math.h>
#include "sfwdraw.h"
using namespace sfw;

float GameWidth = 1800;
float GameHeight = 900;

float getAngle(float x1, float y1, float x2, float y2)
{
	float dx = {x2 - x1};
	float dy = {y2 - y1};
	float angle = atan2f(dy, dx);
	return angle;
}

void main()
{
	initContext(GameWidth,GameHeight,"Beat em' Up!");
	unsigned Shadow = loadTextureMap("./Textures/Characters/Shadow.png", 1, 1);
	unsigned Lynette = loadTextureMap("./Textures/Characters/Lynette_Sprites.png", 8, 9);
	unsigned f = loadTextureMap("./Textures/tonc_font.png", 16, 6);
	unsigned d = loadTextureMap("./Textures/fontmap.png",16,16);
	unsigned r = loadTextureMap("./Textures/Levels/greenscreen1.png",2,2);
	unsigned u = loadTextureMap("./Textures/crosshair.png");
	unsigned b = loadTextureMap("./Textures/block.jpg", 1, 1);




	class Player
	{
	public:
		unsigned Shadow = loadTextureMap("./Textures/Characters/Shadow.png", 1, 1);
		unsigned Lynette = loadTextureMap("./Textures/Characters/Lynette_Sprites.png", 8, 9);
		unsigned b = loadTextureMap("./Textures/block.jpg", 1, 1);
		unsigned d = loadTextureMap("./Textures/fontmap.png", 16, 16);
		float o_width = getTextureWidth(Lynette) / 8;
		float o_height = getTextureHeight(Lynette) / 9;
		float xOffset = 37;
		float yOffset = 80;
		float HP[4] = { 100,100,100,100 };
		float MP[4] = { 100,100,100,100 };
		float x[4] = { 360,720,1080,1440 };
		float y[4] = { 200,200,200,200 };
		unsigned int color1[4] = { RED,BLUE,YELLOW,CYAN };
		unsigned int color2[4] = { 0x660000ff, 0x000066ff, 0x666600ff, 0x006666ff };
		bool punch[4] = { 0, 0, 0, 0 };
		bool hit[4] = { 0, 0, 0, 0 };
		bool skip[4] = { 0, 0, 0, 0};
		float animate[4] = { 0,0,0,0 };
		float moveSpeed = 500;
		float width[4] = {o_width, o_width, o_width, o_width };
		float height[4] = {o_height, o_height, o_height, o_height };
		float xStat[4] = { GameWidth - 1775 , GameWidth - 175, GameWidth - 1775 , GameWidth - 175 };
		float yStat[4] = { GameHeight - 25 , GameHeight - 25, GameHeight - 775, GameHeight - 775 };

		void DrawPlayer(int player)
		{

			drawTexture(Shadow, x[player], y[player], 40 * 2, 15 * 2, 0, true, 0, color1[player]);
			
			if (HP[player] <= 0) HP[player] = 0;

			// if Hit
			if (hit[player] == 1)
			{
				punch[player] = 0;
				if (HP[player] > 0)
				{
					if (animate[player] >= 51 || animate[player] < 44) { animate[player] = 44; }
					if (width[player] > 0) { width[player] = 125;	drawTexture(Lynette, x[player] + xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE); x[player] -= 1; }
					if (width[player] < 0) {width[player] = -125;	drawTexture(Lynette, x[player] - xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE); x[player] += 1;	}
					if (animate[player] == 46) { HP[player] -= 5; }
					animate[player] += .25;
					if (animate[player] >= 51) { hit[player] = 0; animate[player] = 0; }
				}
				if (HP[player] <= 0) 
				{ 
					if (animate[player] >= 61 || animate[player] < 50) { animate[player] = 50; }
					if (width[player] > 0)	{ width[player] = 125;	drawTexture(Lynette, x[player] + xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE); }
					if (width[player] < 0) { width[player] = -125;	drawTexture(Lynette, x[player] - xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE); }
					if (animate[player] >= 60) { goto Q; }
					animate[player] += .25;
				}
				goto Q;
			}

			// if enough MP, ENTER does attack
			if (punch[player] == 0 && MP[player] >= 20 && getKey(KEY_ENTER))
			{punch[player] = 1; animate[player] = 16; MP[player] -= 20;}

			// attack animation
			if (punch[player] == 1)
			{
				if (animate[player] >= 45 || animate[player] < 16) { animate[player] = 16; }

				if (width[player] > 0)	{ width[player] = 125;	drawTexture(Lynette, x[player] + xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE);}
				else					{ width[player] = -125;	drawTexture(Lynette, x[player] - xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE);}
				animate[player] += .25;
				if (animate[player] >= 45) { punch[player] = 0; animate[player] = 0; }
				goto Q; 
			}

			if (MP[player] < 100) { MP[player] += .2; }
			if (MP[player] > 100) { MP[player] = 100; }

			// idle animation
			if (!getKey(KEY_W) && !getKey(KEY_S) && !getKey(KEY_D) && !getKey(KEY_A))
			{
				if (animate[player] >= 6 || animate[player] < 0) { animate[player] = 0;}
				if (width[player] > 0)	{ width[player] = 125;	drawTexture(Lynette, x[player] + xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE);}
				else					{ width[player] = -125;	drawTexture(Lynette, x[player] - xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE);}
				animate[player] += .2;
			}

			// running animation
			if (getKey(KEY_W) || getKey(KEY_S) || getKey(KEY_D) || getKey(KEY_A))
			{
				if (animate[player] >= 16 || animate[player] < 8) { animate[player] = 8; }
				if (width[player] > 0)	{ width[player] = 125;	drawTexture(Lynette, x[player] + xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE);}
				else					{ width[player] = -125;	drawTexture(Lynette, x[player] - xOffset, y[player] + yOffset, width[player] * 2, height[player] * 2, 0, true, animate[player], WHITE);}
				if (getKey(KEY_W))
				{y[player] += getDeltaTime() * moveSpeed / 2;}
				if (getKey(KEY_S))
				{y[player] -= getDeltaTime() * moveSpeed / 2;}
				if (getKey(KEY_D))
				{
					if (width[player] < 0) width[player] *= -1;
					x[player] += getDeltaTime() * moveSpeed;
				}
				if (getKey(KEY_A))
				{
					if (width[player] > 0) width[player] *= -1;
					x[player] -= getDeltaTime() * moveSpeed;
				}
				animate[player] += .2;
				if (animate[player] >= 16) animate[player] = 8;
			}
			Q:

			drawTexture(b, xStat[player] - 9, yStat[player] + 9, 168, 118, 0, false, 0, color1[player]);
			drawTexture(b, xStat[player] - 5, yStat[player] + 5, 160, 110, 0, false, 0, color2[player]);
			switch (player)
			{
			case 0: drawString(d, "P1", xStat[player], yStat[player], 40, 48, 0, '\0', color1[player]);	break;
			case 1: drawString(d, "P2", xStat[player], yStat[player], 40, 48, 0, '\0', color1[player]);	break;
			case 2: drawString(d, "P3", xStat[player], yStat[player], 40, 48, 0, '\0', color1[player]);	break;
			case 3: drawString(d, "P4", xStat[player], yStat[player], 40, 48, 0, '\0', color1[player]);	break;
			}

			drawTexture(b, xStat[player], yStat[player] - 50, 150, 24, 0, false, 0, BLACK);
			drawString(d, "HP", xStat[player] + 3, yStat[player] - 50, 20, 24);
			drawTexture(b, xStat[player] + 47, yStat[player] - 53, HP[player], 18, 0, false, 0, RED);

			drawTexture(b, xStat[player], yStat[player] - 75, 150, 24, 0, false, 0, BLACK);
			drawString(d, "MP", xStat[player] + 3, yStat[player] - 75, 20, 24);
			drawTexture(b, xStat[player] + 47, yStat[player] - 78, MP[player], 18, 0, false, 0, BLUE);
		}
	};
	Player p;

	class Enemy
	{
	public:
		unsigned Shadow = loadTextureMap("./Textures/Characters/Shadow.png", 1, 1);
		unsigned Lynette = loadTextureMap("./Textures/Characters/Lynette_Sprites.png", 8, 8);
		float o_width = getTextureWidth(Lynette) / 8;
		float o_height = getTextureHeight(Lynette) / 9;
		float xOffset = 37;
		float yOffset = 80;
		float HP[4] = { 100,100,100,100 };
		float x[4] = { 1600,1650,1700,1750 };
		float y[4] = { 200,150,100,50 };
		unsigned int color[4] = { MAGENTA,MAGENTA,MAGENTA,MAGENTA };
		bool punch[4] = { 0, 0, 0, 0 };
		bool hit[4] = { 0, 0, 0, 0 };
		float animate[4] = { 0,0,0,0 };
		float moveSpeed = 200;
		float width[4] = { o_width, o_width, o_width, o_width };
		float height[4] = { o_height, o_height, o_height, o_height };

		void move(int enemy,float angle)
		{
			if (animate[enemy] >= 16 || animate[enemy] < 8) animate[enemy] = 8;
			animate[enemy] += .2;
			x[enemy] += cos(angle) * getDeltaTime() * moveSpeed;
			y[enemy] += sin(angle) * getDeltaTime() * moveSpeed;
		}

		void DrawEnemy(int enemy)
		{
			drawTexture(Shadow, x[enemy], y[enemy], 40 * 2, 15 * 2, 0, true, 0, color[enemy]);

		}
	};
	Enemy e;

	int activeEnemy = 1;
	float acc = 0;
	char c = '\0';
	float LevelAnimation = 0;
	setBackgroundColor(NONE);


	while (stepContext())
	{	
		drawTexture(r, 0, 900, 1800, 900, 0, false, LevelAnimation, 0xffffffff);
		acc += getDeltaTime();


		for (int P = 0; P < 1; ++P)
		{
			if (p.y[P] <= e.y[0]) { p.skip[P] = 1; }
			else { p.skip[P] = 0; }

			if (p.punch[P] == 1)
			{
				for (int E = 0; E < 4; ++E)
				{
					if (p.width[P] > 0) { if (p.animate[P] >= 20 && p.animate[P] < 41 && (e.x[E] <= p.x[P] + 150 && e.x[E] >= p.x[P]) && (e.y[E] < p.y[P] + 10 && e.y[E] > p.y[P] - 10)) { e.hit[E] = 1; if (e.HP[E] > 0 && e.animate[E] >= 48) { e.animate[E] = 46; } } }
					if (p.width[P] < 0) { if (p.animate[P] >= 20 && p.animate[P] < 41 && (e.x[E] >= p.x[P] - 150 && e.x[E] <= p.x[P]) && (e.y[E] < p.y[P] + 10 && e.y[E] > p.y[P] - 10)) { e.hit[E] = 1; if (e.HP[E] > 0 && e.animate[E] >= 48) { e.animate[E] = 46; } } }
				}
			}

		}


		for (int P = 0; P < 1; ++P)
		{
			if (p.skip[P] == 0)
			{
				p.DrawPlayer(P);
			}
		}

		for (int E = 0; E < activeEnemy; ++E)
		{
			if (e.HP[E] <= 0 && e.animate[E] == 6)
			{
				if ( activeEnemy < 4) { ++activeEnemy; }
				e.HP[E] = 100;
				e.x[E] = 1600 + (E * 50);
				e.y[E] = 200 - (E * 50);
			}
			// enemy shadow
			if (e.animate[E] != 6) { drawTexture(Shadow, e.x[E], e.y[E], 40 * 2, 15 * 2, 0, true, 0, 0x333333ff); }
			
			// if enemy Hit
			if (e.hit[E] == 1)
			{
				e.punch[E] = 0;
				if (p.width[0] < 0 && e.width[E] < 0) { e.width[E] *= -1; }
				if (p.width[0] > 0 && e.width[E] > 0) { e.width[E] *= -1; }
				if (e.HP[E] > 0)
				{
					if (e.animate[E] >= 51 || e.animate[E] < 44) { e.animate[E] = 44; }
					if (e.width[E] > 0) { drawTexture(Lynette, e.x[E] + e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); e.x[E] -= 1;}
					if (e.width[E] < 0) { drawTexture(Lynette, e.x[E] - e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); e.x[E] += 1;}
					if (e.animate[E] == 46) { e.HP[E] -= 10; }
					e.animate[E] += .25;
					if (e.animate[E] >= 51) { e.hit[E] = 0; e.animate[E] = 0; }
				}
				if (e.HP[E] <= 0)
				{
					if (e.animate[E] != 6) 
					{if (e.animate[E] >= 64 || e.animate[E] < 50) { e.animate[E] = 50; }}
					if (e.width[E] > 0) { drawTexture(Lynette, e.x[E] + e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
					if (e.width[E] < 0) { drawTexture(Lynette, e.x[E] - e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
					if (e.animate[E] >= 63) { e.hit[E] = 0; e.animate[E] = 6; goto Z; }
					e.animate[E] += .25;
				}
				goto Z;
			}

			// Enemy attack animation
			if (e.punch[E] == 1)
			{
				if (e.animate[E] >= 45 || e.animate[E] < 16) { e.animate[E] = 16; }
				if (e.width[E] > 0) { drawTexture(Lynette, e.x[E] + e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
				if (e.width[E] < 0) { drawTexture(Lynette, e.x[E] - e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
				e.animate[E] += .25;
				if (e.width[E] > 0) { if (e.animate[E] >= 20 && e.animate[E] < 41 && (p.x[0] <= e.x[E] + 150 && p.x[0] >= e.x[E]) && (p.y[0] < e.y[E] + 10 && p.y[0] > e.y[E] - 10)) { p.hit[0] = 1; if (p.width[0] > 0) { p.width[0] *= -1; p.punch[0] = 0; } if (p.HP[0] > 0 && p.animate[0] >= 48) { p.animate[0] = 46; } } }
				if (e.width[E] < 0) { if (e.animate[E] >= 20 && e.animate[E] < 41 && (p.x[0] >= e.x[E] - 150 && p.x[0] <= e.x[E]) && (p.y[0] < e.y[E] + 10 && p.y[0] > e.y[E] - 10)) { p.hit[0] = 1; if (p.width[0] < 0) { p.width[0] *= -1; p.punch[0] = 0; } if (p.HP[0] > 0 && p.animate[0] >= 48) { p.animate[0] = 46; } } }
				if (e.animate[E] >= 45) { e.punch[E] = 0; e.animate[E] = 0; }
				goto Z;
			}
			
			// if the player is doing attack and enemy is infront of attack range
			if ((p.animate[0] >= 16 && p.animate[0] <= 41) && ((e.x[E] > p.x[0] + 150 && p.width[0] > 0) || (e.x[E] < p.x[0] - 150 && p.width[0] < 0)))
			{
				

				if ((e.x[E] > p.x[0] + 160 || e.x[E] < p.x[0] - 160))
				{
					if (e.animate[E] >= 16 || e.animate[E] < 8) { e.animate[E] = 8; }
					if (e.x[E] > p.x[0] && e.x[E] < p.x[0] + 160 && e.width[E] < 0) e.width[E] *= -1;
					if (e.x[E] < p.x[0] && e.x[E] > p.x[0] - 160 && e.width[E] > 0) e.width[E] *= -1;
					if (e.x[E] > p.x[0] + 160 && e.width[E] > 0) e.width[E] *= -1;
					if (e.x[E] < p.x[0] - 160 && e.width[E] < 0) e.width[E] *= -1;
					if (e.width[E] > 0) { drawTexture(Lynette, e.x[E] + e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
					if (e.width[E] < 0) { drawTexture(Lynette, e.x[E] - e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
					if (e.x[E] > p.x[0] + 160) { e.move(E, getAngle(e.x[E], e.y[E], p.x[0] + 160, p.y[0])); }
					if (e.x[E] < p.x[0] - 160) { e.move(E, getAngle(e.x[E], e.y[E], p.x[0] - 160, p.y[0])); }
				}
				else
				{
					if (e.animate[E] >= 6 || e.animate[E] < 0) { e.animate[E] = 0; }
					if (e.x[E] > p.x[0] && e.width[E] > 0) e.width[E] *= -1;
					if (e.x[E] < p.x[0] && e.width[E] < 0) e.width[E] *= -1;
					if (e.width[E] > 0) { drawTexture(Lynette, e.x[E] + e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
					if (e.width[E] < 0) { drawTexture(Lynette, e.x[E] - e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
					e.animate[E] += .2;
				}
			}

			else
			{
				// if Enemy is not near the player
				if ((e.x[E] > p.x[0] + 100 || e.x[E] < p.x[0] - 100) || (e.y[E] > p.y[0] + 10 || e.y[E] < p.y[0] - 10))
				{
					if (e.animate[E] >= 16 || e.animate[E] < 8) { e.animate[E] = 8; }
					if (e.width[E] > 0) { drawTexture(Lynette, e.x[E] + e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
					if (e.width[E] < 0) { drawTexture(Lynette, e.x[E] - e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]); }
					if (e.x[E] > p.x[0] && e.width[E] > 0) e.width[E] *= -1;
					if (e.x[E] < p.x[0] && e.width[E] < 0) e.width[E] *= -1;
					if (p.animate[0] >= 16 && p.animate[0] <= 41)
					{
						if (p.width[0] > 0) { e.move(E, getAngle(e.x[E], e.y[E], p.x[0] - 100, p.y[0])); }
						if (p.width[0] < 0) { e.move(E, getAngle(e.x[E], e.y[E], p.x[0] + 100, p.y[0])); }
					}
					else
					{
						if (e.x[E] > p.x[0]) { e.move(E, getAngle(e.x[E], e.y[E], p.x[0] + 100, p.y[0])); }
						if (e.x[E] < p.x[0]) { e.move(E, getAngle(e.x[E], e.y[E], p.x[0] - 100, p.y[0])); }
					}
				}
				// if enemy is near the player
				else
				{
					if (e.animate[E] >= 6 || e.animate[E] < 0) { e.animate[E] = 0;}
					if (e.x[E] > p.x[0] && e.width[E] > 0) e.width[E] *= -1;
					if (e.x[E] < p.x[0] && e.width[E] < 0) e.width[E] *= -1;
					if (e.width[E] > 0) { e.width[E] = 125;		drawTexture(Lynette, e.x[E] + e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]);}
					if (e.width[E] < 0) { e.width[E] = -125;	drawTexture(Lynette, e.x[E] - e.xOffset, e.y[E] + e.yOffset, e.width[E] * 2, e.height[E] * 2, 0, true, e.animate[E], e.color[E]);}
					e.animate[E] += .2;
					if (p.HP[0] != 0) { if (e.animate[E] >= 3 && e.punch[E] == 0) { e.animate[E] = 16; e.punch[E] = 1; } }
				}

			}

		Z:
			drawTexture(b, e.x[E] - 52, e.y[E] + 152, 54, 10, 0, false, 0, BLACK);
			drawTexture(b, e.x[E] - 50, e.y[E] + 150, e.HP[E] / 2, 6, 0, false, 0, MAGENTA);
		}
		
		for (int P = 0; P < 1; ++P)
		{
			if (p.skip[P] == 1)
			{
				p.DrawPlayer(P);
			}
		}
		//if (getMouseButton(MOUSE_BUTTON_LEFT))
		//{
		//	drawTexture(u, getMouseX(), getMouseY(), getTextureWidth(u) / 2.5, getTextureHeight(u) / 2.5, 45, true, 0, 0x88ffffff);
		//	drawLine(p.x[0], p.y[0], getMouseX(), getMouseY(), RED);
		//}
		//else
		//{
		//	drawTexture(u, getMouseX(), getMouseY(), getTextureWidth(u) / 2, getTextureHeight(u) / 2);
		//	drawLine(p.x[0], p.y[0], getMouseX(), getMouseY(), RED);
		//}
		GameOver:
		LevelAnimation += .2;
		if (LevelAnimation >= 4) LevelAnimation = 0;
	}
	termContext();
}