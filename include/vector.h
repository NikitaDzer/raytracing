#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
    	class Kernel
    	{
    	    private:
		float x_;
		float y_;
		float z_;
		float len_;


	    public:
		Kernel( const float x, const float y, const float z);
		Kernel( const Kernel &kern);
		
		~Kernel();


		float get_x()   const;
		float get_y()   const;
		float get_z()   const;
		float get_len() const;

		void set_x  ( const float x);
		void set_y  ( const float y);
		void set_z  ( const float z);
		void set_len( const float len);

		float calc_len() const;
	};


    private:
	Vector::Kernel kern_;


    public:
	Vector();
	Vector( const float x, const float y, const float z);
	Vector( const Vector &vec);

	~Vector();


	bool    operator == ( const Vector &vec) const;
	bool    operator != ( const Vector &vec) const;

	Vector  operator +  ( const Vector &vec) const;
	Vector  operator -  ( const Vector &vec) const;
	
	float   operator &  ( const Vector &vec) const;
	Vector  operator ^  ( const Vector &vec) const;

	Vector &operator += ( const Vector &vec);
	Vector &operator -= ( const Vector &vec);
	Vector &operator *= ( const float   fac);


	float get_x  () const;
	float get_y  () const;
	float get_z  () const;
	float get_len();
	
	void set_x( const float x);
	void set_y( const float y);
	void set_z( const float z);
	void set  ( const float x, const float y, const float z);

	float  cos( const Vector &vector) const;
	Vector normalize()                const;

	void print() const;
};

Vector operator * ( const Vector &vec, const float   fac);
Vector operator * ( const float   fac, const Vector &vec);


#endif // VECTOR_H
