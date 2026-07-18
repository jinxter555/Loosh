#include "../net_ws.hh"


int main() {
  try {
    SimpleWebSocketServer server("0.0.0.0", 8080);
    server.run_echo_server();

  } catch(const exception&e) {
    cerr << "fatal error: " <<  e.what() << "\n";
  }
  return 0;
}