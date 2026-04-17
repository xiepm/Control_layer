#pragma once

#include <Eigen/Core>

#include <pinocchio/spatial/force.hpp>
#include <pinocchio/spatial/motion.hpp>
#include <pinocchio/spatial/se3.hpp>

namespace han::types {

using Scalar = double;
using Vector3 = Eigen::Vector3d;
using Vector6 = Eigen::Matrix<Scalar, 6, 1>;
using VectorX = Eigen::VectorXd;
using Matrix3 = Eigen::Matrix3d;
using Matrix6 = Eigen::Matrix<Scalar, 6, 6>;
using MatrixX = Eigen::MatrixXd;

using SE3 = pinocchio::SE3;
using Motion = pinocchio::Motion;
using Force = pinocchio::Force;

}  // namespace han::types
