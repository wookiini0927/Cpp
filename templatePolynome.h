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

	//Fonctions

	/**
	* Evalue le polynome a la valeur z
	*
	* Param x : valeur que vaudra l'inconnu
	*
	* Retourne le resultat du polynome
	**/
	T evaluer(T& x);

	/**
	* Derive le polynome
	*
	* retourne la derivee du polynome
	**/
	Polynome deriver();

	/**
	* Fais la division euclidienne de deux polynomes
	* 
	* Param p : diviseur de la division
	*
	* Retourne le quotient de la division
	**/
	Polynome divisionEuclidienne(const Polynome& p) const;

	Polynome composition(Polynome& p2);
    Polynome puissance(Polynome& p, int i);

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

		typename map<int,T>::const_reverse_iterator i_d=p1.m_map_coef.rbegin(); //recupere le plus haut degre de p1
		typename map<int,T>::const_reverse_iterator j_d=p2.m_map_coef.rbegin(); //recupere le plus haut degre de p2

	    typename map<int,T>::const_iterator i;
	    typename map<int,T>::const_iterator j;
	    i = p1.m_map_coef.begin();
	    j = p2.m_map_coef.begin();

	    if(i_d->first == j_d->first){

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

            cout<<i->first<<","<<j->first<<endl;
        }
    }

        if (i->first-1 < j->first-1)
        {
            for (;j != p2.m_map_coef.end(); j++)
            {
                p_somme.m_map_coef[j->first] = j->second;
            }
        }
        else if (i->first-1 > j->first-1)
        {
            for (;i != p2.m_map_coef.end(); i++)
            {
                p_somme.m_map_coef[i->first] = i->second;
            }
        }
        return p_somme;
	}


	friend Polynome operator-(const Polynome& p1, const Polynome& p2){
		Polynome<T> p_difference;
		typename map<int,T>::const_reverse_iterator i_d=p1.m_map_coef.rbegin();
		typename map<int,T>::const_reverse_iterator j_d=p2.m_map_coef.rbegin();

		typename map<int,T>::const_iterator i=p1.m_map_coef.begin();
		typename map<int,T>::const_iterator j=p2.m_map_coef.begin();

		if(i_d->first == j_d->first){
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
		}

		else if(i_d->first<j_d->first){
			for(;i!=p1.m_map_coef.end();i++){
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
				j++;
			}
			for(;j!=p2.m_map_coef.end();j++){
					p_difference.m_map_coef[j->first] =  0-j->second;
				
			}
		}
		else if(i_d->first>j_d->first){

			for(;j!=p2.m_map_coef.end();i++){
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
				j++;
			}

			for(;i!=p1.m_map_coef.end();i++){				
					p_difference.m_map_coef[i->first] = i->second;

			}

		}

		return p_difference;
	}
	
	//Surcharge operator * avec deux polynomes
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

	//Surcharge operator * avec un scalaire et un polynome
	friend Polynome operator*(const T& c, const Polynome& p1){
		Polynome<T> p_produit;
		typename map<int,T>::const_iterator i; //iterateur de p1

		for(i=p1.m_map_coef.begin();i!=p1.m_map_coef.end();i++){
				p_produit.m_map_coef[i->firstt] = (c*i->second);
		}


		return p_produit;
	}


	Polynome operator+=(const Polynome& p) {
		//Appel la surcharge operator+
		*this = *this + p;
        return *this;
	}
	
	Polynome operator-=(const Polynome& p) {

		//Appel la surcharge operator-
		*this = *this - p;

		return *this;

	}

	Polynome operator*=(const Polynome& p) {
		map<int,T> tmp_map;
		typename map<int,T>::const_iterator i; //iterateur de this
		typename map<int,T>::reverse_iterator fin = m_map_coef.rbegin();
		typename map<int,T>::const_iterator j; //iterateur de p
		int last = fin->first;

		for(i= this->m_map_coef.begin(); i!= this->m_map_coef.end(); i++){
			tmp_map[i->first]=i->second;
		}

		T tmp =0;
		for(i=this->m_map_coef.begin();i->first!=last+1;i++){
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

}

//Constructeur surchargé : par map
template <typename T>
Polynome<T>::Polynome(const map<int,T>& m_cp):m_map_coef(m_cp){

}

//Constructeur de copie
template <typename T>
Polynome<T>::Polynome(const Polynome<T>& p):m_map_coef(p.m_map_coef){

}

/*===================
===  ACCESSEURS   ===
=====================*/


template <typename T>
map<int,T>& Polynome<T>::getMap(){
	return m_map_coef;
}

/*===================
===   FONCTIONS   ===
=====================*/

template <typename T>
T Polynome<T>::evaluer(T& x) {
	T z; //garde le resultat de x a la puissance k
	T res=0; //resultat final
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
	T d; //resultat de la derive de chaque fonction
	typename map<int,T>::const_iterator it;

	for(it = m_map_coef.begin(); it!=m_map_coef.end();it++){
		d = it->first*it->second;
		n_poly.m_map_coef[it->first-1] = d;
	}

	return n_poly;
}

template <typename T>
Polynome<T> Polynome<T>::divisionEuclidienne(const Polynome& p) const{

	Polynome<T> quotient;
	Polynome<T> reste;

	typename map<int,T>::const_reverse_iterator i = this->m_map_coef.rbegin(); //iterateur de p1
	typename map<int,T>::const_reverse_iterator j = p.m_map_coef.rbegin(); //iterateur de p2

	if(j->first == 0 && j->second == 0){
		throw domain_error("Division par zero");
	}

	int degre_A = i->first;
	int degre_B = j->first;

	if(degre_A<degre_B){
		throw domain_error("Division impossible");
	}

	else if(degre_A == degre_B){
		quotient.m_map_coef[0] = i->second/j->second;
		T tmp = i->second/j->second; //retient le coef
		for(;i!=this->m_map_coef.rend();i++){
			reste.m_map_coef[i->first] = i->second-(tmp*j->second);
			j++;
		}
	}

	else{
		for(;i!=this->m_map_coef.rend();i++){
			int p = i->first - j->first;
			T c_p = i->second/j->second;

			reste.m_map_coef[i->first - p] = i->second-(c_p*j->second);

			quotient.m_map_coef[p] = c_p;
			j++;
		}
	}

	cout<<"A = BQ+R <=> "<<*this<<" = "<<p<<"."<<quotient<<" + "<<reste<<endl;

	return quotient;
}


//Destructeur
template <typename T>
Polynome<T>::~Polynome(){

}
#endif
