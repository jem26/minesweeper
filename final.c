//Jamie Maher
//CSE 20211
//final.c
//This program will create a traditional game of minesweeper

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gfx4.h"
#include <unistd.h>
#include <X11/Xlib.h>
#define DIM 752

struct Cell
{
	int show;
	int flag;
	int bomb;
	int count;
	int xpos;
	int ypos;
} ;

void generate(struct Cell[][16]);
void plant_bomb(struct Cell[][16]);
void find_count(struct Cell[][16]);
void display(struct Cell[][16]);
int  bombcount(struct Cell[][16]);
void firstclick(struct Cell[][16], int x, int y);
void update_click(struct Cell[][16], int x, int y);
void update_flag(struct Cell[][16], int x, int y);
void flag_disp(struct Cell[][16]);
void drawflag(struct Cell[][16], int x, int y);
void drawsquare(int x, int y);
void endgame(struct Cell[][16]);
void clear_zeros(struct Cell[][16], int i, int j);
void bomb_disp(struct Cell[][16]);
int  check_win(struct Cell[][16]);
void line_disp();
void opening();
void win_disp();
int  check_loss(struct Cell[][16], int x, int y);

int main()
{
	int wd=DIM, ht=DIM;
	int x, y, b;
	gfx_open(wd, ht, "MINESWEEPER");
	char c;
	struct Cell board[16][16];

	opening();
	c=gfx_wait();
	if (c=='q')
		return 0;
	generate(board);
	display(board);
	if (c!='q')
	{
		x=gfx_xpos();
		y=gfx_ypos();
		firstclick(board, x, y);
	}

	while (c!='q')
	{
		c=gfx_wait();
		x=gfx_xpos();
		y=gfx_ypos();

		if (c==1)
		{
			update_click(board, x, y);
		}

		if (c=='f')
		{
			update_flag(board, x, y);
		}

		if(check_win(board)==1)
		{
			display(board);
			win_disp();
			c=gfx_wait();
			if (c!='q')
			{
				generate(board);
				display(board);
					if (c!='q')
					{
						x=gfx_xpos();
						y=gfx_ypos();
						firstclick(board, x, y);
					}
			}
			else
				return 0;
		}

		if(check_loss(board, x, y)==1)
		{
			c=gfx_wait();
			if (c!='q')
			{
				generate(board);
				display(board);
					if (c!='q')
					{
						x=gfx_xpos();
						y=gfx_ypos();
						firstclick(board, x, y);
					}
			}
			else
				return 0;
		}
	}
	return 0;
 }

void opening()
{
	int h=700;
	double dh=0.01;
	while (h>300)
	{
		gfx_clear();
		gfx_changefont("rk24");
		gfx_clear_color(0, 0, 0);
		gfx_color(0, 200, 255);
		gfx_text(250, h, "WELCOME TO MINESWEEPER");
		gfx_changefont("rk14");
		gfx_text(305, h+50, "Press any key to play");
		gfx_text(320, h+75, "Press 'q' to quit");
		gfx_text(340, h+175, "Instructions:");
		gfx_text(100, h+200, "Click on a square to clear it, hover over a square and press 'f' to place a flag");
		gfx_text(275, h+300, "Jamie Maher CSE20211 Final Project");
		gfx_flush();
		usleep(10000);
		h=h-dh;
	}
}

void generate(struct Cell board[16][16])
{
	int i, j;
	for (i=0; i<=15; i++)
		for (j=0; j<=15; j++)
		{
			board[i][j].show=0;
			board[i][j].flag=0;
			board[i][j].bomb=0;
			board[i][j].count=0;
			board[i][j].xpos=(DIM/16)*i;
			board[i][j].ypos=(DIM/16)*j;
		}
		plant_bomb(board);
		find_count(board);
}

void plant_bomb(struct Cell board[16][16])
{
	int i, j, r;
				srand(time(NULL));
	for (i=0; i<16; i++)
		for (j=0; j<16; j++)
		{
			r=rand()%101;
			if (r<12)
			board[i][j].bomb=1;
		}
}

int bombcount(struct Cell board[][16])
{
	int i, j, b=0;
	for (i=0; i<16; i++)
		for (j=0; j<16; j++)
			if (board[i][j].bomb==1)
				b++;
	return b;
}

void find_count(struct Cell board[16][16])
{
	int i, j, count=0;
	for (i=0; i<16; i++)
		for (j=0; j<16; j++)
		{
			if (board[i-1][j-1].bomb==1 && i>0 && j>0)
				count++;
			if (board[i-1][j].bomb==1 && i>0)
				count++;
			if (board[i-1][j+1].bomb==1 && i>0 && j<15)
				count++;
			if (board[i][j-1].bomb==1 && j>0)
				count++;
			if (board[i][j+1].bomb==1 && j<15)
				count++;
			if (board[i+1][j-1].bomb==1 && i<15 && j>0)
				count++;
			if (board[i+1][j].bomb==1 && i<15)
				count++;
			if (board[i+1][j+1].bomb==1 && i<16 && j<15)
				count++;
			board[i][j].count=count;
			count=0;
		}
}

void firstclick(struct Cell board[16][16], int x, int y)
{
	int i, j;
		for (i=0; i<16; i++)
			for (j=0; j<16; j++)
				if (x>(DIM/16)*i && x<(DIM/16)*(i+1) && y>(DIM/16)*j && y<(DIM/16)*(j+1))
					board[i][j].bomb=0;
}

void display(struct Cell board[16][16])
{
	int i, j;
	char num[2];
	for (i=0; i<16; i++)
		for (j=0; j<16; j++)
		{
			if (board[i][j].show==0)
			{
				drawsquare(board[i][j].xpos, board[i][j].ypos);
			}
			else
			{
				gfx_color(190, 190, 190);
				gfx_fill_rectangle(board[i][j].xpos, board[i][j].ypos, (DIM/16), (DIM/16));

				if (board[i][j].count!=0 && board[i][j].bomb!=1)
				{
					gfx_color(0, 0, 255);
					if (board[i][j].count==2)
						gfx_color(0, 176, 26);
					if (board[i][j].count==3)
						gfx_color(255, 0, 0);
					if (board[i][j].count==4)
						gfx_color(0, 22, 163);
					if (board[i][j].count==5)
						gfx_color(140, 35, 0);
					gfx_changefont("rk24");
					snprintf(num, sizeof(num), "%d", board[i][j].count);
					gfx_text(board[i][j].xpos+20, board[i][j].ypos+30, num);
				}
			}
			flag_disp(board);
			line_disp();
			bomb_disp(board);
		}
}

void bomb_disp(struct Cell board[16][16])
{
	int i, j;
	for (i=0; i<16; i++)
		for (j=0; j<16; j++)
		{
			if (board[i][j].bomb==1 && board[i][j].show==1)
			{
				gfx_color(255, 0, 0);
				gfx_fill_arc(board[i][j].xpos+15, board[i][j].ypos+15, 15, 15, 0, 360);
			}
		}
}

void line_disp()
{
	int i;
	for (i=0; i<16; i++)
	{
		gfx_color(0, 0, 0);
		gfx_line((DIM/16)*i, 0, (DIM/16)*i, DIM);
		gfx_line(0, (DIM/16)*i, DIM, (DIM/16)*i);
	}
}

void update_click(struct Cell board[16][16], int x, int y)
{
	int i, j;
		for (i=0; i<16; i++)
			for (j=0; j<16; j++)
			{
				if (x>(DIM/16)*i && x<(DIM/16)*(i+1) && y>(DIM/16)*j && y<(DIM/16)*(j+1))
				{
					board[i][j].show=1;
					if (board[i][j].count==0)
					{
						clear_zeros(board, i, j);
					}
				}
			}
	display(board);
}

void update_flag(struct Cell board[16][16], int x, int y)
{
	int i, j;
	for (i=0; i<16; i++)
		for (j=0; j<16; j++)
		{
			if (x>(DIM/16)*i && x<(DIM/16)*(i+1) && y>(DIM/16)*j && y<(DIM/16)*(j+1))
			{
				if (board[i][j].flag==1)
					board[i][j].flag=0;
				else
					board[i][j].flag=1;
			}	
		}
	display(board);
}

void flag_disp(struct Cell board[16][16])
{
	int i, j;
	for (i=0; i<16; i++)
		for (j=0; j<16; j++)
		{
			if (board[i][j].flag==1)
			{
				drawflag(board, board[i][j].xpos+20, board[i][j].ypos+20);
			}
		}
}

void drawflag(struct Cell board[16][16], int x, int y)
{
	gfx_color(255, 102, 0);
	gfx_line(x, y, x, y+15);
	gfx_fill_rectangle(x, y, 7, 5);
}

void drawsquare(int x, int y)
{
	int dim=(DIM/16);
	int off=6;

	XPoint edge1[]={{x,y},{x+dim, y},{x+dim-off,y+off},{x+off,y+off},{x+off,y+dim-off},{x,y+dim},{x,y}};
	XPoint edge2[]={{x+dim,y},{x+dim,y+dim},{x,y+dim},{x+off,y+dim-off},{x+dim-off,y+dim-off},{x+dim-off,y+off},{x+dim,y}};
	XPoint square[]={{x+off,y+off},{x+dim-off,y+off},{x+dim-off,y+dim-off},{x+off,y+dim-off},{x+off,y+off}};

	gfx_color(255, 255, 255);
	gfx_fill_polygon(edge1, sizeof(edge1)/sizeof(XPoint));

	gfx_color(125, 125, 125);
	gfx_fill_polygon(edge2, sizeof(edge2)/sizeof(XPoint));

	gfx_color(200, 200, 200);
	gfx_fill_polygon(square, sizeof(square)/sizeof(XPoint));

}

void clear_zeros(struct Cell board[16][16], int i, int j)
{
	int k;
	if (board[i][j].count!=0)
		return;

	for (k=0; k<10; k++)
		for (i=0; i<16; i++)
			for (j=0; j<16; j++)
				if (board[i][j].show==1 && board[i][j].count==0 && board[i][j].flag!=1)
				{
					if (i>0 && j>0)
						board[i-1][j-1].show=1;
					if (i>0)
						board[i-1][j].show=1;
					if (i>0 && j<15)
						board[i-1][j+1].show=1;
					if (j>0)
						board[i][j-1].show=1;
					if (j<15)
						board[i][j+1].show=1;
					if (i<15 && j>0)
						board[i+1][j-1].show=1;
					if (i<15)
						board[i+1][j].show=1;
					if (i<15 && j<15)
						board[i+1][j+1].show=1;
				}
}

int check_win(struct Cell board[16][16])
{
	int i, j, b, count=0;
	b=bombcount(board);
	for (i=0; i<16; i++)
		for (j=0; j<16; j++)
			if (board[i][j].show==0)
				count++;
			if (count==b)
				return 1;
			else 
				return 0;
}

void endgame(struct Cell board[16][16])
{
	int i, j;
	for (i=0; i<16; i++)
	{
		for (j=0; j<16; j++)
		{
			board[i][j].show=1;
		}
	}
	display(board);
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(226, 300, 300, 80);
	gfx_color(255, 0, 0);
	gfx_changefont("rk24");
	gfx_text(330, 350, "YOU LOST");
}

void win_disp()
{
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(226, 300, 300, 80);
	gfx_color(255, 255, 0);
	gfx_changefont("rk24");
	gfx_text(330, 350, "YOU WIN!");
}

int check_loss(struct Cell board[16][16], int x, int y)
{
		int i, j;
		for (i=0; i<16; i++)
			for (j=0; j<16; j++)
				if (x>(DIM/16)*i && x<(DIM/16)*(i+1) && y>(DIM/16)*j && y<(DIM/16)*(j+1))
					if (board[i][j].bomb==1 && board[i][j].show==1)
					{
						endgame(board);
						return 1;
					}
					else
						return 0;
}
