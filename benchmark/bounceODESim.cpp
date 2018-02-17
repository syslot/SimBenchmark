//
// Created by kangd on 16.02.18.
//

#include <odeSim/World_RG.hpp>

#include "bounce.hpp"

int main() {

  // logger
  std::string path = "/tmp/ode_bounce";
  rai::Utils::logger->setLogPath(path);
  rai::Utils::logger->addVariableToLog(3, "vel_ball", "linear velocity of ball");
  rai::Utils::logger->addVariableToLog(3, "pos_ball", "position of ball");

  ode_sim::World_RG sim(800, 600, 0.5, ode_sim::NO_BACKGROUND);

  sim.setGravity(benchmark::gravity);
  sim.setLightPosition(benchmark::lightX, benchmark::lightY, benchmark::lightZ);

  // add objects
  // checkerboard
  auto checkerboard = sim.addCheckerboard(5.0, 100.0, 100.0, 0.1);
  checkerboard->setRestitutionCoefficient(1.0);
  checkerboard->setFrictionCoefficient(benchmark::friction);

  // ball
  auto ball = sim.addSphere(benchmark::ballR, benchmark::ballM);
  ball->setRestitutionCoefficient(benchmark::restitution);
  ball->setFrictionCoefficient(benchmark::friction);
  ball->setPosition(0, 0, benchmark::dropHeight);

  // camera relative position
  sim.cameraFollowObject(ball, {10, 0, 5});

  // iteration counter
  int cnt = 0;

  // simulation loop
  // press 'q' key to quit
  while (sim.visualizerLoop(benchmark::dt, 1)) {
    if (cnt++ < benchmark::simulationTime / benchmark::dt) {

      // log
      rai::Utils::logger->appendData("vel_ball", ball->getLinearVelocity().data());
      rai::Utils::logger->appendData("pos_ball", ball->getPosition().data());
    }

    sim.integrate(benchmark::dt);
  }
  return 0;
}