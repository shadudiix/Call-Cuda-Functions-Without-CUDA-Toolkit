#include <windows.h>
#include <cstdio>
#define cudaSuccess 0
typedef int(__stdcall* cuDriverGetVersion)(int* driverVersion);
int main() {
	int version = 0;
	HMODULE nvcudaLibrary = LoadLibraryA("nvcuda.dll");
	if (nvcudaLibrary != NULL) {
		cuDriverGetVersion cudaDriverGetVersion = (cuDriverGetVersion)GetProcAddress(nvcudaLibrary, "cuDriverGetVersion");
		if (cudaDriverGetVersion != NULL) {
			if (cudaDriverGetVersion(&version) == cudaSuccess) {
				printf("Cuda version of card is: %d", version);
			}
			else {
				printf("Cannot retrieve Cuda version");
			}
		}
		if (nvcudaLibrary) {
			FreeLibrary(nvcudaLibrary);
		}
	}
	return std::getchar();
}
