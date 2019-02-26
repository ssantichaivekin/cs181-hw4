Part 1.

Assuming that the return address and the frame pointer each takes 8 bytes.
Then, if we add the print lines to the code,
then we will have to more pointer addresses per function, which means the difference in the size of
the stack frame is [32 = 0x20]. However, this is not reflected in out execution. The size of each stack frame 
turns out to be 0x30 for some unknown reason. The results printed from the stack_trace() and the main/recursive
matches. May the return address and the frame pointer each takes 0x10 = 16 bytes.

After talking to grutors and thinking about this carefully, I notice that the two arguments should also
be saved in the stack. Because the chucksize will fo to 8 bytes, this will take 0x10 memory.
This is the parts we are missing.

Part 2.

We see that each frame size is 0x20 confirming the suggestion that the frame pointer and
the return address each occupies 0x10 memory. We see that there are 7 things listed, which would make sense
since the displayed items are [recursive: num=0, recursive: num=1, : num=2, : num=3, : num=4, : num=5, main].
Note that the details we for recursion(5). If we change that to recusrion(8), we will have 10 items.
