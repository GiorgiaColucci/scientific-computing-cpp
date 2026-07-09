#pragma once
#include <ostream>
#include <concepts>		//per std::integral
#include <numeric>		//per eventuale gcd

template <typename I> 
    requires std::integral<I>
class rational {
	I num_;
	I den_;
	
public:	
	// ------------------------- COSTRUTTORI -------------------------
	/* Costruttore di default */
	rational() : num_(0), den_(1) {}
		
	/* Costruttore user-defined */
	//prende n e lo copia dentro num_, che è quello che sto usando attualmente io; stessa cosa per d;
	rational(I n, I d) : num_(n), den_(d) 		{ normalize(); }		
	rational(I n) : num_(n), den_(1) { normalize(); }		//gestione interi

	/* Restituiscono i valori di numeratore e denominatore */    
    I num() const { return num_; }
    I den() const { return den_; }
    
    // ------------------------- ERRORI -------------------------
    /* Gestione degli errori */
    bool is_nan() const { return num_ == 0 && den_ == 0; }	/* restituise true se ho 0/0, altrimenti false */
    bool is_inf() const { return num_ != 0 && den_ == 0; }	/* restituise true se ho n/0 (n != 0), altrimenti false */
    bool is_zero() const { return num_ == 0 && den_ != 0; }
    
	
	// ------------------------- NORMALIZZAZIONE -------------------------
	/* Semplificazione delle frazioni */
	void normalize()
	{
		// se ho inf o nan non normalizzo 
		if (is_nan() || is_inf()) return;
		
		// se ho uno zero, fisso la forma 0/1
        if (is_zero()) { den_ = 1; 	return; }
		 
		// segno sempre sul numeratore
        if (den_ < 0) {
            num_ = -num_;
            den_ = -den_;
        } 
        
        /* semplificazione vera e propria, sfruttando il il GDC (ita: MCD)*/
        I g = std::gcd(num_, den_); //funzione trovata su C++reference: g è sempre positivo!!
        num_ = num_ / g;
        den_ = den_ /g;
	};
	
    
    // ------------------------- SOMMA -------------------------
   	/* Implementazione canonica dell'incremento */
   	rational& operator+=(const rational& other)		
   	{
	   	if (is_nan() || other.is_nan()) 	/* || restituisce true se ALMENO uno dei due valori è true*/
	   	{	num_ = 0; den_ = 0;
           	return *this;
        }

        if (is_inf() && other.is_inf()) 
        {	if ((num_ > 0 && other.num_ < 0) || (num_ < 0 && other.num_ > 0))		// inf + (-inf) = NaN
	        {	num_ = 0;  den_ = 0;
                return *this;  
            }
            /* se Inf + Inf o (-Inf) + (-Inf) (CIOE SONO NEL CASO DI SEGNI CONCORDI) ottengo lo stesso oggetto */
            // num_ = 1; den_ = 0; --> NO perchè cosi non gestisco il segno
            return *this;
        }
        
        if (is_inf()) 
        { 	return *this;	}		// num_ = 1; den_ = 0; --> NO perchè cosi non gestisco il segno
        
        if (other.is_inf()) 
        {	num_ = other.num_;
            den_ = 0;
            return *this;
        }
        
        // formula: a/b + c/d = (ad + cb)/(bd)*/
        num_ = num_ * other.den_ + other.num_ * den_;
        den_ *= other.den_;
        
        normalize();
        return *this;		/* Modifica l’oggetto corrente (*this). Restituisce un riferimento allo stesso oggetto (LO STESSO!), modificato. ECCO PERCHÈ NON METTO CONST: STO RESTITUENDO UNA REFERENCE (ALIAS!!!) !! */
	};
   	
   	/* Implementazione canonica della somma: faccio il caso normale raz e raz + il caso int e razionale */
   	rational operator+(const rational& other) const
   	{	rational ret = *this;		//copia di *this
	   	ret += other;				//uso operator+=
	   	return ret;		/* ritorno la copia modificata; Quindi operator+ crea una copia: ret = *this; Modifica la copia con +=; Restituisce la copia */
	};
	   		
	rational operator+(const I& other) const { return *this + rational(other, 1); }

    
    // ------------------------- DIFFERENZA -------------------------
    /* Implementazione canonica dell'incremento negativo */
    rational& operator-=(const rational& other)
    {	return ( *this += rational(-other.num_, other.den_) );
	};
    
    /* Implementazione canonica della differenza */
	rational operator-(const rational& other) const 
	{	rational ret = *this;
		ret -= other;
		return ret;
	};
	
    rational operator-(const I& other) const { return *this - rational(other, 1); }

    	
    // ------------------------- PRODOTTO -------------------------
    /* Implementazione canonica di *= con un altro razionale */
    rational& operator*=(const rational& other) 
    {	if (is_nan() || other.is_nan()) 		// gestisco NaN * qualsiasi cosa, compreso inf 
	    {	num_ = 0; den_ = 0;
            return *this;
        }
        
        // inf * 0 = NaN o viceversa
        if (is_zero() && other.is_inf()) { num_ = 0; den_ = 0; return *this; }
        if (is_inf() && other.is_zero()) { num_ = 0; den_ = 0; return *this; }
        
        // bool positive = ( num_*other.num_ ) > 0;  	/* --> possibile overflow di moltiplicazione*/
        bool positive = (num_ > 0 && other.num_ > 0) || (num_ < 0 && other.num_ < 0); 	/* È una VARIABILE (non funzione!) che controlla se il prodotto dei due numeri è positivo*/	

		// inf * qualsiasi (diverso da zero e da NaN) ma devo vedere il segno
        if (is_inf() || other.is_inf()) 
        {	if (positive) { num_ = 1; den_ = 0; }
            else { num_ = -1; den_ = 0; }
            return *this;
        }
        
        num_ *= other.num_;
        den_ *= other.den_;
        
        normalize(); 
        return *this;
    };    
    
    /* Implementazione canonica del prodotto con un altro razionale */
    rational operator*(const rational& other) const 
    {	rational ret = *this;
        ret *= other;
        return ret;
    };
    
    rational operator*(const I& other) const { return *this * rational(other, 1); }


	// ------------------------- DIVISIONE -------------------------
	/* Implementazione canonica del rapporto */
	rational& operator/=(const rational& other) 
	{	/* GESTIONE NaN */
		if (is_nan() || other.is_nan()) 
		{	num_ = 0; 
			den_ = 0;
			return *this; 
		};
		
		/* GESTIONE is_zero */
		if (other.is_zero())
		{	// divisione per 0 --> Inf o nan
			if (is_zero()) 
			{	// 0/0 --> nan
				num_ = 0;
				den_ = 0;	
			}
			else 
			{	// x/0 (x != 0) --> inf con segno
				if (num_ > 0) { num_ = 1; den_ = 0; }
                else { num_ = -1; den_ = 0; }
			};
			return *this;
		};
		
		/* GESTIONE Inf */
		bool positive = (num_ > 0 && other.num_ > 0) || (num_ < 0 && other.num_ < 0);
		
        if (is_inf())
        {	if (other.is_inf()) 
	        {	// Inf / Inf --> NaN
                num_ = 0;
                den_ = 0;
            }
            else 
            {	// Inf / q normale -->  Inf con segno corretto
                if (positive) { num_ = 1; den_ = 0; }
                else { num_ = -1; den_ = 0; }
            };
            return *this;
        }
      	else 
      	{	if (other.is_inf()) 
	      	{	num_ = 0; 
		      	den_ = 1;
		      	return *this;
		    }
		};
		
		num_ *= other.den_;
		den_ *= other.num_;
		
		normalize();
		return *this;
	}; 
	
	/* Implementazione canonica della divisione */
	rational operator/(const rational& other) const
	{	rational ret = *this;
		ret /= other;
		return ret;
	};
	
    rational operator/(const I& other) const { return *this / rational(other, 1); }

};


// Uso delle funzioni template per gestire i casi di operazioni tra interi e razionali
template<typename T> requires std::integral<T>
rational<T> operator+(const T& i, const rational<T>& r) {
    return rational<T>(i, 1) + r;
}

template<typename T> requires std::integral<T>
rational<T> operator-(const T& i, const rational<T>& r) {
    return rational<T>(i, 1) - r;
}

template<typename T> requires std::integral<T>
rational<T> operator*(const T& i, const rational<T>& r) {
    return rational<T>(i, 1) * r;
}

template<typename T> requires std::integral<T>
rational<T> operator/(const T& i, const rational<T>& r) {
    return rational<T>(i, 1) / r;
}


/* definisco un Overload di operator<< per la stampa (in particolare viene chiamato quando faccio std::cout <<): è una funzione libera!! (non membro della classe rational);
È definito fuori dalla classe perchè il primo operando è std::ostream, quindi non può essere un metodo di rational (nelle classi i metodi hanno come primo operando la classe stessa)*/

template<typename T> requires std::integral<T>
std::ostream& operator<<(std::ostream& os, const rational<T>& r)		/* os è uno stream QUALSIASI!*/
{
	if (r.num() == 0 && r.den() == 0)
       { return os << "NaN"; };

    if (r.num() > 0 && r.den() == 0)
       { return os << "+Inf"; };
        
    if (r.num() < 0 && r.den() == 0)
       { return os << "-Inf"; };
       
    if (r.is_zero()) 
    	{ return os << "0"; };
    
    if (r.den() == 1) 		//gestione degli interi
    { return os << r.num(); }

    return os << r.num() << "/" << r.den();
};
