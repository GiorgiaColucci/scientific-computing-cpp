#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int main(int argc, char **argv) 
{
  const double tol = 1.0e-15;
  unsigned int n = 3;

  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

  while (abs(B.determinant()) < tol)
    B = Eigen::MatrixXd::Random(n, n);

  Eigen::MatrixXd A = B.transpose() * B;
  Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);

  Eigen::VectorXd b = A * x_ex;

  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);
  Eigen::VectorXd res = b - A * x;
  double res_norm_0 = res.norm();

  const unsigned int it_max = 10000;
  unsigned int it = 0;
  const double res_tol = 1.0e-12;

  std::cout.precision(2);
  std::cout<< std::scientific<< "Matrix Cond: "<< condA(A)<< std::endl;

  while (it < it_max &&
         res.norm() > res_tol * res_norm_0)
  {
    const double alpha_k = ((res.transpose() * res) / (res.transpose() * A * res)).value();
    // const double alpha_k_dot = res.dot(res) / (res.dot(A * res));

    x = x + alpha_k * res;
    res = res - alpha_k * A * res;

    // res_norm_0 = x.norm(); // se lo lascio, il while usa ogni volta la norma della soluzione corrente come criterio di stop, e non l'r_0 iniziale

    it++;
  }

  const auto err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() :
                                              (x - x_ex).norm() / x_ex.norm();

  std::cout.precision(4);
  std::cout<< std::scientific<< "it"<< "/"<< "it_max"<< std::endl;
  std::cout<< std::scientific<< it<< "/"<< it_max<< std::endl;
  std::cout<< std::scientific<< "res"<< "/"<< "res_tol"<< std::endl;
  std::cout<< std::scientific<< res.norm() / res_norm_0<< "/"<< res_tol<< std::endl;
  std::cout<< std::scientific<< "err_rel"<< std::endl;
  std::cout<< std::scientific<< err_rel<< std::endl;
  std::cout<< std::scientific<< "soluzione"<< std::endl;
  std::cout<< std::scientific<< x << std::endl;


  return 0;
}
