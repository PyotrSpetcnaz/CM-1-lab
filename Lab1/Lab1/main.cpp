#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

typedef float real;

//for input
const char* fia = "ia.txt";
const char* fdi = "di.txt";
const char* fal = "al.txt";
const char* fau = "au.txt";
const char* fF = "f.txt";

//for output
const char* ofia = "oia.txt";
const char* ofdi = "odi.txt";
const char* ofal = "oal.txt";
const char* ofau = "oau.txt";

//Профильный формат
typedef struct {
  unsigned int *ia; //Массив индексов 
  real *di; //Диагональные элементы
  real *al; //Нижний треугольник
  real *au; //Верхний треугольник
  unsigned int n; //Размерность матрицы
} matrix;

typedef struct {
  unsigned int n; //Размерность вектора
  real *elem;
}F,X;

typedef struct {
  unsigned int n; //Размерность вектора
  int *elem;
}D;

int readMatrix(matrix& m, unsigned int n, const char* sia, const char* sdi, const char* sal, const char* sau) {
  m.n = n;
  ifstream sfia(sia), sfdi(sdi), sfal(sal), sfau(sau);

  if (!sfia.is_open() || !sfdi.is_open() || !sfal.is_open() || !sfau.is_open()) {
    return 1;
  }
  m.ia = new unsigned int[n + 1];
  m.di = new real[n];

  for (int i = 0; i < n + 1; i++) {
    sfia >> m.ia[i];
    if (i != n + 1) sfdi >> m.di[i];
  }

  m.al = new real[m.ia[n] - 1];
  m.au = new real[m.ia[n] - 1];
  for (int i = 0; i < m.ia[n] - 1; i++) {
    sfal >> m.al[i];
    sfau >> m.au[i];
  }
  sfia.close();
  sfdi.close();
  sfal.close();
  sfau.close();
  return 0;
}

int readF(F& f, unsigned int n, const char* fF) {
  f.n = n;
  ifstream sfF(fF);
  
  if (!sfF.is_open()) {
      return 1; 
  }
  f.elem = new real[n];
  
  for(int i = 0; i < n + 1; n++) {
      sfF >> f.elem[i];
  }
  sfF.close();
  return 0;
}

int makeL(matrix& m, D& d) {
    d.n = m.n;
    d.elem = new int[d.n];
    for(int i = 0; i < d.n; i++) 
        m.di[i] >= 0 ? d.elem[i] = 1 : d.elem[i] = -1;

    m.di[0] = sqrt(abs(m.di[0]));    
    
    // for(int i = 0; i < m.n; i++) {
    //     m.di[i] = 
    //     for(int j = 0; j < m.ia[i] - m.ia[i+1]; j++) {
            
    //     }
    // }
    return 0;
}

int printMatrix(matrix& m, const char* sia, const char* sdi, const char* sal, const char* sau) {
  ofstream ofia(sia), ofdi(sdi), ofal(sal), ofau(sau);

  if (!ofia.is_open() || !ofdi.is_open() || !ofal.is_open() || !ofau.is_open()) {
    return 1;
  }

  for (int i = 0; i < m.n; i++) {
    ofia << m.ia[i] << " "; 
    ofdi << m.di[i] << " ";
  }
  ofia << m.ia[m.n] << " ";

  for (int i = 0; i < m.ia[m.n] - 1; i++) {
    ofal << m.al[i] << " ";
    ofau << m.au[i] << " ";
  }
 
  ofia.close();
  ofdi.close();
  ofal.close();
  ofau.close();
  return 0;
}

int main() {
  matrix m;
  readMatrix(m, 9, fia, fdi, fal, fau);
  printMatrix(m, ofia, ofdi, ofal, ofau);
  return 0;
}
