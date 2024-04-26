#!/usr/bin/env python3
import sys
import bcc
import traceback


source = r'''
int hello(void *ctx) {
    bpf_trace_printk("Hello World!");
    return 0;
}
'''

try:
    program = bcc.BPF(text=source)
    syscall = program.get_syscall_fnname("execve")
    program.attach_kprobe(event=syscall, fn_name="hello")
    program.trace_print()

except Exception:
    traceback.print_exc()
    sys.exit(1)
