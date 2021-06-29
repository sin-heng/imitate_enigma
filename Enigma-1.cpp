/**********************************************************************************************
Project name: Encrypting machine
Date: 2021/6/29 
Programmer: 黃新恒, Sin-heng Huang
Description:
參考二戰時德軍的密碼機而寫成的程式，透過經由時間種子製造的三個模擬齒輪加密，主要核心便是時間。
使用限制:
1.限英文字母(符號跟空白無法處理)
2.輸入可大小寫，但只會輸出大寫
*********************************************************************************************/
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<cctype>
#include<windows.h>
using namespace std;
char select_function();//由輸入'E','e','D'或是'd'決定執行功能
class enigma
{
	private:
		static const int array2 = 3;//齒輪數目 
		static const int array1 = 26;//英文字母數
		string article;//儲存輸入的文章
		time_t time_point;//儲存使用者自行輸入的時間點
		char personal_ascii[array2][array1];//儲存亂數表
	public:
		//加密部分/*************************************************************/
		void input_encrypted();//輸入想要加密的文章 
		void encrypt();//加密 
		//解密部分/*************************************************************/
		void input_decoded();//輸入解密資訊 
		void decode();//解密 
		//共用部分/*************************************************************/
		void produce_random_table(char func);//製造亂數表，func是用以判別呼叫此函數的用途
		void display(); 
};
int main()
{
	enigma encrypted, decoded;
	char answer_repeat = 'y';
	do
	{
		switch (select_function())//根據輸入選擇跑到不同case 
		{
		case 'e'://加密
			encrypted.input_encrypted();
			encrypted.produce_random_table('e');
			encrypted.encrypt();
			encrypted.display();
			break;
		case 'd'://解密
			decoded.input_decoded();
			decoded.produce_random_table('d');
			decoded.decode();
			decoded.display();
			break;
		default:
			cout << "\nWrong answer!!";
			select_function();//重新詢問需要功能	
		}
	LABEL1:
		cout << "\nWant to operate again?(y/n)";//是否再執行一次 
		cin >> answer_repeat;
		answer_repeat = static_cast<char>(tolower(answer_repeat));//全部轉成小寫 
		if (answer_repeat == 'n')//為'n'時結束程式 
			return 0;
		else if (answer_repeat != 'y')//為'y'時再執行一次do_while 
		{
			cout << "\nWrong answer!!";
			goto LABEL1;//重新詢問再次執行與否 
		}
	} while (answer_repeat == 'y');

	return 0;
}
char select_function()//由輸入'E','e','D'或是'd'決定執行功能  
{
	char answer_function;//儲存選取的功能
	cout << "\nWant to encrypted('e') or decoded('d')?";
	cin >> answer_function;
	answer_function = static_cast<char>(tolower(answer_function));//輸入全轉成小寫 
	return answer_function;//回傳輸入值，將選擇設置於main() 
}
void enigma::input_encrypted()//輸入想要加密的文章 
{
	cout << "\nPlease input your article:";
	cin.ignore(100,'\n');//將先前輸入的訊息清除 
	getline(cin,article);

	for (int n = 0; n < article.length(); n++)
	{
		article[n]=static_cast<char>(toupper(article[n]));//將文章中小寫的部分轉成大寫
	}
}
void enigma::encrypt()//加密 
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
void enigma::input_decoded()//輸入解密資訊 
{
	cout << "\nPlease input your encrypted code:";
	cin.ignore(100,'\n');
	getline(cin,article);
	cout << "\nPlease input your time_point:";
	cin >> time_point;
}
void enigma::decode()//解密 
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
void enigma::produce_random_table(char func)//製造亂數表，func是用以判別呼叫此函數的用途
{
	int c;
	bool repeat;
	if (func == 'e')//如果是加密，便用當下的時間做為種子
	{
		srand(time(NULL));
		cout <<"\nTime point is: "<< time(NULL)<<endl;//輸出製作亂數表的時間點
	}
	else //解密便用使用者輸入的時間點做為種子
		srand(time_point);
	for (int a = 0; a < array2; a++)//齒輪 
	{
		for (int b = 0; b < array1; b++)//字母 
		{
			do
			{
				repeat = false;
				personal_ascii[a][b] = static_cast<char>(rand()%(90 - 65 + 1) + 65);//亂數表隨機複製標準序列表中的字母 
				for (c = 0; c < b; c++)//確認有無重複 
				{
					if (personal_ascii[a][b] == personal_ascii[a][c])//新的一格跟過去的格子做比較 
						repeat = true;
				}
			} while (repeat==true);//如果有重複的字母在同一齒輪，便再次執行 
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

