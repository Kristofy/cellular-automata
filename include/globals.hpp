#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

template<unsigned I> struct TwoPow{
  static const unsigned value = TwoPow<(I>>1)>::value + 1;
};
template<> struct TwoPow<1>{
  static const unsigned value = 0;
};

// TODO: ChunkDiv, ChunkMod, SubChunkDiv, SubChunkMod(?), static assert pow 2

const unsigned int TPS = 30;
const unsigned int CameraWidth = 512;
const unsigned int CameraHeight = 512;
const char * const Title = "Testing";
const unsigned int ChunkSize = 256;
const unsigned int SubChunkSize = 16;
const unsigned int SubChunks = ChunkSize / SubChunkSize;
const unsigned int SubChunkShift = TwoPow<SubChunkSize>::value;
const unsigned int ChunkOverlap = 6;
const unsigned int SpeedLimit = ChunkOverlap;
const unsigned int HorizontalChunks = 2;
const unsigned int VerticalChunks = 2;
const unsigned int WorldWidth = HorizontalChunks*ChunkSize;
const unsigned int WorldHeight = VerticalChunks*ChunkSize;
const unsigned int BaseEnergy = 2;

constexpr float Gravity = 0.17f;
constexpr float GravitySide = 0.7071f * Gravity;  // cos(45deg) * Gravity
constexpr float SandFriction = 0.1702f;
constexpr float WaterFriction = 0.2f;
constexpr float Decay = 0.999f;
constexpr float Mu = 0.01f;

static_assert(ChunkOverlap >= SpeedLimit, "The SpeedLimit has to be lower then the overlap between chunks");
static_assert(ChunkSize % SubChunkSize == 0, "Chunks have to divided into sub-chunks");


#endif // GLOBALS_H_INCLUDED
