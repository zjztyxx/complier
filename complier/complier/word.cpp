#include<iostream>
#include<fstream>
#define MAX 10000

using namespace std;


struct WordString {
	string Word;
	int Category;//�ؼ���1����ʶ��2������3�������4���ָ���5��error6
	string left;//
	string right;
};

WordString words[MAX];//����һ�����ʷ��Ŵ�
string text;//�����ı�����text
string word;//�ָ��������word��ʾ
int length;//�ַ�����
int k;//�ܵ��ʸ���

const char *key[] = {
		"int",//0
		"char",//1
		"if",//2
		"then",//3
		"else",//4
		"while",//5
		"do"//6
};


void scan()
{
	int i, j;
	k = 0;
	word = "";
	for (i = 0; i <= length - 1; i++)
	{
		if (word != "")
		{
			if ((word[0] >= 'A'&&word[0] <= 'Z') || (word[0] >= 'a'&&word[0] <= 'z'))//����ĸΪ��ĸ
			{
				if ((text[i] >= 'A'&&text[i] <= 'Z') || (text[i] >= 'a'&&text[i] <= 'z') || (text[i] >= '0'&&text[i] <= '9'))
					word += text[i];
				else {
					words[k].Word = word;
					for (j = 0; j < 7; j++)
					{
						if (words[k].Word == key[j])
						{
							words[k].Category = 1;
							words[k].left = word;
							words[k].right = word;

							break;
						}
						else if (j == 7 - 1)
							words[k].Category = 2;
						words[k].left = "ID";
						words[k].right = word;
					}
					k++;
					word = "";
					i--;
				}
			}

			else if (word[0] == '(' || word[0] == ')' || word[0] == '{' || word[0] == '}' || word[0] == ';')//�ָ��� category=5
			{
				words[k].Word = word;
				words[k].Category = 5;
				words[k].left = word;
				words[k].right = word;
				k++;
				word = "";
				i--;
			}
			else if (word[0] == '+' || word[0] == '-' || word[0] == '*'
				|| word[0] == '/' || word[0] == '=')//���ַ��������
			{
				words[k].Word = word;
				words[k].Category = 4;//��ʾ�����
				words[k].left = word;
				words[k].right = word;
				k++;
				word = "";
				i--;
			}
			else if (word[0] == '#')//���ַ��ǽ�����
			{
				words[k].Word = word;
				words[k].Category = 7;//��ʾ������
				words[k].left = word;
				words[k].right = word;
				k++;
				word = "";
				i--;
			}
			else if (word[0] == '&&' || word[0] == '||' || word[0] == '&'
				|| word[0] == '|')//���ַ��������
			{
				if (text[i] == '&' || text[i] == '|')
				{
					word += text[i];
					words[k].Word = word;
					words[k].Category = 4;//��ʾ����� category=4
					words[k].left = word;
					words[k].right = "---";
					k++;
					word = "";
				}
				else
				{
					words[k].Word = word;
					words[k].Category = 4;//��ʾ�����
					words[k].left = word;
					words[k].right = "---";
					k++;
					word = "";
					i--;
				}
			}

			else if (word[0] == '>' || word[0] == '<' || word[0] == '<='
				|| word[0] == '>=' || word[0] == '==')//���ַ��������
			{
				if (text[i] == '=')
				{
					word += text[i];
					words[k].Word = word;
					words[k].Category = 4;//��ʾ����� category=4
					words[k].left = "relop";
					words[k].right = word;
					k++;
					word = "";
				}
				else
				{
					words[k].Word = word;
					words[k].Category = 4;//��ʾ�����
					words[k].left = "relop";
					words[k].right = word;
					k++;
					word = "";
					i--;
				}
			}
			else if (word[0] >= '0'&&word[0] <= '9')//���ַ�������
			{
				if (text[i] >= '0'&&text[i] <= '9')

					word += text[i];

				else if ((text[i] >= 'A'&&text[i] <= 'Z') || (text[i] >= 'a'&&text[i] <= 'z'))
				{
					word += text[i];
					words[k].Category = 6;//��ʾ������ʶ�������ֿ�ͷ
					words[k].left = "ID";
					words[k].right = "ERROR";
				}
				else
				{
					words[k].Word = word;
					if (words[k].Category != 6)
						words[k].Category = 3;//��ʾ����
					words[k].left = "NUM";
					words[k].right = word;
					k++;
					word = "";
					i--;
				}

			}
		}


		else
		{
			if (text[i] != 10 && text[i] != 32 && text[i] != 9)//����tab �ո� �س���������ı�д�뵥�ʷ��Ŵ�

				word += text[i];

		}

	}
}


void judge()
{
	int i;
	int j = 0, k = 0;
	for (i = 0; i < length; i++)
	{
		if (text[i] != 10 && text[i] != 32 && text[i] != 9)
		{

			if (text[i] == '(')
				j++;
			else if (text[i] == ')')
				j--;
			if (text[i] == '{')
				k++;
			else if (text[i] == '}')
				k--;

		}
	}
	//cout << "J= " << j << endl;
	//cout << "K= " << k << endl;
	if (j != 0)
		cout << "���Ų�ƥ��" << endl;
	if (k != 0)
		cout << "�����Ų�ƥ��" << endl;
}


void cifa() {

	ifstream fp("Text1.txt");//���ļ�
	if (fp.fail())
	{
		printf("Can't open the file! \n");
		exit(0);
	}
	int i = 0;
	cout << "********************�ı���ʾ**********************" << endl;
	while (!fp.eof())
	{
		text += fp.get();
		cout << text[i];
		i++;
	}
	length = i;//text���һ���ַ��ǿ��ַ�

	fp.close();
	fstream outWord("outWord.txt", fstream::out);
	

	scan();
	printf("*******************�ʷ��������Ϊ***************\n");
	for (i = 0; i < k; i++)
	{
		if (words[i].Category == 6)
		{
			printf("%s ERROR\n", words[i].Word.c_str());
			outWord << words[i].Word.c_str();
		}
		else
		{
			printf("\t\t(%s,\t%s)\n", words[i].left.c_str(), words[i].right.c_str());
			outWord << "(" << words[i].left.c_str() << "   " << words[i].right.c_str() << ")" << endl;
		}
	}
	judge();
	printf("********************�ʷ���������****************\n");
	//system("pause");
	outWord.close();
	//	getchar();

}



