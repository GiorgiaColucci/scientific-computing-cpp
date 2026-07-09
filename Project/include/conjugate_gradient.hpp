#pragma once
#include <Eigen/Dense>

// Solo dichiarazione e struct

struct GCDResult
{
  Eigen::VectorXd x;
  unsigned int iterations;
  double res_norm_rel;
};

GCDResult gradiente_cd (const Eigen::MatrixXd& A, 
                        const Eigen::VectorXd& b,  
                        const double res_tol, 
                        const unsigned int it_max);