#include "ModLoader.h"
#include <windows.h>


/**
 * Proxy Forwarding Configuration
 *
 * We are intercepting zlib1.dll. The original zlib1.dll should be renamed to
 * zlib0.dll. All functions below are exported and forwarded to the renamed
 * original DLL.
 *
 * Export list verified against zlib1.dll (2010-10-02, 65 functions).
 */

// Checksum
#pragma comment(linker, "/export:adler32=zlib0.adler32")
#pragma comment(linker, "/export:adler32_combine=zlib0.adler32_combine")
#pragma comment(linker, "/export:crc32=zlib0.crc32")
#pragma comment(linker, "/export:crc32_combine=zlib0.crc32_combine")
#pragma comment(linker, "/export:get_crc_table=zlib0.get_crc_table")

// Compression
#pragma comment(linker, "/export:compress=zlib0.compress")
#pragma comment(linker, "/export:compress2=zlib0.compress2")
#pragma comment(linker, "/export:compressBound=zlib0.compressBound")
#pragma comment(linker, "/export:uncompress=zlib0.uncompress")

// Deflate
#pragma comment(linker, "/export:deflate=zlib0.deflate")
#pragma comment(linker, "/export:deflateBound=zlib0.deflateBound")
#pragma comment(linker, "/export:deflateCopy=zlib0.deflateCopy")
#pragma comment(linker, "/export:deflateEnd=zlib0.deflateEnd")
#pragma comment(linker, "/export:deflateInit2_=zlib0.deflateInit2_")
#pragma comment(linker, "/export:deflateInit_=zlib0.deflateInit_")
#pragma comment(linker, "/export:deflateParams=zlib0.deflateParams")
#pragma comment(linker, "/export:deflatePrime=zlib0.deflatePrime")
#pragma comment(linker, "/export:deflateReset=zlib0.deflateReset")
#pragma comment(linker, "/export:deflateSetDictionary=zlib0.deflateSetDictionary")
#pragma comment(linker, "/export:deflateSetHeader=zlib0.deflateSetHeader")
#pragma comment(linker, "/export:deflateTune=zlib0.deflateTune")

// Inflate
#pragma comment(linker, "/export:inflate=zlib0.inflate")
#pragma comment(linker, "/export:inflateBack=zlib0.inflateBack")
#pragma comment(linker, "/export:inflateBackEnd=zlib0.inflateBackEnd")
#pragma comment(linker, "/export:inflateBackInit_=zlib0.inflateBackInit_")
#pragma comment(linker, "/export:inflateCopy=zlib0.inflateCopy")
#pragma comment(linker, "/export:inflateEnd=zlib0.inflateEnd")
#pragma comment(linker, "/export:inflateGetHeader=zlib0.inflateGetHeader")
#pragma comment(linker, "/export:inflateInit2_=zlib0.inflateInit2_")
#pragma comment(linker, "/export:inflateInit_=zlib0.inflateInit_")
#pragma comment(linker, "/export:inflateMark=zlib0.inflateMark")
#pragma comment(linker, "/export:inflatePrime=zlib0.inflatePrime")
#pragma comment(linker, "/export:inflateReset=zlib0.inflateReset")
#pragma comment(linker, "/export:inflateReset2=zlib0.inflateReset2")
#pragma comment(linker, "/export:inflateSetDictionary=zlib0.inflateSetDictionary")
#pragma comment(linker, "/export:inflateSync=zlib0.inflateSync")
#pragma comment(linker, "/export:inflateSyncPoint=zlib0.inflateSyncPoint")
#pragma comment(linker, "/export:inflateUndermine=zlib0.inflateUndermine")

// GZip file access
#pragma comment(linker, "/export:gzbuffer=zlib0.gzbuffer")
#pragma comment(linker, "/export:gzclearerr=zlib0.gzclearerr")
#pragma comment(linker, "/export:gzclose=zlib0.gzclose")
#pragma comment(linker, "/export:gzclose_r=zlib0.gzclose_r")
#pragma comment(linker, "/export:gzclose_w=zlib0.gzclose_w")
#pragma comment(linker, "/export:gzdirect=zlib0.gzdirect")
#pragma comment(linker, "/export:gzdopen=zlib0.gzdopen")
#pragma comment(linker, "/export:gzeof=zlib0.gzeof")
#pragma comment(linker, "/export:gzerror=zlib0.gzerror")
#pragma comment(linker, "/export:gzflush=zlib0.gzflush")
#pragma comment(linker, "/export:gzgetc=zlib0.gzgetc")
#pragma comment(linker, "/export:gzgets=zlib0.gzgets")
#pragma comment(linker, "/export:gzoffset=zlib0.gzoffset")
#pragma comment(linker, "/export:gzopen=zlib0.gzopen")
#pragma comment(linker, "/export:gzprintf=zlib0.gzprintf")
#pragma comment(linker, "/export:gzputc=zlib0.gzputc")
#pragma comment(linker, "/export:gzputs=zlib0.gzputs")
#pragma comment(linker, "/export:gzread=zlib0.gzread")
#pragma comment(linker, "/export:gzrewind=zlib0.gzrewind")
#pragma comment(linker, "/export:gzseek=zlib0.gzseek")
#pragma comment(linker, "/export:gzsetparams=zlib0.gzsetparams")
#pragma comment(linker, "/export:gztell=zlib0.gztell")
#pragma comment(linker, "/export:gzungetc=zlib0.gzungetc")
#pragma comment(linker, "/export:gzwrite=zlib0.gzwrite")

// Utility
#pragma comment(linker, "/export:zError=zlib0.zError")
#pragma comment(linker, "/export:zlibCompileFlags=zlib0.zlibCompileFlags")
#pragma comment(linker, "/export:zlibVersion=zlib0.zlibVersion")

/**
 * Entry point for the modification logic.
 * Runs on a separate thread to avoid blocking the main application load.
 */
DWORD WINAPI ModThread(LPVOID lpParam) {
  ModLoader::Initialize();
  return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule);

    // Spawn a initialization thread
    HANDLE hThread = CreateThread(nullptr, 0, ModThread, nullptr, 0, nullptr);
    if (hThread) {
      CloseHandle(hThread);
    }
  }
  return TRUE;
}