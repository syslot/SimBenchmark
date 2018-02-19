//---------------------------------//
//  This file is part of MuJoCo    //
//  Written by Emo Todorov         //
//  Copyright (C) 2017 Roboti LLC  //
//---------------------------------//

#include "mujoco.h"
#include "stdio.h"

char error[1000];
mjModel* m;
mjData* d;

int main(void)
{
  // activate MuJoCo Pro
  mj_activate("mjkey.txt");

  // load model from file and check for errors
  m = mj_loadXML("/home/kangd/git/benchmark/mjpro150/model/hello.xml", NULL, error, 1000);
  if( !m )
  {
    printf("%s\n", error);
    return 1;
  }

  // make data corresponding to model
  d = mj_makeData(m);

  // run simulation for 10 seconds
  while( d->time<10 ) {
    mj_step(m, d);
  }

  // free model and data, deactivate
  mj_deleteData(d);
  mj_deleteModel(m);
  mj_deactivate();

  return 0;
}