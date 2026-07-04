#pragma once
#include <Eigen/Dense>

double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

struct GCDResult
{
  Eigen::VectorXd x;
  unsigned int iterations
  double residual_norm;
  double err_rel;
}

GCDResult gradiente_cd(const Eigen::MatrixXd& A, const Eigen::MatrixXd& b, const Eigen::MatrixXd& x_ex, const double res_tol = 1.0-12, const unsigned int it_max = 10000)
{
  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);     //vettore arbitrario di zeri. Ma nel while potrei fermarmi anche prima; come risolvo???
  Eigen::VectorXd res = b - A * x;
  Eigen::VectorXd p = res;   
  const double res_norm_0 = res.norm();

  unsigned int it = 0;

  while (it < it_max && res.norm() > res_tol * res_norm_0)      
  {
    const double alpha_k = ( (p.transpose() * res) / (p.transpose() * A * p) ).value();

    x = x + alpha_k * p;
    res = b - A * x;

    const double beta = ( (p.transpose() * A * res) / (p.transpose() * A * p) ).value();
    p = res - beta * p;
    it++;
  }

  const auto err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() :
                                              (x - x_ex).norm() / x_ex.norm();

  return {x, it, res.norm(), err_rel};
}
