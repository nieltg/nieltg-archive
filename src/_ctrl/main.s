! main.asm by @nieltg

export _main
_main:
	call _kernel_main
	cli
	hlt
.loop:
	jmp .loop
