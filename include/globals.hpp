#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED


const unsigned int TPS = 60;
const unsigned int CameraWidth = 256;
const unsigned int CameraHeight = 256;
const char * const Title = "Testing";
const unsigned int ChunkSize = 256;
const unsigned int SubChunkSize = 16;
const unsigned int ChunkOverlap = 6;
const unsigned int SpeedLimit = ChunkOverlap;
const unsigned int HorizontalChunks = 1;
const unsigned int VerticalChunks = 1;
const unsigned int WorldWidth = HorizontalChunks*ChunkSize;
const unsigned int WorldHeight = VerticalChunks*ChunkSize;

constexpr float Gravity = 0.17f;
constexpr float SandFriction = 0.18f;
constexpr float WaterFriction = 0.19f;
constexpr float Decay = 0.999f;

static_assert(ChunkOverlap >= SpeedLimit, "The SpeedLimit has to be lower then the overlap between chunks");
static_assert(ChunkSize % SubChunkSize == 0, "Chunks have to divided into sub-chunks");


#endif // GLOBALS_H_INCLUDED
