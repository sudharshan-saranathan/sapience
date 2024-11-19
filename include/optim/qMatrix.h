#ifndef QMATRIX_H
#define QMATRIX_H

#define OPTIM_ENABLE_OPENMP
#define OPTIM_ENABLE_EIGEN_WRAPPERS

#include <iostream>
#include "optim.hpp"
#include "EigenLab.h"
#include "core/qInclude.h"

class qMatrix {
public:
   ~qMatrix() = default;
    qMatrix();

public:
    EigenLab::Parser<Eigen::MatrixXd> parser;
    EigenLab::Value <Eigen::MatrixXd> result;

public:
    void on_eval(QString);
    void on_init(QString);
    void on_init(QString, double& value);
};

#endif
