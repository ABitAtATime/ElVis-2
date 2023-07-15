#include "ElVis.hpp"

int main() {
  ElVis elvis;
  while(elvis.isRunning()) {
    elvis.update();
    elvis.draw();
  }
  return 0;
}
