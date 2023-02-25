/*
 * keep in sync with sys/ucontext.h;
 * this is currently not generated
 */
#define oLINK       4                  /* offsetof (ucontext_t, uc_link) */
#define oSS_SP      12                 /* offsetof (ucontext_t, uc_stack.ss_sp) */
#define oSS_SIZE    20                 /* offsetof (ucontext_t, uc_stack.ss_size) */
#define oGREGS      28                 /* offsetof (ucontext_t, uc_mcontext.gregs) */
#define oSP         (oGREGS+15*4)      /* offsetof (ucontext_t, uc_mcontext.gregs[R_SP]) */
#define oPC         (oGREGS+16*4)      /* offsetof (ucontext_t, uc_mcontext.gregs[R_PC]) */
#define oFPREGS     (oGREGS+18*4)      /* offsetof (ucontext_t, uc_mcontext.mcontext.fpregs) */
#ifdef __mcoldfire__
#define oFP2        (oFPREGS+3*4+8*2)  /* offsetof (ucontext_t, uc_mcontext.mcontext.fpregs.f_fpregs[2]) */
#else
#define oFP2        (oFPREGS+3*4+12*2) /* offsetof (ucontext_t, uc_mcontext.mcontext.fpregs.f_fpregs[2]) */
#endif
#define oSIGMASK    8                  /* offsetof (ucontext_t, uc_sigmask) */
