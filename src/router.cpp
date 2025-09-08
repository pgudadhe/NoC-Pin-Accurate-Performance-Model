// router.cpp
#include "router.h"
#define SIM_NUM 30

void router ::func()
{
  int sim_count;
  sim_count = 0;

  // functionality
  while (sim_count++ < SIM_NUM)
  {
    wait();
    if (in0.event())
    {
      pkt_sent++;
      cout << router_id.read() << " -> ";
    }
    if (in1.event())
    {
      pkt_sent++;
      cout << router_id.read() << " -> ";
    }
    if (in2.event())
    {
      pkt_sent++;
      cout << router_id.read() << " -> ";
    }
    if (in3.event())
    {
      pkt_sent++;
      cout << router_id.read() << " -> ";
    }
    if (in4.event())
    {
      pkt_sent++;
      cout << router_id.read() << " -> ";
    }
  }
}