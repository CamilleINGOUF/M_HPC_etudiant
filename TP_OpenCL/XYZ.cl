__kernel void xyz(const float  inputAlpha,
__global const float * inputX,
__global const float * inputY,
__global float * outputZ)
{
    int gid = get_global_id(0);
    outputZ[gid] =  inputAlpha * inputX[gid] + inputY[gid];
}