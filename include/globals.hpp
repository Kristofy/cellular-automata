#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED


const unsigned int TPS = 30;
const unsigned int CameraWidth = 256;
const unsigned int CameraHeight = 256;
const char * const Title = "Testing";
const unsigned int ChunkSize = 256;
const unsigned int ChunkOverlap = 10;
const unsigned int SpeedLimit = 9;

const float Gravity = 0.08f;
const float SandFriction = 0.92f;
const float WaterFriction = 0.97f;
static_assert(ChunkOverlap > SpeedLimit, "The SpeedLimit has to be lower then the overlap between chunks");


#endif // GLOBALS_H_INCLUDED
