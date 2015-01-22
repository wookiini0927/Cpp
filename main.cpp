#include "templatePolynome.h"

int main(int argc, char const *argv[])
{
	/* code */

	vector<int> tab(5);

	tab[0] = 2;
	tab[1] = 5;
	tab[2] = 12;
	tab[3] = 3;
	tab[4] = 7;

	map<int,int> m_map_cp;

	m_map_cp[0] = 3;
	m_map_cp[1] = 4;
	m_map_cp[2] = 13;
	m_map_cp[3] = 9;
	m_map_cp[4] = 64;

	//Test constructeur par defaut
	Polynome<int> t;
	Polynome<int> multi;

	//Test constructeur surcharge : tableau
	Polynome<int> t1(tab);
	cout<<"Affichage de t1 : "<<t1<<endl;

	//Test Constructeur surcharge : map
	Polynome<int> t2(m_map_cp);
	cout<<"Affichage de t2 : "<<t2<<endl;

	//Test constructeur de copie
	Polynome<int> t3(t2);

	//Test soustracion

	t = t1-t2;

	cout<<t<<endl;

	//Test multiplication

	map<int,int> coeff_p1;
	coeff_p1[0] = 4;
	coeff_p1[1] = 7;
	coeff_p1[2] = 2;

	map<int,int> coeff_p2;

	coeff_p2[0] = 7;
	coeff_p2[1] = -3;
	coeff_p2[2] = 8;

	Polynome<int> m1(coeff_p1);
	Polynome<int> m2(coeff_p2);

	cout<<m1<<endl;

	cout<<m2<<endl;
	
	multi = m1*m2;

	cout<<multi<<endl;
	
	//test surcharge -=

	cout<<"affichage t : "<<t<<endl;
	t1-=t2;
	cout<<"affichage t1 : "<<t1<<endl;

/**

	int res = 0;
	int x = 2;
	res = t1.evaluer(x);

	cout<<res<<endl;

	t=t1.deriver();

	cout<<"derive : "<<t<<endl;**/

	return 0;
}
