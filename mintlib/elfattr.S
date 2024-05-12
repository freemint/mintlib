#ifdef __ELF__
	.section .note.GNU-stack,"",@progbits
#ifdef __MSHORT__
#ifdef __FASTCALL__
	.gnu_attribute 8,7
#else
	.gnu_attribute 8,3
#endif
#else
#ifdef __FASTCALL__
	.gnu_attribute 8,5
#else
	.gnu_attribute 8,1
#endif
#endif
#endif
