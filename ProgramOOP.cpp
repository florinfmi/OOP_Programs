/* matrice de numere complexe reprezentate ca tablouri bidimensionale (nu neaparat
ca matrici patratice):
* Clasa numar complex sa contina metode pentru: supraincarcarea operatorilor << si
>>; suma a doua numere complexe, implementata prin supraincarcarea
operatorului +; produsul a doua numere complexe, implementat prin
supraincarcarea operatorului *; scaderea a doua numere complexe implementata
prin supraincarcarea operatorului -; impartirea a doua numere complexe
implementata prin supraincarcarea operatorului /; aruncarea unei exceptii in caz
ca se imparte la 0.
* Clasa matrice sa fie prietena a clasei numar complex si sa contina metode pentru:
supraincarcarea operatorilor << si >>, apelandu-le pe cele din clasa numar
complex; suma a doua matrici, implementata prin supraincarcarea operatorului +
si pe baza functiei de supraincarcare a lui + din clasa numar complex; produsul a
doua matrici, implementat prin supraincarcarea operatorului * si pe baza functiilor
de supraincarcare ale lui + si * din clasa numar complex; determinantul unei
matrici patratice, implementat tot cu ajutorul sumei si produsului de numere
complexe (cele care supraincarca + si * in clasa numar complex); inversa unei
matrici patratice cu determinantul nenul, care sa foloseasca functiile descrise
anterior; aruncarea unei exceptii daca se apeleaza functia inversa, dar inversa
matricii nu exista.
* Clasa matrice trebuie implementata folosind alocare dinamica */

#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
using namespace std;

class Complex
{
	float p_r, p_i;

public:
	Complex();
	Complex(const Complex&);
	Complex(float, float);
	friend istream& operator >>(istream&, Complex&);
	friend ifstream& operator >>(ifstream&, Complex&);
	friend ostream& operator <<(ostream&, Complex);
	Complex& operator = (const Complex&);
	Complex operator + (Complex);
	Complex operator * (Complex);
	Complex operator - (Complex);
	Complex operator / (Complex);
	double modul(Complex);
	bool operator ==(Complex);
	bool operator !=(Complex);
	bool operator <(Complex);
	friend class Matrice;
	~Complex() {};

};
Complex::Complex()
{
	p_r = 0;
	p_i = 0;
}

Complex::Complex(const Complex& ob)
{
	p_r = ob.p_r;
	p_i = ob.p_i;
}

Complex::Complex(float r, float i)
{
	p_r = r;
	p_i = i;
}

ifstream& operator >>(ifstream& in, Complex& ob)
{
	in >> ob.p_r >> ob.p_i;
	return in;
}

istream& operator >>(istream& in, Complex& ob)
{
	in >> ob.p_r >> ob.p_i;
	return in;
}

ostream& operator <<(ostream& out, Complex ob)
{
	out << ob.p_r << " " << ob.p_i<<"i ";
	return out;
}

Complex& Complex::operator =(const Complex& ob)
{
	if (this != &ob)
	{
		p_r = ob.p_r;
		p_i = ob.p_i;
	}
	return *this;
}

Complex Complex::operator +(Complex ob)
{
	Complex p;
	p.p_r = p_r + ob.p_r;
	p.p_i = p_i + ob.p_i;
	return p;
}

Complex Complex::operator * (Complex ob)
{
	Complex p;
	p.p_r = p_r * ob.p_r - p_i * ob.p_i;
	p.p_i = p_r * ob.p_i + ob.p_r * p_i;
	return p;
}

Complex Complex::operator - (Complex ob)
{
	Complex p;
	p.p_r = p_r - ob.p_r;
	p.p_i = p_i - ob.p_i;
	return p;
}

Complex Complex::operator / (Complex ob)
{
	try {
		if (!ob.p_r && !ob.p_i)
			throw "Impartire la 0";
		Complex p;
		p.p_r = (p_r * ob.p_r + p_i * ob.p_i) / (p_r * p_r + p_i * p_i);
		p.p_i = (p_r * ob.p_i - ob.p_r * p_i) / (p_r * p_r + p_i * p_i);
		return p;
	}
	catch (const char* h)
	{
		cout << h << endl;
	}
	
}

double Complex::modul(Complex ob)
{
	return sqrt(pow(ob.p_r,2)+pow(ob.p_i,2));
}

bool Complex::operator==(Complex ob)
{
	if (p_r == ob.p_r && p_i == ob.p_i)
		return true;
	return false;
}

bool Complex::operator!=(Complex ob)
{
	if (p_r != ob.p_r && p_i != ob.p_i)
		return true;
	return false;
}

bool Complex::operator<(Complex ob)
{
	return modul(*this) < modul(ob);
}

class Matrice
{
	int nr_L, nr_C;
	Complex **v;

public:
	Matrice();
	Matrice(int,int);
	Matrice(const Matrice&);
	friend istream& operator >>(istream&, Matrice&);
	friend ifstream& operator >>(ifstream&, Matrice&);
	friend ostream& operator <<(ostream&, Matrice&);
	Matrice& operator =(const Matrice);
	Matrice operator +(Matrice);
	Matrice operator -(Matrice);
	Matrice operator *(Matrice);
	Matrice operator *(Complex);
	Matrice Submatrice(int,int);
	Complex Determinant();
	Matrice Transpusa();
	Matrice Adjuncta();
	Matrice Inversa();
	~Matrice() { delete []v; };

};


Matrice::Matrice()
{
	nr_L = 0;
	nr_C = 0;
	v = NULL;
}

Matrice::Matrice(int l,int c)
{
	nr_L = l;
	nr_C = c;

	v = new Complex*[l];
	for (int i = 0; i < l; i++)
		v[i] = new Complex[c];

}
Matrice::Matrice(const Matrice& ob)
{
	
	int i, j;

	nr_L = ob.nr_L;
	nr_C = ob.nr_C;

	v = new Complex*[nr_L];
	for (j = 0; j < nr_L; j++)
		v[j] = new Complex[nr_C];

	for (i = 0; i < nr_L; i++)
		for (j = 0; j < nr_C; j++)
			v[i][j] = ob.v[i][j];
	
}

istream& operator>>(istream& in, Matrice& a)
{
	int j, i;

	in >> a.nr_L >> a.nr_C;

	a.v = new Complex*[a.nr_L];
	for (int j = 0; j < a.nr_L; j++)
		a.v[j] = new Complex[a.nr_C];

	for (i = 0; i < a.nr_L; i++)
		for (j = 0; j < a.nr_C; j++)
			in >> a.v[i][j];
	return in;
}

ifstream& operator>>(ifstream& in, Matrice& a)
{
	int j, i;

	in >> a.nr_L >> a.nr_C;

	a.v = new Complex*[a.nr_L];
	for (int j = 0; j < a.nr_L; j++)
		a.v[j] = new Complex[a.nr_C];

	for (i = 0; i < a.nr_L; i++)
		for (j = 0; j < a.nr_C; j++)
			in >> a.v[i][j];

	return in;
}
ostream& operator <<(ostream& out, Matrice&  a)
{
	int i, j;
	for (i = 0; i < a.nr_L; i++)
	{
		cout << endl;
		for (j = 0; j < a.nr_C; j++)
			out << a.v[i][j] << " ";
	}
	return out;
}

Matrice& Matrice::operator =(const Matrice ob)
{
	if (this != &ob)
	{
        int i, j;
		nr_L = ob.nr_L;
		nr_C = ob.nr_C;

		v = new Complex*[nr_L];
		for (j = 0; j < nr_L; j++)
			v[j] = new Complex[nr_C];

		for (i = 0; i < nr_L; i++)
			for (j = 0; j < nr_C; j++)
				v[i][j] = ob.v[i][j];
	}

	return *this;
}

Matrice Matrice::operator +(Matrice m)
{
	try {
		if (nr_L != m.nr_L || nr_C != m.nr_C)
			throw "Matricele nu au numar egal de linii si coloane";

		Matrice p(nr_L, nr_C);

		for (int i = 0; i < nr_L; i++)
			for (int j = 0; j < nr_C; j++)
				p.v[i][j] = v[i][j] + m.v[i][j];

		return p;

	}
	catch (const char* h)
	{
		cout << h << endl;
	}
	
}

Matrice Matrice::operator -(Matrice m)
{
	Matrice p(nr_L, nr_C);
	try
	{
	if (nr_L != m.nr_L || nr_C != m.nr_C)
		throw "Matricele nu au numar egal de linii si coloane";

	for (int i = 0; i < nr_L; i++)
		for (int j = 0; j < nr_C; j++)
			p.v[i][j] = v[i][j] - m.v[i][j];

	return p;
	
}
	catch (const char* h)
	{
		cout << h << endl;
	}
  
 
}

Matrice Matrice::operator *(Matrice m)
{ 
	int i, j, k;
	try {
		if (nr_C != m.nr_L)
			throw "Nu se poate efectua inmultirea pentru aceste dimensiuni.";

		Matrice p(nr_L, m.nr_C);
		
		for (i = 0; i < p.nr_L; i++)
			for (j = 0; j < p.nr_C; j++)
				for (k = 0; k < nr_C; k++)
					p.v[i][j] = p.v[i][j] + v[i][k] * m.v[k][j];
		return p;
	}
	catch (const char* h)
	{
		cout << h << endl;
	}

}
Matrice Matrice::operator*(Complex a)
{
	int i, j;

	Matrice p(nr_L, nr_C);

	for (i = 0; i < p.nr_L; i++)
		for (j = 0; j < p.nr_C; j++)
			p.v[i][j] = a * v[i][j];
	return p;
}
Matrice Matrice::Submatrice(int linie,int coloana)
{
	Matrice p(nr_L-1,nr_C-1);

	int i, j, c = 0, l = 0;

	for (i = 0; i < nr_L; i++)
		for (j = 0; j < nr_C; j++)
			if (j != coloana && i != linie)
			{
				p.v[l][c] = v[i][j];
				c++;
				if (c == p.nr_L)
				{
					c = 0;
					l++;
				}
				
			}

	return p;
	
}

Complex Matrice::Determinant()
{
	try
	{
		if (nr_L != nr_C)
			throw "Matricea nu este patratica.";
		int i;
		Complex det, c;
		Matrice sub;
		if (nr_L == 1)
		{
			det = v[0][0];
		}
		if (nr_L == 2)
		{
			det = v[0][0] * v[1][1] - v[0][1] * v[1][0];
		}
		if (nr_L >= 3)
		{
			for (i = 0; i < nr_L; i++)
			{
				sub = Submatrice(0, i);
				if (i % 2)
					det = det + v[0][i] * sub.Determinant();
				else
					det = det - v[0][i] * sub.Determinant();
			}
		}

		return det;
		
	}
	catch (const char* h)
	{
		cout << h << endl;
	}
	
}

Matrice Matrice::Transpusa()
{
	Matrice p(nr_L,nr_C);

	for (int i = 0; i < nr_L; i++)
		for (int j = 0; j < nr_C; j++)
			p.v[i][j] = v[j][i];

	return p;		
}

Matrice Matrice::Adjuncta()
{
	int i, j;
	Complex a(-1,0);
;
	Matrice sub,p(nr_L, nr_C);
	for (i = 0; i < nr_L; i++)
		for (j = 0; j < nr_C; j++)
		{
			sub = Submatrice(i, j);
			cout << endl;
			cout << "Submatricea "<<i<<" "<<j<<": "<< sub;

			if ((i + j) % 2)
				p.v[i][j] = v[i][j] * sub.Determinant();
			else
				p.v[i][j] = a * v[i][j] * sub.Determinant();
		}
	return p;
	
}

Matrice Matrice::Inversa()
{
	
	try {
		Complex x = Determinant();

		if (!x.p_r && !x.p_i)
			throw "Matricea nu este inversabila.";

		Complex unu(1, 0);
		Matrice p1(nr_L, nr_C), p2(nr_L, nr_C);

		if (nr_L == 1)
			p2.v[0][0] = unu / v[0][0];
		else
		{
			p1 = Transpusa();
			p2 = p1.Adjuncta();
		}
		
		return p2*x;
	}
	catch (const char *h)
	{
		cout << "Exceptie aruncata.\n";
		cout << h << endl;
	}
}
int main()
{
	ifstream f("date.txt");

	int n1;
	Matrice m,n,a,d,*e;
	Complex c,b;
	f >> m >> n;
   //	cin >> n1;
	//e = new Matrice[n1];
	//cin >> c >> b;
	//cout << c / b;
	a = m * n;
	cout << a;
    /*cin >> b >> c;
	cout << b * c;
	f >> m >> n;
	cout << m;
	cout << endl;
	a = m.Inversa();
	
	a = m * n;
	cout << endl << a << endl << endl;
	d = n.Inversa();
	cout << endl << d;
	//cout << m << endl;
	/*f >> n;
	a = m * n;
	cout << a << endl;
	//cout << b<<endl;*/
	/*for (int i = 0; i < n1; i++)
		f >> e[i];
	for (int i = 0; i < n1; i++)
	{
		cout << e[i].Inversa;
		//m = m * e[i];
		cout << m<< "\n\n";
	}*/
	return 0;
	
}