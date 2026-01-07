	.file	"genpass.c"
	.text
	.globl	init_random
	.type	init_random, @function
init_random:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %edi
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	init_random, .-init_random
	.globl	generate_random
	.type	generate_random, @function
generate_random:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	call	rand@PLT
	movl	-8(%rbp), %edx
	subl	-4(%rbp), %edx
	leal	1(%rdx), %esi
	cltd
	idivl	%esi
	movl	%edx, %ecx
	movl	%ecx, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	generate_random, .-generate_random
	.section	.rodata
	.align 8
.LC0:
	.string	"Error: At least one character type must be selected.\n"
	.text
	.globl	generate_password
	.type	generate_password, @function
generate_password:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$192, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edi, -180(%rbp)
	movl	%ecx, %eax
	movl	%r8d, %edi
	movl	%esi, %ecx
	movb	%cl, -184(%rbp)
	movb	%dl, -188(%rbp)
	movb	%al, -192(%rbp)
	movl	%edi, %eax
	movb	%al, -196(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	%rsp, %rax
	movq	%rax, %r12
	movabsq	$7523094288207667809, %rax
	movabsq	$8101815670912281193, %rdx
	movq	%rax, -128(%rbp)
	movq	%rdx, -120(%rbp)
	movabsq	$8318836189426511212, %rax
	movabsq	$34473505465988468, %rdx
	movq	%rax, -117(%rbp)
	movq	%rdx, -109(%rbp)
	movabsq	$5208208757389214273, %rax
	movabsq	$5786930140093827657, %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movabsq	$6003950658608057676, %rax
	movabsq	$25430983861228884, %rdx
	movq	%rax, -85(%rbp)
	movq	%rdx, -77(%rbp)
	movabsq	$3978425819141910832, %rax
	movq	%rax, -139(%rbp)
	movl	$3749943, -132(%rbp)
	movabsq	$3037218512321069089, %rax
	movabsq	$6727018010997762344, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movabsq	$8970461673683631455, %rax
	movabsq	$17801351726381627, %rdx
	movq	%rax, -53(%rbp)
	movq	%rdx, -45(%rbp)
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	addq	%rax, %rbx
	leaq	-139(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	addq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	addq	%rbx, %rax
	addq	$1, %rax
	movq	%rax, %rdx
	subq	$1, %rdx
	movq	%rdx, -168(%rbp)
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %ecx
	movl	$0, %edx
	divq	%rcx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -160(%rbp)
	cmpb	$0, -188(%rbp)
	je	.L5
	leaq	-128(%rbp), %rdx
	movq	-160(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
.L5:
	cmpb	$0, -184(%rbp)
	je	.L6
	leaq	-96(%rbp), %rdx
	movq	-160(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
.L6:
	cmpb	$0, -192(%rbp)
	je	.L7
	leaq	-139(%rbp), %rdx
	movq	-160(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
.L7:
	cmpb	$0, -196(%rbp)
	je	.L8
	leaq	-64(%rbp), %rdx
	movq	-160(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
.L8:
	movq	-160(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L9
	movq	stderr(%rip), %rax
	leaq	.LC0(%rip), %rdi
	movq	%rax, %rcx
	movl	$53, %edx
	movl	$1, %esi
	call	fwrite@PLT
	movl	$1, %edi
	call	exit@PLT
.L9:
	call	init_random
	movl	$0, -176(%rbp)
	jmp	.L10
.L11:
	movq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	subl	$1, %eax
	movl	%eax, %esi
	movl	$0, %edi
	call	generate_random
	movl	%eax, -172(%rbp)
	movl	-176(%rbp), %eax
	movslq	%eax, %rdx
	movq	-152(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	-160(%rbp), %rdx
	movl	-172(%rbp), %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	movb	%al, (%rcx)
	addl	$1, -176(%rbp)
.L10:
	movl	-176(%rbp), %eax
	cmpl	-180(%rbp), %eax
	jl	.L11
	movl	-180(%rbp), %eax
	movslq	%eax, %rdx
	movq	-152(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-152(%rbp), %rax
	movq	%r12, %rsp
	movq	-24(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L13
	call	__stack_chk_fail@PLT
.L13:
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	generate_password, .-generate_password
	.section	.rodata
	.align 8
.LC1:
	.string	"Password length must be a positive integer.\n"
.LC2:
	.string	"Generated Password: %s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$12, -12(%rbp)
	cmpl	$0, -12(%rbp)
	jg	.L15
	movq	stderr(%rip), %rax
	leaq	.LC1(%rip), %rdi
	movq	%rax, %rcx
	movl	$44, %edx
	movl	$1, %esi
	call	fwrite@PLT
	movl	$1, %eax
	jmp	.L16
.L15:
	movl	-12(%rbp), %eax
	movl	$1, %r8d
	movl	$1, %ecx
	movl	$1, %edx
	movl	$1, %esi
	movl	%eax, %edi
	call	generate_password
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leaq	.LC2(%rip), %rdx
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20250813"
	.section	.note.GNU-stack,"",@progbits
