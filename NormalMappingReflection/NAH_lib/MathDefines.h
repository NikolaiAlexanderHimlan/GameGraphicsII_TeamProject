//namespace nah {
//namespace math {
#define I0 0 /*int 0*/
#define F0 0.0f /*float 0.0f*/
#define D0 0.0 /*double 0.0*/

#define U unsigned
typedef U int uint;
typedef float ufloat;//TODO: make unsigned float
typedef double udouble;//TODO: make unsigned double

//Real number declaration
#define REAL_DOUBLE

#ifdef REAL_DOUBLE
typedef double real;
#define REAL_MAX DBL_MAX

#elif REAL_FLOAT
typedef float real;
#define REAL_MAX FLT_MAX
#endif
	//}
//}
