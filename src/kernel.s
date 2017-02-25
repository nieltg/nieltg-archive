; kernel.asm
; Michael Black, 2007
; Modified by @nieltg

; kernel.asm contains assembly functions that you can use in your kernel

; void putInMemory (int segment, int address, char character)

export _putInMemory
_putInMemory:
	push    bp
	mov     bp, sp
	push    ds
	mov     ax, [bp + 4]
	mov     si, [bp + 6]
	mov     cl, [bp + 8]
	mov     ds, ax
	mov     [si], cl
	pop     ds
	pop     bp
	ret

; void  outb (uint16_t port, uint8_t value)

export _outb
_outb:
	push    bp
	mov     bp, sp
	mov     dx, [bp + 4]
	mov     ax, [bp + 6]
	out     dx, al
	pop     bp
	ret

; char  inb (uint16_t port)

export _inb
_inb:
	push    bp
	mov     bp, sp
	mov     dx, [bp + 4]
	xor     ah, ah
	in      al, dx
	pop     bp
	ret
