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
  	B = Eigen::MatrixXd::Random(n, n);		//metto while con ridefinizione della matrice cosi che il programma non si bloccca quando trova una matrice singolare o quasi singolare, ma rigenera randomicamente la matrice finchè non va bene

  Eigen::MatrixXd A = B.transpose() * B;    //cosi è SPD
  Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);

  Eigen::VectorXd b = A * x_ex;

  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);     //vettore arbitrario di zeri. Ma nel while potrei fermarmi anche prima; come risolvo???
  Eigen::VectorXd res = b - A * x;
  const double res_norm_0 = res.norm();
  Eigen::VectorXd p = res;   

  const unsigned int it_max = 10000;
  unsigned int it = 0;
  const double res_tol = 1.0e-12;

  std::cout.precision(2);
  std::cout<< std::scientific<< "Matrix Cond: "<< condA(A)<< std::endl;  //per capire quanto è condizionata la matrice che ho creato randomicamente

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

  std::cout.precision(4);
  std::cout<< std::scientific << "it"<< "/" << "it_max" << std::endl;
  std::cout<< std::scientific << it<< "/" << it_max << std::endl;
  std::cout<< std::scientific << "res"<< "/" << "res_tol" << std::endl;
  std::cout<< std::scientific << res.norm() / res_norm_0 << "/"<< res_tol << std::endl;
  std::cout<< std::scientific << "err_rel" << std::endl;
  std::cout<< std::scientific << err_rel << std::endl;
  std::cout<< std::scientific << "soluzione" << std::endl;
  std::cout<< std::scientific << x << std::endl;

  return 0;

}
