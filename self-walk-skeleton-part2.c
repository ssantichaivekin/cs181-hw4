#include <stdio.h>
#include <signal.h>

int recursive(int val, void* main_fp);
void stack_trace(void* last_fp);

int main(int argc, char *argv[])
{
    void* main_fp = __builtin_frame_address(0);
    recursive(8, main_fp);
    return 0;
}

// This function reads four bytes from (offset * 4) bytes
// away from "where".  As an example, if "where" points
// to address 0x100 and "offset" is 2, then this function
// will return the four bytes starting at address 0x108.
//
// Both positive and negative offsets are allowed.  No 
// alignment restrictions are enforced, so on most systems
// this function will crash if "where" is not
// aligned to a four-byte boundary.
unsigned int four_bytes_nearby(void *where, int offset)
{
	return *((unsigned int *)where + offset);
}

// On x64, this returns the 8-byte return address given
// a valid stack frame pointer.  The return address is always
// the 8 bytes immediately above (higher address) the frame
// pointer.
long long return_addr_from_frame(void *frame_pointer)
{
	return *((long long *)frame_pointer + 1);
}

// On x64, given a valid frame pointer, return the frame pointer
// of the calling function (i.e. traverse one step up the stack).
// This function makes no attempt to validate that either the
// current or the calling frame pointer are valid.
void *prior_frame(void *frame_pointer)
{
	return (void *)*((long long *)frame_pointer);
}

void stack_trace(void* last_fp)
{
    // 
    // x86_64
    //   %rbp is the frame pointer
    //   Don't forget to build with -fno-omit-frame-pointer!
    void* fp = __builtin_frame_address(1);
    void* rp = __builtin_return_address(1);
    // don't observe this function, rather, observe the one that calls it
    while(last_fp != fp) {
        printf("=== stack trace via function ===\n");
        printf("Frame Address (FP) is currently: %10llx\n", (long long)fp);
        printf("Return Address (RP) is currently: %10llx\n", (long long)rp);

        fp = prior_frame(fp);
        rp = (void*)return_addr_from_frame(fp);
    }
    printf("=== stack trace via function ===\n");
    printf("Frame Address (FP) is currently: %10llx\n", (long long)fp);
    printf("Return Address (RP) is currently: %10llx\n", (long long)rp);
    return;
}


int recursive(int num, void* main_fp)
{
    if (num == 0) {
        stack_trace(main_fp);
	return 0;
    }
	
    return 1 + recursive(num - 1, main_fp);
}
