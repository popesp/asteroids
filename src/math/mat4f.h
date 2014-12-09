#ifndef	MAT4F
#define	MAT4F


#include	<math.h>


static inline void swap(float* a, float* b)
{
	float t;
	
	t = *a;
	*a = *b;
	*b = t;
}


/*	Copy matrix
	param:	dst		destination matrix (modified)
	param:	src		source matrix
*/
static inline void mat4f_copy(float* dst, float* src)
{
	int i;
	
	for (i = 0; i < 16; i++)
		dst[i] = src[i];
}


/*	Set all matrix elements to 0
	param:	m		matrix to clear (modified)
*/
static inline void mat4f_clear(float* m)
{
	int i;
	
	for (i = 0; i < 16; i++)
		m[i] = 0.f;
}

/*	Set matrix to the identity
	param:	m		matrix to be set (modified)
*/
static inline void mat4f_identity(float* m)
{
	mat4f_clear(m);
	m[0] = m[5] = m[10] = m[15] = 1.f;
}


/*	Find transpose of matrix
	param:	m		matrix to find transpose of (modified)
*/
static inline void mat4f_transpose(float* m)
{
	swap(m+1, m+4);
	swap(m+2, m+8);
	swap(m+3, m+12);
	swap(m+6, m+9);
	swap(m+7, m+13);
	swap(m+11, m+14);
}

/*	Find transpose of matrix
	param:	res		resultant matrix (modified)
	param:	m		matrix to find transpose of
*/
static inline void mat4f_transposen(float* res, float* m)
{
	mat4f_copy(res, m);
	mat4f_transpose(res);
}


/*	Multiply matrix by other matrix (new)
	param:	res		resultant matrix (modified)
	param:	m0		matrix multiplicand
	param:	m1		matrix multiplier
*/
static inline void mat4f_multiplyn(float* res, float* m0, float* m1)
{
	int r, c;
	
	for (c = 0; c < 16; c += 4)
		for (r = 0; r < 4; r++)
			res[c+r] =	m0[r+0]	*m1[c+0]+
						m0[r+4]	*m1[c+1]+
						m0[r+8]	*m1[c+2]+
						m0[r+12]*m1[c+3];
}

/*	Multiply matrix by other matrix
	param:	m0		matrix multiplicand (modified)
	param:	m1		matrix multiplier
*/
static inline void mat4f_multiply(float* m0, float* m1)
{
	float n[16];
	
	mat4f_copy(n, m0);
	mat4f_multiplyn(m0, n, m1);
}


/*	Set matrix to perspective projection
	param:	m		matrix to be set (modified)
	param:	l		left clipping plane
	param:	r		right clipping plane
	param:	b		bottom clipping plane
	param:	t		top clipping plane
	param:	n		near clipping plane
	param:	f		far clipping plane
*/
static inline void mat4f_frustum(float* m, float l, float r, float b, float t, float n, float f)
{
	m[0] = 2.f*n/(r-l);
	m[1] = m[2] = m[3] = m[4] = 0.f;
	m[5] = 2.f*n/(t-b);
	m[6] = m[7] = 0.f;
	m[8] = (r+l)/(r-l);
	m[9] = (t+b)/(t-b);
	m[10] = -(f+n)/(f-n);
	m[11] = -1.f;
	m[12] = m[13] = 0.f;
	m[14] = -(2.f*f*n)/(f-n);
	m[15] = 0.f;
}

/*	Set matrix to orthographic projection
	param:	m		matrix to be set (modified)
	param:	l		left clipping plane
	param:	r		right clipping plane
	param:	b		bottom clipping plane
	param:	t		top clipping plane
	param:	n		near clipping plane
	param:	f		far clipping plane
*/
static inline void mat4f_ortho(float* m, float l, float r, float b, float t, float n, float f)
{
	m[0] = 2.f/(r-l);
	m[1] = m[2] = m[3] = m[4] = 0.f;
	m[5] = 2.f/(t-b);
	m[6] = m[7] = m[8] = m[9] = 0.f;
	m[10] = -2.f/(f-n);
	m[11] = 0.f;
	m[12] = -(r+l)/(r-l);
	m[13] = -(t+b)/(t-b);
	m[14] = -(f+n)/(f-n);
	m[15] = 1.f;
}


/*	Set matrix to translation transformation
	param:	m		matrix to be set (modified)
	param:	x		translation in x-axis
	param:	y		translation in y-axis
	param:	z		translation in z-axis
*/
static inline void mat4f_translate(float* m, float x, float y, float z)
{
	mat4f_identity(m);
	
	m[12] = x;
	m[13] = y;
	m[14] = z;
}

/*	Multiply matrix by translation transformation (new)
	param:	res		resultant matrix (modified)
	param:	m		original matrix
	param:	x		translation in x-axis
	param:	y		translation in y-axis
	param:	z		translation in z-axis
*/
static inline void mat4f_translatemuln(float* res, float* m, float x, float y, float z)
{
	float n[16];
	
	mat4f_translate(n, x, y, z);
	mat4f_multiplyn(res, m, n);
}

/*	Multiply matrix by translation transformation
	param:	m		original matrix (modified)
	param:	x		translation in x-axis
	param:	y		translation in y-axis
	param:	z		translation in z-axis
*/
static inline void mat4f_translatemul(float* m, float x, float y, float z)
{
	float n[16];
	
	mat4f_translate(n, x, y, z);
	mat4f_multiply(m, n);
}


/*	Set matrix to non-uniform scale transformation
	param:	m		matrix to be set (modified)
	param:	x		scale along x-axis
	param:	y		scale along y-axis
	param:	z		scale along z-axis
*/
static inline void mat4f_scale(float* m, float x, float y, float z)
{
	mat4f_clear(m);
	
	m[0] = x;
	m[5] = y;
	m[10] = z;
	m[15] = 1.f;
}

/*	Multiply matrix by non-uniform scale transformation (new)
	param:	res		resultant matrix (modified)
	param:	m		original matrix
	param:	x		scale along x-axis
	param:	y		scale along y-axis
	param:	z		scale along z-axis
*/
static inline void mat4f_scalemuln(float* res, float* m, float x, float y, float z)
{
	float n[16];
	
	mat4f_scale(n, x, y, z);
	mat4f_multiplyn(res, m, n);
}

/*	Multiply matrix by non-uniform scale transformation
	param:	m		original matrix (modified)
	param:	x		scale along x-axis
	param:	y		scale along y-axis
	param:	z		scale along z-axis
*/
static inline void mat4f_scalemul(float* m, float x, float y, float z)
{
	float n[16];
	
	mat4f_scale(n, x, y, z);
	mat4f_multiply(m, n);
}


/*	Set matrix to rotation around x-axis
	param:	m		matrix to be set (modified)
	param:	angle	angle of rotation
*/
static inline void mat4f_rotatex(float* m, float angle)
{
	angle *= M_PI/180.f;
	
	mat4f_identity(m);
	
	m[5] = cosf(angle);
	m[6] = sinf(angle);
	m[9] = -sinf(angle);
	m[10] = cosf(angle);
}

/*	Multiply matrix by rotation around x-axis (new)
	param:	res		resultant matrix (modified)
	param:	m		original matrix
	param:	angle	angle of rotation
*/
static inline void mat4f_rotatexmuln(float* res, float* m, float angle)
{
	float n[16];
	
	mat4f_rotatex(n, angle);
	mat4f_multiplyn(res, m, n);
}

/*	Multiply matrix by rotation around x-axis
	param:	m		original matrix (modified)
	param:	angle	angle of rotation
*/
static inline void mat4f_rotatexmul(float* m, float angle)
{
	float n[16];
	
	mat4f_rotatex(n, angle);
	mat4f_multiply(m, n);
}


/*	Set matrix to rotation around y-axis
	param:	m		matrix to be set (modified)
	param:	angle	angle of rotation
*/
static inline void mat4f_rotatey(float* m, float angle)
{
	angle *= M_PI/180.f;
	
	mat4f_identity(m);
	
	m[0] = cosf(angle);
	m[2] = -sinf(angle);
	m[8] = sinf(angle);
	m[10] = cosf(angle);
}

/*	Multiply matrix by rotation around y-axis (new)
	param:	res		resultant matrix (modified)
	param:	m		original matrix
	param:	angle	angle of rotation
*/
static inline void mat4f_rotateymuln(float* res, float* m, float angle)
{
	float n[16];
	
	mat4f_rotatey(n, angle);
	mat4f_multiplyn(res, m, n);
}

/*	Multiply matrix by rotation around y-axis
	param:	m		original matrix (modified)
	param:	angle	angle of rotation
*/
static inline void mat4f_rotateymul(float* m, float angle)
{
	float n[16];
	
	mat4f_rotatey(n, angle);
	mat4f_multiply(m, n);
}


/*	Set matrix to rotation around z-axis
	param:	m		matrix to be set (modified)
	param:	angle	angle of rotation
*/
static inline void mat4f_rotatez(float* m, float angle)
{
	angle *= M_PI/180.f;
	
	mat4f_identity(m);
	
	m[0] = cosf(angle);
	m[1] = sinf(angle);
	m[4] = -sinf(angle);
	m[5] = cosf(angle);
}

/*	Multiply matrix by rotation around z-axis (new)
	param:	res		resultant matrix (modified)
	param:	m		original matrix
	param:	angle	angle of rotation
*/
static inline void mat4f_rotatezmuln(float* res, float* m, float angle)
{
	float n[16];
	
	mat4f_rotatez(n, angle);
	mat4f_multiplyn(res, m, n);
}

/*	Multiply matrix by rotation around z-axis
	param:	m		original matrix (modified)
	param:	angle	angle of rotation
*/
static inline void mat4f_rotatezmul(float* m, float angle)
{
	float n[16];
	
	mat4f_rotatez(n, angle);
	mat4f_multiply(m, n);
}


/*	Find the inverse of a matrix (new)
	param:	res		resultant matrix (modified) (assumed invertible)
	param:	m		original matrix
*/
static inline void mat4f_invertn(float* res, float* m)
{
	float det;
	int i;
	
	// ugly math; taken from GLU's inverse implementation
	res[0]	=	m[5]  * m[10] * m[15] -
				m[5]  * m[11] * m[14] -
				m[9]  * m[6]  * m[15] +
				m[9]  * m[7]  * m[14] +
				m[13] * m[6]  * m[11] -
				m[13] * m[7]  * m[10];
	
	res[4]	=	-m[4] * m[10] * m[15] +
				m[4]  * m[11] * m[14] +
				m[8]  * m[6]  * m[15] -
				m[8]  * m[7]  * m[14] -
				m[12] * m[6]  * m[11] +
				m[12] * m[7]  * m[10];
	
	res[8]	=	m[4]  * m[9]  * m[15] -
				m[4]  * m[11] * m[13] -
				m[8]  * m[5]  * m[15] +
				m[8]  * m[7]  * m[13] +
				m[12] * m[5]  * m[11] -
				m[12] * m[7]  * m[9];
	
	res[12]	=	-m[4] * m[9]  * m[14] +
				m[4]  * m[10] * m[13] +
				m[8]  * m[5]  * m[14] -
				m[8]  * m[6]  * m[13] -
				m[12] * m[5]  * m[10] +
				m[12] * m[6]  * m[9];
	
	res[1]	=	-m[1] * m[10] * m[15] +
				m[1]  * m[11] * m[14] +
				m[9]  * m[2]  * m[15] -
				m[9]  * m[3]  * m[14] -
				m[13] * m[2]  * m[11] +
				m[13] * m[3]  * m[10];
	
	res[5]	=	m[0]  * m[10] * m[15] -
				m[0]  * m[11] * m[14] -
				m[8]  * m[2]  * m[15] +
				m[8]  * m[3]  * m[14] +
				m[12] * m[2]  * m[11] -
				m[12] * m[3]  * m[10];
	
	res[9]	=	-m[0] * m[9]  * m[15] +
				m[0]  * m[11] * m[13] +
				m[8]  * m[1]  * m[15] -
				m[8]  * m[3]  * m[13] -
				m[12] * m[1]  * m[11] +
				m[12] * m[3]  * m[9];
	
	res[13]	=	m[0]  * m[9]  * m[14] -
				m[0]  * m[10] * m[13] -
				m[8]  * m[1]  * m[14] +
				m[8]  * m[2]  * m[13] +
				m[12] * m[1]  * m[10] -
				m[12] * m[2]  * m[9];
	
	res[2]	=	m[1]  * m[6]  * m[15] -
				m[1]  * m[7]  * m[14] -
				m[5]  * m[2]  * m[15] +
				m[5]  * m[3]  * m[14] +
				m[13] * m[2]  * m[7] -
				m[13] * m[3]  * m[6];
	
	res[6]	=	-m[0] * m[6]  * m[15] +
				m[0]  * m[7]  * m[14] +
				m[4]  * m[2]  * m[15] -
				m[4]  * m[3]  * m[14] -
				m[12] * m[2]  * m[7] +
				m[12] * m[3]  * m[6];
	
	res[10]	=	m[0]  * m[5]  * m[15] -
				m[0]  * m[7]  * m[13] -
				m[4]  * m[1]  * m[15] +
				m[4]  * m[3]  * m[13] +
				m[12] * m[1]  * m[7] -
				m[12] * m[3]  * m[5];
	
	res[14]	=	-m[0] * m[5]  * m[14] +
				m[0]  * m[6]  * m[13] +
				m[4]  * m[1]  * m[14] -
				m[4]  * m[2]  * m[13] -
				m[12] * m[1]  * m[6] +
				m[12] * m[2]  * m[5];
	
	res[3]	=	-m[1] * m[6]  * m[11] +
				m[1]  * m[7]  * m[10] +
				m[5]  * m[2]  * m[11] -
				m[5]  * m[3]  * m[10] -
				m[9]  * m[2]  * m[7] +
				m[9]  * m[3]  * m[6];
	
	res[7]	=	m[0]  * m[6]  * m[11] -
				m[0]  * m[7]  * m[10] -
				m[4]  * m[2]  * m[11] +
				m[4]  * m[3]  * m[10] +
				m[8]  * m[2]  * m[7] -
				m[8]  * m[3]  * m[6];
	
	res[11]	=	-m[0] * m[5]  * m[11] +
				m[0]  * m[7]  * m[9] +
				m[4]  * m[1]  * m[11] -
				m[4]  * m[3]  * m[9] -
				m[8]  * m[1]  * m[7] +
				m[8]  * m[3]  * m[5];
	
	res[15]	=	m[0]  * m[5]  * m[10] -
				m[0]  * m[6]  * m[9] -
				m[4]  * m[1]  * m[10] +
				m[4]  * m[2]  * m[9] +
				m[8]  * m[1]  * m[6] -
				m[8]  * m[2]  * m[5];
	
	det = 1.f/(m[0] * res[0] + m[1] * res[4] + m[2] * res[8] + m[3] * res[12]);
	
	for (i = 0; i < 16; i++)
		res[i] *= det;
}

/*	Find the inverse of a matrix
	param:	m		original matrix (modified) (assumed invertible)
*/
static inline void mat4f_invert(float* m)
{
	float n[16];
	
	mat4f_invertn(n, m);
	mat4f_copy(m, n);
}


#endif
