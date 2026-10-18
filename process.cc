#include "process.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace std;

namespace Loosh 
{




Node::OpStatusRef Process::frame_current(Node&process)  {
  MYLOGGER(trace_function, "LispExpr::frame_current(Node& process)", __func__, SLOG_FUNC_INFO);

  auto frames_ref_status = process[Index::Frames];
  //cout << "frame_current(): frames_ref_status " << frames_ref_status << "\n";

  if(!frames_ref_status.first) {
    cerr << "frames[] doesn't exist!\n";
    return frames_ref_status;
  }
  auto s = frames_ref_status.second.size();

  auto frame_ref_back_status = frames_ref_status.second.back();
  if(!frame_ref_back_status.first) {
    cerr << "frames back() doesn't exist!\n";
  }
  return frame_ref_back_status;
}



}