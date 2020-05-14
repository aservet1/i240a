#include <iostream>

#include "job.hh"
#include "command-stream.hh"
#include "multi-queues.hh"

static int cmp0(const Job& job1, const Job& job2) {
  int diff = job1.priority0 - job2.priority0;
  return (diff != 0) ? diff : job1.id.compare(job2.id);
}

static int cmp1(const Job& job1, const Job& job2) {
  int diff = job2.priority1 - job1.priority1;
  return (diff != 0) ? diff : job2.id.compare(job1.id);
}



MultiQueue::MultiQueue(std::ostream& out) : q0(cmp0), q1(cmp1), out(out) { }

void MultiQueue::enter(const Job& job) {
  q0.enqueue(job);
  out << "enter " << job << std::endl;
}

void MultiQueue::move() {
  if (q0.size() > 0) {
    Job j = q0.dequeue();
    q1.enqueue(j);
    out << "move " << j << std::endl;
  }
}

void MultiQueue::leave() {
  if (q1.size() > 0) {
    Job j = q1.dequeue();
    out << "leave " << j << std::endl;
  }
}

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " FILE_PATH" << std::endl;
    std::exit(1);
  }
  MultiQueue q(std::cout);
  CommandStream commandIn(argv[1]);
  for (std::unique_ptr<Command> commandP = commandIn.next();
       commandP != nullptr;
       commandP = commandIn.next()) {
    switch (commandP->cmd) {
    case Command::Cmd::ENTER: 
      q.enter(dynamic_cast<EnterCommand*>(commandP.get())->job);
      break;
    case Command::Cmd::MOVE:
      q.move();
      break;
    case Command::Cmd::LEAVE:
      q.leave();
      break;
    default:
      assert(false);
    }
  }
}
