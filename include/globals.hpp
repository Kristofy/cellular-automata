#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED


const unsigned int TPS = 30;
const unsigned int CameraWidth = 512;
const unsigned int CameraHeight = 512;
const char * const Title = "Testing";
const unsigned int ChunkSize = 128;
const unsigned int ChunkOverlap = 12;
const unsigned int SpeedLimit = 10;
const unsigned int HorizontalChunks = 4;
const unsigned int VerticalChunks = 4;
const unsigned int WorldWidth = HorizontalChunks*ChunkSize;
const unsigned int WorldHeight = VerticalChunks*ChunkSize;

constexpr float Gravity = 0.17f;
constexpr float SandFriction = 0.18f;
constexpr float WaterFriction = 0.19f;
constexpr float Decay = 0.999f;

static_assert(ChunkOverlap > SpeedLimit, "The SpeedLimit has to be lower then the overlap between chunks");
//static_assert((SpeedLimit+Gravity)*SandFriction/(float)SpeedLimit < 1.0f, "Sand would never stop moving");
//static_assert((SpeedLimit+Gravity)*WaterFriction*WaterFriction/(float)SpeedLimit < 1.0f, "Water would never stop moving");



#endif // GLOBALS_H_INCLUDED
