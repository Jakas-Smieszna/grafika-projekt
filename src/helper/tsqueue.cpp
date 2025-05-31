#include "tsqueue.h"
#include "../mesh.h"

tsQueue<std::function<void()>> terrainGenQueue{};



