typedef unsigned long size_t;

#ifdef MT_STRIP_PREFIX
typedef struct {
  float x;
  float y;
} Vec2;
#else
typedef struct {
  float x;
  float y;
} mt_Vec2;
#define Vec2 mt_Vec2
#endif

Vec2 mt_Vec2add(Vec2 a, Vec2 b);
Vec2 mt_Vec2sub(Vec2 a, Vec2 b);
Vec2 mt_Vec2dot(Vec2 a, Vec2 b);
Vec2 mt_Vec2scale(Vec2 vec, float v);
void mt_Vec2scaleP(Vec2 *vec, float v);
void mt_Vec2transformP(Vec2 *vec, float x, float y);
Vec2 mt_Vec2norm(Vec2 v);
double factorial(size_t n);
float sqrtf(float num);
float powf(float x, float power);
double sin(double x);
double cos(double x);

#ifdef MT_IMPLEMENTATION
Vec2 mt_Vec2add(Vec2 a, Vec2 b){
  Vec2 result = {0};
  result.x += a.x+b.x;
  result.y += a.y+b.y;
  return result;
}

Vec2 mt_Vec2sub(Vec2 a, Vec2 b){
  Vec2 result = {0};
  result.x -= a.x+b.x;
  result.y -= a.y+b.y;
  return result;
}

Vec2 mt_Vec2dot(Vec2 a, Vec2 b){
  Vec2 result = {0};
  result.x += a.x*b.x;
  result.y += a.y*b.y;
  return result;
}

Vec2 mt_Vec2scale(Vec2 vec, float v){
  Vec2 result = {0};
  result.x += vec.x*v;
  result.y += vec.y*v;
  return result;
}

void mt_Vec2transformP(Vec2 *vec, float x, float y){
  vec->x += x;
  vec->y -= y;
}

void mt_Vec2scaleP(Vec2 *vec, float v){
  vec->x += vec->x*v;
  vec->y += vec->y*v;
}


double factorial(size_t n){
  float result = 1;
  for (size_t i=1; i<n+1; ++i){
    result *= i;
  }
  return result;
}

float sqrtf(float num){
  float h = 1e-3;
  float y = num/2;
  for (size_t i=0; i<4; ++i){
    y = 0.5 * (y + num / y);
  }
  return y;
}

float powf(float x, float power){
  float result = 1.0f;
  for (size_t i=0; i<power; ++i){
    result*=x;
  }
  return result;
}

Vec2 mt_Vec2norm(Vec2 v){
  Vec2 result = {0};
  float len = sqrtf(v.x*v.x + v.y*v.y);
  result.x = v.x/len;
  result.y = v.y/len;
  return result; 
}

double sin(double x){
  double result = x;
  size_t n = 3;
  int sign = -1; 
  for (size_t i=0; i<20; ++i){
    result += (powf(x, n)/factorial(n))*sign;
    n+=2;
    sign*=-1;
  }
  return result;
}

double cos(double x){
  double result = x;
  size_t n = 2;
  int sign = -1; 
  for (size_t i=0; i<20; ++i){
    result += (powf(x, n)/factorial(n))*sign;
    n+=2;
    sign*=-sign;
  }
  return result;
}
#endif // MT_IMPLEMENTATION

#ifdef MT_STRIP_PREFIX
#define Vec2add        mt_Vec2add
#define Vec2sub        mt_Vec2sub
#define Vec2dot        mt_Vec2dot
#define Vec2scale      mt_Vec2scale
#define Vec2scaleP     mt_Vec2scaleP
#define Vec2transformP mt_Vec2transformP
#define Vec2norm       mt_Vec2norm
#endif
