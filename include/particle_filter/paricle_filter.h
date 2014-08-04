#ifndef PARTICLE_FILTER_H
#define PARTICLE_FILTER_H

#include "particle_filter/particle.h"
#include <Eigen/Core>
#include "particle_filter/motion_model.h"
#include "particle_filter/sensor_model.h"
#include "articulation_model.h"

template <class ParticleType>
class ParticleFilter
{
public:
  ParticleFilter(const std::vector <Particle <ParticleType> >& particles);
  ParticleFilter(const int& size, const Eigen::VectorXd& mean, const Eigen::MatrixXd& cov);
  ParticleFilter(const int& size, const Eigen::VectorXd &rigid_mean, const Eigen::MatrixXd &rigid_cov,
                 const Eigen::VectorXd &rotational_mean, const Eigen::MatrixXd &rotational_cov,
                 const Eigen::VectorXd &prismatic_mean, const Eigen::MatrixXd &prismatic_cov);
  ParticleFilter(const int &size, articulation_model_msgs::ModelMsg &model);
  ParticleFilter(const int& size, articulation_model_msgs::ModelMsg& model,
                 const MotionModel<ArticulationModelPtr> &motion_model, const Eigen::MatrixXd& rigid_cov,
                 const Eigen::MatrixXd &rotational_cov, const Eigen::MatrixXd& prismatic_cov);


  virtual ~ParticleFilter();

  bool normalize();

  bool normalizeWeights();

  bool normalizeLogWeights();

  void sortParticles();

  void weightsToLogWeights();

  void logWeightsToWeights();

  void printParticles() const;

  bool getLogLikelihoodsFlag() const;

  void setLogLikelihoodsFlag(const bool& flag);

  double getWeightsSum()const;

  Eigen::VectorXd getWeightedAvg(const double& particles_fraction);

  virtual void propagate(const Eigen::VectorXd& u, const Eigen::MatrixXd& noiseCov,
                         const MotionModel<ParticleType>& model);

  template <class ZType> void correct(const ZType z, const Eigen::MatrixXd& noiseCov,
                       const SensorModel<ParticleType, ZType>& model);

  virtual bool resample(const int& particles_number);

  std::vector <Particle <ParticleType> > particles;


private:
  bool logLikelihoods_;
  uint freemodel_samples_;

};

#endif // PARTICLE_FILTER_H
