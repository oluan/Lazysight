#pragma once
#include <cmath>

#define PI ( 3.14159265358979f )

class Vector3
{
public:
	float x, y, z;

	Vector3() { this->x = this->y = this->z = 0; }
	Vector3( float x, float y, float z ) : x( x ), y( y ), z( z ) {}
	Vector3( float* pvec ) : x( pvec[0] ), y( pvec[1] ), z( pvec[2] ) {}

	bool    operator== ( const Vector3& vec ) const { return this->x == vec.x && this->y == vec.y && this->z == vec.z; }
	bool    operator!= ( const Vector3& vec ) const { return this->x != vec.x || this->y != vec.y || this->z != vec.z; }
	Vector3 operator=  ( const Vector3& vec ) { this->x = vec.x; this->y = vec.y; this->z = vec.z; return *this; }
	Vector3 operator-  ( const Vector3& vec  ) const { return Vector3(x - vec.x, y - vec.y, z - vec.z); };

	float get_distance_x  ( const Vector3& vec ) const { return this->x - vec.x; }
	float get_distance_y  ( const Vector3& vec ) const { return this->y - vec.y; }
	float get_distance_z  ( const Vector3& vec ) const { return this->z - vec.z; }
	float get_3d_distance ( const Vector3& vec ) const 
	{
		return sqrtf( ( ( this->x - vec.x ) * ( this->x - vec.x ) ) + 
					  ( ( this->y - vec.y ) * ( this->y - vec.y ) ) + 
					  ( ( this->z - vec.z ) * ( this->z - vec.z ) ) );
	}
};