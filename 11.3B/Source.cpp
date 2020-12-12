#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Special { KN, SA, IS, KB };
string specialStr[] = { "Комп'ютерні науки", "Системний аналіз", "Інформаційні ссистеми", "Кібербезпека" };
struct Student
{
	string prizv;
	int kurs;
	Special special;
	int physic;
	int math;
	union
	{
		int programing;
		int method;
		int pedagogy;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
int CountMark(Student* p, const int N);
double physics_and_math_five(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Special special);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
void CreateBIN(char* fname);
void PrintBIN(char* fname);
void ProcessBIN1(char* fname, char* gname);
void fWrite(fstream& f, const int i, const char x);
char fRead(fstream& f, const int i);
void fChange(fstream& f, const int i, const int j);
void SortBIN(char* fname);
void SortBIN(char* fname, char* gname);
int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];
	double proc;
	int ispecial;
	Special special;
	string prizv;
	int found;
	char filename[100];
	Create(p, N);
	cout << endl;
	Print(p, N);
	cout << endl;
	Sort(p, N);
	cout << endl;
	cout << "| Процент оцінок відмінно: " << setprecision(2) << CountMark(p, N) << "%" << endl << endl;
	cout << "| Процент студентів які отримали з фізики і математики 5:" << physics_and_math_five(p, N) << "%" << endl;
	cout << "=========================================================================" << endl;
	if (physics_and_math_five(p, N));
	else
		cout << "Студенти які не отимали 5: " << endl << endl;

	cout << " спеціальність (0 -Комп'ютерні науки, 1-Системний аналіз, 2-Інформаційні ссистеми, 3-Кібербезпека ): ";
	cin >> ispecial;
	special = (Special)ispecial;
	cin.get();
	cin.sync();
	cout << " прізвище: "; getline(cin, prizv);
	cout << endl;
	if ((found = BinSearch(p, N, prizv, special)) != -1)
		cout << "Знайдено студента в позиції " << found + 1 << endl;
	else
		cout << "Шуканого студента не знайдено" << endl << endl;
	PrintIndexSorted(p, IndexSort(p, N), N);
	cout << endl;
	char fname[100];
	cout << "enter file name 1: "; cin >> fname;
	CreateBIN(fname);
	PrintBIN(fname);
	char gname[100];
	cout << "enter file name 2: "; cin >> gname;
	ProcessBIN1(fname, gname);
	PrintBIN(gname);
	SortBIN(fname, gname);
	PrintBIN(gname);
	SortBIN(fname);
	PrintBIN(fname);
	delete[] p;
}
void Create(Student* p, const int N)
{
	int kurs, specialty;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спеціальність(0-КН, 1-ІФ, 2-МЕ, 3-ФІ, 4-ТН): ";
		cin >> specialty;
		p[i].special = (Special)specialty;
		switch (specialty)
		{
		case 0:
			cout << " програмування : "; cin >> p[i].programing;
			break;
		case 1:
			cout << " чисельння методів : "; cin >> p[i].method;
			break;
		case 2:
		case 3:
		case 4:
			cout << " педагогіка : "; cin >> p[i].pedagogy;
			break;
		default:
			cout << "Помилкове значення!" << endl;
		}
		cout << "фізика: "; cin >> p[i].physic;
		cout << "математика: "; cin >> p[i].math;
	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування |  Числовий метод | Педагогіка |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(3) << right << p[i].kurs << " "
			<< "| " << setw(22) << right << specialStr[p[i].special] << "    "
			<< "| " << setw(4) << right << p[i].physic << " "
			<< "| " << setw(6) << right << p[i].math;
		switch (p[i].special)
		{
		case 0:
			cout << "| " << setw(7) << right << p[i].programing << " |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 1:
			cout << "| " << setw(15) << " |" << setw(10) << right << p[i].method << " |" << setw(13) << "|" << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << p[i].pedagogy << " |" << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
}

int CountMark(Student* p, const int N)
{
	int k = 0;
	for (int i = 0; i < N; i++)
	{
		switch (p[i].special)
		{
		case 0:
			if (p[i].physic == 5 && p[i].math == 5 && p[i].programing == 5)
				k++;
			break;
		case 1:
			if (p[i].physic == 5 && p[i].math == 5 && p[i].method == 5)
				k++;
			break;
		case 2:
		case 3:
		case 4:
			if (p[i].physic == 5 && p[i].math == 5 && p[i].pedagogy == 5)
				k++;
			break;

		}
	}
	return 100.0 * k / N;
}
double physics_and_math_five(Student* p, const int N)
{
	int k = 0;
	for (int i = 0; i < N; i++)
		if (p[i].physic == 5 && p[i].math == 5)
			k++;
	return 100.0 * k / N;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].special > p[i1 + 1].special)
				||
				(p[i1].special == p[i1 + 1].special &&
					p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const string prizv, const Special special)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].special == special)
			return m;
		if ((p[m].special < special)
			||
			(p[m].special == special &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{
	int* I = new int[N];
	for (int i = 0; i < N; i++)
		I[i] = i;
	int i, j, value;
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].special > p[value].special) ||
				(p[I[j]].special == p[value].special &&
					p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | Рік.нар. | Посада | Тариф | Ставка |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(3) << right << p[i].kurs << " "
			<< "| " << setw(22) << right << specialStr[p[i].special] << "    "
			<< "| " << setw(4) << right << p[i].physic << " "
			<< "| " << setw(6) << right << p[i].math;
		switch (p[i].special)
		{
		case 0:
			cout << "| " << setw(7) << right << p[i].programing << " |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 1:
			cout << "| " << setw(15) << " |" << setw(10) << right << p[i].method << " |" << setw(13) << "|" << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << p[i].pedagogy << " |" << endl;
			break;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
void CreateBIN(char* fname)
{
	ofstream fout(fname, ios::binary);
	char ch;
	string s;
	do
	{
		cin.get();
		cin.sync();
		cout << "enter line: "; getline(cin, s);
		for (unsigned i = 0; i < s.length(); i++)
			fout.write((char*)&s[i], sizeof(s[i]));
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
void PrintBIN(char* fname)
{
	ifstream fin(fname, ios::binary);
	char c;
	while (fin.read((char*)&c, sizeof(c)))
	{
		cout << c << endl;
	}
	cout << endl;
}
void ProcessBIN1(char* fname, char* gname)
{
	ifstream f(fname, ios::binary);
	ofstream g(gname, ios::binary);
	char c;
	while (f.read((char*)&c, sizeof(c)))
	{
		if (c >= '0' && c <= '9')
			g.write((char*)&c, sizeof(c));
	}
}
void fWrite(fstream& f, const int i, const char x)
{
	f.seekp(i * (long)sizeof(char));
	f.write((char*)&x, sizeof(char));
}
char fRead(fstream& f, const int i)
{
	char x;
	f.seekg(i * (long)sizeof(char));
	f.read((char*)&x, sizeof(char));
	return x;
}
void fChange(fstream& f, const int i, const int j)
{
	char x = fRead(f, i);
	char y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}
void SortBIN(char* fname)
{
	fstream f(fname, ios::binary | ios::in | ios::out);
	f.seekg(0, ios::end);
	int size = f.tellg();
	f.seekg(0, ios::beg);
	for (int i0 = 1; i0 < size; i0++)
		for (int i1 = 0; i1 < size - i0; i1++)
		{
			char a = fRead(f, i1);
			char b = fRead(f, i1 + 1);
			if (a > b)
				fChange(f, i1, i1 + 1);
		}
	f.seekp(0, ios::end);
}
void SortBIN(char* fname, char* gname)
{
	ofstream g(gname, ios::binary);
	char s, mins, z = 0;
	int k;
	do
	{
		k = 0;
		ifstream f(fname, ios::binary);
		while (f.read((char*)&s, sizeof(char)))
		{
			if (s <= z)
				continue;
			mins = s;
			k++;
			break;
		}
		while (f.read((char*)&s, sizeof(char)))
		{
			if (s <= z)
				continue;
			if (s < mins)
			{
				mins = s;
				k++;
			}
		}

		z = mins;
		if (k > 0)
			g.write((char*)&z, sizeof(char));
		f.close();
	} while (k > 0);
}
