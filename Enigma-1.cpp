/**********************************************************************************************
Project name: Encrypting machine
Date: 2021/6/29 
Programmer: ���s��, Sin-heng Huang
Description:
�ѦҤG�Ԯɼw�x���K�X���Ӽg�����{���A�z�L�g�Ѯɶ��ؤl�s�y���T�Ӽ��������[�K�A�D�n�֤߫K�O�ɶ��C
�ϥέ���:
1.���^��r��(�Ÿ���ťյL�k�B�z)
2.��J�i�j�p�g�A���u�|��X�j�g
*********************************************************************************************/
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<cctype>
#include<windows.h>
using namespace std;
char select_function();//�ѿ�J'E','e','D'�άO'd'�M�w����\��
class enigma
{
	private:
		static const int array2 = 3;//�����ƥ� 
		static const int array1 = 26;//�^��r����
		string article;//�x�s��J���峹
		time_t time_point;//�x�s�ϥΪ̦ۦ��J���ɶ��I
		char personal_ascii[array2][array1];//�x�s�üƪ�
	public:
		//�[�K����/*************************************************************/
		void input_encrypted();//��J�Q�n�[�K���峹 
		void encrypt();//�[�K 
		//�ѱK����/*************************************************************/
		void input_decoded();//��J�ѱK��T 
		void decode();//�ѱK 
		//�@�γ���/*************************************************************/
		void produce_random_table(char func);//�s�y�üƪ�Afunc�O�ΥH�P�O�I�s����ƪ��γ~
		void display(); 
};
int main()
{
	enigma encrypted, decoded;
	char answer_repeat = 'y';
	do
	{
		switch (select_function())//�ھڿ�J��ܶ]�줣�Pcase 
		{
		case 'e'://�[�K
			encrypted.input_encrypted();
			encrypted.produce_random_table('e');
			encrypted.encrypt();
			encrypted.display();
			break;
		case 'd'://�ѱK
			decoded.input_decoded();
			decoded.produce_random_table('d');
			decoded.decode();
			decoded.display();
			break;
		default:
			cout << "\nWrong answer!!";
			select_function();//���s�߰ݻݭn�\��	
		}
	LABEL1:
		cout << "\nWant to operate again?(y/n)";//�O�_�A����@�� 
		cin >> answer_repeat;
		answer_repeat = static_cast<char>(tolower(answer_repeat));//�����ন�p�g 
		if (answer_repeat == 'n')//��'n'�ɵ����{�� 
			return 0;
		else if (answer_repeat != 'y')//��'y'�ɦA����@��do_while 
		{
			cout << "\nWrong answer!!";
			goto LABEL1;//���s�߰ݦA������P�_ 
		}
	} while (answer_repeat == 'y');

	return 0;
}
char select_function()//�ѿ�J'E','e','D'�άO'd'�M�w����\��  
{
	char answer_function;//�x�s������\��
	cout << "\nWant to encrypted('e') or decoded('d')?";
	cin >> answer_function;
	answer_function = static_cast<char>(tolower(answer_function));//��J���ন�p�g 
	return answer_function;//�^�ǿ�J�ȡA�N��ܳ]�m��main() 
}
void enigma::input_encrypted()//��J�Q�n�[�K���峹 
{
	cout << "\nPlease input your article:";
	cin.ignore(100,'\n');//�N���e��J���T���M�� 
	getline(cin,article);

	for (int n = 0; n < article.length(); n++)
	{
		article[n]=static_cast<char>(toupper(article[n]));//�N�峹���p�g�������ন�j�g
	}
}
void enigma::encrypt()//�[�K 
{
	for(int i=0;i<article.length();i++)
	{
		int k=i%3;
		for(int z=0;z<3;z++,k++)
		{
			k%=3;
			for(int j=0;j<array1;j++)
			{
				if(personal_ascii[k][j]==article[i])
				{
					article[i] = static_cast<char>(j+65);
					break;
				}
					
			}
		}
	}
}
void enigma::input_decoded()//��J�ѱK��T 
{
	cout << "\nPlease input your encrypted code:";
	cin.ignore(100,'\n');
	getline(cin,article);
	cout << "\nPlease input your time_point:";
	cin >> time_point;
}
void enigma::decode()//�ѱK 
{
	for(int i=0;i<article.length();i++)
	{
		int k=(i+2)%3;
		for(int z=0;z<3;z++,k--)
		{
			k%=3;
			int index=static_cast<int>(article[i])-65;
			article[i]=personal_ascii[k][index];
			if(k==0)
				k+=3;
		}
	}
}
void enigma::produce_random_table(char func)//�s�y�üƪ�Afunc�O�ΥH�P�O�I�s����ƪ��γ~
{
	int c;
	bool repeat;
	if (func == 'e')//�p�G�O�[�K�A�K�η�U���ɶ������ؤl
	{
		srand(time(NULL));
		cout <<"\nTime point is: "<< time(NULL)<<endl;//��X�s�@�üƪ��ɶ��I
	}
	else //�ѱK�K�ΨϥΪ̿�J���ɶ��I�����ؤl
		srand(time_point);
	for (int a = 0; a < array2; a++)//���� 
	{
		for (int b = 0; b < array1; b++)//�r�� 
		{
			do
			{
				repeat = false;
				personal_ascii[a][b] = static_cast<char>(rand()%(90 - 65 + 1) + 65);//�üƪ��H���ƻs�зǧǦC�����r�� 
				for (c = 0; c < b; c++)//�T�{���L���� 
				{
					if (personal_ascii[a][b] == personal_ascii[a][c])//�s���@���L�h����l����� 
						repeat = true;
				}
			} while (repeat==true);//�p�G�����ƪ��r���b�P�@�����A�K�A������ 
		}
	}
}
void enigma::display()
{
	cout << "\nYour code is: ";
	for(int i=0;i<article.length();i++)
	{
		Sleep(1000);
		cout << article[i];
	}	
}

