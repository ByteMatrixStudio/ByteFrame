#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  float x;
  float y;
} Vec2;

Vec2 Vec2add(Vec2 a, Vec2 b){
  Vec2 result = {0};
  result.x += a.x+b.x;
  result.y += a.y+b.y;
  return result;
}

Vec2 Vec2sub(Vec2 a, Vec2 b){
  Vec2 result = {0};
  result.x -= a.x+b.x;
  result.y -= a.y+b.y;
  return result;
}

Vec2 Vec2dot(Vec2 a, Vec2 b){
  Vec2 result = {0};
  result.x += a.x*b.x;
  result.y += a.y*b.y;
  return result;
}

Vec2 Vec2scale(Vec2 vec, float v){
  Vec2 result = {0};
  result.x += vec.x*v;
  result.y += vec.y*v;
  return result;
}



void Vec2print(Vec2 v){
  printf("[%f, %f]\n", v.x, v.y);
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




Vec2 Vec2norm(Vec2 v){
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

int main(void){
  Vec2 vec1 = {3.0f, 10000.0f};
  Vec2 vec2 = {7.0f, 8.0f};
  Vec2 sum = Vec2norm(vec1);
  Vec2print(sum);
  return 0;
}
