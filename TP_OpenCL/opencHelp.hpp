
#ifndef _OPENCHELP_HPP_
#define _OPENCHELP_HPP_

#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

#include <CL/cl.hpp>

namespace opencHelp
{

    class Random
    {
        std::mt19937 _engine;
        std::uniform_real_distribution<float> _distribution; 
        public:
        Random() : _engine(time(0)), _distribution(0.f, 1.f) 
        {
        }
        float rand()
        {
            return _distribution(_engine);
        }
    };

    class Chrono
    {
        std::chrono::time_point<std::chrono::system_clock> _t0;
        public:
        Chrono()
        {
            reset();
        }
        void reset()
        {
	    _t0 = std::chrono::system_clock::now();
        }
        double elapsed() const  // elapsed time in seconds
        {
	    std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
	    return std::chrono::duration<double>(t1 - _t0).count();
        }
    };

    std::string deviceTypeToString(cl_device_type type)
    {
        switch (type) 
        {
            case CL_DEVICE_TYPE_CPU: return "CL_DEVICE_TYPE_CPU";
            case CL_DEVICE_TYPE_GPU: return "CL_DEVICE_TYPE_GPU";
            case CL_DEVICE_TYPE_ACCELERATOR: return "CL_DEVICE_TYPE_ACCELERATOR";
            case CL_DEVICE_TYPE_DEFAULT: return "CL_DEVICE_TYPE_DEFAULT";
            case CL_DEVICE_TYPE_CUSTOM: return "CL_DEVICE_TYPE_CUSTOM";
            default: return "unknown device type";
        }
    }

    void printPlatformsAndDevices()
    {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms); 
        if (platforms.empty())
        {
            std::cout << "Error: no OpenCL platform found" << std::endl;
            exit(-1);
        }
        for (unsigned i=0; i<platforms.size(); i++)
        {
            std::cout << "iPlatform " << i << ": " 
                << platforms[i].getInfo<CL_PLATFORM_NAME>() << std::endl;
            std::vector<cl::Device> devices;
            platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &devices); 
            if (devices.empty())
            {
                std::cout << "Error: no OpenCL device found" << std::endl;
                exit(-1);
            }
            for (unsigned j=0; j<devices.size(); j++)
            {
                std::cout << "  iDevice " << j << ": " 
                    << opencHelp::deviceTypeToString(devices[j].getInfo<CL_DEVICE_TYPE>()) << "; " 
                    << devices[j].getInfo<CL_DEVICE_VENDOR>() << "; " 
                    << devices[j].getInfo<CL_DEVICE_NAME>() << std::endl;
            }
        }
    }

    void getPlatformAndDevice(unsigned iPlatform, cl::Platform & refPlatform, unsigned iDevice, cl::Device & refDevice)
    {
        // get platform
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        if (iPlatform >= platforms.size())
        {
            std::cout << "Error: invalid iPlatform (" << iPlatform << ")" << std::endl;
            exit(-1);
        }
        refPlatform = platforms[iPlatform];
        std::cout << "Using iPlatform " << iPlatform << std::endl;

        // get device
        std::vector<cl::Device> devices;
        refPlatform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
        if (iDevice >= devices.size())
        {
            std::cout << "Error: invalid iDevice (" << iDevice << ")" << std::endl;
            exit(-1);
        }
        refDevice = devices[iDevice];
        std::cout << "Using iDevice " << iDevice << std::endl;
    }

    cl::Device getDevice(unsigned iPlatform, unsigned iDevice)
    {
        cl::Platform platform;
        cl::Device device;
        getPlatformAndDevice(iPlatform, platform, iDevice, device);
        return device;
    }

    std::string readKernelFile(const std::string & filename)
    {
        // open file
        std::ifstream fileStream(filename);
        if (not fileStream.is_open())
        {
            std::cout << "Error: failed to open kernel file (" << filename << ")" << std::endl;
            exit(-1);
        }
        // read file into a string
        std::ostringstream stringStream;
        stringStream << fileStream.rdbuf();
        return stringStream.str();
    }

    bool validateResult(const std::vector<float> & result, const std::vector<float> & expected, float epsilon)
    {
        assert(result.size() == expected.size());
        float error = 0.0;
        float reference = 0.0;
        for (unsigned k=0; k<result.size(); k++)
	{
            float delta = result[k] - expected[k];
            error += delta * delta;
            reference += expected[k] * expected[k];
        }
        if (reference < 1e-6)
            return false;
        else
            return sqrtf(error) / sqrtf(reference) < epsilon;
    }

    std::string errorToString(int error)
    {
        switch (error) 
        {
            // awk 'NF==0{next} NR==119,NR==178{print "case " $2 ": return \"" $2 "\";"}' /usr/include/CL/cl.h
            case CL_SUCCESS: return "CL_SUCCESS";
            case CL_DEVICE_NOT_FOUND: return "CL_DEVICE_NOT_FOUND";
            case CL_DEVICE_NOT_AVAILABLE: return "CL_DEVICE_NOT_AVAILABLE";
            case CL_COMPILER_NOT_AVAILABLE: return "CL_COMPILER_NOT_AVAILABLE";
            case CL_MEM_OBJECT_ALLOCATION_FAILURE: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
            case CL_OUT_OF_RESOURCES: return "CL_OUT_OF_RESOURCES";
            case CL_OUT_OF_HOST_MEMORY: return "CL_OUT_OF_HOST_MEMORY";
            case CL_PROFILING_INFO_NOT_AVAILABLE: return "CL_PROFILING_INFO_NOT_AVAILABLE";
            case CL_MEM_COPY_OVERLAP: return "CL_MEM_COPY_OVERLAP";
            case CL_IMAGE_FORMAT_MISMATCH: return "CL_IMAGE_FORMAT_MISMATCH";
            case CL_IMAGE_FORMAT_NOT_SUPPORTED: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
            case CL_BUILD_PROGRAM_FAILURE: return "CL_BUILD_PROGRAM_FAILURE";
            case CL_MAP_FAILURE: return "CL_MAP_FAILURE";
            case CL_MISALIGNED_SUB_BUFFER_OFFSET: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
            case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
            case CL_COMPILE_PROGRAM_FAILURE: return "CL_COMPILE_PROGRAM_FAILURE";
            case CL_LINKER_NOT_AVAILABLE: return "CL_LINKER_NOT_AVAILABLE";
            case CL_LINK_PROGRAM_FAILURE: return "CL_LINK_PROGRAM_FAILURE";
            case CL_DEVICE_PARTITION_FAILED: return "CL_DEVICE_PARTITION_FAILED";
            case CL_KERNEL_ARG_INFO_NOT_AVAILABLE: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";
            case CL_INVALID_VALUE: return "CL_INVALID_VALUE";
            case CL_INVALID_DEVICE_TYPE: return "CL_INVALID_DEVICE_TYPE";
            case CL_INVALID_PLATFORM: return "CL_INVALID_PLATFORM";
            case CL_INVALID_DEVICE: return "CL_INVALID_DEVICE";
            case CL_INVALID_CONTEXT: return "CL_INVALID_CONTEXT";
            case CL_INVALID_QUEUE_PROPERTIES: return "CL_INVALID_QUEUE_PROPERTIES";
            case CL_INVALID_COMMAND_QUEUE: return "CL_INVALID_COMMAND_QUEUE";
            case CL_INVALID_HOST_PTR: return "CL_INVALID_HOST_PTR";
            case CL_INVALID_MEM_OBJECT: return "CL_INVALID_MEM_OBJECT";
            case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
            case CL_INVALID_IMAGE_SIZE: return "CL_INVALID_IMAGE_SIZE";
            case CL_INVALID_SAMPLER: return "CL_INVALID_SAMPLER";
            case CL_INVALID_BINARY: return "CL_INVALID_BINARY";
            case CL_INVALID_BUILD_OPTIONS: return "CL_INVALID_BUILD_OPTIONS";
            case CL_INVALID_PROGRAM: return "CL_INVALID_PROGRAM";
            case CL_INVALID_PROGRAM_EXECUTABLE: return "CL_INVALID_PROGRAM_EXECUTABLE";
            case CL_INVALID_KERNEL_NAME: return "CL_INVALID_KERNEL_NAME";
            case CL_INVALID_KERNEL_DEFINITION: return "CL_INVALID_KERNEL_DEFINITION";
            case CL_INVALID_KERNEL: return "CL_INVALID_KERNEL";
            case CL_INVALID_ARG_INDEX: return "CL_INVALID_ARG_INDEX";
            case CL_INVALID_ARG_VALUE: return "CL_INVALID_ARG_VALUE";
            case CL_INVALID_ARG_SIZE: return "CL_INVALID_ARG_SIZE";
            case CL_INVALID_KERNEL_ARGS: return "CL_INVALID_KERNEL_ARGS";
            case CL_INVALID_WORK_DIMENSION: return "CL_INVALID_WORK_DIMENSION";
            case CL_INVALID_WORK_GROUP_SIZE: return "CL_INVALID_WORK_GROUP_SIZE";
            case CL_INVALID_WORK_ITEM_SIZE: return "CL_INVALID_WORK_ITEM_SIZE";
            case CL_INVALID_GLOBAL_OFFSET: return "CL_INVALID_GLOBAL_OFFSET";
            case CL_INVALID_EVENT_WAIT_LIST: return "CL_INVALID_EVENT_WAIT_LIST";
            case CL_INVALID_EVENT: return "CL_INVALID_EVENT";
            case CL_INVALID_OPERATION: return "CL_INVALID_OPERATION";
            case CL_INVALID_GL_OBJECT: return "CL_INVALID_GL_OBJECT";
            case CL_INVALID_BUFFER_SIZE: return "CL_INVALID_BUFFER_SIZE";
            case CL_INVALID_MIP_LEVEL: return "CL_INVALID_MIP_LEVEL";
            case CL_INVALID_GLOBAL_WORK_SIZE: return "CL_INVALID_GLOBAL_WORK_SIZE";
            case CL_INVALID_PROPERTY: return "CL_INVALID_PROPERTY";
            case CL_INVALID_IMAGE_DESCRIPTOR: return "CL_INVALID_IMAGE_DESCRIPTOR";
            case CL_INVALID_COMPILER_OPTIONS: return "CL_INVALID_COMPILER_OPTIONS";
            case CL_INVALID_LINKER_OPTIONS: return "CL_INVALID_LINKER_OPTIONS";
            case CL_INVALID_DEVICE_PARTITION_COUNT: return "CL_INVALID_DEVICE_PARTITION_COUNT";
            default: return "unknown error";
        }
    }

}

#endif

