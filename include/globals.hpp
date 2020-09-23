#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <cstdint>

// Utility checks
template<unsigned I> struct LogTwo{
  static const unsigned value = LogTwo<(I>>1)>::value + 1;
};
template<> struct LogTwo<1>{
  static const unsigned value = 0;
};

template<unsigned I> struct isPowerOfTwo{
  static const bool value = (I && (I&(I-1)) == 0);
};

// TODO:  ChunkMod, SubChunkMod(?)

const unsigned int TPS = 60;
const char * const Title = "Testing";
const unsigned int CameraWidth = 512;
const unsigned int CameraHeight = 512;
const unsigned int ChunkSize = 512;
const unsigned int SubChunkSize = 16;
const unsigned int ChunkOverlap = 6;
const unsigned int HorizontalChunks = 1;
const unsigned int VerticalChunks = 1;
const unsigned int BaseEnergy = 2;
const std::uint8_t UpdateMask = 0x0f;

constexpr float Gravity = 0.17f;
constexpr float SandFriction = 0.1702f;
constexpr float WaterFriction = 0.2f;
constexpr float Decay = 0.999f;
constexpr float Mu = 0.01f;

// Computed Constants
const unsigned int SubChunks = ChunkSize / SubChunkSize;
const unsigned int SubChunkShift = LogTwo<SubChunkSize>::value;
const signed int SpeedLimit = ChunkOverlap;
const unsigned int WorldWidth = HorizontalChunks*ChunkSize;
const unsigned int WorldHeight = VerticalChunks*ChunkSize;
const unsigned int ChunkShift = LogTwo<ChunkSize>::value;
const unsigned int ChunkMod = ChunkSize-1;
const unsigned int SubChunkMod = SubChunks-1;


constexpr float GravitySide = 0.7071f * Gravity;  // cos(45deg) * Gravity

// Checks
static_assert(ChunkOverlap >= SpeedLimit, "The SpeedLimit has to be lower then the overlap between chunks");
static_assert(isPowerOfTwo<ChunkSize>::value, "ChunkSize has to be a power of two");
static_assert(isPowerOfTwo<SubChunkSize>::value, "SubChunkSize has to be a power of two");
static_assert(ChunkSize >= SubChunkSize, "A SubChunk can not be bigger than a Chunk");


#endif // GLOBALS_H_INCLUDED
