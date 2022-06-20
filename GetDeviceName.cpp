#include <windows.h>
#include <cstdio>
#define cudaSuccess 0
typedef int(__stdcall* cuInit)(unsigned int Flags);
typedef int(__stdcall* cuDeviceGetCount)(int* count);
typedef int(__stdcall* cuDeviceGetName)(char* name, int len, int dev);
int main() {
	HMODULE nvcudaLibrary = LoadLibraryA("nvcuda.dll");
	if (nvcudaLibrary != NULL) {
		cuInit cudaInit = (cuInit)GetProcAddress(nvcudaLibrary, "cuInit");
		cuDeviceGetCount cudaGetDeviceCount = (cuDeviceGetCount)GetProcAddress(nvcudaLibrary, "cuDeviceGetCount");
		cuDeviceGetName cudaDeviceGetName = (cuDeviceGetName)GetProcAddress(nvcudaLibrary, "cuDeviceGetName");
		if (cudaInit != NULL && cudaGetDeviceCount != NULL && cudaDeviceGetName != NULL) {
			if (cudaInit(0) == cudaSuccess) {
				/// <summary>
				/// Call cuInit to initialize cuda driver,
				/// Otherwise, it will throw exception CUDA_ERROR_NOT_INITIALIZED
				/// and This indicates that the CUDA driver has not been initialized with cuInit()
				/// or that initialization has failed.
				/// </summary>
				int deviceCount = 0;
				if (cudaGetDeviceCount(&deviceCount) == cudaSuccess) {
					printf("Number of cuda devices in pc is: %d\n", deviceCount);
					for (int DeviceID = 0; DeviceID < deviceCount; DeviceID++) {
						char deviceName[256];
						if (cudaDeviceGetName(deviceName, 256, DeviceID) == cudaSuccess) {
							printf("Device Name: %s\n", deviceName);
						}
				    	}
				}
				else {
					printf("Cannot retrieve Cuda Devices");
				}
			}
		}
		if (nvcudaLibrary) {
			FreeLibrary(nvcudaLibrary);
		}
	}
	return std::getchar();
}
