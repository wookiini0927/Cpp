#ifndef TEMPLATEPOLYNOME_H_INCLUDED
#define TEMPLATEPOLYNOME_H_INCLUDED 

#include <iostream>
#include <map>
#include <vector>
#include <math.h>

using namespace std;

template <typename T>
class Polynome{

	map<int,T> m_map_coef;

public:
	//Constructeur par defaut
	Polynome();

	//Constructeur surchargé avec tableau
	Polynome(const vector<T>&);

	//Constructeur surchargé avec map
	Polynome(const map<int,T>&);

	//Constructeur de copie
	Polynome(const Polynome<T>& p);

	//Accesseurs
	map<int,T>& getMap();

	//Mutateurs
	void setMap(const map<int,T>&);

	//Fonctions
	T evaluer(T& z);
	Polynome deriver() ;

	//Surcharge
	friend ostream& operator<<(ostream& os, const Polynome& p){
		os<<"P(x) : ";
		typename map<int,T>::const_iterator it=p.m_map_coef.begin();
		
		while(it!=p.m_map_coef.end()){
			if(it!=p.m_map_coef.begin() && it->second>0){
				if(it->first>0){
					os<<"+";
				}
			}
			if(it->first==1){
				os<<it->second<<"x";
			}
			else if(it->first==0){
				os<<it->second;
			}
			else if(it->first>=0){
				os<<it->second<<"x^"<<it->first;
			}

			it++;
		}
		return os;
	}
	
	friend Polynome operator+(const Polynome& p1, const Polynome& p2){
		Polynome<T> p_somme;
	    typename map<int,T>::const_iterator i;
	    typename map<int,T>::const_iterator j;
	    i = p1.m_map_coef.begin();
	    j = p2.m_map_coef.begin();
	    while (i != p1.m_map_coef.end() && j != p2.m_map_coef.end())
        {
            if (i->second == 0 && j->second == 0)
            {
                p_somme.m_map_coef[i->first] = 0;
            }
            else if (i->second == 0 && j->second != 0)
            {
                p_somme.m_map_coef[i->first] = j->second;
            }
            else if (i->second != 0 && j->second == 0)
            {
                p_somme.m_map_coef[i->first] = i->second;
            }
            else
            {
                p_somme.m_map_coef[i->first] = i->second + j->second;
            }
            i++;
            j++;
        }
        if (i->first < j->first)
        {
            for (j; j != p2.m_map_coef.end(); j++)
            {
                p_somme.m_map_coef[j->first] = j->second;
            }
        }
        else if (i->first > j->first)
        {
            for (i; i != p2.m_map_coef.end(); i++)
            {
                p_somme.m_map_coef[i->first] = i->second;
            }
        }
        return p_somme;
	}

	friend Polynome operator-(const Polynome& p1, const Polynome& p2){
		Polynome<T> p_difference;
		typename map<int,T>::const_iterator i=p1.m_map_coef.begin();
		typename map<int,T>::const_iterator j=p2.m_map_coef.begin();

		while(i!=p1.m_map_coef.end() && j!=p2.m_map_coef.end()){
			//Cas ou les deux puissances n'ont pas de coeff
			if(i->second ==0 && j->second ==0){
				p_difference.m_map_coef[i->first] = 0;
			}
			//Cas ou le premier polynome n'a pas cette puissance et le deuxieme existe
			else if(i->second == 0 && j->second!=0){
				p_difference.m_map_coef[i->first] = j->second;
			}
			//Cas ou le premier polynome a cette puissance et le deuxieme non
			else if(i->second != 0 && j->second==0){
				p_difference.m_map_coef[i->first] = i->second;
			}
			//Cas ou les deux puissances ont un coeff non nul
			else{
				p_difference.m_map_coef[i->first] = i->second-j->second;
			}
			i++;
			j++;
		}

		//A ce stade dans le cas ou un des deux polynomes a un ordre de grandeur plus grand
		if(i->first<j->first){
			for(j;j!=p2.m_map_coef.end();j++){
				if(j->second<0){
					p_difference.m_map_coef[j->first] =  0-j->second;
				}
				else{
					p_difference.m_map_coef[j->first] = j->second;

				}
			}
		}
		else if(i->first>j->first){
			for(i;i!=p1.m_map_coef.end();i++){
				if(i->second<0){
					p_difference.m_map_coef[i->first] =0-i->second;
				}
				else{
					p_difference.m_map_coef[i->first] = i->second;

				}
			}

		}

		return p_difference;
	}
	
	friend Polynome operator*(const Polynome& p1, const Polynome& p2){
		Polynome<T> p_produit;
		typename map<int,T>::const_iterator i; //iterateur de p1
		typename map<int,T>::const_iterator j; //iterateur de p2

		for(i=p1.m_map_coef.begin();i!=p1.m_map_coef.end();i++){
			for(j=p2.m_map_coef.begin();j!=p2.m_map_coef.end();j++){			
				p_produit.m_map_coef[i->first+j->first] += (i->second*j->second);
			}
		}


		return p_produit;
	}

	Polynome operator+=(const Polynome& p) const;
	Polynome operator-=(const Polynome& p) {
		typename map<int,T>::const_iterator i=this->m_map_coef.begin();
		typename map<int,T>::const_iterator j=p.m_map_coef.begin();

		while(i!=this->m_map_coef.end() && j!=p.m_map_coef.end()){
			//Cas ou les deux puissances n'ont pas de coeff
			if(i->second ==0 && j->second ==0){
				this->m_map_coef[i->first] = 0;
			}
			//Cas ou le premier polynome n'a pas cette puissance et le deuxieme existe
			else if(i->second == 0 && j->second!=0){
				this->m_map_coef[i->first] = j->second;
			}
			//Cas ou le premier polynome a cette puissance et le deuxieme non
			else if(i->second != 0 && j->second==0){
				this->m_map_coef[i->first] = i->second;
			}
			//Cas ou les deux puissances ont un coeff non nul
			else{
				this->m_map_coef[i->first] = i->second-j->second;
			}
			i++;
			j++;
		}

		//A ce stade dans le cas ou un des deux polynomes a un ordre de grandeur plus grand
		if(i->first<j->first){
			for(j;j!=p.m_map_coef.end();j++){
				if(j->second<0){
					this->m_map_coef[j->first] =  0-j->second;
				}
				else{
					this->m_map_coef[j->first] = j->second;

				}
			}
		}
		else if(i->first>j->first){
			for(i;i!=this->m_map_coef.end();i++){
				if(i->second<0){
					this->m_map_coef[i->first] =0-i->second;
				}
				else{
					this->m_map_coef[i->first] = i->second;

				}
			}

		}

		return *this;

	}

	Polynome operator*=(const Polynome& p) {
		cout<<"surcharge *="<<endl;
		map<int,T> tmp_map;
		typename map<int,T>::const_iterator i; //iterateur de this
		typename map<int,T>::reverse_iterator fin = m_map_coef.rbegin();
		typename map<int,T>::const_iterator j; //iterateur de p
		int last = fin->first;

		for(i= this->m_map_coef.begin(); i!= this->m_map_coef.end(); i++){
			tmp_map[i->first]=i->second;
		}

		T tmp =0;
		cout<<"this : "<<*this<<endl;
		cout<<"p2 : "<<p<<endl;
		cout<<"dernier element :"<<last<<endl;
		for(i=this->m_map_coef.begin();i->first!=last+1;i++){
			cout<<"this["<<i->first<<"] = "<<tmp_map[i->first];
			tmp = tmp_map[i->first];
			for(j=p.m_map_coef.begin();j!=p.m_map_coef.end();j++){
				if(i->first == 0){			
					this->m_map_coef[i->first+j->first] = (tmp_map[i->first]*j->second);
				}
				else{
					this->m_map_coef[i->first+j->first] += (tmp_map[i->first]*j->second);

				}
				
			}

		}


		return *this;
	}



	//Destructeur
	~Polynome();

};

/*======================
===   CONSTRUCTEUR   ===
========================*/

//Constructeur par défaut
template <typename T>
Polynome<T>::Polynome(){
	typename map<int, T>::const_iterator it;

 	for(it = m_map_coef.begin(); it != m_map_coef.end(); it++)
    {
    	m_map_coef[it->first] = 0;
    }
}

//Constructeur surchargé : par tableau
template <typename T>
Polynome<T>::Polynome(const vector<T>& tab){
	for (int i = 0; i<tab.size();i++){
		m_map_coef[i] = tab[i];
	}
	

/** Affiche test
    for(it = m_map_coef.begin(); it != m_map_coef.end(); it++)
    {
    	if(it->second!=0){
	        cout<<"tab["<<it->first<<"] ="<<it->second<<endl;
    	}
    }
**/
}

//Constructeur surchargé : par map
template <typename T>
Polynome<T>::Polynome(const map<int,T>& m_cp):m_map_coef(m_cp){
	cout<<"TEST surcharge map"<<endl;
	typename map<int, T>::const_iterator it;

 	for(it = m_map_coef.begin(); it != m_map_coef.end(); it++)
    {
    	if(it->second!=0){
	        cout<<"m_map_coef["<<it->first<<"] = "<<it->second<<endl;
	        
    	}
    }
}

//Constructeur de copie
template <typename T>
Polynome<T>::Polynome(const Polynome<T>& p):m_map_coef(p.m_map_coef){
		cout<<"TEST Constructeur copie"<<endl;

 	typename map<int, T>::const_iterator it;

 	for(it = m_map_coef.begin(); it != m_map_coef.end(); it++)
    {
    	if(it->second!=0){
	        cout<<"m_map_coef2["<<it->first<<"] = "<<it->second<<endl;
	        
    	}
    }
}

/*===================
===  ACCESSEURS   ===
=====================*/


template <typename T>
map<int,T>& Polynome<T>::getMap(){
	return m_map_coef;
}

/*=====================
====   SURCHARGES   ===
=======================*/

/*===================
===   FONCTIONS   ===
=====================*/

template <typename T>
T Polynome<T>::evaluer(T& x) {
	Polynome<T> n_poly;
	T z;
	T res=0;
	typename map<int,T>::const_iterator it;
	for(it = this->getMap().begin(); it!=this->getMap().end();it++){
		z = pow(x,it->first);
		if(it->first == 0){
			res = it->second;
		}
		else{
			res += (z*it->second);
		}
	}

	return res;
}

template <typename T>
Polynome<T> Polynome<T>::deriver() {
	Polynome<T> n_poly;
	T d;
	typename map<int,T>::const_iterator it;

	for(it = m_map_coef.begin(); it!=m_map_coef.end();it++){
		d = it->first*it->second;
		n_poly.m_map_coef[it->first-1] = d;
	}

	return n_poly;
}

//Destructeur
template <typename T>
Polynome<T>::~Polynome(){

}
#endif
