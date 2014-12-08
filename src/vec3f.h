#ifndef	VEC3F
#define	VEC3F


#include	<math.h>						// for sqrtf


#define	X	0
#define	Y	1
#define	Z	2


/*	Set vector values
	param:	v		vector to set (modified)
	param:	x		x value
	param:	y		y value
	param:	z		z value
*/
static inline void vec3f_set(float* v, float x, float y, float z)
{
	v[X] = x;
	v[Y] = y;
	v[Z] = z;
}

/*	Copy vector
	param:	dst		destination vector (modified)
	param:	src		source vector
*/
static inline void vec3f_copy(float* dst, float* src)
{
	dst[X] = src[X];
	dst[Y] = src[Y];
	dst[Z] = src[Z];
}


/*	Add vector to other vector (new)
	param:	res		resultant vector (modified)
	param:	v0		vector augend
	param:	v1		vector addend
*/
static inline void vec3f_addn(float* res, float* v0, float* v1)
{
	res[X] = v0[X]+v1[X];
	res[Y] = v0[Y]+v1[Y];
	res[Z] = v0[Z]+v1[Z];
}

/*	Add vector to other vector
	param:	v0		vector augend (modified)
	param:	v1		vector addend
*/
static inline void vec3f_add(float* v0, float* v1)
{
	vec3f_addn(v0, v0, v1);
}

/*	Subtract vector from other vector (new)
	param:	res		resultant vector (modified)
	param:	v0		vector minuend
	param:	v1		vector subtrahend
*/
static inline void vec3f_subtractn(float* res, float* v0, float* v1)
{
	res[X] = v0[X]-v1[X];
	res[Y] = v0[Y]-v1[Y];
	res[Z] = v0[Z]-v1[Z];
}

/*	Subtract vector from other vector
	param:	v0		vector minuend (modified)
	param:	v1		vector subtrahend
*/
static inline void vec3f_subtract(float* v0, float* v1)
{
	vec3f_subtractn(v0, v0, v1);
}


/*	Vector dot product
	param:	v0		first vector
	param:	v1		second vector
	return:	float	dot product of the two input vectors
*/
static inline float vec3f_dot(float* v0, float* v1)
{
	return v0[X]*v1[X] + v0[Y]*v1[Y] + v0[Z]*v1[Z];
}

/*	Find squared length of vector
	param:	v		vector to find squared length of
	return:	float	squared length of input vector
*/
static inline float vec3f_length2(float* v)
{
	return vec3f_dot(v, v);
}

/*	Find length of vector
	param:	v		vector to find length of
	return:	float	length of input vector
*/
static inline float vec3f_length(float* v)
{
	return sqrtf(vec3f_length2(v));
}


/*	Scale vector by a scalar (new)
	param:	res		resultant vector (modified)
	param:	v		vector to scale
	param:	s		scalar
*/
static inline void vec3f_scalen(float* res, float* v, float s)
{
	res[X] = v[X]*s;
	res[Y] = v[Y]*s;
	res[Z] = v[Z]*s;
}

/*	Scale vector by a scalar
	param:	v		vector to scale (modified)
	param:	s		scalar
*/
static inline void vec3f_scale(float* v, float s)
{
	vec3f_scalen(v, v, s);
}


/*	Normalize vector (new)
	param:	res		resultant vector (modified)
	param:	v		vector to normalize (assumed length > 0)
*/
static inline void vec3f_normalizen(float* res, float* v)
{
	vec3f_scalen(res, v, 1.f/vec3f_length(v));
}

/*	Normalize vector
	param:	v		vector to normalize (modified) (assumed length > 0)
*/
static inline void vec3f_normalize(float* v)
{
	vec3f_normalizen(v, v);
}


/*	Negate vector (new)
	param:	res		resultant vector (modified)
	param:	v		vector to negate
*/
static inline void vec3f_negaten(float* res, float* v)
{
	res[X] = -v[X];
	res[Y] = -v[Y];
	res[Z] = -v[Z];
}

/*	Negate vector
	param:	v		vector to negate (modified)
*/
static inline void vec3f_negate(float* v)
{
	vec3f_negaten(v, v);
}


/* Vector cross product
	param:	res		resultant vector (modified)
	param:	v0		first vector
	param:	v1		second vector
*/
static inline void vec3f_cross(float* res, float* v0, float* v1)
{
	res[X] = v0[Y]*v1[Z] - v0[Z]*v1[Y];
	res[Y] = v0[Z]*v1[X] - v0[X]*v1[Z];
	res[Z] = v0[X]*v1[Y] - v0[Y]*v1[X];
}


/*	Project vector onto unit vector (new)
	param:	res		resultant vector (modified)
	param:	v0		vector to project
	param:	v1		axis of projection (assumed to be unit length)
*/
static inline void vec3f_projectn(float* res, float* v0, float* v1)
{
	vec3f_scalen(res, v1, vec3f_dot(v0, v1));
}

/*	Project vector onto unit vector
	param:	v0		vector to project (modified)
	param:	v1		axis of projection (assumed to be unit length)
*/
static inline void vec3f_project(float* v0, float* v1)
{
	vec3f_projectn(v0, v0, v1);
}


/*	Reflect vector around unit vector (new)
	param:	res		resultant vector (modified)
	param:	v0		vector to reflect
	param:	v1		axis of reflection (assumed to be unit length)
*/
static inline void vec3f_reflectn(float* res, float* v0, float* v1)
{
	float a = 2.f*vec3f_dot(v0, v1);
	
	res[X] = v1[X]*a - v0[X];
	res[Y] = v1[Y]*a - v0[Y];
	res[Z] = v1[Z]*a - v0[Z];
}

/*	Reflect vector around unit vector
	param:	v0		vector to reflect (modified)
	param:	v1		axis of reflection (assumed to be unit length)
*/
static inline void vec3f_reflect(float* v0, float* v1)
{
	vec3f_reflectn(v0, v0, v1);
}


#endif
