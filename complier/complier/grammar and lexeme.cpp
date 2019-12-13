#include "grammar and lexeme.h"
#pragma warning(disable:4996)
using namespace std;

int m = 0, n = 0, kk = 0, xx = 0, yy = 0;
struct WordString;
string sym;
SymList symlist[MAX];
Four four[MAX];

/*
�﷨
<����>                  P ��{DS}�ռ�
<�������>              D ��int ID ;| D int ID;
						S��if (B) then S else S  | while (B) do S | { L } �ռ�| ID=E
<�������>              L��SL��
						L�� ��; L | e
<�������ʽ>            B��T��T
						T��F �� F
						F��ID relop ID | ID
						E��T + T | T -T
						T��F * F |T / F 
<�������ʽ>            F�� (E) | NUM | ID

			FIRST                                            FOLLOW
P			{												#
D			int												if while { ID
S			if while { ID									}; ldefollow
L			if while { ID									}
L��			; e												}
B			ID												)
T��			ID												|| )
F��			ID												|| ) &&
E			( NUM ID										}; ldefollow )
T			( NUM ID										}; ldefollow ) + -
F			( NUM ID										}; ldefollow ) + - * /
*/
string  newtemp()
{
	string one;
	char* p;
	char m[8];
	p = (char *)malloc(8);
	kk++;
	_itoa_s(kk, m, 10);
	strcpy(p + 1, m);
	p[0] = 't';
	one = p;
	return(one);
}
string  newlabel()
{
	string two;
	char* qq;
	char s[8];
	qq = (char *)malloc(8);
	yy++;
	_itoa_s(yy, s, 10);
	strcpy(qq + 5, s);
	qq[0] = 'L';
	qq[1] = 'a';
	qq[2] = 'b';
	qq[3] = 'l';
	qq[4] = 'e';
	two = qq;
	return two;
}
string getsym()
{
	string symm = words[m].left;
	//string symval =words[m].right;
	m++;
	return symm;

}
void emit(string OP, string Arg1, string Arg2, string Result)
{
	four[xx].fir = OP;
	four[xx].sec = Arg1;
	four[xx].thi = Arg2;
	four[xx].fou = Result;
	printf("\t(%s,%s,%s,%s)\n", OP.c_str(), Arg1.c_str(), Arg2.c_str(), Result.c_str());
	FILE *fpWrite = fopen("outLexeme.txt", "a+");
	fprintf(fpWrite, "\t(%s,%s,%s,%s)\n", OP.c_str(), Arg1.c_str(), Arg2.c_str(), Result.c_str());
	fclose(fpWrite);
	xx++;
}
string  lookup(string x) {
	for (int i = 0; symlist[i].name != ""; i++)
	{
		if (symlist[i].name == x)
			return symlist[i].address;
	}
	return "";
}
/*int location(string search_list) {
	int j = 0;
	for (int i = 0; symlist[i].name != ""; i++)
	{
		if (search_list == symlist[i].name)
			return j;
		else j++;
	}
	return -1;

}
void RESULT()
{
	for (int i = 0; symlist[i].name != ""; i++)
	{
		printf("\tname=%s   value=%d   address=%s\n", symlist[i].name.c_str(), symlist[i].value, symlist[i].address.c_str());
	}
}*/
void P()//P ��{DS}   //{}���ս��
{
	printf("BEGIN��\n");
	if (sym == "{")
	{
		sym = getsym();
		D();
		S();
		if (sym == "}")
			sym = getsym();
		else
		{
			printf("ERROR:��Ҫ������ĩβȱ }");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
	}
	else
	{
		printf("ERROR:��Ҫ�����忪ͷȱ{\n");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
}
void D()//D ��int ID ;{int ID;}
{
	if (sym == "int")
	{
		sym = getsym();
		if (sym == "ID")
		{
			if (lookup(words[m - 1].right) == "")
			{
				symlist[n].type = "int";
				symlist[n].name = words[m - 1].right;
				symlist[n].address = newtemp();
				printf("������\t<%s,%s>\n", symlist[n].type.c_str(), symlist[n].name.c_str());
				emit("place", symlist[n].address, "_", symlist[n].name);
				n++;
				sym = getsym();
				if (sym == ";")
				{
					sym = getsym();
				}
				else
				{
					printf("ERROR:�������ĩβȱ ;\n");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}

			}
			else
			{
				printf("\nERROR:��ʶ��%s�ظ�����\n", words[m - 1].right.c_str());
				printf("\n*************δ�ɹ�ͨ���������������***********\n");
				system("pause");
				exit(0);
			}
		}
		else
		{
			printf("ERROR:�������ȱ�ٱ�ʶ��\n");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
	}
	else
	{
		printf("ERROR:�������ȱ int ����˵��\n");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
	while (sym == "int")
	{
		sym = getsym();
		if (sym == "ID")
		{
			if (lookup(words[m - 1].right) == "")
			{
				symlist[n].type = "int";
				symlist[n].name = words[m - 1].right;
				symlist[n].address = newtemp();
				printf("������\t<%s,%s>\n", symlist[n].type.c_str(), symlist[n].name.c_str());
				emit("place", symlist[n].address, "_", symlist[n].name);
				n++;
				sym = getsym();
				if (sym == ";")
				{
					sym = getsym();
				}
				else
				{
					printf("ERROR:�������ĩβȱ ;");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}

			}
			else
			{
				printf("\nERROR:��ʶ��%s�ظ�����\n", words[m - 1].right.c_str());
				printf("\n*************δ�ɹ�ͨ���������������***********\n");
				system("pause");
				exit(0);
			}
		}
		else
		{
			printf("ERROR:�������ȱ�ٱ�ʶ��");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
	}
}
string  S()//S��if (B) then S [else S ] | while (B) do S | { L } //�ռ�| ID=E
{
	string sp, ssp1, ssp2;

	if (sym == "if")
	{
		ssp1 = newlabel();
		ssp2 = newlabel();
		sym = getsym();
		if (sym == "(")
		{
			sym = getsym();
			sp = B();

			emit("JZ", sp, "_", ssp1);

			if (sym != ")")
			{
				printf("ERROR:�ж����ĩβȱ�� )");
				printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
				system("pause");
				exit(0);

			}
			else
			{
				sym = getsym();
				if (sym == "then")
				{
					sym = getsym();
					sp = S();

					emit("JP", "_", "_", ssp2);

					printf("%s:\n", ssp1.c_str());
					FILE *fpWrite = fopen("outLexeme.txt", "a+");
					fprintf(fpWrite, "%s:\n", ssp1.c_str());
					fclose(fpWrite);
				}
				else
				{
					printf("ERROR:if���ȱ�� then");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}
			}
		}
		else
		{
			printf("ERROR:if����жϲ���ȱ�٣�");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
		if (sym == "else")
		{
			sym = getsym();
			sp = S();
		}
		printf("%s:\n", ssp2.c_str());
		FILE *fpWrite = fopen("outLexeme.txt", "a+");
		fprintf(fpWrite, "%s:\n", ssp2.c_str());
		fclose(fpWrite);

	}
	else if (sym == "while")
	{
		ssp1 = newlabel();
		ssp2 = newlabel();
		printf("%s:\n", ssp1.c_str());
		FILE *fpWrite = fopen("outLexeme.txt", "a+");
		fprintf(fpWrite, "%s:\n", ssp1.c_str());
		fclose(fpWrite);
		sym = getsym();
		if (sym == "(")
		{
			sym = getsym();
			sp = B();

			emit("JZ", sp, "_", ssp2);

			if (sym != ")")
			{
				printf("ERROR:ѭ������жϲ���ȱ )");
				printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
				system("pause");
				exit(0);
			}
			else
			{
				sym = getsym();
				if (sym == "do")
				{
					sym = getsym();
					sp = S();

					emit("JP", "_", "_", ssp1);

				}
				else
				{
					printf("ERROR:ѭ�����ȱ��do");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}
			}
		}
		else
		{
			printf("ERROR:ѭ������жϲ���ȱ(");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}

		printf("%s:\n", ssp2.c_str());
		fpWrite = fopen("outLexeme.txt", "a+");
		fprintf(fpWrite, "%s:\n", ssp1.c_str());
		fclose(fpWrite);
	}
	else if (sym == "{")
	{
		sym = getsym();
		sp = L();
		if (sym != "}")
		{
			printf("ERROR:��Ƕ������ȱ�� }");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
		else sym = getsym();
	}
	else if (sym == "ID")
	{
		string k = lookup(words[m - 1].right);
		if (k == "")
		{
			printf("ERROR:����δ����");
			printf("\n*************δ�ɹ�ͨ���������������***********\n");
			system("pause");
			exit(0);
		}
		string p = words[m - 1].right;
		sym = getsym();
		if (sym != "=")
		{
			printf("ERROR:��ֵ���ȱ��=");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
		else
		{
			sym = getsym();
			string x = E();
			/*char ret = x.at(0);
			if ((ret >= 'a'&&ret <= 'z') || (ret >= 'A'&&ret <= 'Z'))
				symlist[location(p)].value = atoi(x.c_str());*/
			sp = k;
			emit("=", x, "_", p);


		}
	}
	else
	{
		printf("ERROR:�����忪ͷ������ȱ if�� while�� { �� ID");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
	return sp;
}
string B()//B��TT {||TT}
{
	string bp;
	if (sym == "ID")
		bp = TT();
	else
	{
		printf("ERROR:�������ʽ��ȱID");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
	while (sym == "||")
	{
		sym = getsym();
		if (sym == "ID")
			bp = TT();
		else
		{
			printf("ERROR:||��Ĳ������ʽ��ȱID");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
	}
	return bp;
}
string  TT()//TT ��FF {&& FF }
{
	string tp;
	if (sym == "ID")
		tp = FF();
	else {
		printf("ERROR:������������ȱID");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
	while (sym == "&&")
	{
		sym = getsym();
		if (sym == "ID")
			tp = FF();
		else {
			printf("ERROR:������������ȱID");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
	}
	return tp;
}
string  FF()//FF ��ID relop ID| ID
{
	string ffp;
	if (sym == "ID")
	{
		sym = getsym();
		if (sym == "relop")
		{
			if (words[m - 1].right == "<")
			{
				sym = getsym();
				if (sym == "ID")
				{
					ffp = newtemp();
					emit("j<", words[m - 3].right, words[m - 1].right, ffp);
					sym = getsym();
				}
				else
				{
					printf("ERROR:�������ʽ relop ��ȱID");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}
			}
			else if (words[m - 1].right == ">")
			{
				sym = getsym();
				if (sym == "ID")
				{
					ffp = newtemp();
					emit("j>", words[m - 3].right, words[m - 1].right, ffp);
					sym = getsym();

				}
				else
				{
					printf("ERROR:�������ʽ relop��ȱID");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}
			}
			else if (words[m - 1].right == ">=")
			{
				sym = getsym();
				if (sym == "ID")
				{
					ffp = newtemp();
					emit("j>=", words[m - 3].right, words[m - 1].right, ffp);
					sym = getsym();

				}
				else
				{
					printf("ERROR:�������ʽ relop��ȱID");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}
			}
			else if (words[m - 1].right == "<=")
			{
				sym = getsym();
				if (sym == "ID")
				{
					ffp = newtemp();
					emit("j<=", words[m - 3].right, words[m - 1].right, ffp);
					sym = getsym();

				}
				else
				{
					printf("ERROR:�������ʽ relop��ȱID");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}
			}
			else if (words[m - 1].right == "==")
			{
				sym = getsym();
				if (sym == "ID")
				{
					ffp = newtemp();
					emit("j==", words[m - 3].right, words[m - 1].right, ffp);
					sym = getsym();

				}
				else
				{
					printf("ERROR:�������ʽrelop��ȱID");
					printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
					system("pause");
					exit(0);
				}
			}

		}
		else
		{
			string k = lookup(words[m - 1].right);
			if (k != "")
			{
				ffp = k;
				sym = getsym();
			}
			else {
				printf("ERROR:����δ����");
				printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
				system("pause");
				exit(0);
			}

		}

	}
	else
	{
		printf("�������ʽ ȱID");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
	return ffp;
}
string E()//E��T{+T| -T}
{
	string ep;
	if (sym == "(" || sym == "NUM" || sym == "ID")
		ep = T();
	else
	{
		printf("ERROR:�������ʽȱ(,NUM,��ID");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
	while (sym == "+" || sym == "-")
	{
		string ssym = sym;
		sym = getsym();
		if (sym == "(" || sym == "NUM" || sym == "ID")
		{
			string x = T();
			ep = newtemp();
			emit(ssym, ep, "_", x);
		}
		else
		{
			printf("ERROR:�������ʽȱ(,NUM,��ID");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
	}
	return ep;
}

string  T()//T��F{* F | /F }
{
	string tp;
	if (sym == "(" || sym == "NUM" || sym == "ID")
		tp = F();
	else
	{
		printf("ERROR:�������ʽȱ(,NUM,��ID");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
	while (sym == "*" || sym == "/")
	{
		string ssym = sym;
		sym = getsym();
		if (sym == "(" || sym == "NUM" || sym == "ID")
		{
			string x = F();
			tp = newtemp();
			emit(ssym, tp, "_", x);
		}
		else
		{
			printf("ERROR:�������ʽȱ(,NUM,��ID");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}
	}
	return tp;
}

string  F()//F�� (E) | NUM | ID
{
	string fp;
	if (sym == "(")
	{
		sym = getsym();
		fp = E();
	}
	else if (sym == "NUM")//?
	{
		fp = words[m - 1].right;

		sym = getsym();
	}
	else if (sym == "ID")
	{
		string k = lookup(words[m - 1].right);
		if (k != "")
		{
			fp = k;
			sym = getsym();
		}
		else {
			printf("ERROR:����δ����");
			printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
			system("pause");
			exit(0);
		}

	}
	else
	{
		printf("ERROR:�������ʽȱ������ȱNUM����ID");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
		exit(0);
	}
	return fp;
}
string L() {//L��S LL
	string lp;
	if (sym == "if" || "while" || "{" || "ID")
	{
		S();
		lp = LL();
		return lp;
	}
	else
	{
		printf("ERROR:�Ƿ�����");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");
	}
	return "";
}

string  LL() {//LL ��; L | e
	string llp;
	if (sym == ";")
	{
		sym = getsym();
		llp = L();
		return llp;
	}
	else if (sym != "#"&&sym != "}")
	{
		printf("ERROR:�Ƿ�����");
		printf("\n*************δ�ɹ�ͨ���﷨����������***********\n");
		system("pause");

	}
	return "";
}
void yufa() {
	sym = getsym(); //��ȡ��ǰ���봮�ĵ�һ������
	P();         //���ķ���ʼ���Ŷ�Ӧ���ӳ���ʼʶ��
	if (sym == "#")
	{
		printf("END��");
		printf("\n*************�ѳɹ�ͨ���������������***********\n");
		printf("\n*************�ѳɹ�ͨ���﷨����������***********\n");
		/*printf("\n****************���º�ķ��ű�Ϊ��**************\n\n");
		RESULT();
		printf("\n*************������������������������***********\n");*/
		system("pause");
		exit(0);
	} //��#���ǳ�������ı�־
	else
	{
		printf("error in main");
		exit(0);
	}


}