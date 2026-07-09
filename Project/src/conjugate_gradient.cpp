#include "conjugate_gradient.hpp"

// Implementation only

GCDResult gradiente_cd (const Eigen::MatrixXd& A, 
                        const Eigen::VectorXd& b, 
                        const double res_tol, 
                        const unsigned int it_max)
{
  Eigen::VectorXd x = Eigen::VectorXd::Zero(b.size());     // arbitrary vector of zeros
  Eigen::VectorXd res = b - A * x;      // initial residual r0 = b - A*x0
  Eigen::VectorXd p = res;              // initial direction p0 = r0
  const double res_norm_0 = res.norm();

  unsigned int it = 0;

  while (it < it_max && res.norm() > res_tol * res_norm_0)      
  {
    // alpha_k = (p_k^T * r_k)/(p_k^T * A * p_k)
    const double pAp = (p.transpose() * A * p).value();               // or p.dot(A*p)
    const double alpha_k = ( (p.transpose() * res) / pAp ).value();   // or p.dot(res)/pAp 

    x = x + alpha_k * p;    // x_k+1 = x_k + alpha_k * p_k
    res = b - A * x;        // r_k+1 = b - A * x_k+1
                            // recompute the residual from scratch each time to avoid accumulating error

    // beta_k = (p_k^T * A * res_k+1)/(p_k^T * A * p_k)
    const double beta = ( (p.transpose() * A * res) / pAp ).value();
    p = res - beta * p;     // p_k+1 = r_k+1 - beta_k * p_k
    it++;
  }

  const double res_rel = (res_norm_0 == 0.0) ? 0.0 :
                                              res.norm() / res_norm_0;
  return {x, it, res_rel};
}
