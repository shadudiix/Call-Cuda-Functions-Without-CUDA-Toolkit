# Invoke Cuda Functions Via Win32 API :bulb:

Is that even possible? 

to be honest, I thought it wasn't possible because I guess the toolkit is using Inline assembly

but after analysis, I found it's using a pre-compiled library, ( i guess it's developed in C/C++ ) and have an exported functions.

Like ntdll, kernel32.. etc

So can we invoke it like NvAPI ?

let's see.

Research and analysis :mag::
=======

In the first, I wrote a very simple program and linked it to Cuda-Toolkit

it use "cudaDriverGetVersion" to get Driver cuda version Reference: [#](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART____VERSION.html)

![](https://raw.githubusercontent.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/main/Pictures/1.png)

A very simple program, and works without a problem..

and 11060 represent as 11.6 Cuda version for my graphic card in current time ( GTX 1650 )

![](https://raw.githubusercontent.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/main/Pictures/2.png)

But let's go to [ProcessHacker](https://github.com/processhacker) and see our program modules..

![](https://raw.githubusercontent.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/main/Pictures/3.png)

### NvAPI.dll, Nvcuda.dll

Nvcuda is our target, NvAPI had been explained before, and you could see it here as an example: [#](https://github.com/JeremyMain/NVAPIQuery-Windows-)

But Nvcuda, as an example, I never saw someone invoke cudaDriverGetVersion via [GetProcAddress](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress) before!

### Note

Nvcuda.dll Can be located in 2 Paths

1 - For x64 Process in: 

### %windir%\System32\nvcuda.dll

2 - For x86 Process in:

### %windir%\SysWOW64\nvcuda.dll

And every device uses Nvidia graphics card..

Nvcuda.dll is installed in System32 and SysWOW64 (for x64 Architecture), so no need to link to Cuda Toolkit :wink:

So let's analyze it in CFF Explorer to find the exported functions 

![](https://raw.githubusercontent.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/main/Pictures/4.png)

We found ( cuDriverGetVersion ), could we invoke it via [LoadLibrary](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya) and [GetProcAddress](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress) ? 

We'll do that in the next section.

# Examples of functions :gear:: 

#### cudaDriverGetVersion: 

So after we found our function, I wrote a procedure for cudaDriverGetVersion to invoke it in Runtime, 

I just load the library via LoadLibrary ( Nvcuda.dll ) and Get the address of the function via GetProcAddress, Very Simple!

![](https://raw.githubusercontent.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/main/Pictures/5.png)

It's worked without a problem, and show the same result when I linked Cuda Toolkit..

![](https://raw.githubusercontent.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/main/Pictures/6.png)

### Source could be found [Here](https://github.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/blob/main/cudaDriverGetVersion.cpp)

#### cuInit, cudaGetDeviceCount and cuDeviceGetName:

Again, I wrote procedures for what I need, 3 functions, and every one of them I found in CFF Explorer

![](https://raw.githubusercontent.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/main/Pictures/7.png)

Worked Again, without a problem.. Have Fun. :yum:	

![](https://raw.githubusercontent.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/main/Pictures/8.png)

### Source could be found [Here](https://github.com/shadyelmaadawy/Invoke-Cuda-Functions-Via-Win32-API/blob/main/GetDeviceName.cpp)

# Credits
### Copyright (©) 2022, Shady K. Maadawy, All rights reserved.
  [@shadudiix](https://github.com/shadyelmaadawy)
