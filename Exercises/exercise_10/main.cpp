#include <iostream>
#include <cmath>      //per abs
#include <Eigen/Dense>
#include "gradiente_cd.hpp"

Eigen::MatrixXd generaSPD(unsigned int n)
{
  const double tol = 1.0e-15;
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n,n);
  while (std::abs(B.determinant()) < tol)
    B = Eigen::MatrixXd::Random(n, n);
  return B.transpose() * B;
} 

void stampa(const std::string& nome, const GCDResult& r, const double res_tol, const unsigned int it_max)
{
  std::cout.precision(4);
  std::cout << "--- " << nome << " ---\n";
  std::cout<< std::scientific << "it      : " << r.iterations << "/" << it_max << "\n";
  std::cout<< std::scientific << "res_rel : " << r.res_norm_rel << " (tol: " << res_tol << ")\n";
  std::cout<< std::scientific << "err_rel : " << r.err_rel << "\n";
  std::cout<< std::scientific << "x       : " << r.x.transpose() << "\n\n";
}

bool check (const GCDResult& r, const double res_tol, const unsigned int it_max)
{
  if (r.iterations >= it_max) {
    std::cerr << " FAIL: raggiunto il numero massimo di iterazioni\n";
    return false; }
  
  if (r.res_norm_rel > res_tol) {
    std::cerr << " FAIL: residuo relativo superato\n";
    return false; }

  std::cout << " PASS\n\n";
  return true;
}

int main(int argc, char **argv) 
{
  const double res_tol = 1.0e-12;
  bool ok1, ok2;

  {
    unsigned int n = 3;
    const unsigned int it_max1 = 100*n;
    Eigen::MatrixXd A = generaSPD(n);
    Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
    Eigen::VectorXd b = A * x_ex;
    auto r = gradiente_cd(A, b, x_ex, res_tol, it_max1);
    stampa("TEST 1: n = 3, x_ex = ones", r, res_tol, it_max1);
    ok1 = check(r, res_tol, it_max1);
  }

  {
    unsigned int n = 50;
    const unsigned int it_max2 = 100*n;
    Eigen::MatrixXd A = generaSPD(n);
    Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
    Eigen::VectorXd b = A * x_ex;
    auto r = gradiente_cd(A, b, x_ex, res_tol, it_max2);
    stampa("TEST 2: n = 50, x_ex = ones", r, res_tol, it_max2);
    ok2 = check(r, res_tol, it_max2);
  }

  if (ok1 && ok2) {
    std::cout << " Tutti i test superati. \n";
    return EXIT_SUCCESS;
  } else {
    std::cerr << " Uno dei test è fallito. \n";
    return EXIT_FAILURE;
  }
}
