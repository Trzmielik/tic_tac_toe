#include <iostream>
#include <cstdlib>

bool check_victory(char plane[],char checked)
{
	if(
	((plane[0]==checked)&&(plane[1]==checked)&&(plane[2]==checked))||
	((plane[3]==checked)&&(plane[4]==checked)&&(plane[5]==checked))||
	((plane[6]==checked)&&(plane[7]==checked)&&(plane[8]==checked))||
	((plane[0]==checked)&&(plane[3]==checked)&&(plane[6]==checked))||
	((plane[1]==checked)&&(plane[4]==checked)&&(plane[7]==checked))||
	((plane[2]==checked)&&(plane[5]==checked)&&(plane[8]==checked))||
	((plane[0]==checked)&&(plane[4]==checked)&&(plane[8]==checked))||
	((plane[2]==checked)&&(plane[4]==checked)&&(plane[6]==checked))
			) return true;
	return false;
		
}
bool check_draw(char plane[])
{
	for(int i =0;i<9;i++)
	{
		if(plane[i]==' ') return false;
	}
	return true;
}

int minimax(char plane[],int depth,bool maximazing_player,bool is_ai_x)
{
	int x;
	char temp[9];
	for(int i = 0;i<9;i++)temp[i]=plane[i];
	if(check_victory(plane,'X')) 
	{
		if(is_ai_x) return 10+depth;
		else return -10-depth;
	}
	else if(check_victory(plane,'O'))
	{
		if(is_ai_x) return -10-depth;
		else return 10+depth;

	}
	else if(check_draw(plane))return 0;
	else if(depth==0)return 0;

	if(maximazing_player)
	{
		char pos=0;
		char eval=-20; //Bo niebedzie nigdy mniej
		for(int i=0;i<8;i++)
		{
			if(temp[i]==' ')
			{	
				temp[i]='X';
				x = minimax(temp,depth-1,false,is_ai_x);
				if(x>=eval)
				{
					pos=i;
					eval=x;
				}
			}
		}
		return eval;
	}
	else
	{
		char pos=0;
		char eval=-20;
		for(int i=0;i<8;i++)
		{
			if(temp[i]==' ')
			{
				temp[i]='X';
				x = minimax(temp,depth-1,false,is_ai_x);
				if(x<=eval)
				{	
				pos=i;
				eval=x;
				}
			}
		}
		return eval;
	}
}
char find_best_move(char plane[9])
{
	int best_val =-1000;
	char move=-1;

	for(int i = 0;i<9;i++)
	{
		if(plane[i]==' ')
		{
		plane[i]='O';
		int move_val=minimax(plane,9,false,false);
		plane[i]=' ';
		if (move_val > best_val)
		{
			move=i;
			best_val=move_val;
		}
		}
	}
	return move;

}
void print_plane(char plane[])
{
	std::cout << "   || 0 || 1 || 2" << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "0  || " << plane[0] << " || " << plane[1] << " || " << plane[2] << " || " << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "1  || " << plane[3] << " || " << plane[4] << " || " << plane[5] << " || " << std::endl;
	std::cout << "--------------------" << std::endl;
	std::cout << "2  || " << plane[6] << " || " << plane[7] << " || " << plane[8] << " || " << std::endl;
}


int main()
{
	srand(time(NULL));
	bool x_turn = false;
	int x;
	char plane[9];
	for(int i=0;i<9;i++)plane[i]=' ';
	while(true)
	{
		if(check_victory(plane,'X'))
		{
			system("clear");
			print_plane(plane);
			std::cout<<"Krzyzyki wygraly!"<<std::endl;
			break;
		}
		else if(check_victory(plane,'O'))
		{
			system("clear");
			print_plane(plane);
			std::cout<<"Kolka wygraly!"<<std::endl;
			break;
		}
		else if(check_draw(plane))
		{
			system("clear");
			print_plane(plane);
			std::cout<<"Remis!"<<std::endl;
			break;
		}
		do
		{
			system("clear");
			print_plane(plane);
			if(x_turn)
			{
				x=find_best_move(plane);
			}
			else
			{
				std::cout<<"Ruch kółka."<<std::endl;
				std::cout << "Podaj numer komorki."<<std::endl;
				std::cin >> x;
			}
		}
		while(plane[x]!=' '||x<0||x>8);
		if(x_turn)plane[x]='X';
		else plane[x]='O';
		x_turn = !x_turn;
	}
}
