//��Ӫ�[�K�k�ĤC��
/********************************* 
�w����̲ת����A�G�}�l�i��{���u��
*********************************/ 
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
#include<stdlib.h>
#include<ctime>
#include<cstring>
#include<cctype>
using std::tolower;
using namespace std;
const int MAX=10000;
char print_table[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
class enigma
{
	private:
		//�ŧi
		char answer_function;
		char article[MAX]; 
		char personal_ascii[2][26];
		char choice[MAX];//������ܲĴX���L 
		int n,j,k,b;//���n���ܷ|�X���D 
		time_t lasttime;
		
		char code[MAX];
	
	public:
		char choice_function()
		{
			//��ܥ\��
			cout << "Want to encrypted('e') or decoded('d')?";
			cin >> answer_function ;
			answer_function = static_cast<char>(tolower(answer_function));
			return answer_function;
		}
		void input_encrypted()
		{
			//��J�[�K���e
			cout << "Please input your article:";
			cin.ignore(100,'\n');
			cin.getline(article,MAX);
		}
		void produce_encrypted_ascii()
		{
			//���͹�Ӫ� (������) 
			srand((unsigned)time(NULL));
			cout <<"time for ascii is : "<< time(NULL)<<endl;
			for(int z=0;z<2;z++)
			{
				for(int n=0;n<26;n++)
				{
					do
					{
						personal_ascii[z][n]=print_table[rand()%26];
						for(j=0,k=0;j<n;j++)
						{
							if(personal_ascii[z][n]==personal_ascii[z][j])
							k++;
						}
					}
					while(k>0);
				}
				
			}
		}
		void output_encrypted_ascii()
		{
			//��X��Ӫ� 
			for(int z=0;z<2;z++)
			{
				for(int n=0;n<26;n++)
				{
					cout << personal_ascii[z][n];
				}	
				cout <<endl;
			}	
			cout << "\n";
			//��X���T�ƦC�� 
			for(int n=0;n<26;n++)
			{
				cout << print_table[n];
			}
			
			cout << "\n=============================="<<endl;
		}
		void output_encrypted_article()
		{
			//produce_encrypted_ascii();
			//��X�[�K���e 
			srand(time(NULL));
			//cout << "time for choice :" <<time(NULL)<<endl;
			for(int n=0;n<strlen(article);n++)
			{
				int a=rand()%2;
				choice[n]=static_cast<char>(a+65);
				for(int j=0;j<26;j++)//����۩w�q��Ӫ���X���T�� 
				{
					if(article[n]==personal_ascii[a][j])
						cout << print_table[j];
				}
			}
			cout <<endl;
			for(int n=0;n<strlen(article);n++)
			{
				cout << choice[n];
			}
		}
		void input_decoded()
		{
			cout << "Please input your encrypted code:";
			cin.ignore(100,'\n');
			cin.getline(code,MAX);
			cout << "Please input your choice code:";
			cin.getline(choice,MAX);	
			cout << "Please input your time:"<<endl;
			cin >> lasttime;
		}
		void produce_decoded_ascii() 
		{
			srand(lasttime);
			
			for(int z=0;z<2;z++)
			{
				for(int n=0;n<26;n++)
				{
					do
					{
						personal_ascii[z][n]=print_table[rand()%26];
						for(j=0,k=0;j<n;j++)
						{
							if(personal_ascii[z][n]==personal_ascii[z][j])
							k++;
						}
					}
					while(k>0);
				}
				
			}
		}
		void output_decoded_ascii()
		{
			//��X��Ӫ� 
			for(int z=0;z<2;z++)
			{
				for(int n=0;n<26;n++)
				{
					cout << personal_ascii[z][n];
				}	
				cout <<endl;
			}	
			cout << "\n";
			//��X���T�ƦC�� 
			for(int n=0;n<26;n++)
			{
				cout << print_table[n];
			}
			
			cout << "\n=============================="<<endl;
		}
		void output_decoded_article()
		{
			for(int n=0;n<strlen(code);n++)
			{
				for(int j=0;j<26;j++)
					if(code[n]==print_table[j])
					{
						b=choice[n]-65;
						cout << personal_ascii[b][j];
					}	
			}
		}
		
};
int main()
{
	//�ŧi 
	enigma e1;
	char answer_repeat='y';
	do
	{
		switch(e1.choice_function())
		{
			case 'e':
				e1.input_encrypted();
				e1.produce_encrypted_ascii();
				e1.output_encrypted_ascii();
				e1.output_encrypted_article();
				break;
			case 'd':
				e1.input_decoded();
				e1.produce_decoded_ascii();
				e1.output_decoded_ascii();
				e1.output_decoded_article();
				break;
			default:
				cout << "Wrong answer!!";
				e1.choice_function();	
		}
		LABEL1:
			cout << "\nWant to operate again?(y/n)";
			cin >> answer_repeat;
			answer_repeat = static_cast<char>(tolower(answer_repeat));
			if(answer_repeat=='n')
				return 0;
			else if(answer_repeat!='y')
			{
				cout << "Wrong answer!!";
				goto LABEL1;
			}
	}while(answer_repeat=='y');
	
	return 0;
}
