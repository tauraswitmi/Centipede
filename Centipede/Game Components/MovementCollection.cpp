#include "MovementCollection.h"

const OffsetArray MovementCollection::OffsetsStraightRight = OffsetArray(1, 0);
const OffsetArray MovementCollection::OffsetsTurnUpEndRight = OffsetArray(0, -1);
const OffsetArray MovementCollection::OffsetsTurnDownEndRight = OffsetArray(0, 1);
const OffsetArray MovementCollection::OffsetsStraightLeft = OffsetArray(-1, 0);
const OffsetArray MovementCollection::OffsetsTurnUpEndLeft = OffsetArray(0, -1);
const OffsetArray MovementCollection::OffsetsTurnDownEndLeft = OffsetArray(0, 1);

// Note: In this demoe, I move one cell per frame, so I only need one movement offset per direction.
// If your centipede takes 8 frame to move fro mone cell to another, then these offset collection would 
// need to be an array of 8 offsets, one for each frame. The sprite position at frame i would be
// previous cell center + ith offset value