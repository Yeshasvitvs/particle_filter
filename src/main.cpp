
#include <iostream>
#include "particle_filter/particle.h"
#include "particle_filter/paricle_filter.h"
#include "particle_filter/identity_motionmodel.h"

int main(int argc, char **argv)
{
  const int particles_number = 100;

  Eigen::Vector2d mean = Eigen::Vector2d::Identity();
  Eigen::Matrix2d cov;
  cov << 1, 0.5, 0.5, 1;
  ParticleFilter pf(particles_number, mean, cov);

  MotionModel* motionModel = new IdentityMotionModel;

  Eigen::Vector2d u = Eigen::Vector2d::Identity();
  Eigen::Matrix2d noiseCov = Eigen::Matrix2d::Identity();


  pf.propagate(u, noiseCov, *motionModel);
  pf.resample(particles_number);

}
