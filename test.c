#include <stdio.h>
#include "common.h"
#include "partial/partial.h"

char endianness = IS_LITTLE_ENDIAN;

void callback(ZipInfo* info, CDFile* file, size_t progress) {
	int percentDone = progress * 100/file->compressedSize;
	printf("Getting: %d%%\n", percentDone);
}

int main(int argc, char* argv[]) {
	ZipInfo* info = PartialZipInit("http://appldnld.apple.com/iPhone4/041-3417.20111215.Slnt4/iPhone4,1_5.0.1_9A406_Restore.ipsw"); // iPhone 4s 5.0.1 ipsw
	if(!info)
	{
		printf("Cannot find file.\n");
		return 0;
	}
    
	PartialZipSetProgressCallback(info, callback);
    
	CDFile* file = PartialZipFindFile(info, "Firmware/all_flash/all_flash.n94ap.production/manifest"); // Just a list of files
	if(!file)
	{
		printf("Cannot show info of file.\n");
		return 0;
	}
    
	unsigned char* data = PartialZipGetFile(info, file);
	int dataLen = file->size; 
    
	PartialZipRelease(info);
    
	data = realloc(data, dataLen + 1);
	data[dataLen] = '\0';
	
	printf("%s\n", data);
    
	free(data);
    
	return 0;
}
